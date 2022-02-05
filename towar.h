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
        plikZapis<<tab[i].nazwa<<","<<tab[i].kategoria<<","<<tab[i].ilosc<<","<<tab[i].cena<<","<<tab[i].miejsce.ID<<","<<tab[i].miejsce.maxIlosc<<"\n";
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
                if(tab[i].miejsce.maxIlosc>nowy.ilosc+tab[i].ilosc)
                    {tab[i].cena=nowy.cena;
                    tab[i].ilosc+=nowy.ilosc;
                    flaga=true;
                    }
                    else{
                        strcpy(tab[*n].nazwa, nowy.nazwa);
                        strcpy(tab[*n].kategoria, nowy.kategoria);
                        tab[*n].ilosc=nowy.ilosc;
                        tab[*n].cena=nowy.cena;
                        strcpy(tab[*n].miejsce.ID, generujNoweID().c_str());
                        tab[*n].miejsce.maxIlosc=nowy.miejsce.maxIlosc;
                        *n=(*n)+1;
                        flaga=true;
                    }
                    break;
        }
    }
    if(flaga==false)
        {
        //cout<<flaga<<endl;
        strcpy(tab[*n].nazwa, nowy.nazwa);
        strcpy(tab[*n].kategoria, nowy.kategoria);
        tab[*n].ilosc=nowy.ilosc;
        tab[*n].cena=nowy.cena;
        strcpy(tab[*n].miejsce.ID, nowy.miejsce.ID);
        tab[*n].miejsce.maxIlosc=nowy.miejsce.maxIlosc;
        *n=(*n)+1;

    }
    zapiszTowary(tab, *n, "data.bin");
    return *n;
}

void wypiszTowary(artykul *tab, int n){
    cout<<fixed;
    cout<<"L.p."<<"\tMiejsce\t"<<"\t"<<"Nazwa"<<"\t"<<"Kategoria"<<"\t"<<"Ilosc"<<"\t"<<"Cena"<<endl;
    for(int i=0;i<n;i++)
        {   if(strlen(tab[i].nazwa)==0) break;
            cout<<i<<"\t"<<tab[i].miejsce.ID<<"\t"<<tab[i].nazwa<<"\t"<<tab[i].kategoria<<"\t"<<tab[i].ilosc<<"\t"<<tab[i].cena<<endl;}
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
			string ilosc, cena, nazwa, kategoria, miejsce;

                getline( ss, nazwa, ',' );
                getline( ss, kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                strcpy(tab[i].nazwa, nazwa.c_str());
                strcpy(tab[i].kategoria, kategoria.c_str());
                getline(ss, miejsce, ',');
                tab[i].ilosc=stoi(ilosc);
                tab[i].cena=stod(cena);
                strcpy(tab[i].miejsce.ID, miejsce.c_str());
            if (plikOdczyt.eof()) break;
            i++;
        }
        *n=i;
        plikOdczyt.close();
      }
      else cout <<"brak pliku"<<endl;
      //zapisz miejsca odkladcze
    ofstream plikMiejsca;
    plikMiejsca.open("miejsca.dat");
    for(int i=0; i<*n; i++){
            if(strlen(tab[i].nazwa)==0) break;
        plikMiejsca<<tab[i].miejsce.ID<<","<<tab[i].miejsce.maxIlosc<<"\n";
    }
    plikMiejsca.close();

}


#endif // _TOWAR_H_

