#pragma once
#include <string>
using namespace std;

class DTO
{
private:
	std::string gen;
	int contor;
public:
	DTO(const string gen, int contor) : gen{gen}, contor{contor}{}

	string getGen() const {
		return gen;
	}

	int getContor() const {
		return contor;
	}

};