#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * print_python_bytes - prints a python bytes
 * @p: ptr
 */
void print_python_bytes(PyObject *p)
{
	ssize_t sized, i = 0;

	printf("[.] bytes object info\n");
	if (p->ob_type != &PyBytes_Type)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	sized = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", sized);
	printf("  trying string: %s\n", ((PyBytesObject *)p)->ob_sval);
	sized = sized < 9 ? sized + 1 : 10;
	printf("  first %ld bytes: ", sized);
	for (i = 0; i < sized; i++)
		printf("%02hhx%c",
			((PyBytesObject *)p)->ob_sval[i], i + 1 == sized ? '\n' : ' ');

}

/**
 * print_python_list - doc
 * @p: ptr
 */
void print_python_list(PyObject *p)
{
	ssize_t sized = ((PyVarObject *)p)->ob_size, i = 0;

	printf("%s", "[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", sized);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < sized; i++)
	{
		PyObject *pobj = ((PyListObject *)p)->ob_item[i];

		printf("Element %ld: %s\n", i, pobj->ob_type->tp_name);
		if (pobj->ob_type == &PyBytes_Type)
			print_python_bytes(pobj);
	}
}
