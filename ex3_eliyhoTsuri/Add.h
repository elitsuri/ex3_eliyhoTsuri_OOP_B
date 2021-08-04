#pragma once
#include "SimpOperation.h"
class Add : public SimpOperation
{
public:
	Add(shared_ptr<Function> func1,shared_ptr<Function> func2, double num);
	Add(const Add &add, double num);
	const double getValue();
	const double getCalc();
	const string getDimens();
private:
	shared_ptr <Function> m_func1;
	shared_ptr <Function> m_func2;
	double m_num;
	double m_calc;
};