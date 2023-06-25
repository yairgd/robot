/*
 * =====================================================================================
 *
 *       Filename:  messages.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/2022 12:25:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef ProtoclDataStructures_h
#define ProtoclDataStructures_h 

#pragma pack(push)
#pragma pack(1)


namespace Simple {

		// this commands are received are being send to MCU
		enum  CmdId:unsigned char   {Reserved=0,
						RequestRawData=1 , 
						RobotSingleConfig,
						DeviceInfoData,
						GetDeviceInfo, 
						RobotTimeSlotConfig,
						RobotSetSlotSize, 
						RobotSetScanMode, 
						RobotSetNumberOfPulses, 
						RobotSetLedWidth,
						GetConfig
		};

		struct EmptyStruct {
			//int empty;
		};

		struct StartStopData {
			char on_off; 
		};

		struct RobotSingleConfigData {
			char id;
			char value;
		};

		struct RobotTimeslotConfigData {
			char time_slot;
			char led_id;
			char pd_id_for_chan_1;
			char pd_id_for_chan_2;	
		};

		struct RobotSetSlotSizeData {
			char signal;
			char dark;
		};

		struct RobotSetScanModeData {
			char mode; //  0 conitunes, 1 digital model
		};


		struct RobotSetNumberOfPulsesData {
			char num_int; 
			char num_repeat; 
		};


		struct RobotSetLedWidthData {
			char led_width_in_microseconds;
		};

		struct ConfigData {
			char config_id; 
		};

	
		// this data structures are commands ID are being received from MCU

		struct DeviceInfoData {
			char sw_version[3];
			char hw_version[2];
			char mcu_serial_number[8];
		};


		struct AckNack  {
			char ack_nack;
			char cmd_id;
			char payload_idx;
		};

		struct ConfigParamData  {
			char config_id;
			char config_param;
		};

		template<int n>
			struct GenericParsingData {
				unsigned char buffer[n]; 
				int size;
			};


};

#pragma pack(pop)
#endif
