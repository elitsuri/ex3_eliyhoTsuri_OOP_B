#include "Multiple.h"
#include "Ln.h"
#include "Square.h"

Multiple::Multiple(shared_ptr<Function> func1, shared_ptr<Function> func2)
	: m_num(0), m_func1(func1), m_func2(func2)
{
	m_name = string().append(func1->getDimens()).append(" * ").append(func2->getName());

}

Multiple::Multiple(const Multiple &mul, double num)
	: m_num(num), m_calc(0)
{
	m_func1 = mul.m_func1;
	m_func2 = mul.m_func2;
	Ln ln(num);
	Square square(num);
	m_calc = ln.getCalc();
	m_calc *= square.getCalc();
}

const double Multiple::getCalc()
{
	return m_calc;
}

const string Multiple::getDimens()
{
	std::ostringstream osString;

	if (m_num == 0)
		osString << '(' << m_func1->getName() << "(x)) * (" << m_func2->getName() << "(x))";
	else
		osString << '(' << m_func1->getName() << '(' << m_num << ")) * ("
		<< m_func2->getName() << '(' << m_num << "))";
	return osString.str();
}

