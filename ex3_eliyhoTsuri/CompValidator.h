#pragma once
#include "Validator.h"
class CompValidator : public Validator 
{
public:
	CompValidator() {};
	virtual bool checkInput(string func,string args, int size);
	bool checkLogArgs(string args, int size);
	bool checkPolyArgs(string args);
	bool checkRevArgs(string args,int size);
	virtual int getArg1() { return m_args[0]; }
	virtual int getArg2() { return m_args[1]; }
	~CompValidator() {};
private:
	int m_args[2];
};