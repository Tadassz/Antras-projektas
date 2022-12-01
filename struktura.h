#ifndef STRUKTURA_H_INCLUDED
#define STRUKTURA_H_INCLUDED

#include "headeriai.h"
#include "generavimas.h"
#include "laikas.h"

class Studentas
{
  private:
    string vardas;
    string pavarde;
    int pazymiuSk;
    vector <int>pazymiai;
    int egzaminas; //egzamino rezultatas
    double galutinis;
    double galutinisMed;
  public:
    Studentas() : egzaminas{0} {};
    Studentas(std::istream& ivedimas); //skaitymui is failo

    string getVardas() const { return vardas; }
    void setVardas(string vardas) { this->vardas = vardas; }

    string getPavarde() const { return pavarde; }
    void setPavarde(string pavarde) { this->pavarde = pavarde; }

    int getEgzaminas() const { return egzaminas; }
    void setEgzaminas(int egzaminas) { this->egzaminas = egzaminas; }

    int getPazymys(int i) const { return pazymiai[i]; }
    int getPazymiuSk() const { return pazymiuSk; }
    void setPazymys(int pazymys) { pazymiai.push_back(pazymys); }
    void setPazymiuSk(int pazymiuSk) { this->pazymiuSk = pazymiuSk; }
    void removePazymys() { pazymiai.pop_back(); }

    double getGalutinis() const { return galutinis; }
    double getGalutinisMed() const { return galutinisMed; }

    void GeneruokPazymius();
    void IsvalykPazymius();
    void NuskaitykStudenta(std::istringstream& ivedimas);
    void GalutinisBalas(bool vidurkis);

    bool operator < (const Studentas &kitas) { return this->galutinis<kitas.galutinis;}
};

#endif
