#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "Python.h"
#include "eca.h"
#include "numpy/arrayobject.h"

static PyObject *
FastECA_ktr(PyObject *self, PyObject* args) {
  int64_t delta;
  PyObject *arg;
  PyArrayObject *input_arr, *output_arr;

  if (!PyArg_ParseTuple(args, "OL", &arg, &delta))
    return NULL;
  input_arr = (PyArrayObject *) PyArray_ContiguousFromObject(arg, NPY_INT64, 2, 2);
  if (!input_arr)
    return NULL;

  if (!eca_assert_01((int64_t *) PyArray_DATA(input_arr), PyArray_DIM(input_arr, 0), PyArray_DIM(input_arr, 1))) {
    PyErr_SetString(PyExc_ValueError, "input matrix must contain 0/1 only");
    Py_DECREF(input_arr);
    return NULL;
  };

  int64_t dims[2] = {PyArray_DIM(input_arr, 0), PyArray_DIM(input_arr, 0)};
  output_arr = (PyArrayObject *) PyArray_SimpleNew(2, dims, NPY_INT64);
  if (!output_arr) {
      Py_DECREF(input_arr);
      return NULL;
  }

  if (!PyArray_ISCONTIGUOUS(output_arr)) {
    PyErr_SetString(PyExc_MemoryError, "memory not contiguous");
    Py_DECREF(input_arr);
    Py_DECREF(output_arr);
    return NULL;
  }

  if (!eca_ktr((int64_t *) PyArray_DATA(input_arr), PyArray_DIM(input_arr, 0),
      PyArray_DIM(input_arr, 1), delta, (int64_t *) PyArray_DATA(output_arr))) {
    PyErr_SetString(PyExc_MemoryError, "cannot allocate memory for indicator matrix");
    Py_DECREF(input_arr);
    Py_DECREF(output_arr);
    return NULL;
  }

  Py_DECREF(input_arr);
  return PyArray_Return(output_arr);
}

static PyObject *
FastECA_kpr(PyObject *self, PyObject* args) {
  int64_t delta;
  PyObject *arg;
  PyArrayObject *input_arr, *output_arr;

  if (!PyArg_ParseTuple(args, "OL", &arg, &delta))
    return NULL;
  input_arr = (PyArrayObject *) PyArray_ContiguousFromObject(arg, NPY_INT64, 2, 2);
  if (!input_arr)
    return NULL;

  if (!eca_assert_01((int64_t *) PyArray_DATA(input_arr), PyArray_DIM(input_arr, 0), PyArray_DIM(input_arr, 1))) {
    PyErr_SetString(PyExc_ValueError, "input matrix must contain 0/1 only");
    Py_DECREF(input_arr);
    return NULL;
  };

  int64_t dims[2] = {PyArray_DIM(input_arr, 0), PyArray_DIM(input_arr, 0)};
  output_arr = (PyArrayObject *) PyArray_SimpleNew(2, dims, NPY_INT64);
  if (!output_arr) {
      Py_DECREF(input_arr);
      return NULL;
  }

  if (!PyArray_ISCONTIGUOUS(output_arr)) {
    PyErr_SetString(PyExc_MemoryError, "memory not contiguous");
    Py_DECREF(input_arr);
    Py_DECREF(output_arr);
    return NULL;
  }

  if (!eca_kpr((int64_t *) PyArray_DATA(input_arr), PyArray_DIM(input_arr, 0),
      PyArray_DIM(input_arr, 1), delta, (int64_t *) PyArray_DATA(output_arr))) {
    PyErr_SetString(PyExc_MemoryError, "cannot allocate memory for indicator matrix");
    Py_DECREF(input_arr);
    Py_DECREF(output_arr);
    return NULL;
  }

  Py_DECREF(input_arr);
  return PyArray_Return(output_arr);
}

