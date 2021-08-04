#pragma once
#include "Validator.h"
class CalcValidator: public Validator
{
public:
	CalcValidator();
	virtual bool checkInput(string func,string args, int size);
	virtual int getArg1() { return m_args[0]; }
	virtual int getArg2() { return m_args[1]; }
	~CalcValidator();
private:
	int m_args[2];
};