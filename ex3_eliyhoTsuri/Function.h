#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <sstream>
// ---------------------- using ------------------------
using::std::string;
using::std::cin;
using::std::cout;
using std::vector;
using std::shared_ptr;
using std::make_shared;

class Function
{
public:
	Function() {};
	Function(string name) :m_name(std::move(name)) {};
	const string &getName()const { return m_name; }
	virtual const double getCalc() = 0;
	virtual const string getDimens() = 0;
protected:
	string m_name;
};