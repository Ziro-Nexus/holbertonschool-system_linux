#include <stdio.h>
#include <Python.h>

/**
 * print_python_list - print information about python list
 * @p: Python list object
 * Return: void
 */
void print_python_list(PyObject *p)
{
	PyListObject *allocated = (PyListObject *)p;
	Py_ssize_t size = PyList_Size(p);
	Py_ssize_t i;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lo\n", size);
	printf("[*] Allocated = %ld\n", allocated->allocated);

	for (i = 0; i < size; i++)
	{
		PyObject *tmp = PyList_GetItem(p, i);

		printf("element %lo: %s\n", i, Py_TYPE(tmp)->tp_name);
	}
}
