#ifndef _TOWAR_H_
#define _TOWAR_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "log.h"
#include "miejsce.h"

using namespace std;

struct artykul{
    char nazwa[30];
    char kategoria[20];
    int ilosc;
    float cena;
    miejsce miejsce;
    };

void wczytajTowary(artykul *tab, int *n, string plik);
void wypiszTowary(artykul *tab, int n);
int dodajTowar(artykul *tab, int *n, artykul nowy);
void zapiszTowary(artykul *tab, int n, string plik);

void zapiszTowary(artykul *tab, int n, string plik){
    ofstream plikZapis;
    plikZapis.open(plik);
    for(int i=0; i<n; i++){
            if(strlen(tab[i].nazwa)==0) break;
        plikZapis<<tab[i].nazwa<<","<<tab[i].kategoria<<","<<tab[i].ilosc<<","<<tab[i].cena<<"\n";
    }
    logInfo("zapisano plik: " + plik);
    plikZapis.close();
}

int dodajTowar(artykul *tab, int *n, artykul nowy){
    string nazwa=nowy.nazwa;
    logInfo("dodano towar: " + nazwa);
    bool flaga=false;
    //cout<<*n<<endl;
    for(int i=0; i<*n; i++){
        if(strcmp(tab[i].nazwa, nowy.nazwa)==0){
            tab[i].cena=nowy.cena;
            tab[i].ilosc+=nowy.ilosc;
            flaga=true;

            break;
        }
    }
    if(flaga==false)
        {
        cout<<flaga<<endl;
        strcpy(tab[*n].nazwa, nowy.nazwa);
        strcpy(tab[*n].kategoria, nowy.kategoria);
        tab[*n].ilosc=nowy.ilosc;
        tab[*n].cena=nowy.cena;
        //tab[*n].miejsce, nowy.miejsce);
        *n=(*n)+1;

    }
        //cout<<tab[*n].nazwa<<","<<tab[*n].kategoria<<","<<tab[*n].ilosc<<","<<tab[*n].cena<<"\n";
    zapiszTowary(tab, *n, "data.bin");
    return *n;
}

void wypiszTowary(artykul *tab, int n){
    //logInfo("wypisz towary");
    cout<<fixed;
    cout<<"L.p."<<"\t"<<"Nazwa"<<"\t"<<"Kategoria"<<"\t"<<"Ilosc"<<"\t"<<"Cena"<<endl;
    for(int i=0;i<n;i++)
        {   if(strlen(tab[i].nazwa)==0) break;
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
			string ilosc, cena, nazwa, kategoria;

                getline( ss, nazwa, ',' );
                getline( ss, kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                strcpy(tab[i].nazwa, nazwa.c_str());
                strcpy(tab[i].kategoria, kategoria.c_str());
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

