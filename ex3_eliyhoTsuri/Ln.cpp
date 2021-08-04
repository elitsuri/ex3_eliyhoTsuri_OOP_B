#include "Ln.h"

Ln::Ln(double num)
	: m_num(num)
{
	m_name = "ln";
}

const double Ln::getCalc()
{
	return log(m_num);
}

const std::string Ln::getDimens()
{
	std::ostringstream osString;
	if (m_num > 0)
		osString << '(' << m_num << ')';
	else
		osString << "ln(x)";
	return osString.str();
}

