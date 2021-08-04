#pragma once
#include <string>
using::std::string;
class Validator
{
public:
	Validator() {};
	virtual bool checkInput(string func,string args, int size) = 0;
	virtual int getArg1() = 0;
	virtual int getArg2() = 0;
	~Validator() {};
};