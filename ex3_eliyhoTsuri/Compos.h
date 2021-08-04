#pragma once
#include "SimpOperation.h"
class Compos :public SimpOperation
{
public:
	Compos(shared_ptr<Function> func1, shared_ptr<Function> func2);
	Compos(const Compos & compos, double num);
	const double getCalc();
	const string getDimens();
private:
	shared_ptr <Function> m_func1;
	shared_ptr <Function> m_func2;
	double m_num;
	double m_calc;
	double m_calc_comps;
};