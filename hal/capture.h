/*
 * =====================================================================================
 *
 *       Filename:  capture.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/08/2023 08:54:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef CAMERA_H
#define CAMERA_H 
#ifdef __cplusplus
extern "C" {
#endif
	typedef void (*camera_callback_t)(void);
	int camera_stop();
	int camera_main();
	void camera_set_callback(camera_callback_t cb);
	void camera_capture_frame(char *buffer);
	void camera_suspend_thread();
	void camera_resume_thread();	
	const char  * camera_get_frame() ;
	void camera_exit() ;	
#ifdef __cplusplus
}
#endif

#endif
