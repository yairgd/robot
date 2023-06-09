/*
 * =====================================================================================
 *
 *       Filename:  algo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/19/2021 03:03:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <Python.h>
#include <structmember.h>
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include "git.h"

#include "model.h"

//np in c example
//https://stuff.mit.edu/afs/sipb/project/python/src/python-numeric-22.0/doc/www.pfdubois.com/numpy/html2/numpy-13.html
//void * getModelType() ;



	static PyObject *
hello(PyObject *self, PyObject *args)
{
	const char *name;
	if (! PyArg_ParseTuple(args,  "s;the function requires a valid led light enum value",&name)) {
		Py_RETURN_NONE;
	}

	//	char * s= PyUnicode_AsUTF8(name);
	printf("hello %s\r\n", name);
	Py_RETURN_NONE;

}


	static PyObject *
trace1(PyObject *self, PyObject *args)
{
	PyArrayObject *array;
	double sum;
	int i, n;


	if (!PyArg_ParseTuple(args, "O!",&PyArray_Type, &array))
		return NULL;

	if (array->nd != 2 || array->descr->type_num != PyArray_DOUBLE) {
		PyErr_SetString(PyExc_ValueError,
				"array must be two-dimensional and of type float");
		return NULL;
	}


	n = array->dimensions[0];
	if (n > array->dimensions[1])
		n = array->dimensions[1];
	sum = 0.;
	for (i = 0; i < n; i++)
		sum += *(double *)(array->data + i*array->strides[0] + i*array->strides[1]);
	return PyFloat_FromDouble(sum);
}

static PyObject *

trace(PyObject *self, PyObject *args)

{
	PyObject *input;
	PyArrayObject *array;
	double sum;
	int i, n;



	if (!PyArg_ParseTuple(args, "O", &input))
		return NULL;

	array = (PyArrayObject *)PyArray_ContiguousFromObject(input, PyArray_DOUBLE, 2, 2);

	if (array == NULL)
		return NULL;



	n = array->dimensions[0];
	if (n > array->dimensions[1])
		n = array->dimensions[1];

	sum = 0.;
	for (i = 0; i < n; i++)
		sum += *(double *)(array->data + i*array->strides[0] + i*array->strides[1]);

	Py_DECREF(array);
	return PyFloat_FromDouble(sum);
}

static PyMethodDef algo_methods[] = {
	{"hello", (PyCFunction)hello, METH_VARARGS,
		"displays hello"
	},

	{"trace", (PyCFunction)trace, METH_VARARGS,
		"numpy example"
	},


	{NULL, NULL, 0, NULL}
};


void register_enum(PyObject *py_module, const char *enum_name, PyObject *py_constants_dict) {
		PyObject *py_enum_class = NULL;
	{
		
		PyObject *py_enum_module = PyImport_ImportModule("enum");
		if (py_enum_module == NULL) {
			Py_CLEAR(py_constants_dict);
		}

		py_enum_class = PyObject_CallMethod(py_enum_module,
				"IntEnum", "sO", enum_name,
				py_constants_dict);

		Py_CLEAR(py_constants_dict);
		Py_CLEAR(py_enum_module);
	}

	if (py_enum_class && PyModule_AddObject(py_module, enum_name, py_enum_class) < 0) {
		Py_CLEAR(py_enum_class);
	}

}

static struct PyModuleDef robot_c =
{
	PyModuleDef_HEAD_INIT,
	"robot_c",	 /* name of module */
	"",          /* module documentation, may be NULL */
	-1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
	algo_methods
};




	PyMODINIT_FUNC
PyInit_robot_c(void)
{
	PyObject *m;

	m = PyModule_Create(&robot_c);
	
	//register of class inside the module 
	PyTypeObject *ModelType = getModelType();	
	if (PyType_Ready(ModelType) < 0)
		return NULL;
	Py_INCREF(&robot_c);
	if (PyModule_AddObject(m, "Model", (PyObject *) ModelType) < 0) {
		Py_DECREF(&robot_c);
		Py_DECREF(m);
		return NULL;
	}
	



	



	/* enum register example
	py_constants_dict = PyDict_New(); // empty for the sake 
	PyDict_SetItemString(py_constants_dict, "logistic_regression",  PyLong_FromLong(MODEL_LOGISTIC_REGRESSION) );
	PyDict_SetItemString(py_constants_dict, "huristic_rsi_ema",  PyLong_FromLong(MODEL_HURISTIC_RSI_EMA) );
	register_enum (m , "ModelType", py_constants_dict);
	*/

	// use to initilize numpyt array system
//	import_array();
	return m;



}



#if 0
	// make a tuple of your bases
	PyObject *enum_module= PyImport_AddModule("enum");
	PyObject *int_enum = PyObject_GetAttrString(enum_module, "IntEnum");
	PyObject *int_enum_c  = Py_BuildValue("(O)", int_enum);
#if 1
	PyObject* bases = PyTuple_Pack(  1, int_enum_c); // assume no bases
	// make a dictionary of member functions, etc
	PyObject* dict = PyDict_New(); // empty for the sake of example 
	PyDict_SetItemString(dict, "led1",  PyLong_FromLong(1) );
	PyDict_SetItemString(dict, "led2",  PyLong_FromLong(2) );

	PyObject* my_new_class = PyObject_CallFunction(&PyType_Type,"sOO",
			"IndicatorName", // class name
			int_enum_c,
			dict);

	PyModule_AddObject(m, "my_new_class", my_new_class);

	// check if null

	// decref bases and dict
	Py_CLEAR(bases);
	Py_CLEAR(dict);
#endif

#endif


