#include "Calculator.h"
#include "Ln.h"
#include "Square.h"
#include "Multiple.h"
#include "Add.h"
#include "Compos.h"
#include "Log.h"
#include "Poly.h"
#include "SimpValidator.h"
#include "CompValidator.h"
#include "CalcValidator.h"
// ----------------------------------------------------------------
Calculator::Calculator()
{
	setFunctions();
	getMaxFunc();
	while (end)
		run();
}
// ----------------------------------------------------------------
void Calculator::setFunctions()
{
	m_function.push_back("eval");
	m_function.push_back("add");
	m_function.push_back("mul");
	m_function.push_back("poly");
	m_function.push_back("comp");
	m_function.push_back("log");
	m_function.push_back("rev");
	m_function.push_back("read");
	m_function.push_back("del");
	m_function.push_back("inc");
	m_function.push_back("help");
	m_function.push_back("exit");
	m_function.push_back("Error");
	m_val.push_back(make_shared<SimpValidator>());
	m_val.push_back(make_shared<CompValidator>());
	m_val.push_back(make_shared<CalcValidator>());
}
// ----------------------------------------------------------------
void Calculator::getMaxFunc()
{
	string str = "Enter maximum number for functions calculator (min 1, max 20)\n";
	while (1)
	{
		string size;
		cout << str;
		cin >> size;
		if (checkSize(size))
		{
			if (std::stoi(size) > 20)
				m_size = 20;
			else
				m_size = std::stoi(size);
			break;
		}
		std::cin.ignore(INT_MAX, '\n');
	}
	if (m_size == 1)
	{
		v_Func.push_back(make_shared<Ln>());
		size_vec = 1;
	}
	else if (m_size > 1)
	{
		v_Func.push_back(make_shared<Ln>());
		v_Func.push_back(make_shared<Square>());
		size_vec = 2;
	}
	std::cin.ignore(INT_MAX, '\n');
}
// ----------------------------------------------------------------
bool Calculator::checkSize(string size)
{
	size_t index = 0;
	bool check = true;
	while (index < size.size() && check)
	{
		if (!isdigit(size[index]) || isalpha(size[index]))
			check = false;
		index++;
	}
	return check;
}
// ----------------------------------------------------------------
void Calculator::run()
{
	string str = "***********************************************************\n";
	try
	{
		if (!flag_file)
		{
			printMenu();
			getline(cin, m_line);
		}
		checkCommand(m_line);
		if (flag_file)
			return;
		buildFunction();
	}
	catch (std::invalid_argument & argError)
	{
		cout << '\n' << str;
		cout << m_function[12] << ": ";
		cout << argError.what();
		if (flag_file)
			errorFile();
		cout << str << '\n';
	}
	catch (std::length_error & lenError)
	{
		cout << '\n' << str;
		cout << m_function[12] << ": ";
		cout << lenError.what();
		if (flag_file)
			errorFile();
		cout << str << '\n';
	}
	catch (std::domain_error & domError)
	{
		cout << '\n' << str;
		cout << m_function[12] << ": ";
		cout << domError.what();
		if (flag_file)
			errorFile();
		cout << str << '\n';
	}
}
// ----------------------------------------------------------------
void Calculator::checkCommand(string line)
{
	int index = line.find(' ');
	m_func = line.substr(0, index);
	m_args = line.substr(index + 1, '\n');
	bool check = false;

	for (size_t i = 0; i < m_function.size() && !check; ++i)
	{
		if (m_func == m_function[i])
		{
			check = true;
			if (m_func == "eval")
				num_command = calc;
			if (m_func == "add" || m_func == "mul" || m_func == "comp")
				num_command = simpel;
			if (m_func == "poly" || m_func == "rev" || m_func == "log")
				num_command = complex;
			if (m_func == "del" || m_func == "inc")
				num_command = change;
			if (m_func == "read")
				getFile();
			if (m_func == "help")
				num_command = help;
			if (m_func == "exit")
				num_command = exit_f;
		}
	}
	if (!check)
		throw (std::invalid_argument("Wrong name function\n"));
}
// ----------------------------------------------------------------
void Calculator::buildFunction()
{
	int index = 0;
	bool flag_change = false;
	switch (num_command)
	{
		case simpel:
		{
			if (m_val[num_command]->checkInput(m_func, m_args, size_vec))
				if (size_vec == m_size)
					changeSize();
			setSimpleFunc();
			break;
		}
		case complex:
		{
			if (m_val[num_command]->checkInput(m_func, m_args, size_vec))
				if (size_vec == m_size)
					changeSize();
			setComplexFunc();
			break;
		}
		case calc:
		{
			if (m_val[num_command]->checkInput(m_func, m_args, size_vec))
				setCalcFunc();
			break;
		}
		case change:
		{
			delOrEnlarge();
			break;
		}
		case help:
		{
			printHelp();
			break;
		}
		case exit_f:
		{
			end = false;
			flag_file = false;
			break;
		}
		case error:
		{
			cout << m_function[error] << '\n';
			break;
		}
		default:
		break;
	}
}
// ----------------------------------------------------------------
void Calculator::setSimpleFunc()
{
	int arg1 = m_val[0]->getArg1();
	int arg2 = m_val[0]->getArg2();
	if (m_func == "add")
		v_Func.push_back(make_shared<Add>(v_Func[arg1], v_Func[arg2], 0));
	if (m_func == "mul")
		v_Func.push_back(make_shared<Multiple>(v_Func[arg1], v_Func[arg2]));
	if (m_func == "comp")
		v_Func.push_back(make_shared<Compos>(v_Func[arg1], v_Func[arg2]));
	size_vec++;
}
// ----------------------------------------------------------------
void Calculator::setComplexFunc()
{
	if (m_func == "poly")
		v_Func.push_back(make_shared<Poly>(m_args));
	if (m_func == "rev")
	{
		int arg = m_val[1]->getArg1();
		if (Poly *p = dynamic_cast <Poly*>(&(*v_Func[arg])))
		{
			Poly &poly = *p;
			v_Func.push_back(make_shared <Poly>(poly));
		}
		else
			throw (std::invalid_argument("The function is not a polynomial\n"));
	}
	if (m_func == "log")
	{
		int arg1 = m_val[1]->getArg1();
		int arg2 = m_val[1]->getArg2();
		v_Func.push_back(make_shared<Log>(arg1, v_Func[arg2]));
	}
	size_vec++;
}
// ----------------------------------------------------------------
void Calculator::setCalcFunc()
{
	int arg1 = m_val[2]->getArg1();
	int arg2 = m_val[2]->getArg2();
	if (arg1 > size_vec || arg1 < 0)
		throw (std::invalid_argument("There is no such function in the calculator\n"));
	else
	{
		if (m_func == "eval")
		{
			m_flag = true;
			if (arg1 == 0)
				v_Func.push_back(make_shared <Ln>(arg2));
			if (arg1 == 1)
				v_Func.push_back(make_shared <Square>(arg2));
			if (Function *f = dynamic_cast <Multiple*>(&(*v_Func[arg1])))
			{
				Multiple *m = dynamic_cast <Multiple*>(&(*v_Func[arg1]));
				Multiple &mul = *m;
				v_Func.push_back(make_shared <Multiple>(mul, arg2));
			}
			if (Function *f = dynamic_cast <Add*>(&(*v_Func[arg1])))
			{
				Add *m = dynamic_cast <Add*>(&(*v_Func[arg1]));
				Add &mul = *m;
				v_Func.push_back(make_shared <Add>(mul, arg2));
			}
			if (Function *f = dynamic_cast <Compos*>(&(*v_Func[arg1])))
			{
				Compos *c = dynamic_cast <Compos*>(&(*v_Func[arg1]));
				Compos &compos = *c;
				v_Func.push_back(make_shared <Compos>(compos, arg2));
			}
			if (Function *f = dynamic_cast <Poly*>(&(*v_Func[arg1])))
			{
				Poly *p = dynamic_cast <Poly*>(&(*v_Func[arg1]));
				Poly &poly = *p;
				v_Func.push_back(make_shared <Poly>(poly, arg2));
			}
			if (Function *f = dynamic_cast <Log*>(&(*v_Func[arg1])))
			{
				Log *l = dynamic_cast <Log*>(&(*v_Func[arg1]));
				Log &log = *l;
				v_Func.push_back(make_shared <Log>(log, arg2));
			}
		}
	}
}
// ----------------------------------------------------------------
void Calculator::changeSize()
{
	string str = "Enter\n'inc' - To increase the size of functions in the calculator\n";
	str.append("'del' - To delete the last function on the calculator\n");
	str.append("Please select a new size or delete functions from the calculator\n");
	char c;
	string command;
	cout << str;
	cin >> command;
	std::transform(command.begin(), command.end(), command.begin(), ::toupper);

	while (command != "DEL" && command != "INC")
	{
		cout << str;
		cin >> command;
	}
	if (command == "INC")
	{
		cout << "Enter the new size of the function on the calculator \n";
		cin >> c;
		while (!isdigit(c))
		{
			cout << "Enter the new size of the function on the calculator \n";
			std::cin.ignore(INT_MAX, '\n');
			cin >> c;
		}
		m_size = atoi(&c);
		size_vec = m_size;
		v_Func.resize(m_size);
		int i = size_vec;
		while (i < m_size)
		{
			v_Func.pop_back();
			i++;
		}
	}
	else
		v_Func.erase(v_Func.begin() + v_Func.size() - 1);
	std::cin.ignore(INT_MAX, '\n');
}
// ----------------------------------------------------------------
void Calculator::getFile()
{
	if (!flag_file)
	{
		string nameFile;
		string str = "Enter the path and file name\n";
		string str2 = "No file with this name\nWould you like to try entering a valid filename or ending?\n";
		while (1)
		{
			char c;
			cout << str;
			cin >> nameFile;
			m_file.open(nameFile);
			if (m_file.is_open())
			{
				flag_file = true;
				break;
			}
			else
			{
				cout << str2;
				cout << "Enter u - To try again\nEnter e - To end the program\n";
			}
			cin >> c;
			if (c == 'e')
			{
				end = false;
				break;
			}
		}
	}
	else
	{
		while (!m_file.eof() && flag_file)
		{
			num_line++;
			printMenu();
			getline(m_file, line_file);
			checkCommand(line_file);
			buildFunction();
		}
	}
	m_flag = false;
	if (end)
		std::cin.ignore(INT_MAX, '\n');
}
// ----------------------------------------------------------------
void Calculator::errorFile()
{
	char command_file;
	string str = "\nEnter y - To keep reading from file\nEnter n - To end and back the last step\nYour command: ";
	cout << "Line number: " << num_line << " is invalid\n";
	cout << "The line content is: " << "'" << line_file << "'\n";
	cout << "Would you like to keep reading from a file or finish ?\n";
	cout << str;

	cin >> command_file;
	while (command_file != 'n' && command_file != 'y')
	{
		cout << str;
		cin >> command_file;
	}
	if (command_file == 'n')
	{
		flag_file = false;
		end = false;
	}
}
// ----------------------------------------------------------------
void Calculator::delOrEnlarge()
{
	int arg = atoi(&m_args[0]);
	if (m_func == "del")
	{
		if (size_vec > arg)
		{
			v_Func.erase(v_Func.begin() + arg);
			size_vec--;
		}
		else
			throw(std::invalid_argument("No such function on the calcildator\n"));
	}
	else
	{
		string str = "The number of functions in the calculator is greater than the desired size\n";
		if (size_vec > arg)
			throw(std::invalid_argument(str));
		m_size = arg;
		v_Func.resize(m_size);
		int i = size_vec;
		while (i < m_size)
		{
			v_Func.pop_back();
			i++;
		}
	}
}
// ----------------------------------------------------------------
void Calculator::printMenu()
{
	string str = "===========================================================\n";

	int p = v_Func.size() - 1;
	if (m_flag)
	{
		cout << str;
		cout << "Result: " << v_Func[p]->getName() << v_Func[p]->getDimens()
			<< " = " << v_Func[p]->getCalc() << "\n";
		v_Func.erase(v_Func.begin() + p);
	}
	int i = 0;
	cout << str;
	cout << "This is the functions list: \n";
	cout << "List function is: (" << size_vec << '/' << m_size << ")\n";

	for (auto &p : v_Func)
	{
		if (p != NULL)
			cout << i++ << ": " << p->getDimens() << '\n';
	}
	if (!flag_file)
	{
		cout << "Please enter a command:\n'help' - for show the command list\n";
		cout << "'read' - To read command from text file\n";
		cout << str;
		cout << "Your command: ";
	}
	m_flag = false;
}
// ----------------------------------------------------------------
void Calculator::printHelp()
{
	cout << "\nThis is the manu function :\n"
		R"(eval(uate) num x - Evaluates function #num on x
poly(nomial) N c0 c1 ... cN - 1 - Creates a polynomial with N coefficients.
rev(erse) num - Creates a polynomial with N coefficients in reverse order.	
mul(tiply) num1 num2 - Creates a function that is the multiplication of function #num1 and function #num2.
add num1 num2 - Creates a function that is the sum of function #num1 and function #num2.
comp(osite) num1 num2 - Creates a function that is the composition of function #num1 and function #num2.
log N num - Log N of function #num.
del(ete) num - Deletes function #num from function list.
help - Prints this help screen.
exit - Exits the program)" << '\n';
}