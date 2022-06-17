#include<iostream>
#include <fstream>
#include<Python.h>
using namespace std;
int main(int argc, char* argv[])
{
    //初始化python
    Py_Initialize();

    //直接运行python代码
    PyRun_SimpleString("print('----------Python Start')");

    //引入当前路径,否则下面模块不能正常导入
    PyRun_SimpleString("import sys");  
    PyRun_SimpleString("sys.path.append('./')");  

    //引入模块
    PyRun_SimpleString("print('----------PyImport_ImportModule')");
    PyObject *pModule = PyImport_ImportModule("HHH");
    //获取模块字典属性
    PyRun_SimpleString("print('----------PyModule_GetDict')");
    PyObject *pDict = PyModule_GetDict(pModule);


    //读取调用读文件的函数
    PyRun_SimpleString("print('----------ReadBfile')");
    PyObject *rFunc =  PyObject_GetAttrString(pModule, "ReadBfile");
    PyObject *pyValue = PyEval_CallObject(rFunc, NULL);
    Py_ssize_t size = PyBytes_Size(pyValue);
    printf("suncL :%d\n",PyBytes_Check(pyValue));
    char *utf8string;
    PyObject *ret;
    ofstream outfile;
    outfile.open("file.dat", ios::out | ios::binary );
      // 再次向文件写入用户输入的数据
    if (PyBytes_Check(pyValue)){
       int r = PyBytes_AsStringAndSize(pyValue, &utf8string, &size);
       char d[size];
       memcpy(d, utf8string, size);
       int x= strlen(d);
       int y = sizeof(utf8string);
       printf("y %d\n",y);
       printf("$@ %d\n",x);
      // utf8string = PyBytes_AS_STRING(pyValue);
         // 再次向文件写入用户输入的数据
       outfile.write(d, size);

       outfile.close();
    }else{
       ret = PyUnicode_AsUTF8String(pyValue);
       utf8string = strdup(PyBytes_AsString(ret));
    }
    //char *utf8string = PyBytes_AS_STRING(pyValue); 
    printf("%s\n", utf8string);
    
   /**
    //直接获取模块中的函数
    PyRun_SimpleString("print('----------PyObject_GetAttrString')");
    PyObject *pFunc = PyObject_GetAttrString(pModule, "Hello");

    //参数类型转换，传递一个字符串。将c/c++类型的字符串转换为python类型，元组中的python类型查看python文档
    PyRun_SimpleString("print('----------Py_BuildValue')");
    PyObject *pArg = Py_BuildValue("(s)", "Hello Charity");

    PyRun_SimpleString("print('----------PyEval_CallObject')");
    //调用直接获得的函数，并传递参数
    PyEval_CallObject(pFunc, pArg);

    //从字典属性中获取函数
    PyRun_SimpleString("print('----------PyDict_GetItemString Add function')");
    pFunc = PyDict_GetItemString(pDict, "Add");
    //参数类型转换，传递两个整型参数
    pArg = Py_BuildValue("(i, i)", 1, 2);

    //调用函数，并得到python类型的返回值
    PyObject *result = PyEval_CallObject(pFunc, pArg);
    //c用来保存c/c++类型的返回值
    int c;
    //将python类型的返回值转换为c/c++类型
    PyArg_Parse(result, "i", &c);
    //输出返回值
    printf("a+b=%d\n", c);

    //通过字典属性获取模块中的类
    PyRun_SimpleString("print('----------PyDict_GetItemString test class')");
    PyObject *pClass = PyDict_GetItemString(pDict, "Test");

    //实例化获取的类
    PyRun_SimpleString("print('----------PyInstanceMethod_New test class')");
    PyObject *pInstance = PyInstanceMethod_New(pClass);
    //调用类的方法
    PyRun_SimpleString("print('----------PyObject_CallMethod SayHello')");
    result = PyObject_CallMethod(pInstance, "SayHello", "(Os)", pInstance, "Charity");
    //输出返回值
    char* name=NULL;
    PyRun_SimpleString("print('----------PyArg_Parse')");
    PyArg_Parse(result, "s", &name);
    printf("%s\n", name);

    **/
    PyRun_SimpleString("print('Python End')");

    //释放python
    Py_Finalize();
    getchar();
    return 0;
}
