#pragma once
#include "SimpOperation.h"
class Multiple : public SimpOperation
{
public:
	Multiple(shared_ptr<Function> func1,shared_ptr<Function> func2);
	Multiple(const Multiple &mul, double num);
	const double getCalc();
	const string getDimens();
private:
	shared_ptr <Function> m_func1;
	shared_ptr <Function> m_func2;
	double m_num;
	double m_calc;
};