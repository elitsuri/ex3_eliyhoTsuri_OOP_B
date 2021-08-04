#include "Poly.h"
#include <string>

Poly::Poly(string function)
{
	unsigned index = 0;
	bool flag = false;
	while(index < function.size())
	{
		if (isdigit(function[index]))
		{
			if (flag)
				m_poly.push_back(atoi(&function[index]));
			else
			{
				m_size = atoi(&function[index]);
				flag = true;
			}
		}
		index++;
	}
	check = true;
}

Poly::Poly(int size)
	: m_size(size), m_num(0)
{
	int num;
	for (int index = 0 ; index < size ; index++)
	{
		cin >> num;
		m_poly.push_back(num);
	}
}

Poly::Poly(const Poly & poly)
	:m_size(poly.getSize()),m_num(0) ,m_calc(0)
{
	for (int i = poly.getSize() - 1; i >= 0 ; --i)
		m_poly.push_back(poly[i]);
	check = true;
}

Poly::Poly(const Poly &poly, double num)
	:m_size(poly.getSize()), m_num(num), m_calc(0)
{
	int j = m_size - 1;
	for (int i = 0 ; i < poly.getSize() && j >= 0 ; i++)
	{
		m_poly.push_back(poly[j]);
		j--;
	}
}


const double Poly::getCalc()
{
	double result = 0;
	double exp = m_poly.size() - 1;
	for (unsigned i = 0; i < m_poly.size() ; ++i,exp--)
		result += m_poly[i] * (pow(m_num, exp));

	return result;
}

const string Poly::getDimens()
{
	std::ostringstream osString;
	if (m_num == 0 || check)
	{
		for (int i = m_poly.size() - 1; i >= 0; i--)
		{
			if (m_poly[i] != 0)
			{
				osString << m_poly[i] << "*(x)^" << i;
				if (i != 0)
					osString << " + ";
			}
		}
		m_name = osString.str();
	}
	else
	{
		m_name = "";
		int index = 1;
		for (unsigned i = 0 ; i < m_poly.size(); i++)
		{
			osString << m_poly[i] << "*(" << m_num << ")^" << m_poly.size() - index;
			if (i != m_poly.size() - 1)
				osString << " + ";
			index++;
		}
	}
	return osString.str();
}

int Poly::getSize()const
{
	return m_poly.size();
}

