#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
 
using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
pModule = PyImport_Import(pName);
// pDict is a borrowed reference 
pDict = PyModule_GetDict(pModule);
// pFunc is also a borrowed reference 
pFunc = PyDict_GetItemString(pDict, procname);
if (PyCallable_Check(pFunc))
{
	pValue = Py_BuildValue("(z)", paramval);
	PyErr_Print();
	presult = PyObject_CallObject(pFunc, pValue);
	PyErr_Print();
}
else
{
	PyErr_Print();
}
//printf("Result is %d\n", _PyLong_AsInt(presult));
Py_DECREF(pValue);
// Clean up
Py_DECREF(pModule);
Py_DECREF(pName);
// Finish the Python Interpreter
Py_Finalize();

// clean 
delete[] procname;
delete[] paramval;


return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//converts num into num of asterisks
string intToAsterisks(int num) {
	return string(num, '*');
}

//counts the frequency of the requested item
void countGroceryItem(){
	cout << "What item would you like to view?" << endl;
	string itemName;
	cin >> itemName;
	int frequency = callIntFunc("countGroceryItem", itemName);
	cout << itemName << ":" << frequency << endl;
}

//writes .dat file and prints histogram
void printHistogram(){
	CallProcedure("writeGroceryListToFile");
	//opens file
	ifstream input;
	input.open("frequency.dat");
	cout << "Reading file" << endl;
	string itemName;
	int frequency;

	while (input >> itemName >> frequency) {
		cout << itemName << " " << intToAsterisks(frequency) << endl;
	}
	input.close();
}

void main()
{
	//Display Menu
	cout << "1: Display items purchased today & amount purchased" << endl;
	cout << "2: Display how many times requested item was purchased today" << endl;
	cout << "3: Display histogram of items purchased today, & amount purchased " << endl;
	cout << "4: Exit" << endl;

	//Input Validation for 1-4, if user enters 4 exits
	int userInput = -1;
	while (userInput < 1 || userInput > 4) {
		cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;
		cin >> userInput;
	}

	if (userInput == 1) {
		//prints all items purchased and amount of each
		CallProcedure("printGroceryList");
	}
	else if (userInput == 2) {
		countGroceryItem();
	}
	else if (userInput == 3) {
		printHistogram();
	}
}