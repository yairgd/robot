/*
 * =====================================================================================
 *
 *       Filename:  messages.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/2022 07:46:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef MESSGAE_1_H
#define MESSGAE_1_H 
#include <string>
#include <memory>
#include <vector>
#include <cstring>
//#include "ProtoclDataStructures.h"


namespace Simple {
	
	template <typename MsgData>
		struct   Msg {
			unsigned char preamble;
			char cmd;
			//unsigned char length;
			MsgData data; 
			unsigned char crc;
			unsigned char postamble;

			// 6 is the total size og the meta data of the packet
			char buffer[sizeof (MsgData) + 6];

			constexpr size_t size() {
				return sizeof (buffer);
			}
			std::shared_ptr<Msg<MsgData> > Create(MsgData & msg, unsigned int  msg_counter, CmdId cmdId) {
				auto m =  std::make_shared<Msg<MsgData>>();
				m->preamble = 0xaa;
				//m->type = msgType;
				m->cmd = cmdId;
				//m->length = sizeof (msg);
				std::memcpy (&m->data, &msg, sizeof (msg));
				m->crc = 0;
				m->postamble = 0xee;

				m->Serialize();
				return m;
			}


			

			/**
			 * Created  02/20/2023
			 * @brief   Serialize command message
			 * @param   
			 * @return  return the message length
			 */
			void   Serialize() {
				int n = 0;
				crc = 0;
				buffer [n++] = preamble;
				buffer [n++] = 123;//type;
				buffer [n++] = cmd;
				buffer [n++] = sizeof (MsgData);				
				if (sizeof (MsgData)) {
					std::memcpy (&buffer[n], &data, sizeof (MsgData));
					n+=sizeof (MsgData);
				}
				buffer [n++] = 0; // empty crc to calculate later
				buffer [n++] = postamble;

				// find crc
				for (int i = 0;i < (int)size();i++) {
					auto c = static_cast<unsigned char>(buffer[i]);
					crc += c;
				}
				buffer[n-2] = crc;
			}

		};



	template <typename MsgData, CmdId cmdId>
		struct IMessageCreator {
			static unsigned int  m_msg_counter; 	

			std::shared_ptr<Msg<MsgData>>  Create(MsgData & data)  {
				Msg<MsgData>  msg;
				auto m = msg.Create(data, m_msg_counter++, cmdId );
				return m;
			}

		};


	
	template <typename MsgData,  CmdId cmdId>
		unsigned int IMessageCreator< MsgData, cmdId >::m_msg_counter = 0;


	
	/**
	 * @class DeviceInfoData1DeviceInfoRequest
	 * @brief message creator to request Device Info message 
	 */
	struct DeviceInfo:public IMessageCreator<Payload::EmptyStruct, CmdId::GetDeviceInfo> {
		public:
			std::shared_ptr<Msg<Payload::EmptyStruct>> operator() () {
				Payload::EmptyStruct  data  ;
				return IMessageCreator::Create(data); 	
			}
	};


	





		
	/**
	 * @class DeviceInfoData1
	 * @brief This message used to send the device info
	 */
	struct ServoParams:public IMessageCreator<Payload::ServoParams, CmdId::SetMotorAngle> {
		public:
			std::shared_ptr<Msg<Payload::ServoParams>> operator() (Payload::ServoParams &data) {
				return IMessageCreator::Create(data); 	
			}
	};


	/**
	 * @class creates Ack message
	 * @brief This message used to send the device info
	 */
	struct Ack:public IMessageCreator<Payload::AckNack, CmdId::AckNack> {
		public:
			std::shared_ptr<Msg<Payload::AckNack>> operator() () {
				Payload::AckNack  data = {0} ;
				data.ack_nack = 1;
				return IMessageCreator::Create(data); 	
			}
	};


	/**
	 * @class creates Not Ack message
	 * @brief This message used to send the device info
	 */
	struct NotAck:public IMessageCreator<Payload::AckNack, CmdId::AckNack> {
		public:
			std::shared_ptr<Msg<Payload::AckNack>> operator() () {
				Payload::AckNack  data = {0} ;
				data.ack_nack = 0;
				return IMessageCreator::Create(data); 	
			}
	};


}

#endif
