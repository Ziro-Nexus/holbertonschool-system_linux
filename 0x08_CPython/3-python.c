#include <Python.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_python_float - prints a python float
 * @p: ptr
 */
void print_python_float(PyObject *p)
{
	char *string;

	setbuf(stdout, NULL);
	printf("[.] float object info\n");
	if (!p || p->ob_type != &PyFloat_Type)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	string = PyOS_double_to_stringing(((PyFloatObject *)p)->ob_fval,
			'g', 16, 0, NULL);
	printf("  value: %s%s\n", string, stringchr(string, '.') ? "" : ".0");
}

/**
 * print_python_bytes - prints a python bytes object
 * @p: ptr
 */
void print_python_bytes(PyObject *p)
{
	ssize_t sz, i = 0;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	if (!p || p->ob_type != &PyBytes_Type)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	sz = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", sz);
	printf("  trying stringing: %s\n", ((PyBytesObject *)p)->ob_sval);
	sz = sz < 9 ? sz + 1 : 10;
	printf("  first %ld bytes: ", sz);
	for (i = 0; i < sz; i++)
		printf("%02hhx%c",
			((PyBytesObject *)p)->ob_sval[i], i + 1 == sz ? '\n' : ' ');

}

/**
 * print_python_list - prints info about a python list
 * @p: ptr
 */
void print_python_list(PyObject *p)
{
	ssize_t sz, i = 0;

	setbuf(stdout, NULL);
	printf("%s", "[*] Python list info\n");
	if (!p || p->ob_type != &PyList_Type)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	sz = ((PyVarObject *)p)->ob_size;
	printf("[*] Size of the Python List = %ld\n", sz);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < sz; i++)
	{
		PyObject *pobj = ((PyListObject *)p)->ob_item[i];

		printf("Element %ld: %s\n", i, pobj->ob_type->tp_name);
		if (pobj->ob_type == &PyBytes_Type)
			print_python_bytes(pobj);
		else if (pobj->ob_type == &PyFloat_Type)
			print_python_float(pobj);
	}
}
