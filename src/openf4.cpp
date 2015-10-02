#include <Python.h>
#include <vector>
#include <string>
#include <libopenf4.h>

static PyObject *calcurate_groebner_basis(PyObject *self, PyObject *args) {
  PyObject *vname_obj, *polynomial_obj;
  unsigned long long int modulo;
  std::vector<std::string> variableName;
  std::vector<std::string> polynomialArray;
  std::vector<std::string> basis;
  PyObject *iter_vn, *iter_pol, *ret_pollist;

  if (!PyArg_ParseTuple(args, "KOO", &modulo, &vname_obj, &polynomial_obj)) return NULL;

  // Variable Name Iteration
  iter_vn = PyObject_GetIter(vname_obj);
  if (!iter_vn) return NULL;

  while (true) {
    PyObject *next = PyIter_Next(iter_vn);
    if (!next) {
      break;
    }

    if (!PyString_Check(next)) {
      return NULL;
    }
    std::string vname = std::string(PyString_AsString(next));
    variableName.push_back(vname);
  }


  // Polynomial Iteration
  iter_pol = PyObject_GetIter(polynomial_obj);
  if (!iter_pol) return NULL;

  while (true) {
    PyObject *next = PyIter_Next(iter_pol);
    if (!next) {
      break;
    }

    if (!PyString_Check(next)) {
      return NULL;
    }
    std::string polynomial = std::string(PyString_AsString(next));
    polynomialArray.push_back(polynomial);
  }

  basis = groebnerBasisF4(modulo, variableName.size(), variableName, polynomialArray, 1, 0);


  // Construct List
  ret_pollist = PyList_New(0);

  for (std::vector<std::string>::iterator it = basis.begin(); it != basis.end(); ++it) {
    std::string v = *it;
    PyObject *str = PyString_FromString(v.c_str());
    PyList_Append(ret_pollist, str);
  }

  return ret_pollist;
}

static PyMethodDef Openf4Py_Methods [] = {
  {"calcurate_groebner_basis", calcurate_groebner_basis, METH_VARARGS, "Calcurate Groebner Basis\n\tcalcurate_groebner_basis(modulo, list_of_variable_names, list_of_polynomials)"},
  {NULL, NULL, 0, NULL}
};

extern "C" PyMODINIT_FUNC initopenf4(void)
{
    (void) Py_InitModule("openf4", Openf4Py_Methods);
}
