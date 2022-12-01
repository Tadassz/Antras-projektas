#include "headeriai.h"
#include "struktura.h"
#include "laikas.h"

int main() {

  cout<<"Ar norite atlikti programos veikimo spartos testa? Iveskite t/n:"<<endl;
  string testavimas = AtsakymoIvedimas();
  if (testavimas == "t")
  {
    cout<<"Su kokiu konteineriu norite atlikti si testa?"<<endl;
    cout<<"\n0 - vektorius\n1 - list'as\n2 - atsaukti testa"<<endl;
    cout<<"Iveskite sveikaji skaiciu nuo 0 iki 2:"<<endl;
    int pasirinkimas = IvedimasIntervale(0, 2, false);
    PasirinktasTestas(pasirinkimas);
    if (pasirinkimas != 2) exit(1);
  }

  //vektoriuje bus saugomi studentai
  vector <Studentas>studentai;
  //rezervuojam vektoriui vietos spartesniam darbui
  studentai.reserve(1024);

  string DuomFailas = "kursiokai.txt";
  bool ArReikiaIvesti = true;

    if (ArEgzistuoja(DuomFailas))
    {
      cout<<"Ar noretumete studentu duomenis nuskaityti is failo 'kursiokai.txt'? Iveskite t/n:"<<endl;
      string ArNuskaityti = AtsakymoIvedimas();
      if (ArNuskaityti == "t")
      {
        NuskaitykDuomenis(DuomFailas, studentai, ArReikiaIvesti);

        std::sort(studentai.begin(),studentai.end(), PagalVardus);
      }
      else cout<<"Tuomet iveskite visus duomenis ranka: "<<endl<<endl;
    }
    if (ArReikiaIvesti)
    {
      string KitasStudentas; //tikrinimui, ar yra kitas studentas
      string kiekNd; //tikrinimui, ar namu darbu pazymiu skaicius zinomas
      string ArGeneruoti; //ar generuoti atsitiktini skaiciu

      do
      {
        Studentas s; //cia bus saugomi studento duomenys, pabaigoj bus pushinami i studentu vektoriu

        cout<<"Iveskite studento varda: "<<endl;
        cin>>s.vardas;

        cout<<"Iveskite studento pavarde: "<<endl;
        cin>>s.pavarde;

        cout<<"Ar sugeneruoti studento namu darbu pazymius ir egzamino rezultata? Iveskite t/n:"<<endl;
        ArGeneruoti = AtsakymoIvedimas();

        if (ArGeneruoti == "t")
        {
          GeneruokPazymius(s);
          cout<<"Egzamino pazymys: "<<s.egzaminas<<endl<<"Pazymiu skaicius: "<<s.pazymiuSk<<endl<<"Pazymiai: ";
          for (int i = 0; i<s.pazymiuSk; i++)
          {
            cout<<s.pazymiai[i]<<endl;
          }
          cout<<endl;
        }
        else
        {
          cout<<"Iveskite studento egzamino rezultata (sveikaji skaiciu nuo 0 iki 10): "<<endl;
          s.egzaminas=IvedimasIntervale(0,10,false);

          cout<<"Ar zinomas namu darbu pazymiu skaicius? Iveskite t/n:"<<endl;
          kiekNd = AtsakymoIvedimas();

          if (kiekNd == "t")
          {
            cout<<"Iveskite, kiek namu darbu pazymiu turi studentas (sveikaji skaiciu nuo 0 iki 40): "<<endl;
            s.pazymiuSk=IvedimasIntervale(0,40,false);

            if (s.pazymiuSk!=0)
            {
              cout<<"Iveskite namu darbu pazymius (sveikuosius skaicius nuo 0 iki 10): "<<endl;

              for (int i=0; i<s.pazymiuSk; i++)
              {
                s.pazymiai.push_back(IvedimasIntervale(0,10,false));
              }
            }
          }
          else
          {
            cout<<"Iveskite namu darbu pazymius (jei ivedete visus pazymius, iveskite -1):"<<endl;
            int ivestis; //laikinas kintamasis ivesciai patikrinti
            do
            {
              ivestis = IvedimasIntervale(0,10,true);
              if (ivestis!=-1)
              {
                s.pazymiai.push_back(ivestis);
              }
              else break;
            } while (ivestis!=-1 || ivestis > 10);
            s.pazymiuSk = s.pazymiai.size();
          }
        }
        try{
          s.ndVid = RaskVidurki(s.pazymiai, s.pazymiuSk);
          s.galutinis = GalutinisBalas(s.ndVid, s.egzaminas);

          s.mediana = RaskMediana(s.pazymiai, s.pazymiuSk);
          s.galutinisMed = GalutinisBalas(s.mediana, s.egzaminas);

          cout<<"Ar bus daugiau studentu? Iveskite t/n: "<<endl;
          KitasStudentas = AtsakymoIvedimas();
          studentai.push_back(s);
        }
        catch (std::domain_error klaida)
        {
          cout<<klaida.what();
        }
      } while(KitasStudentas == "t");
    }

    //Isvedimas kai duomenys ivedami ranka/nuskaitomi is failo
    if (ArReikiaIvesti) DuomIsvedimas(studentai, false);
    else DuomIsvedimas (studentai, true);

    return 0;
  }
