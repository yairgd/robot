/*
 * =====================================================================================
 *
 *       Filename:  model.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/08/2023 06:08:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef TAG_INDICATOR
#define TAG_INDICATOR 

#include <Python.h>
#include <structmember.h>
#include "model.h"


/* Type definition */
typedef struct {
	PyObject_HEAD
	struct model *model;
	//PyObject *value;

} Model;


int  Model_Check(PyObject *v) ;
void * getModelType() ;

#endif
