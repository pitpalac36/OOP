#pragma once
#include <string>
using std::string;
#include <ostream>
using std::ostream;

class RepoException
{
private:
	string msg;
public:
	RepoException(string m) :msg{ m } {}

	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);