/*
 * =====================================================================================
 *
 *       Filename:  signals.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/03/2023 06:56:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include <pxp.h>
//#include "common/logger.h"

static struct sigaction sa;
static struct sigaction sa_pipe;
int quitflag = 0;

void signal_handler(int s)
{
	printf("Got signal %i\n", s);
	if (!quitflag) {
		quitflag = 1;	
	//camera_exit();
	//} else {
	//exit(1);	

	}
}

void signal_pipe_handler(int s)
{
	printf("Got signal %i\n", s);

	fclose(stdout);
}


int  signal_quitflag() {
	return quitflag;
}
void set_signal_handlers()
{
	memset(&sa, 0x00, sizeof(struct sigaction));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);

//	sa_pipe.sa_handler = signal_pipe_handler;
//	sigemptyset(&sa_pipe.sa_mask);

	sa_pipe.sa_flags = 0;	
 	sigaction(SIGPIPE, &(struct sigaction){signal_pipe_handler}, NULL);

//	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction ( SIGTERM,&sa,NULL)==-1 ||   sigaction ( SIGPIPE,&sa_pipe,NULL)==-1  ) {
		//	dzlog_fatal("Could not register SIGINT -- quitting");
	//	log4phantom_print(LOG_ERR,"fatal: Could not register SIGINT -- quitting\n");
		exit(1);
	}
	 quitflag = 0;
	
}
