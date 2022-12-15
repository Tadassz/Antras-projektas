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

      string a; //laikinas stringas vardui, pavardei set-inti

      do
      {
        Studentas s; //cia bus saugomi studento duomenys, pabaigoj bus pushinami i studentu vektoriu

        cout<<"Iveskite studento varda: "<<endl;
        cin>>a;
        s.setVardas(a);

        cout<<"Iveskite studento pavarde: "<<endl;
        cin>>a;
        s.setPavarde(a);

        cout<<"Ar sugeneruoti studento namu darbu pazymius ir egzamino rezultata? Iveskite t/n:"<<endl;
        ArGeneruoti = AtsakymoIvedimas();

        if (ArGeneruoti == "t")
        {
          s.GeneruokPazymius();
          cout<<"Egzamino pazymys: "<<s.getEgzaminas()<<endl<<"Pazymiu skaicius: "<<s.getPazymiuSk()<<endl<<"Pazymiai: ";
          for (int i = 0; i<s.getPazymiuSk(); i++)
          {
            cout<<s.getPazymys(i)<<endl;
          }
          cout<<endl;
        }
        else
        {
          cout<<"Iveskite studento egzamino rezultata (sveikaji skaiciu nuo 0 iki 10): "<<endl;
          s.setEgzaminas(IvedimasIntervale(0,10,false));

          cout<<"Ar zinomas namu darbu pazymiu skaicius? Iveskite t/n:"<<endl;
          kiekNd = AtsakymoIvedimas();

          if (kiekNd == "t")
          {
            cout<<"Iveskite, kiek namu darbu pazymiu turi studentas (sveikaji skaiciu nuo 0 iki 40): "<<endl;
            s.setPazymiuSk(IvedimasIntervale(0,40,false));

            if (s.getPazymiuSk()!=0)
            {
              cout<<"Iveskite namu darbu pazymius (sveikuosius skaicius nuo 0 iki 10): "<<endl;

              for (int i=0; i<s.getPazymiuSk(); i++)
              {
                s.setPazymys(IvedimasIntervale(0,10,false));
              }
            }
          }
          else
          {
            cout<<"Iveskite namu darbu pazymius (jei ivedete visus pazymius, iveskite -1):"<<endl;
            int ivestis; //laikinas kintamasis ivesciai patikrinti
            int kiekis = 0; //kiek pazymiu praejo pro cikla
            do
            {
              ivestis = IvedimasIntervale(0,10,true);
              if (ivestis!=-1)
              {
                s.setPazymys(ivestis);
                kiekis++;
              }
              else break;
            } while (ivestis!=-1 || ivestis > 10);
            s.setPazymiuSk(kiekis);
          }
        }
        try{
          s.GalutinisBalas(true);
          s.GalutinisBalas(false);

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

