/*
 * =====================================================================================
 *
 *       Filename:  model.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/08/2023 02:15:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include "model.h"

#include <stddef.h>
#include "Python.h"

//https://dev.to/dandyvica/how-to-call-rust-functions-from-c-on-linux-h37
//struct tech_indicator * model_new(int period,int *instrument,int n_inst) ;

void * getModelType() ;
//struct PyTickData * get_tickdata(PyObject *v) ;



static PyMemberDef Model_members[] = {
	//	{"value", T_OBJECT_EX, offsetof(Model, value), 0, "model value"},	
	{NULL}  /* Sentinel */

};






/**
 * Created  06/08/2023
 * @brief   returns a jpoint chanin info  info. TBD: node name instead of point to endeffector
 * @param   
 * @return  
 */
	static PyObject *
Model_get(Model* self,PyObject *args, PyObject *kwds)
{
	struct vec3_list *list,*next;

	if (!self->model)
		Py_RETURN_NONE;

	list = forward_kinetic_for_chain (self->model->endeffector, self->model->base_link);
	PyObject* PyList = PyList_New(0);
	while (list) {

		PyObject *joint = PyDict_New();
		if(!joint) 
			return 0;


		PyObject* pyValue = PyUnicode_FromString(list->joint->name);
		PyDict_SetItemString(joint, "name", pyValue);


		/* add axis values into a list */
		PyObject* PyListRpy = PyList_New(0);
		if (!PyListRpy)
			Py_RETURN_NONE;
		PyList_Append (PyListRpy,  Py_BuildValue("d", list->joint->rpy.x ));
		PyList_Append (PyListRpy,  Py_BuildValue("d", list->joint->rpy.y ));
		PyList_Append (PyListRpy,  Py_BuildValue("d", list->joint->rpy.z ));
		PyDict_SetItemString(joint, "rpy", PyListRpy);


		/* add axis values into a list */
		PyObject* PyOrigin = PyList_New(0);
		if (!PyOrigin)
			Py_RETURN_NONE;
		PyList_Append (PyOrigin,  Py_BuildValue("d", list->joint->origin.x ));
		PyList_Append (PyOrigin,  Py_BuildValue("d", list->joint->origin.y ));
		PyList_Append (PyOrigin,  Py_BuildValue("d", list->joint->origin.z ));
		PyDict_SetItemString(joint, "origin", PyOrigin);


		// add axis values into a list
		PyObject* PyListAxis = PyList_New(0);
		if (!PyListAxis)
			Py_RETURN_NONE;
		if (parameter_is_constant(&list->joint->axis.x ))
			PyList_Append (PyListAxis,  Py_BuildValue("d", parameter_get(&list->joint->axis.x) ));
		else
			PyList_Append (PyListAxis,  Py_BuildValue("s", "Rx" ));

		if (parameter_is_constant(&list->joint->axis.y ))
			PyList_Append (PyListAxis,  Py_BuildValue("d", parameter_get(&list->joint->axis.y) ));
		else
			PyList_Append (PyListAxis,  Py_BuildValue("s", "Ry" ));


		if (parameter_is_constant(&list->joint->axis.z ))
			PyList_Append (PyListAxis,  Py_BuildValue("d", parameter_get(&list->joint->axis.z) ));
		else
			PyList_Append (PyListAxis,  Py_BuildValue("s", "Rz" ));





		PyDict_SetItemString(joint, "axis", PyListAxis);
		


		/*
		   PyDict_SetItemString(joint, "cx",  PyBool_FromLong (cos (list->joint->axis.x )));
		   PyDict_SetItemString(joint, "cy",  PyBool_FromLong (sin (list->joint->axis.y )));
		   PyDict_SetItemString(joint, "cz",  PyBool_FromLong (sin (list->joint->axis.z )));
		   PyDict_SetItemString(joint, "sx",  PyBool_FromLong (cos (list->joint->axis.x )));
		   PyDict_SetItemString(joint, "sy",  PyBool_FromLong (sin (list->joint->axis.y )));
		   PyDict_SetItemString(joint, "sz",  PyBool_FromLong (sin (list->joint->axis.z )));
		   */


		PyList_Append (PyList,  Py_BuildValue("O", joint ));

		next=list->next;
		free(list);
		list = next;
	}
	if (PyList)
		return PyList;
	Py_RETURN_NONE;
}

	static PyObject *
Model_load(Model* self,PyObject *args, PyObject *kwds)
{
	if (!self->model) 
		model_free (self->model);

	self->model = init_robot();
	Py_RETURN_TRUE;

	Py_RETURN_FALSE;
}


	static PyObject *
