#include "headeriai.h"
#include "struktura.h"
#include "laikas.h"
#include "generavimas.h"

bool Lygink_5(Studentas s1)
{
  return s1.getGalutinis() == 5;
}


//konteineriu rusiavimui
template <class kont>
void KontRusiavimas(kont &studentai)
{
  sort(studentai.begin(), studentai.end());
}

template <>
void KontRusiavimas(list<Studentas> &studentai)
{
  studentai.sort();
}

template void KontRusiavimas(vector<Studentas> &studentai);

//funkcija simboliu isvalymui, kai irasytas netinkamas simbolis
void NeteisingasIvedimas()
{
  cin.clear();
  cin.ignore(10000, '\n'); //"isvalo" paskutinius 10000 simboliu - kazin ar vartotojas prirasys daugiau nei tiek
}

//tikrinimui, ar ivesti vien skaitmenys
bool ArVienSkaiciai(const string s)
{
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

//tikrinimui, ar egzistuoja failas
bool ArEgzistuoja (string DuomFailas)
{
  ifstream failas(DuomFailas);
  bool ArEgzistuoja = failas.good();
  return ArEgzistuoja;
}

//tikrinimui, ar ivesta t/n
string AtsakymoIvedimas()
{
  string TaipNe;
  do
  {
    cin>>TaipNe;
    if (TaipNe!="t" && TaipNe!="n")
      {
        cout<<"Iveskite is naujo."<<endl;
      }
  } while (TaipNe!="t" && TaipNe!="n");
  return TaipNe;
}

//funkcija tikrinimui ar ivestas skaicius priklauso tam tikram (reikalingui intervalui)
int IvedimasIntervale(int pradzia, int pabaiga, bool Breakinimui) //bool kintamasis tam kad zinociau ar reikia breakint po -1 irasymo
{
  string ivestis; //tikrinimui, ar ivestas skaicius
  bool ArSkaicius;

  int skaicius=-1;

  while (skaicius < pradzia || skaicius > pabaiga)
  {
    cin>>ivestis;
    if (ivestis == "-1" && Breakinimui) return -1;
    else
    {
      ArSkaicius = ArVienSkaiciai(ivestis);
      if(ArSkaicius) skaicius = std::stoi(ivestis);
    }
    if (skaicius == -1 || skaicius > pabaiga) cout<<"Iveskite skaiciu is naujo."<<endl;
  }
  return skaicius;
}

//generavimo klases konstruktorius
AtsitiktinisSk::AtsitiktinisSk() : mt{rd()} {}

//skaièiaus generavimas
int AtsitiktinisSk::Skaicius(int pradzia, int pabaiga) {
    std::uniform_int_distribution<int> uid(pradzia, pabaiga);
    return uid(mt);
}

//funkcija vidurkiui apskaiciuoti
double RaskVidurki(int pazymiuSk, vector<int> pazymiai)
{
  double vidurkis=0;
  double suma; //pazymiu suma (double, kadangi reikes dalint)
  for (int i=0;i<pazymiuSk;i++)
  {
    suma = suma + pazymiai.at(i);
  }
  if (pazymiuSk!=0)
  {
    vidurkis = suma / pazymiuSk;
  }
  return vidurkis;
}

//funkcija medianai apskaiciuoti
double RaskMediana(int pazymiuSk, vector<int> pazymiai)
{
  int temp;
  double mediana=0;

  //rusiavimas
  KontRusiavimas(pazymiai);

  if (pazymiuSk!=0)
  {
    if (pazymiuSk % 2 == 1)
    {
      mediana = pazymiai[pazymiuSk/2];
    }
    else mediana = (pazymiai[pazymiuSk/2] + pazymiai[pazymiuSk/2-1])/2;
  }
  return mediana;
}

//funkcija duomenu nuskaitymui is failo
template <class kont>
void NuskaitykDuomenis(string DuomFailas, kont &studentai, bool &ArReikiaIvesti)
{
  ifstream failas(DuomFailas);
  if (failas.is_open())
  {
    ArReikiaIvesti = false;
    string eilute;
    getline(failas,eilute); //pirma eilute nereikalinga

    while (getline(failas,eilute))
    {
      istringstream ivedimas(eilute);

      Studentas s; //cia bus saugomi studento duomenys, pabaigoj bus pushinami i studentu vektoriu

      s.NuskaitykStudenta(ivedimas);

      studentai.push_back(s);
    }
    failas.close();
    cout<<"Duomenys nuskaityti."<<endl;
  }
  else if (ArReikiaIvesti)
  {
    cout<<"Nepavyko nuskaityti duomenu."<<endl;
    cout<<"Ar norite ranka ivesti duomenis? (t - ivesti duomenis, n - uzbaigti programos darba) Iveskite t/n:"<<endl;
    string ProgramosTesinys = AtsakymoIvedimas();
    if (ProgramosTesinys == "n") exit(1);
  }
  else throw std::runtime_error("Nepavyko atidaryti failo");
}
template void NuskaitykDuomenis(string DuomFailas, vector <Studentas> &studentai, bool &ArReikiaIvesti);
template void NuskaitykDuomenis(string DuomFailas, list <Studentas> &studentai, bool &ArReikiaIvesti);

//funkcija rusiavimui pagal vardus (jei vardai sutampa, tai pagal pavardes)
bool PagalVardus(Studentas s1, Studentas s2)
{
  if (s1.getVardas() < s2.getVardas()) return true;
  else if (s1.getVardas() == s2.getVardas() && s1.getPavarde() < s2.getPavarde()) return true;
  else return false;
}

//funkcija duomenu isvedimui i faila
template <class kont>
void DuomenuIsvedimasFaile (kont studentai, string failas)
{
  ostringstream Isvedimas;
  Isvedimas<<"Vardas          Pavarde            Galutinis (Vid.)    Galutinis (Med.)\n";
  Isvedimas<<"-----------------------------------------------------------------------\n";
  typename kont::iterator it = studentai.begin();
  for (int i = 0; i<studentai.size();i++)
  {
    Isvedimas<<left<<setw(16)<<(*it).getVardas()<<setw(19)<<(*it).getPavarde()<<setw(20)<<setprecision(3)  <<(*it).getGalutinis()<<setprecision(3)<<(*it).getGalutinisMed()<<endl;
    it++;
  }
  std::ofstream Rezultatas(failas);
  Rezultatas<<Isvedimas.str();
  Rezultatas.close();
  cout<<"Duomenys isvesti i faila '"<<failas<<"'."<<endl;
}

//funkcija duomenu isvedimui i ekrana
template <class kont>
void IprastinisDuomIsvedimas (kont studentai)
{
  KontRusiavimas(studentai);
  cout<<left<<setw(16)<<"Vardas"<<setw(19)<<"Pavarde"<<setw(20)<<"Galutinis (Vid.)"<<"Galutinis (Med.)"<<endl;

  cout<<"-------------------------------------------------------------------------"<<endl;

  typename kont::iterator it = studentai.begin();
  for (int i = 0; i<studentai.size();i++)
  {
    cout<<left<<setw(16)<<(*it).getVardas()<<setw(19)<<(*it).getPavarde()<<setw(20)<<setprecision(3)  <<(*it).getGalutinis()<<setprecision(3)<<(*it).getGalutinisMed()<<endl;
    it++;
  }
}

template <class kont>
void DuomIsvedimas(kont studentai, bool ArFailas, string failas)
{
  if (studentai.size()!=0)
  {
    if (ArFailas) DuomenuIsvedimasFaile(studentai, failas);
    else IprastinisDuomIsvedimas(studentai);
  }
}
template void DuomIsvedimas(vector<Studentas> studentai, bool ArFailas, string failas);
template void DuomIsvedimas(list<Studentas> studentai, bool ArFailas, string failas);

//failu generavimo funkcija
void GeneruokFaila(int dydis)
{
  Studentas s;

  ostringstream duomenys;
  duomenys<<left<<setw(16)<<"Vardas"<<setw(25)<<"Pavarde"<<endl;

  for (int i = 1; i <= dydis; i++)
  {
    s.IsvalykPazymius();
    s.setVardas("Vardas"+to_string(i));
    s.setPavarde("Pavarde"+to_string(i));

    duomenys<<left<<setw(16)<<s.getVardas()<<setw(25)<<s.getPavarde();

    s.GeneruokPazymius();
    for (int j = 0; j<s.getPazymiuSk();j++)
    {
      duomenys<<left<<setw(4)<<s.getPazymys(j);
    }
    duomenys<<setw(4)<<s.getEgzaminas()<<endl;
  }

  string DuomFailas = "Sugeneruotas" + to_string(dydis) + ".txt";
  std::ofstream Isvedimas(DuomFailas);
  Isvedimas<<duomenys.str();
  Isvedimas.close();
  cout<<"Sugeneruotas "<<dydis<<" dydzio failas."<<endl;
}

template <class kont>
void ProgramosSparta(kont studentai, string konteineris)
{
  cout<<"\nKokia strategija norite naudoti rusiavimui?"<<endl;
  cout<<"0 - Studentai ikeliami i du naujus konteinerius (blogieciai/gerieciai)\n1 - Studentai ikeliami tik i blogieciu konteineri, gerieciai paliekami studentu konteineryje"<<endl;
  cout<<"Iveskite 0 arba 1:"<<endl;
  int Rusiavimui = IvedimasIntervale(0,1,false);

  double visasLaikas; //galutiniam testo laikui pateikti
  bool temp=false; //kintamasis kad veiktu funkcija
  string rezFailas; //isvedimui gerieciu/blogieciu
  string ProgramosTesinys; //tikrinimui, ar vartotojas nori pratesti testa
  LaikoMatavimas laikas;
  for (int i = 1000; i<=10000000; i*=10)
  {
    visasLaikas = 0;
    cout<<"\nProgramos veikimo spartos testas su "<<i<<" studentu pradetas.\n"<<endl;

    laikas.reset();

    //failo generavimas
    string DuomFailas="Sugeneruotas"+to_string(i)+".txt";
    ifstream f(DuomFailas);
    if (!f.good())
    {
      GeneruokFaila(i);
      cout<<i<<" studentu failo generavimas uztruko "<<laikas.elapsed()<<" s."<<endl;
      visasLaikas+=laikas.elapsed();
    }
    laikas.reset();
    //failo generavimas

    //failo nuskaitymas
    NuskaitykDuomenis(DuomFailas, studentai, temp);
    cout<<"Duomenu ("<<i<<" studentu) nuskaitymas is failo uztruko "<<laikas.elapsed()<<" s."<<endl;
    visasLaikas+=laikas.elapsed();
    laikas.reset();
    //failo nuskaitymas

    //studentu rusiavimas i dvi grupes
    KontRusiavimas(studentai);
    auto it = find_if(studentai.begin(),studentai.end(),Lygink_5);
    //studentu rusiavimas i dvi grupes
    kont blogieciai;
    kont gerieciai;
    //studentu skaidymas pagal 1-a strategija (i du naujus konteinerius)
    if (!Rusiavimui)
    {
      blogieciai.assign(studentai.begin(),it);
      gerieciai.assign(it,studentai.end());
    }
    else //studentu skaicymas pagal 2-a strategija (perkeliami tik blogieciai)
    {
      blogieciai.assign(studentai.begin(),it);
      studentai.erase(studentai.begin(),it);
    }
    cout<<i<<" studentu rusiavimas uztruko "<<laikas.elapsed()<<" s."<<endl;
    visasLaikas+=laikas.elapsed();
    laikas.reset();


    //"gerieciu" isvedimas i faila
    rezFailas = "rez_gerieciai"+to_string(i)+konteineris+".txt";
    if(Rusiavimui) DuomIsvedimas(studentai, true, rezFailas);
    else DuomIsvedimas(gerieciai, true, rezFailas);
    cout<<i<<" studentu (gerieciu) isvedimas i faila '"<<rezFailas<<"' uztruko "<<laikas.elapsed()<<" s."<<endl;
    visasLaikas+=laikas.elapsed();
    laikas.reset();
    //"gerieciu" isvedimas i faila

    //"blogieciu" isvedimas i faila
    rezFailas = "rez_blogieciai"+to_string(i)+konteineris+".txt";
    DuomIsvedimas(blogieciai, true, rezFailas);
    cout<<i<<" studentu (blogieciu) isvedimas i faila '"<<rezFailas<<"' uztruko "<<laikas.elapsed()<<" s."<<endl<<endl;
    visasLaikas+=laikas.elapsed();
    //"blogieciu" isvedimas i faila

    //viso testo laiko Isvedimas
    cout<<i<<" irasu testas uztruko "<<visasLaikas<<" s."<<endl<<endl;
    //viso testo laiko Isvedimas

    if (i!=10000000)
    {
      int a = i*10;
      cout<<"Ar norite toliau testuoti (kitas testas - su "<<a<<" irasu)? Iveskite t/n: "<<endl;
      ProgramosTesinys = AtsakymoIvedimas();
      if (ProgramosTesinys=="n")
      {
        blogieciai.clear();
        gerieciai.clear();
        studentai.clear();
        cout<<"Programos darbas baigtas."<<endl;
        break;
      }
      else
      {
        studentai.clear();
        blogieciai.clear();
        gerieciai.clear();
      }
    }
  }
}

template void ProgramosSparta(vector<Studentas> studentai, string konteineris);
template void ProgramosSparta(list<Studentas> studentai, string konteineris);

//funkcija, kuri iskviecia atitinkamas benchmarkinimo funkcijas
void PasirinktasTestas(int n)
{
  if (n == 0) ProgramosSparta(vector <Studentas> (), "vector");
  else if (n == 1) ProgramosSparta(list <Studentas> (), "list");
  else cout<<"Atsaukiamas programos testavimas."<<endl;
}
