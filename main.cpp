#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "m4_test.h"
#include "Python.h"
#include <iostream>
#include <numpy/arrayobject.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// C++调用python  simple_module.py脚本

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
//	string path = "H:/demo";  //模块simple_module.py文件存储路径
//	string chdir_cmd = string("sys.path.append(\"");
//
//	//初始化Python环境
//	Py_Initialize();
//	import_array();
//	chdir_cmd += path;
//	chdir_cmd += "\")";
//
//	const char* cstr_cmd = chdir_cmd.c_str();
//	PyRun_SimpleString("import sys");	//PyRun_SimpleString("")可以简单的直接运行字符串内的Python语句
//	PyRun_SimpleString(cstr_cmd);	//添加Insert模块路径
//
//	
//	PyObject* pModule = PyImport_ImportModule("simple_module"); //导入模块simple_module.py
//
//	// 模块是否导入成功
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
//	PyObject *pFunc = PyObject_GetAttrString(pModule, "simple_func"); //从模块simple_module.py导入函数 
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
//	PyObject *pArgs = PyTuple_New(2);    //初始化输入参数列表，长度为2
//	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 100));	// 设置参数 Py_BuildValue: C->python
//	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 200));	// 设置参数
//	PyObject *pRetValue = PyObject_CallObject(pFunc, pArgs);  //传入参数调用函数，并获取返回值
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


	string path = "H:/demo";  //模块simple_module.py文件存储路径
	string chdir_cmd = string("sys.path.append(\"");

	//初始化Python环境
	Py_Initialize();
	import_array();
	chdir_cmd += path;
	chdir_cmd += "\")";

	const char* cstr_cmd = chdir_cmd.c_str();
	PyRun_SimpleString("import sys");	//PyRun_SimpleString("")可以简单的直接运行字符串内的Python语句
	PyRun_SimpleString(cstr_cmd);	//添加Insert模块路径


	PyObject* pModule = PyImport_ImportModule("get_cvmat"); //导入模块simple_module.py

	// 模块是否导入成功
	if (!pModule)
	{
		cout << "Python get module failed." << endl;
		return 0;
	}
	else
	{
		cout << "Python get module succeed." << endl;
	}

	PyObject *pFunc = PyObject_GetAttrString(pModule, "super_resolution"); //从模块simple_module.py导入函数 
	// 函数是否导入成功
	if (!pFunc || !PyCallable_Check(pFunc))
	{
		cout << "Can't find funftion 'super_resolution'" << endl;
		return 0;
	}
	else
	{
		cout << "Get function 'super_resolution' succeed ." << endl;
	}

	PyObject *pArgs = PyTuple_New(2);    //初始化输入参数列表，长度为2
	npy_intp dims[] = { img.rows, img.cols, 3 }; // numpy的维度
	PyObject *pValue = PyArray_SimpleNewFromData(3, dims, NPY_UINT8, img.data); //numpy的创建
	PyTuple_SetItem(pArgs, 0, pValue);	/* pValue的引用计数被偷偷减一，无需手动再减 */
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));	/* 图像放大4倍 */

	PyObject *pRetValue = PyObject_CallObject(pFunc, pArgs);  //传入参数调用函数，并获取返回值
	/* 解析返回结果 */
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




