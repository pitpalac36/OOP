#pragma once
#include <string>
#include <vector>
#include "Carte.h"

/*
  Scrie in format CSV in fisier cartile din vector
  arunca exceptie daca nu poate crea fisierul
*/
void exportToCSV(const std::string& fisier, const std::vector<Carte>& carti);


/*
  Scrie in format HTML in fisier cartile din vector
  arunca exceptie daca nu poate crea fisierul
*/
void exportToHTML(const std::string& fisier, const std::vector<Carte>& carti);