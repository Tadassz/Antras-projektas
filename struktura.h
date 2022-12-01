
#ifndef STRUKTURA_H_INCLUDED
#define STRUKTURA_H_INCLUDED

struct Studentas
{
  string vardas;
  string pavarde;
  int pazymiuSk;
  vector <int>pazymiai;
  double ndVid; //namu darbu vidurkis
  double mediana; //namu darbu mediana
  int egzaminas; //egzamino rezultatas
  double galutinis;
  double galutinisMed;
  bool operator < (const Studentas &kitas) { return this->galutinis<kitas.galutinis;}
};

#endif
