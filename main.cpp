#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "m4_test.h"
#include "Python.h"
#include <iostream>
#include <numpy/arrayobject.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// C++����python  simple_module.py�ű�

//int main(int argc, char *argv[])
//{
//	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
//	if (program == NULL) {
//		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
//		exit(1);
//	}
//	Py_SetProgramName(program);  /* optional but recommended */
//	
//
//	string path = "H:/demo";  //ģ��simple_module.py�ļ��洢·��
//	string chdir_cmd = string("sys.path.append(\"");
//
//	//��ʼ��Python����
//	Py_Initialize();
//	import_array();
//	chdir_cmd += path;
//	chdir_cmd += "\")";
//
//	const char* cstr_cmd = chdir_cmd.c_str();
//	PyRun_SimpleString("import sys");	//PyRun_SimpleString("")���Լ򵥵�ֱ�������ַ����ڵ�Python���
//	PyRun_SimpleString(cstr_cmd);	//���Insertģ��·��
//
//	
//	PyObject* pModule = PyImport_ImportModule("simple_module"); //����ģ��simple_module.py
//
//	// ģ���Ƿ���ɹ�
//	if (!pModule)
//	{
//		cout << "Python get module failed." << endl;
//		return 0;
//	}
//	else
//	{
//		cout << "Python get module succeed." << endl;
//	}
//	
//	PyObject *pFunc = PyObject_GetAttrString(pModule, "simple_func"); //��ģ��simple_module.py���뺯�� 
//	if (!pFunc || !PyCallable_Check(pFunc))
//	{
//		cout << "Can't find funftion 'simple_func'" << endl;
//		return 0;
//	}
//	else
//	{
//		cout << "Get function 'simple_func' succeed ." << endl;
//	}
//	
//	PyObject *pArgs = PyTuple_New(2);    //��ʼ����������б�����Ϊ2
//	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 100));	// ���ò��� Py_BuildValue: C->python
//	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 200));	// ���ò���
//	PyObject *pRetValue = PyObject_CallObject(pFunc, pArgs);  //����������ú���������ȡ����ֵ
//	int ret, ret1, ret2;
//	PyArg_Parse(pRetValue, "(iii)", &ret, &ret1, &ret2); //PyArg_Parse: python->C
//	printf("return value: %d %d %d", ret, ret1, ret2);
//
//	Py_Finalize();
//	PyMem_RawFree(program);
//	getchar();
//	return 0;
//}


int main(int argc, char *argv[])
{
	Mat img = imread("C:/Users/yang/Desktop/celian/6.jpg");
	imshow("image", img);
	waitKey();

	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
	if (program == NULL) {
		fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
		exit(1);
	}
	Py_SetProgramName(program);  /* optional but recommended */


	string path = "H:/demo";  //ģ��simple_module.py�ļ��洢·��
	string chdir_cmd = string("sys.path.append(\"");

	//��ʼ��Python����
	Py_Initialize();
	import_array();
	chdir_cmd += path;
	chdir_cmd += "\")";

	const char* cstr_cmd = chdir_cmd.c_str();
	PyRun_SimpleString("import sys");	//PyRun_SimpleString("")���Լ򵥵�ֱ�������ַ����ڵ�Python���
	PyRun_SimpleString(cstr_cmd);	//���Insertģ��·��


	PyObject* pModule = PyImport_ImportModule("get_cvmat"); //����ģ��simple_module.py

	// ģ���Ƿ���ɹ�
	if (!pModule)
	{
		cout << "Python get module failed." << endl;
		return 0;
	}
	else
	{
		cout << "Python get module succeed." << endl;
	}

	PyObject *pFunc = PyObject_GetAttrString(pModule, "super_resolution"); //��ģ��simple_module.py���뺯�� 
	// �����Ƿ���ɹ�
	if (!pFunc || !PyCallable_Check(pFunc))
	{
		cout << "Can't find funftion 'super_resolution'" << endl;
		return 0;
	}
	else
	{
		cout << "Get function 'super_resolution' succeed ." << endl;
	}

	PyObject *pArgs = PyTuple_New(2);    //��ʼ����������б�����Ϊ2
	npy_intp dims[] = { img.rows, img.cols, 3 }; // numpy��ά��
	PyObject *pValue = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, img.data); //numpy�Ĵ���
	PyTuple_SetItem(pArgs, 0, pValue);	/* pValue�����ü�����͵͵��һ�������ֶ��ټ� */
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));	/* ͼ��Ŵ�4�� */

	PyObject *pRetValue = PyObject_CallObject(pFunc, pArgs);  //����������ú���������ȡ����ֵ
	/* �������ؽ�� */
	PyArrayObject *ret_array;
	PyArray_OutputConverter(pRetValue, &ret_array);
	npy_intp *shape = PyArray_SHAPE(ret_array);
	Mat big_img(shape[0], shape[1], CV_8UC3, PyArray_DATA(ret_array));
	imshow("image", big_img);
	waitKey();

	Py_Finalize();
	PyMem_RawFree(program);
	getchar();
	return 0;
}




