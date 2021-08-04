#include "Compos.h"
#include "Ln.h"
#include "Square.h"
Compos::Compos(shared_ptr<Function> func1, shared_ptr<Function> func2)
	: m_func1(func1), m_func2(func2),m_num(0)
{
}

Compos::Compos(const Compos & compos, double num)
	:m_num(num),m_calc(0)
{
	m_func2 = compos.m_func2;	
	if (m_func2->getName() == "ln")
	{
		Ln ln(num);
		m_calc_comps = ln.getCalc();
	}
	else
	{
		Square square(num);
		m_calc_comps = square.getCalc();
	}
	m_func1 = compos.m_func1;
	if (m_func1->getName() == "ln")
	{
		Ln ln(m_calc_comps);
		m_calc = ln.getCalc();
	}
	else
	{
		Square square(m_calc_comps);
		m_calc = square.getCalc();
	}
}

const double Compos::getCalc()
{
	return m_calc;
}

const string Compos::getDimens()
{
	std::ostringstream osString;
	if(m_num == 0)
		osString << m_func1->getName() << '(' << m_func2->getDimens() << ')';
	else
		osString << m_func1->getName() << '(' << m_func2->getName() <<'(' << m_num << "))";

	return osString.str();
}
