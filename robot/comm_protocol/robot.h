/*
 * =====================================================================================
 *
 *       Filename:  Robot.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/03/2023 10:47:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef ADPD_H
#define ADPD_H 
#include "IUart.h"
#include <memory>
#include "protocol-v1/messages.h"
#include "common/logger.h"


using namespace Simple;
/**
 * @class Robot
 * @brief collection of functions to manage the Robot device
 */
class Robot {
	public:
		Robot(std::shared_ptr<Hal::IUart> uart) {
			m_uart = uart;
		};

		void getDeviceInfo() {
			DeviceInfo deviceInfo;
			
			auto msg = deviceInfo();
			int n = m_uart->Send(msg->buffer,msg->size()); 
			(void)n;
		}

		void setServoParams(Payload::ServoParams &data) {
			ServoParams servoParams;
			auto msg = servoParams(data);
			int n = m_uart->Send(msg->buffer,msg->size()); 
			(void)n;
		}	

	private:
		std::shared_ptr<Hal::IUart> m_uart;
//		Simple::ResponseData::ConfigParamData m_ConfigParamData;
//		Simple::ResponseData::DeviceInfoData m_DeviceInfoData;



};
#endif
