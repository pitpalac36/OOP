#include "fileUtils.h"
#include <fstream>
#include "ServiceException.h"


void exportToCSV(const std::string& fisier, const std::vector<Carte>& carti) {
	std::ofstream out("cos\\" + fisier + ".csv", std::ios::trunc);
	//if (!out.is_open()) {
		//throw ServiceException("Nu se poate deschide fisierul " + fisier);
	//}
	for (const auto& c : carti) {
		out << c.getTitlu() << ",";
		out << c.getAutor() << ",";
		out << c.getGen() << ",";
		out << c.getAn() << std::endl;
	}
	out.close();
}

void exportToHTML(const std::string& fisier, const std::vector<Carte>& carti) {
	std::ofstream out("cos\\" + fisier + ".html", std::ios::trunc);
	//if (!out.is_open()) {
	//	throw ServiceException("Nu se poate deschide fisierul " + fisier);
	//}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& c : carti) {
		out << "<tr>" << std::endl;
		out << "<td>" << c.getTitlu() << "</td>" << std::endl;
		out << "<td>" << c.getAutor() << "</td>" << std::endl;
		out << "<td>" << c.getGen() << "</td>" << std::endl;
		out << "<td>" << c.getAn() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();
}