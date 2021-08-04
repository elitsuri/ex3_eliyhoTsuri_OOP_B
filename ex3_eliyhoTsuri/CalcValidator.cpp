#include "CalcValidator.h"



CalcValidator::CalcValidator()
{
}

bool CalcValidator::checkInput(string func,string args, int size)
{
	int count = 0;
	size_t index = 0;
	bool check = true;
	while (index < args.size() && check)
	{
		if (args.size() == func.size() && args == func)
			break;
		if (!isdigit(args[index]) && !isspace(args[index]))
			throw (std::invalid_argument("The number of functions must be an integer"));
		if (isdigit(args[index]))
		{
			if (count == 0 && atoi(&args[index]) >= size)
				break;
			m_args[count] = atoi(&args[index]);
			count++;
		}
		index++;
	}
	if (count > 2)
		throw(std::length_error("Too many arguments\n"));
	if (count < 1)
		throw(std::length_error("Too few arguments\n"));
	if(m_args[0] < 0 || m_args[0] > size)
		throw(std::invalid_argument("There isn't such function on calculator\n"));
	return true;
}


CalcValidator::~CalcValidator()
{
}
