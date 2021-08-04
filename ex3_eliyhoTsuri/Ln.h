#pragma once
#include "NoneOperation.h"
class Ln : public NoneOperation
{
public:
	Ln(double num = 0);
	const double getCalc();
	const string getDimens();
private:
	double m_num;
};