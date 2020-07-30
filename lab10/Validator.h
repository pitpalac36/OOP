#pragma once
#include <string>
#include <vector>
#include "Carte.h"
using std::vector;
using std::string;
using std::ostream;

class ValidationException
{
private:
	vector<string> messages;

public:
	ValidationException(const vector<string>& msgs) : messages{ msgs } {}

	vector<string> getMessages() {
		return messages;
	}

	friend ostream& operator<<(ostream& out, const ValidationException& ex);
};

ostream& operator<<(ostream& out, const ValidationException& ex);

class CarteValidator {
public:
	void valideazaCarte(const Carte& c);
};


void testValidator();