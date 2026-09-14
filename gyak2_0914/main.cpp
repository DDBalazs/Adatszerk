#include "utility.h"
#include <iostream>
using namespace std;

int main() {
  // Ez a program demonstralja a valtozok es a memoria kapcsolatat

  cout << "1. ora 1. demonstracio - Valtozok\n";

  int i = 5; // Valtozo sajat memoriaterulettel
  cout << "Az i memoriacime " << &i << ", tipusa " << type_name<decltype(i)>()
       << " es a memoriaterulet tartalma " << i << "\n";
  int &r = i; // Referencia az elozo valtozora
  cout << "Az r memoriacime " << &r << ", tipusa " << type_name<decltype(r)>()
       << " es a memoriaterulet tartalma " << r << "\n";

  int *p = &i; // Pointer az elozo memoriateruletre
  cout << "A  p memoriacime " << &p << ", tipusa " << type_name<decltype(p)>()
       << " es a memoriaterulet tartalma " << p << "\n";
  cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
       << ", tipusa " << type_name<decltype(*p)>() << " es annak tartalma "
       << (*p) << "\n";

  cout << "Vegyuk eszre, hogy az eredeti valtozo es a referencia ugyanazon a "
          "cimen dolgozik\n";
  cout << "Vegyuk eszre, hogy a pointer altal tarolt cim pontosan az a cim, "
          "ami az i valtozo cime\n";
  cout << "Tovabba, nezzuk meg azt is, hogy a pointer teljesen mas cimen "
          "talalhato\n";

  cout << "---------------------------------------------------\n";
  cout << "Valtoztassuk meg az ertekeket";
  i++;
  cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
       << endl;
  cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
       << endl;
  cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
       << endl;
  cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
       << " es annak tartalma " << (*p) << endl;
  cout << "---------------------------------------------------\n";
  r++;
  cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
       << endl;
  cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
       << endl;
  cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
       << endl;
  cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
       << " es annak tartalma " << (*p) << endl;
  cout << "---------------------------------------------------n";
  (*p)++;
  cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
       << "\n";
  cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
       << "\n";
  cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
       << "\n";
  cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
       << " es annak tartalma " << (*p) << "\n";
  // FIGYELEM!!
  cout << "---------------------------------------------------\n";
  cout << "- MOST JON EGY SZOKASOS HIBA, ELRETTENTO PELDANAK -\n";
  cout << "---------------------------------------------------\n";
  p++; // Itt a memóriacímet változtatjuk meg
  cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
       << "\n";
  cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
       << "\n";
  cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
       << "\n";
  cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
       << " es annak tartalma " << (*p) << "\n";
  cout << "Nezzuk meg, hogy az uj terulet mogotti dolgokat meg lehet-e "
          "valtoztatni!\n";
  cout << "Itt valami teljesen mas tortenik! A memoriateruletet valtoztattuk "
          "meg!\n";
  (*p)++;
  cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
       << "\n";
  cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
       << " es annak tartalma " << (*p) << "\n";
  cout << "Ne feledjuk, c++-ban alapvetoen mindent lehet, kiveve par dolgot "
          "amit tilos!\n";

  return 0;
}