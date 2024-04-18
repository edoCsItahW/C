// Copyright (c) 2024. All rights reserved.
// This source code is licensed under the CC BY-NC-SA
// (Creative Commons Attribution-NonCommercial-NoDerivatives) License, By Xiao Songtao.
// This software is protected by copyright law. Reproduction, distribution, or use for commercial
// purposes is prohibited without the author's permission. If you have any questions or require
// permission, please contact the author: 2207150234@st.sziit.edu.cn

#include <pybind11/pybind11.h>

/*
PyDoc_STRVAR(py_extent_example_doc, "example(obj, number)Example function");

PyObject *py_extent_example(PyObject *self, PyObject *args, PyObject *kwargs) {

    PyObject *obj = NULL;
    int number = 0;


    static char* keywords[] = { "obj", "number", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
        return NULL;
    }


    if (number < 0) {
        PyErr_SetObject(PyExc_ValueError, obj);
        return NULL;   
    }

    Py_RETURN_NONE;
}


static PyMethodDef py_extent_functions[] = {
    { "example", (PyCFunction)py_extent_example, METH_VARARGS | METH_KEYWORDS, py_extent_example_doc },
    { NULL, NULL, 0, NULL } 
};


int exec_py_extent(PyObject *module) {
    PyModule_AddFunctions(module, py_extent_functions);

    PyModule_AddStringConstant(module, "__author__", "Lenovo");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2024);

    return 0; 
}


PyDoc_STRVAR(py_extent_doc, "The py_extent module");


static PyModuleDef_Slot py_extent_slots[] = {
    { Py_mod_exec, exec_py_extent },
    { 0, NULL }
};

static PyModuleDef py_extent_def = {
    PyModuleDef_HEAD_INIT,
    "py_extent",
    py_extent_doc,
    0,             
    NULL,       
    py_extent_slots,
    NULL,          
    NULL,     
    NULL,          
};

PyMODINIT_FUNC PyInit_py_extent() {
    return PyModuleDef_Init(&py_extent_def);
}
*/


int add(int i, int j) {
    return i + j;
}



PYBIND11_MODULE(pyExtent, m) {
    m.def("add", &add, "A function which adds two numbers");
}

