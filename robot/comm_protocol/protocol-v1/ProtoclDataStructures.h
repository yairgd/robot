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
		DeviceInfoData,
		GetDeviceInfo, 
		SetMotorAngle,
		AckNack,
	};
	namespace Payload {

		struct EmptyStruct {
			//int empty;
		};

		struct StartStopData {
			char on_off; 
		};


		struct ServoParams {
			unsigned char angle[16];
			unsigned short update_bit;	
			unsigned short min_pwm;
			unsigned short max_pwm;

		};


		// this data structures are commands ID are being received from MCU

		struct DeviceInfoData {
			char sw_version[3];
			char hw_version[2];
			char mcu_serial_number[8];
		};


		struct AckNack  {
			char ack_nack;
		};

		template<int n>
			struct GenericParsingData {
				unsigned char buffer[n]; 
				int size;
			};
	}


};

#pragma pack(pop)
#endif
