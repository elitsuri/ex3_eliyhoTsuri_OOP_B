#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <sstream>
#include "Function.h"
#include "Validator.h"
enum command { simpel, complex, calc, change, read, help, exit_f, error };

class Calculator
{
public:
	Calculator();
	void setFunctions();
	void getMaxFunc();
	bool checkSize(string size);
	void run();
	void checkCommand(string line);
	void buildFunction();
	void setSimpleFunc();
	void setComplexFunc();
	void setCalcFunc();
	void changeSize();
	void getFile();
	void errorFile();
	void delOrEnlarge();
	void printHelp();
	void printMenu();
private:
	bool m_flag = false;
	int m_size, size_vec;
	int num_command;
	string m_line;
	string m_func;
	string m_args;
	bool flag_file = false;
	bool end = true;
	int num_line = 0;
	string line_file;
	std::ifstream m_file;
	vector <string> m_function;
	vector <shared_ptr <Function>> v_Func;
	vector <shared_ptr <Validator>> m_val;
};