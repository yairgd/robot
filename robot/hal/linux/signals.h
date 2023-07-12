/*
 * =====================================================================================
 *
 *       Filename:  signals.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/2023 07:04:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef SIGNALS_H
#ifdef __cplusplus
extern "C" {
#endif

	void set_signal_handlers();
	int  signal_quitflag();
#ifdef __cplusplus
}
#endif
#endif
