#include "Log.h"
#include "Multiple.h"
#include "Add.h"
#include "Poly.h"

Log::Log(int log_num, shared_ptr<Function> func)
	:m_func(func),m_log(log_num),m_num(0),m_calc(0)
{
}

Log::Log(Log &log_func, double num)
	:m_num(num)
{
	m_log = log_func.m_log;
	m_func = log_func.m_func;

	if (Function *f = dynamic_cast <Multiple*>(&*log_func.m_func))
		m_calc = (log(sqrt(num) * log(num))) / (log(m_log));	
	else if (Function *f = dynamic_cast <Add*>(&*log_func.m_func))
		m_calc = m_log * log(m_log) + log(num);
	else if (Function *f = dynamic_cast <Poly*>(&*log_func.m_func))
		m_calc = sqrt(m_log) + (m_log * log(m_log));
	else
		m_calc = sqrt(num) * log(m_log);
}

const double Log::getCalc()
{
	return m_calc;
}

const string Log::getDimens()
{
	std::ostringstream osString;
	if (m_num == 0)
		osString << "log" << m_log << "(" << m_func->getDimens() << ')';
	else
		osString << "log" << m_log << "(" << m_func->getName() << '(' << m_num << "))";
	
	return osString.str();
}