#include "CompValidator.h"


bool CompValidator::checkInput(string func, string args, int size)
{
	if (args.size() == func.size() && args == func)
		throw(std::length_error("Too few arguments\n"));
	bool check = false;
	if (func == "log")
		check = checkLogArgs(args, size);
	if (func == "poly")
		check = checkPolyArgs(args);
	if (func == "rev")
		check = checkRevArgs(args, size);
	return check;
}

bool CompValidator::checkLogArgs(string args, int size)
{
	int count = 0;
	size_t index = 0;
	bool check = true;
	int arg;
	while (index < args.size() && check)
	{
	
		if (!isdigit(args[index]) && !isspace(args[index]))
			throw (std::invalid_argument("The arguments must be integer\n"));
		if (isdigit(args[index]))
		{
			arg = atoi(&args[index]);
			if (count == 0)
			{
				if (arg < 1)
					throw (std::invalid_argument("The base of the log must be a positive number\n"));
				else
					m_args[count] = arg;
			}
			else
			{
				if (arg < size)
					m_args[count] = arg;
				else
					throw(std::invalid_argument("There isn't such function on calculator\n"));
			}
			count++;
		}
		index++;
	}
	if (count > 2)
		throw(std::length_error("Too many arguments\n"));
	if (count < 2)
		throw(std::length_error("Too few arguments\n"));
	return true;
}

bool CompValidator::checkPolyArgs(string args)
{
	int size_poly;
	int count = 0;
	size_t index = 0;

	while (index < args.size())
	{
		if (!isdigit(args[index]) && !isspace(args[index]))
			throw (std::invalid_argument("The arguments of polynomial must be integer\n"));

		if (isdigit(args[index]))
		{
			if (count == 0)
			{
				size_poly = atoi(&args[index]);
				if (size_poly < 1)
					throw (std::invalid_argument("The size of the polynomial must be a positive number\n"));
			}
			else
			{
				int arg = atoi(&args[index]);
				m_args[count] = arg;
			}
			count++;
		}
		index++;
	}
	if (count - 1 > size_poly)
		throw(std::length_error("Too many arguments for polynomial\n"));
	if (count - 1 < size_poly)
		throw(std::length_error("Too few arguments for polynomial\n"));
	return true;
}

bool CompValidator::checkRevArgs(string args, int size)
{
	int count = 0;
	for (unsigned i = 0; i < args.size(); ++i)
	{
		if (!isdigit(args[i]))
			throw (std::invalid_argument("The arguments must be integer\n"));
		else
		{
			m_args[0] = atoi(&args[i]);
			count++;
		}
	}
	if (count > 1)
		throw(std::length_error("Too many arguments\n"));
	else if (count < 1)
		throw(std::length_error("Too few arguments\n"));
	else if (m_args[0] > size-1)
		throw(std::invalid_argument("There is no such function in the calculator\n"));
}