#pragma once
#include "NoneOperation.h"
class Square : public NoneOperation
{
public:
	Square(double num = 0);
	const double getValue();
	const double getCalc();
	const string getDimens();
private:
	double m_num;
};