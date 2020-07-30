#include "Validator.h"
#include <sstream>
#include <cassert>

ostream& operator<<(ostream& out, const ValidationException& ex)
{
	for (const auto& msg : ex.messages)
		out << msg << " ";
	return out;
}


void CarteValidator::valideazaCarte(const Carte& c)
{
	// titlu, autor, gen, an
	std::vector<string> messages;
	if (c.getAutor().size() == 0)
		messages.push_back("Autor invalid!");
	if (c.getTitlu().size() == 0)
		messages.push_back("Titlu invalid!");
	if (c.getGen().size() == 0)
		messages.push_back("Gen invalid!");
	if (!messages.empty())
		throw ValidationException(messages);
}


void testValidator()
{
	CarteValidator v;
	Carte c{ "", "", "", 1900 };
	try {
		v.valideazaCarte(c);
	}
	catch (const ValidationException& ex) {
		std::stringstream sout;
		sout << ex;
		auto mesaj = sout.str();
		assert(mesaj.find("Titlu") >= 0);
		assert(mesaj.find("Gen") >= 0);
		assert(mesaj.find("Autor") >= 0);
	}
}