#pragma once
#include <string>
using std::string;
#include <ostream>
using std::ostream;

class ServiceException
{
private:
	string msg;
public:
	ServiceException(string m) :msg{ m } {}

	friend ostream& operator<<(ostream& out, const ServiceException& ex);
};

ostream& operator<<(ostream& out, const ServiceException& ex);