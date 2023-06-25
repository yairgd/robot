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
	 * Created  11/11/2022
	 * @brief   create message to request IR data from phtodioes
	 * @param   
	 * @return  
	 */

	struct GetIRData:public IMessageCreator<EmptyStruct,CmdId::RequestRawData> {
		public:
			std::shared_ptr<Msg<EmptyStruct>> operator() () {
				EmptyStruct data;
				return IMessageCreator::Create(data); 	
			}
	};



	/**
	 * Created  02/20/2023
	 * @brief   request to start sending raw data
	 * @param   
	 * @return  
	 */
	struct StatTransmitting:public IMessageCreator<StartStopData, CmdId::RequestRawData> {
		public:
			std::shared_ptr<Msg<StartStopData>> operator() () {
				StartStopData  data ;
				data.on_off = 1;
				return IMessageCreator::Create(data); 	
			}
	};


	/**
	 * Created  02/20/2023
	 * @brief   request to stop sending raw data
	 * @param   
	 * @return  
	 */
	struct StopTransmitting:public IMessageCreator<StartStopData, CmdId::RequestRawData> {
		public:
			std::shared_ptr<Msg<StartStopData>> operator() () {
				StartStopData  data ;
				data.on_off = 0;
				return IMessageCreator::Create(data); 	
			}
	};



	
	/**
	 * Created  03/21/2023
	 * @brief   creates the RobotSingleConfigRequest command stream
	 * @param   
	 * @return  
	 */
	struct RobotSingleConfig:public IMessageCreator<RobotSingleConfigData, CmdId::RobotSingleConfig> {
		public:
			std::shared_ptr<Msg<RobotSingleConfigData>> operator() (char id, char value) {
				RobotSingleConfigData  data ;
				data.id = id;
				data.value = value;
				return IMessageCreator::Create(data); 	
			}
	};


	/**
	 * Created  03/21/2023
	 * @brief   creates the ApdpMultipleTimeSlotConfig command stream
	 * @param   
	 * @return  
	 */
	struct RobotTimeSlotConfig:public IMessageCreator<RobotTimeslotConfigData, CmdId::RobotTimeSlotConfig> {
		public:
			std::shared_ptr<Msg<RobotTimeslotConfigData>> operator() (char time_slot, char led_id , char pd_id_for_chan_1, char pd_id_for_chan_2) {
				RobotTimeslotConfigData  data ;
				data.time_slot = time_slot;
				data.led_id = led_id;
				data.pd_id_for_chan_1 = pd_id_for_chan_1;
				data.pd_id_for_chan_2 = pd_id_for_chan_2;

				return IMessageCreator::Create(data); 	
			}
	};



	
	/**
	 * Created  03/21/2023
	 * @brief   Device Info message - it gets empty data structire
	 * @param   
	 * @return  
	 */
	struct DeviceInfoRequest:public IMessageCreator<EmptyStruct, CmdId::GetDeviceInfo> {
		public:
			std::shared_ptr<Msg<EmptyStruct>> operator() () {
				EmptyStruct  data ;
				return IMessageCreator::Create(data); 	
			}
	};


	struct GetDeviceInfo:public IMessageCreator<EmptyStruct, CmdId::GetDeviceInfo> {
		public:
			std::shared_ptr<Msg<EmptyStruct>> operator() () {
				EmptyStruct  data  ;
				return IMessageCreator::Create(data); 	
			}
	};


	struct DeviceInfoData1:public IMessageCreator<struct DeviceInfoData, CmdId::DeviceInfoData> {
		public:
			std::shared_ptr<Msg<struct DeviceInfoData>> operator() () {
				struct DeviceInfoData  data = {0} ;
				data.sw_version[0] = 1;
				data.sw_version[1] = 2;
				data.sw_version[2] = 3;
				return IMessageCreator::Create(data); 	
			}
	};
	/*
	struct DeviceInfoData1:public IMessageCreator<DeviceInfoData, CmdId::DeviceInfoData> {
		public:
			std::shared_ptr<Msg<DeviceInfoData>> operator() () {
				DeviceInfoData  data ;
				data.sw_version[0] = 1;
				data.sw_version[1] = 2;
				data.sw_version[2] = 3;

				return IMessageCreator::Create(data); 	
			}
	};
*/

	


	
	/**
	 * Created  03/22/2023
	 * @brief   set slot size 
	 * @param   
	 * @return  
	 */
	struct RobotSetSlotSize:public IMessageCreator<RobotSetSlotSizeData, CmdId::RobotSetSlotSize> {
		public:
			std::shared_ptr<Msg<RobotSetSlotSizeData>> operator () (int signal, int dark)  {
				RobotSetSlotSizeData  data ;
				data.signal = signal;
				data.dark = dark;
				return IMessageCreator::Create(data); 	
			}
	};

	
	/**
	 * Created  04/17/2023
	 * @brief   set scan mode command
	 * @param   
	 * @return  
	 */
	struct RobotSetScanMode:public IMessageCreator<RobotSetScanModeData, CmdId::RobotSetScanMode> {
		public:
			std::shared_ptr<Msg<RobotSetScanModeData>> operator () (char mode)  {
				RobotSetScanModeData  data ;
				data.mode = mode;
				return IMessageCreator::Create(data); 	
			}
	};


	
	/**
	 * Created  04/17/2023
	 * @brief  set number of pulses 
	 * @param   
	 * @return  
	 */
	struct RobotSetNumberOfPulses:public IMessageCreator<RobotSetNumberOfPulsesData, CmdId::RobotSetNumberOfPulses> {
		public:
			std::shared_ptr<Msg<RobotSetNumberOfPulsesData>> operator () (char num_int, char num_repeat)  {
				RobotSetNumberOfPulsesData  data ;
				data.num_int = num_int;
				data.num_repeat = num_repeat;
				return IMessageCreator::Create(data); 	
			}
	};



	
	/**
	 * Created  04/17/2023
	 * @brief   set led width
	 * @param   
	 * @return  
	 */
	struct RobotSetLedWidth:public IMessageCreator<RobotSetLedWidthData, CmdId::RobotSetLedWidth> {
		public:
			std::shared_ptr<Msg<RobotSetLedWidthData>> operator () (char led_width_in_microseconds)  {
				RobotSetLedWidthData  data ;
				data.led_width_in_microseconds = led_width_in_microseconds;
				return IMessageCreator::Create(data); 	
			}
	};


	
	/**
	 * Created  04/17/2023
	 * @brief   get config data
	 * @param   
	 * @return  
	 */
	struct GetConfig:public IMessageCreator<ConfigData,CmdId::GetConfig> {
		public:
			std::shared_ptr<Msg<ConfigData>> operator () (char config_id)  {
				ConfigData  data ;
				data.config_id = config_id;
				return IMessageCreator::Create(data); 	
			}
	};





}

#endif
