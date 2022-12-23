#ifndef STRUKTURA_H_INCLUDED
#define STRUKTURA_H_INCLUDED

#include "headeriai.h"
#include "generavimas.h"
#include "laikas.h"

//bazine klase
class Zmogus
{
  protected:
    string vardas;
    string pavarde;

    Zmogus(string vardas ="", string pavarde="");

    virtual string getVardas() const = 0;
    virtual void setVardas(string vardas) = 0;

    virtual string getPavarde() const = 0;
    virtual void setPavarde(string pavarde) = 0;
};

//isvestine klase
class Studentas : public Zmogus
{
  private:
    string vardas;
    string pavarde;
    int pazymiuSk;
    vector <int> *pazymiai;
    int egzaminas; //egzamino rezultatas
    double galutinis;
    double galutinisMed;
  public:
    //rule of five realizacija

      //konstruktorius/destruktorius
      Studentas();
      ~Studentas();
      //konstruktorius/destruktorius

      Studentas(const Studentas &s); //kopijavimas per konstruktoriu
      Studentas& operator= (const Studentas &s); //kopijavimas per operatoriu

      Studentas (Studentas &&s); //move per konstruktoriu
      Studentas& operator= (Studentas &&s); //move per operatoriu

    //rule of five realizacija

    bool operator < (const Studentas &kitas) { return this->galutinis<kitas.galutinis;} //lyginimo (per galutini bala) operatorius

    Studentas(std::istream& ivedimas); //skaitymui is failo

    string getVardas() const { return vardas; }
    void setVardas(string vardas) { this->vardas = vardas; }

    string getPavarde() const { return pavarde; }
    void setPavarde(string pavarde) { this->pavarde = pavarde; }

    int getEgzaminas() const { return egzaminas; }
    void setEgzaminas(int egzaminas) { this->egzaminas = egzaminas; }

    int getPazymys(int i) const { return (*pazymiai)[i]; }
    int getPazymiuSk() const { return pazymiuSk; }
    void setPazymys(int pazymys) { (*pazymiai).push_back(pazymys); }
    void setPazymiuSk(int pazymiuSk) { this->pazymiuSk = pazymiuSk; }
    void removePazymys() { (*pazymiai).pop_back(); }

    double getGalutinis() const { return galutinis; }
    double getGalutinisMed() const { return galutinisMed; }

    void GeneruokPazymius();
    void IsvalykPazymius();
    void NuskaitykStudenta(std::istringstream& ivedimas);
    void GalutinisBalas(bool vidurkis);
};

#endif
