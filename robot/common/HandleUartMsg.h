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
extern int gg;
namespace Simple {

	class HandleUartMsg: public IHandleUartMsg {
		public:
			HandleUartMsg(std::shared_ptr<Hal::IUart> uart) : m_uart(uart)  {};
			void NewData(const MsgToParse &msg) override {
				switch (msg.cmd) {



					case CmdId::DeviceInfoData:
						{
							static int cnt = 0;
							Payload::DeviceInfoData *di = (Payload::DeviceInfoData*)(msg.data.buffer);
							logger_print(LOG_INFO,"Get device Info Commnand : %d  sw ver: %d.%d.%d, hw_ver: %d.%d" ,cnt, di->sw_version[2],
							     di->sw_version[1],
							     di->sw_version[0],
							     di->hw_version[1],
							     di->hw_version[0]
							    );
							gg=0;
							cnt++;
							break;
						}
					case CmdId::AckNack:
						{
							logger_print(LOG_INFO,"AckNack");
						}







				}

			};
			void Wrongdata() override {
			};
		private:
			std::shared_ptr<Hal::IUart> m_uart;


	};





}



#endif