Model_forward_kinetic(Model* self,PyObject *args, PyObject *kwds)
{
	struct vec3_list *list,*next;

	if (!self->model)
		Py_RETURN_NONE;

	list = forward_kinetic_for_chain (self->model->endeffector, self->model->base_link);

	int k = 0;
	PyObject* PyList = PyList_New(0);
	if (!PyList)
		Py_RETURN_NONE;
	while (list) {
		PyObject* xyz = PyTuple_New(3);
		if (xyz == NULL) {
			PyErr_Print();
			Py_DECREF(PyList);
			return 1;
		}

		PyTuple_SetItem (xyz, 0, Py_BuildValue("(d)", list->p.x ));
		PyTuple_SetItem (xyz, 1, Py_BuildValue("(d)", list->p.y ));
		PyTuple_SetItem (xyz, 2, Py_BuildValue("(d)", list->p.z ));
/*
		if (PyTuple_SetItem (xyz, 0, Py_BuildValue("O", list->p.x )) != 0 
				|| PyTuple_SetItem (xyz, 1, Py_BuildValue("O", list->p.y ))!=0
				|| PyTuple_SetItem (xyz, 2, Py_BuildValue("O", list->p.z ) !=0 ) {
			PyErr_Print();
			Py_DECREF(xyz);
			Py_DECREF(list);
			return 1;
		}
		*/
		PyList_Append (PyList,  Py_BuildValue("O", xyz ));


		next=list->next;
		free(list);
		list = next;
	}


	return PyList;
}


static PyMethodDef Model_methods[] = {


	{"get", (PyCFunction)Model_get, METH_NOARGS,
		"get model value"
	},

	{"forward_kinetic", (PyCFunction)Model_forward_kinetic, METH_NOARGS,
		"forward_kinetic"
	},


	{"load", (PyCFunction)Model_load, METH_NOARGS,
		"get model value"
	},






	{NULL}  /* Sentinel */
};


	static int
Model_tp_clear(Model *self)
{
	//Py_CLEAR(self->value);
	return 0;
}

	static void
Model_tp_dealloc(Model *self)
{   
	model_free (self->model);	
	//Py_XDECREF(self->value);
	Py_TYPE(self)->tp_free((PyObject *)self);
}



	static PyObject *
Model_tp_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
	Model *self ;
	self = (Model *) type->tp_alloc(type, 0);
	return (PyObject *)self;
}

	static int
Model_tp_init(Model *self, PyObject *args, PyObject *kwargs)
{

	((Model*)self)->model = 0;
	return 1;
}

	static int
Model_tp_traverse(Model *self, visitproc visit, void *arg)
{
	//Py_VISIT(self->value);
	return 0;
}


PyObject *Model_tp_repr(PyObject *self) {

	return PyUnicode_FromString ("model");
}

PyObject *Model_tp_str(PyObject *self) {
	char *str = "model";
	return PyUnicode_FromString (str);
}


static PyTypeObject ModelType = {
	PyVarObject_HEAD_INIT(NULL, 0)
		"Model",                                  /*tp_name*/
	sizeof(Model),                                /*tp_basicsize*/
	0,                                          /*tp_itemsize*/
	(destructor)Model_tp_dealloc,                 /*tp_dealloc*/
	0,                                          /*tp_print*/
	0,                                          /*tp_getattr*/
	0,                                          /*tp_setattr*/
	0,                                          /*tp_compare*/
	Model_tp_repr,                                          /*tp_repr*/
	0,                                          /*tp_as_number*/
	0,                                          /*tp_as_sequence*/
	0,                                          /*tp_as_mapping*/
	0,                                          /*tp_hash */
	0,                                          /*tp_call*/
	Model_tp_str,                                          /*tp_str*/
	0,                                          /*tp_getattro*/
	0,                                          /*tp_setattro*/
	0,                                          /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC,		/* tp_flags          */
	0,                                          /*tp_doc*/
	(traverseproc)Model_tp_traverse,              /*tp_traverse*/
	(inquiry)Model_tp_clear,                      /*tp_clear*/
	0,                                          /*tp_richcompare*/
	0,                                          /*tp_weaklistoffset*/
	0,                                          /*tp_iter*/
	0,                                          /*tp_iternext*/
	Model_methods,                           /*tp_methods*/
	/*	Model_members,*/ 0 ,                               /*tp_members*/
	0,                                          /*tp_getsets*/
	0,                                          /*tp_base*/
	0,                                          /*tp_dict*/
	0,                                          /*tp_descr_get*/
	0,                                          /*tp_descr_set*/
	0,                                          /*tp_dictoffset*/
	(initproc)Model_tp_init,                      /*tp_init*/
	0,                                          /*tp_alloc*/
	Model_tp_new,                                 /*tp_new*/
};

void * getModelType() {
	return &ModelType;
}



inline int  Model_Check(PyObject *v) 
{
	if (v->ob_type==&ModelType)
		return 1;
	return 0;
}

