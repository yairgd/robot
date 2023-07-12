/*
 * =====================================================================================
 *
 *       Filename:  motor.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/11/2023 10:58:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef MOTOR_H
#define MOTOR_H 
#include "pcb9685.h"
#include <zephyr/kernel.h>
#include "protocol-v1/ProtoclDataStructures.h"

class Motor {
	public:
		Motor(pcb9685 * pwm, k_msgq * msgq) : m_pwm(pwm) {
			m_msgq = msgq;
		}
		void setServoPulse(uint8_t n, double pulse);
		void pushMessage(Simple::Payload::ServoParams  & motorAngle) {
			k_msgq_put(m_msgq, &motorAngle, K_NO_WAIT);			
		}
		void setup();
		
	private:
		pcb9685  * m_pwm;
		k_msgq * m_msgq;
};
#endif