static PyObject *
FastECA_rtr(PyObject *self, PyObject* args) {
  PyObject *arg;
  PyArrayObject *input_arr, *output_arr;

  if (!PyArg_ParseTuple(args, "O", &arg))
    return NULL;
  input_arr = (PyArrayObject *) PyArray_ContiguousFromObject(arg, NPY_INT64, 2, 2);
  if (!input_arr)
    return NULL;

  if (PyArray_DIM(input_arr, 0) != PyArray_DIM(input_arr, 1)) {
    PyErr_SetString(PyExc_AttributeError, "input must be a square matrix with pairwise coincidences");
    Py_DECREF(input_arr);
    return NULL;
  }

  int64_t dims[2] = {PyArray_DIM(input_arr, 0), PyArray_DIM(input_arr, 0)};
  output_arr = (PyArrayObject *) PyArray_SimpleNew(2, dims, NPY_DOUBLE);
  if (!output_arr) {
      Py_DECREF(input_arr);
      return NULL;
  }

  if (!PyArray_ISCONTIGUOUS(output_arr)) {
    PyErr_SetString(PyExc_MemoryError, "memory not contiguous");
    Py_DECREF(input_arr);
    Py_DECREF(output_arr);
    return NULL;
  }

  eca_rtr((int64_t *) PyArray_DATA(input_arr), PyArray_DIM(input_arr, 0), (double *) PyArray_DATA(output_arr));

  Py_DECREF(input_arr);
  return PyArray_Return(output_arr);
}

static PyObject *
FastECA_rpr(PyObject *self, PyObject* args) {
  PyObject *arg;
  PyArrayObject *input_arr, *output_arr;

  if (!PyArg_ParseTuple(args, "O", &arg))
    return NULL;
  input_arr = (PyArrayObject *) PyArray_ContiguousFromObject(arg, NPY_INT64, 2, 2);
  if (!input_arr)
    return NULL;

  if (PyArray_DIM(input_arr, 0) != PyArray_DIM(input_arr, 1)) {
    PyErr_SetString(PyExc_AttributeError, "input must be a square matrix with pairwise coincidences");
    Py_DECREF(input_arr);
    return NULL;
  }

  int64_t dims[2] = {PyArray_DIM(input_arr, 0), PyArray_DIM(input_arr, 0)};
  output_arr = (PyArrayObject *) PyArray_SimpleNew(2, dims, NPY_DOUBLE);
  if (!output_arr) {
      Py_DECREF(input_arr);
      return NULL;
  }

  if (!PyArray_ISCONTIGUOUS(output_arr)) {
    PyErr_SetString(PyExc_MemoryError, "memory not contiguous");
    Py_DECREF(input_arr);
    Py_DECREF(output_arr);
    return NULL;
  }

  eca_rpr((int64_t *) PyArray_DATA(input_arr), PyArray_DIM(input_arr, 0), (double *) PyArray_DATA(output_arr));

  Py_DECREF(input_arr);
  return PyArray_Return(output_arr);
}


static PyMethodDef FastECA_methods[] = {
  {"ktr", FastECA_ktr, METH_VARARGS,
   "mat = ktr(data, delta)"},
  {"kpr", FastECA_kpr, METH_VARARGS,
   "mat = kpr(data, delta)"},
  {"rtr", FastECA_rtr, METH_VARARGS,
   "mat = rtr(ktr)"},
  {"rpr", FastECA_rpr, METH_VARARGS,
   "mat = rpr(kpr)"},
  {NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef FastECA_module = {
  PyModuleDef_HEAD_INIT,
  "_eca", // name
  NULL,      // module documentation
  -1,        // size of per-interpreter state of the module
             // or -1 if the module keeps state in global variables.
  FastECA_methods
};
#endif

#if PY_MAJOR_VERSION >= 3
  #define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
  #define MOD_RETURN(val) return val
#else
  #define MOD_INIT(name) void init##name(void)
  #define MOD_RETURN(val) return
#endif

MOD_INIT(_eca) {
#if PY_MAJOR_VERSION < 3
  PyObject *m = Py_InitModule("_eca", FastECA_methods);
#else
  PyObject *m = PyModule_Create(&FastECA_module);
#endif
  if (m == NULL)
    MOD_RETURN(NULL);

  import_array(); // numpy import
  MOD_RETURN(m);
}

