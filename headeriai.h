
#ifndef HEADERIAI_H_INCLUDED
#define HEADERIAI_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <exception>
#include <list>
#include <deque>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::setfill;
using std::left;
using std::setprecision;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::to_string;
using std::deque;
using std::list;
using std::find_if;

//atsitiktiniams skaiciams
using std::mt19937;
using Laikas = std::chrono::high_resolution_clock;
typedef std::uniform_int_distribution<int> intDistribution;

struct Studentas;

//funkcijos
template <class kont>
void KontRusiavimas(kont &studentai);

void NeteisingasIvedimas();
bool ArVienSkaiciai(const string s);
bool ArEgzistuoja (string DuomFailas);
string AtsakymoIvedimas();
int IvedimasIntervale(int pradzia, int pabaiga, bool Breakinimui);
double RaskVidurki (vector<int> pazymiai, int pazymiuSk);
double RaskMediana (vector<int> pazymiai, int pazymiuSk);
double GalutinisBalas(double ndRez, int egzaminas);
void GeneruokPazymius(Studentas &s);

bool Lygink_5(Studentas &s1);

template <class kont>
void NuskaitykDuomenis (string DuomFailas, kont &studentai, bool &ArReikiaIvesti);

bool PagalVardus(Studentas s1, Studentas s2);

/*template <class kont>
void DuomenuIsvedimasFaile (kont studentai, string failas);

template <class kont>
void IprastinisDuomIsvedimas (kont studentai);*/
template <class kont>
void DuomIsvedimas(kont studentai, bool ArFailas, string failas = "rez.txt");
void GeneruokFaila(int dydis);

template <class kont>
void ProgramosSparta(kont studentai, string konteineris);

void PasirinktasTestas(int n);

#endif
