#include "SimpValidator.h"



SimpValidator::SimpValidator()
{
}

bool SimpValidator::checkInput(string func,string args,int size)
{
	int count = 0;
	size_t index = 0;
	bool check = true;
	while (index < args.size() && check)
	{
		if (args.size() == func.size() && args == func)
			break;
		if (!isdigit(args[index]) && !isspace(args[index]))
			throw (std::invalid_argument("The number of functions must be an integer\n"));
		if (isdigit(args[index]))
		{
			if (atoi(&args[index]) <= size-1)
			{
				m_funcs[count] = atoi(&args[index]);
				count++;
			}
			else
				throw(std::invalid_argument("There isn't such function on calculator\n"));
		}
		index++;
	}
	if (count > 2)
		throw(std::length_error("Too many arguments\n"));
	if (count < 2)
		throw(std::length_error("Too few arguments\n"));
	return true;
}


SimpValidator::~SimpValidator()
{
}
