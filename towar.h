#ifndef _TOWAR_H_
#define _TOWAR_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "log.h"

using namespace std;

struct artykul{
    string nazwa;
    string kategoria;
    int ilosc;
    float cena;
    };

void wczytajTowary(artykul *tab, int *n, string plik);
void wypiszTowary(artykul *tab, int n);
int dodajTowar(artykul *tab, int *n, artykul nowy);
void zapiszTowary(artykul *tab, int n, string plik);

void zapiszTowary(artykul *tab, int n, string plik){
    ofstream plikZapis;
    plikZapis.open(plik);
    for(int i=0; i<n; i++){
            if(tab[i].nazwa.empty()) break;
        plikZapis<<tab[i].nazwa<<","<<tab[i].kategoria<<","<<tab[i].ilosc<<","<<tab[i].cena<<"\n";
    }
    logInfo("zapisano plik: " + plik);
    plikZapis.close();
}

int dodajTowar(artykul *tab, int *n, artykul nowy){
    logInfo("dodano towar: " + nowy.nazwa);
    bool flaga=false;
    //cout<<*n<<endl;
    for(int i=0; i<*n; i++){
            //cout<<"probuje dodac "<<nowy.nazwa<<" porownuje z "<<tab[i].nazwa<<endl;
        if(!tab[i].nazwa.compare(nowy.nazwa)){
            tab[i].cena=nowy.cena;
            tab[i].ilosc+=nowy.ilosc;
            flaga=true;
            break;
        }
    }
    if(flaga==false){
        tab[*n]=nowy;
    }
    zapiszTowary(tab, *n, "data.bin");
    return *n=(*n)+1;
}

void wypiszTowary(artykul *tab, int n){
    //int el=sizeof(tab)/sizeof(artykul);
    //cout<<el<<endl;
    logInfo("wypisz towary");
    cout<<fixed;
    cout<<"L.p."<<"\t"<<"Nazwa"<<"\t"<<"Kategoria"<<"\t"<<"Ilosc"<<"\t"<<"Cena"<<endl;
    for(int i=0;i<n;i++)
        {   if(tab[i].nazwa.empty()) break;
            cout<<i<<"\t"<<tab[i].nazwa<<"\t"<<tab[i].kategoria<<"\t"<<tab[i].ilosc<<"\t"<<tab[i].cena<<endl;}
    cout<<endl;
}

void wczytajTowary(artykul *tab, int *n, string plik){
    fstream plikOdczyt;
    logInfo("wczytano towary z: " + plik);
    plikOdczyt.open(plik, ios::in| ios::app);
    cout<<setprecision(2);
    cout<<fixed;
    if (plikOdczyt.good())
    {
		int i=0;
		string liniaTekstu;
        while (!plikOdczyt.eof())
        {
			if(!getline(plikOdczyt, liniaTekstu)) break;
			istringstream ss( liniaTekstu );
			string ilosc, cena;

                getline( ss, tab[i].nazwa, ',' );
                getline( ss, tab[i].kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                tab[i].ilosc=stoi(ilosc);
                tab[i].cena=stod(cena);
            if (plikOdczyt.eof()) break;
            i++;
        }
        *n=i;
        plikOdczyt.close();
      }
      else cout <<"brak pliku"<<endl;
}


#endif // _TOWAR_H_

