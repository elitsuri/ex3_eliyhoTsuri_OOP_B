#include "Square.h"

Square::Square(double num)
	: m_num(num)
{
	m_name = "sqrt";
}

const double Square::getValue()
{
	return m_num;
}

const double Square::getCalc()
{
	return sqrt(m_num);
}

const string Square::getDimens()
{
	std::ostringstream osString;
	if (m_num > 0)
		osString << '(' << m_num << ')' ;
	else
		osString << "sqrt(x)";
	return osString.str();
}
