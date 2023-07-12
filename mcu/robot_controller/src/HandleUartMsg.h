/*
 * =====================================================================================
 *
 *       Filename:  protocol.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/11/2022 03:14:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H 
#include <string>
#include <memory>
#include <vector>

#include <cstring>
#include <type_traits>
#include <utility>

#include "IProtocolParser.h"

#include "protocol-v1/ProtoclDataStructures.h"
#include "protocol-v1/SensorDataParser.h"
#include "protocol-v1/messages.h"
#include "protocol-v1/IHandleUartMsg.h"
#include "common/logger.h"

#include "motor.h"
namespace Simple {

	class HandleUartMsg: public IHandleUartMsg {
		public:
			HandleUartMsg(std::shared_ptr<Hal::IUart> uart, Motor *motor) : m_uart(uart) {
				m_motor = motor;
			}
			void NewData(const MsgToParse &msg) override {
				switch (msg.cmd) {

					case CmdId::GetDeviceInfo:
						{

							DeviceInfo deviceInfo;
							auto msg = deviceInfo();
							///msg->data.hw_version [0] = 1;
							int n = m_uart->Send(msg->buffer,msg->size()); 
							(void)n;

							break;
						}
					case CmdId::SetMotorAngle:
						{
							// send response
							Ack ack;
							auto res_msg = ack();
							int n = m_uart->Send(res_msg->buffer,res_msg->size()); 
							(void)n;
							
							Payload::ServoParams *di = (Payload::ServoParams*)(msg.data.buffer);	
							m_motor->pushMessage(*di);
							break;

						}

				}

			};
			void Wrongdata() override {
			};
		private:
			std::shared_ptr<Hal::IUart> m_uart;			
			Motor * m_motor;


	};





}



#endif
