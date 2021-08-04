#include "Add.h"
#include "Ln.h"
#include "Square.h"

Add::Add(shared_ptr<Function> func1,shared_ptr<Function> func2, double num)
	: m_func1(func1), m_func2(func2), m_num(num)
{
	m_name = string().append(func1->getDimens()).append(" + ").append(func2->getName());
}

Add::Add(const Add & add, double num)
	:m_num(num),m_calc(0)
{
	m_func1 = add.m_func1;
	m_func2 = add.m_func2;
	Ln ln(num);
	Square square(num);
	m_calc = ln.getCalc();
	m_calc += square.getCalc();
}

const double Add::getValue()
{
	return m_num;
}

const double Add::getCalc()
{
	return m_calc;
}

const string Add::getDimens()
{
	std::ostringstream osString;
	if (m_num != 0)
	{
		osString << '(' << this->m_func1->getName() << '(' << m_num
			<< ")) + (" << this->m_func2->getName() << '(' << m_num << "))";
	}
	else
		osString << '(' << m_func1->getDimens() << ") + (" << m_func2->getDimens() << ')';
	return osString.str();
}