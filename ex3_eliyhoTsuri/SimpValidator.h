#pragma once
#include "Validator.h"
class SimpValidator: public Validator
{
public:
	SimpValidator();
	virtual bool checkInput(string func,string args,int size);
	virtual int getArg1() { return m_funcs[0]; }
	virtual int getArg2() { return m_funcs[1]; }
	~SimpValidator();
private:
	int m_funcs[2];
};