#include "struktura.h"

//funkcija atsitiktiniams pazymiams (ir ju skaiciui) generuoti
void Studentas::GeneruokPazymius() //pradzia/pabaiga - intervalo reziai
{
  AtsitiktinisSk generuok;

  egzaminas = generuok.Skaicius(0,10);
  pazymiuSk = generuok.Skaicius(0,20);
  for (int i = 0; i < pazymiuSk; i++)
  {
    pazymiai.push_back(generuok.Skaicius(0,10));
  }
}

void Studentas::IsvalykPazymius()
{
    pazymiai.clear();
}

void Studentas::NuskaitykStudenta(std::istringstream& ivedimas)
{
  ivedimas>>vardas;
  ivedimas>>pavarde;

  pazymiai.clear();
  string ivestasSk; //tikrinimui, ar ivestas tinkamas skaicius
  int pazymys=0;
  while (ivedimas>>ivestasSk)
  {
    if (ArVienSkaiciai(ivestasSk))
    {
      pazymys = std::stoi(ivestasSk);
      if((pazymys>=0)&&(pazymys<=10)) pazymiai.push_back(pazymys);
    }
  }
  egzaminas = pazymys;
  pazymiai.pop_back();

  pazymiuSk = pazymiai.size();

  GalutinisBalas(true);
  GalutinisBalas(false);
}

//funkcija galutiniam balui apskaiciuoti
void Studentas::GalutinisBalas(bool vidurkis)
{
  double ndRez;
  if (vidurkis)
  {
    ndRez = RaskVidurki(pazymiuSk, pazymiai);
    galutinis = 0.4 * ndRez + 0.6 * egzaminas;
  }
  else
  {
    ndRez = RaskMediana(pazymiuSk, pazymiai);
    galutinisMed = 0.4 * ndRez + 0.6 * egzaminas;
  }
}
