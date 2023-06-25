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
#if 0 	
		void start() {
			// send command to start 
			Simple::StatTransmitting statTransmitting;
			auto msg = statTransmitting();
			int n = m_uart->Send(msg->buffer,msg->size()); 
		}

		void stop() {
			Simple::StopTransmitting stopTransmitting;
			auto msg = stopTransmitting();
			int n = m_uart->Send(msg->buffer,msg->size()); 
		}

		void setSlotSize(char signal, char dark) {
			Simple::AdpdSetSlotSize RobotSetSlotSize;
			auto msg = RobotSetSlotSize(signal ,dark);
			int n = m_uart->Send(msg->buffer,msg->size()); 	
		}

		
		void timeSlotConfigData(char time_slot, char led_id,char pd_id_for_chan_1,char pd_id_for_chan_2  ) {
			Simple::AdpdTimeSlotConfig RobotTimeSlotConfig;
			auto msg = RobotTimeSlotConfig(time_slot, led_id, pd_id_for_chan_1, pd_id_for_chan_2);
			int n = m_uart->Send(msg->buffer,msg->size()); 	
		}

		void setScanMode(char mode) {
			Simple::AdpdSetScanMode RobotSetScanMode;
			auto msg = RobotSetScanMode(mode);
			int n = m_uart->Send(msg->buffer,msg->size()); 	

		}

		void setNumberOfPulses(char num_int, char num_repeat) {
			Simple::AdpdSetNumberOfPulses RobotSetNumberOfPulses;
			auto msg = RobotSetNumberOfPulses(num_int, num_repeat);
			int n = m_uart->Send(msg->buffer,msg->size()); 	

		}

		
		void setLedWidth(char led_width_in_microseconds) {
			Simple::AdpdSetLedWidth RobotSetLedWidth;
			auto msg = RobotSetLedWidth(led_width_in_microseconds);
			int n = m_uart->Send(msg->buffer,msg->size()); 	

		}


		void getConfigData(char config_id) {
			Simple::GetConfig getConfig;

			auto msg = getConfig(config_id);
			int n = m_uart->Send(msg->buffer,msg->size()); 	
		}

		

		auto & configData() {
			return m_ConfigParamData;
		}

		void configData(Simple::ResponseData::ConfigParamData & ConfigParamData) {
			m_ConfigParamData = ConfigParamData;
		}

		

		auto  & deviceInfo() {
			return m_DeviceInfoData;
		}

		void deviceInfo(Simple::ResponseData::DeviceInfoData & DeviceInfoData) {
			m_DeviceInfoData = DeviceInfoData; 
		}

		
			bool scan(std::shared_ptr<Data::Scan> scan, std::shared_ptr<StreamData> streamData) {
			scan->setReadyToSend(false);									
			start();
			int i = scan->size();
			auto start = std::chrono::system_clock::now();

			while (i) {
				// take next sample and push it to buffer
				auto data = streamData->popData();
				if (data.v != InvalidValue) {
					std::cout<<i<<"   "<<data.sysTick<<"  "<<data.v<<std::endl;;
					scan->pushData(data.v);
					i--;
					start = std::chrono::system_clock::now();
				} else{
					auto end = std::chrono::system_clock::now();
					std::chrono::duration<double> diff = end - start;
					if (diff.count() > 0.5) {
						logger_print(LOG_ERR,"ADPD data receving Error");
						return false;
					}
				}
			}
			stop();
			return true;
		}

			
#endif
		void getDeviceInfo() {
			struct GetDeviceInfo deviceInfo;
			
			auto msg = deviceInfo();
			int n = m_uart->Send(msg->buffer,msg->size()); 
			(void)n;
		}

	

	private:
		std::shared_ptr<Hal::IUart> m_uart;
//		Simple::ResponseData::ConfigParamData m_ConfigParamData;
//		Simple::ResponseData::DeviceInfoData m_DeviceInfoData;



};
#endif
