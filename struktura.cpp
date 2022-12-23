#include "struktura.h"

Zmogus::Zmogus(string vardas, string pavarde) : vardas{vardas}, pavarde{pavarde} {}

//-------------------------------------------------
//rule of five realizacija

//konstruktorius/destruktorius
Studentas::Studentas() : egzaminas{0}, pazymiai{ new vector<int> } {}
Studentas::~Studentas() { delete pazymiai; }
//konstruktorius/destruktorius

//kopijavimas per konstruktoriu
Studentas::Studentas(const Studentas &s) :
  Zmogus{s.vardas, s.pavarde},
  pazymiuSk{s.pazymiuSk},
  pazymiai{ new vector<int>(*(s.pazymiai)) },
  egzaminas{s.egzaminas},
  galutinis{s.galutinis},
  galutinisMed{s.galutinisMed}
{}
//kopijavimas per konstruktoriu

//kopijavimas per operatoriu
Studentas& Studentas::operator= (const Studentas &s)
{
  //saves priskyrimo aptikimas
  if(&s==this) return *this;

  vardas = s.vardas;
  pavarde = s.pavarde;
  pazymiuSk = s.pazymiuSk;
  vector<int> *temp = new vector<int>(*(s.pazymiai));
  pazymiai = temp;
  egzaminas = s.egzaminas;
  galutinis = s.galutinis;
  galutinisMed = s.galutinisMed;

  return *this;
}
//kopijavimas per operatoriu

//move per konstruktoriu
Studentas::Studentas (Studentas &&s) :
  Zmogus{move(s.vardas), move(s.pavarde)},
  pazymiuSk{move(s.pazymiuSk)},
  pazymiai{move(s.pazymiai)},
  egzaminas{move(s.egzaminas)},
  galutinis{move(s.galutinis)},
  galutinisMed{move(s.galutinisMed)}
  {
    s.pazymiuSk = 0;
    s.pazymiai = nullptr;
    s.egzaminas = 0;
    s.galutinis = 0;
    s.galutinisMed = 0;
  }
//move per konstruktoriu

//move per operatoriu
Studentas& Studentas::operator= (Studentas &&s)
{
  //saves priskyrimo aptikimas
  if(&s==this) return *this;

  vardas = move(s.vardas);
  pavarde = move(s.pavarde);
  pazymiuSk = move(s.pazymiuSk);
  delete pazymiai;
  pazymiai = move(s.pazymiai);
  egzaminas = move(s.egzaminas);
  galutinis = move(s.galutinis);
  galutinisMed = move(s.galutinisMed);

  s.pazymiuSk = 0;
  s.pazymiai = nullptr;
  s.egzaminas = 0;
  s.galutinis = 0;
  s.galutinisMed = 0;

  return *this;
}
//move per operatoriu

//rule of five realizacija
//-------------------------------------------------
//member funkcijos

//funkcija atsitiktiniams pazymiams (ir ju skaiciui) generuoti
void Studentas::GeneruokPazymius() //pradzia/pabaiga - intervalo reziai
{
  AtsitiktinisSk generuok;

  egzaminas = generuok.Skaicius(0,10);
  pazymiuSk = generuok.Skaicius(0,20);
  for (int i = 0; i < pazymiuSk; i++)
  {
    (*pazymiai).push_back(generuok.Skaicius(0,10));
  }
}

void Studentas::IsvalykPazymius()
{
  (*pazymiai).clear();
}

//funkcija studentui (vienam) nuskaityti
void Studentas::NuskaitykStudenta(std::istringstream& ivedimas)
{
  ivedimas>>vardas;
  ivedimas>>pavarde;

  IsvalykPazymius();
  string ivestasSk; //tikrinimui, ar ivestas tinkamas skaicius
  int pazymys=0;
  while (ivedimas>>ivestasSk)
  {
    if (ArVienSkaiciai(ivestasSk))
    {
      pazymys = std::stoi(ivestasSk);
      if((pazymys>=0)&&(pazymys<=10)) (*pazymiai).push_back(pazymys);
    }
  }
  egzaminas = pazymys;
  (*pazymiai).pop_back();

  pazymiuSk = (*pazymiai).size();

  GalutinisBalas(true);
  GalutinisBalas(false);
}

//funkcija galutiniam balui apskaiciuoti
void Studentas::GalutinisBalas(bool vidurkis)
{
  double ndRez;
  if (vidurkis)
  {
    ndRez = RaskVidurki(pazymiuSk, (*pazymiai));
    galutinis = 0.4 * ndRez + 0.6 * egzaminas;
  }
  else
  {
    ndRez = RaskMediana(pazymiuSk, (*pazymiai));
    galutinisMed = 0.4 * ndRez + 0.6 * egzaminas;
  }
}
