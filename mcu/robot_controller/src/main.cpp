/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <string.h>
#include <memory>

#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/i2c.h>
#include "zephyr/uart_zephyr.h"

#include "protocol-v1/ProtocolStateMachine.h"
#include "protocol-v1/ProtoclDataStructures.h"
#include "HandleUartMsg.h"
#include "robot.h"
#include "pcb9685.h"
#include "motor.h"


/* size of stack area used by each thread */
#define STACKSIZE 8096

/* scheduling priority used by each thread */
#define PRIORITY 7



# if DT_NODE_HAS_STATUS(DT_ALIAS(a_i2c4), okay)
#	define I2C_DEV_NODE	DT_ALIAS(a_i2c4)
# else
#	error "Please set the correct I2C device"
# endif


//const struct device *const sl_uart1 ;//= DEVICE_DT_GET(UART_NODE2);
#define UART_NODE2 DT_CHOSEN(zephyr_console)
const struct device *const sl_uart2 = DEVICE_DT_GET(UART_NODE2);

//uint32_t i2c_cfg = I2C_SPEED_SET(I2C_SPEED_STANDARD) | I2C_MODE_CONTROLLER;
//const struct device *const i2c_dev = DEVICE_DT_GET(I2C_DEV_NODE);
const struct device * const i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c4));
//const struct device * i2c_dev = 
// static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);


K_MSGQ_DEFINE(sevo_msgq, sizeof(Payload::ServoParams), 16, 4);



pcb9685 * g_pwm = new pcb9685(i2c_dev);
Motor  * g_motor = new Motor(g_pwm, &sevo_msgq);


int main(void)
{
	std::cout << "begin c++ app"<<std::endl;		
	printk("Zephyr USART Example\n");

	while (1) {
		k_sleep(K_MSEC(2000));		
	}


	return 0;

}




void servo_command_listenr(void *p1,void *p2, void *p3)
{
	int e;
	Simple::Payload::ServoParams  servoParams;
	Motor * motor = * ( (Motor **) p1); 

	printk("servo_command_listenr\n");

	motor->setup();
	unsigned int c=0;
	while (1) {
		e = k_msgq_get(&sevo_msgq, &servoParams, K_FOREVER) ;
		motor->setServoPulse(0,c == 0 ? 0.0025 : 0.0005 );
		c = ~c;

		int g=3;
		g=g+1;
	}
	k_sleep(K_MSEC(2000));			
}

K_THREAD_DEFINE(servo_command_listenr_id, STACKSIZE, servo_command_listenr, &g_motor, NULL, NULL, PRIORITY, 0, 0);



void message_in_listenr(void *p1,void *p2, void *p3)
{
	Motor * motor = *( (Motor **) p1); 

	auto uart = Hal::GetUartZephyr(sl_uart2);
	uart->Open();
	auto p  =  std::shared_ptr<Simple::HandleUartMsg>(new Simple::HandleUartMsg(uart, motor) );
	std::shared_ptr<IProtocolParser> parser = std::shared_ptr<Simple::ProtocolStateMachine> ( new Simple::ProtocolStateMachine  (uart, p));


#if 0
	auto login =  [] () ->void{

	};	
	login();
#endif

	while (1) {
		parser->Parse();
	}
}

K_THREAD_DEFINE(message_in_listenr_id, STACKSIZE, message_in_listenr, &g_motor, NULL, NULL, PRIORITY, 0, 0);

