/*
 * =====================================================================================
 *
 *       Filename:  test1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/25/2023 01:55:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include <memory>
#include <chrono>
#include <vector>
#include <thread>
#include <memory>
#include <iostream>


#include "protocol-v1/ProtocolStateMachine.h"
#include "common/HandleUartMsg.h"

#include "common/ThreadPool.h"
#include "common/logger.h"

#include "IUart.h"
#include "robot.h"
#include "git.h"

#ifdef __GNUC__
#include "signals.h"
#endif

#define UART_DEVICE "/dev/ttyACM0"

int gg=0;
void run_the_application() {
	auto threadPool= ThreadPool::Instance();
	auto uart = Hal::GetUart(UART_DEVICE);
	uart->Open();
	if (uart->IsOpen() == false) {
		logger_print(LOG_INFO,"cannot open uart %s",UART_DEVICE );				
		return;
	}

	char m_exit = false;

	threadPool->beginTask([uart,&m_exit]()->void{
		auto p  =  std::make_shared<Simple::HandleUartMsg>(uart);
		std::shared_ptr<IProtocolParser> parser = std::make_shared<Simple::ProtocolStateMachine> (uart, p);
		std::mutex m;

		while (true) {
			if (signal_quitflag()) {
				logger_print(LOG_DEBUG,"exit from state observer thread ");				
				return;
			}

			m.lock();
			if (m_exit) {
				m.unlock();						
				return;
			}
			m.unlock();
			parser->Parse();
		}
	});

	threadPool->beginTask([uart, &m_exit]()->void{
		auto robot = std::make_shared<::Robot>(uart);		

		for (int i=0;i<0;i++) {
			gg=1;
			robot->getDeviceInfo(); // works
			while (gg);

		}
		
		// set servo location
		ServoParams servoParams;
		auto msg = servoParams();
		msg->data.angle[0] = 40;
		msg->data.update_bit = 1;
		msg->data.min_pwm = 500;
		msg->data.max_pwm = 2500;
		robot->setMotorAngle(servoParams);
		
		usleep(100000);
		m_exit = true;		
		return;

	});





	logger_print(LOG_DEBUG,"joining %ld threads at ThreadPool",threadPool->size() );


	threadPool->finish();
	threadPool->join();
}


int main(int argc, char *argv[]) {

#ifdef __GNUC__
	logger_init(0, LOG_LOCAL0);
	set_signal_handlers();
#endif
	logger_set_log_level(7);
	logger_print(LOG_DEBUG,"Begin to Run");

# if  CONFIG_SINGLE_INSTANCE
	// Open the lock file
	int fd = open("/var/run/myprogram.lock", O_CREAT | O_RDWR, 0644);
	if (fd < 0) {
		// Error opening the lock file
		return 1;
	}
	// Acquire an exclusive lock on the file
	if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
		// Lock failed, another instance is running
		return 1;
	}
#endif

	run_the_application();


#if CONFIG_SINGLE_INSTANCE
	// Release the lock and close the file
	flock(fd, LOCK_UN);
	close(fd);
#endif
	return 0;
}

