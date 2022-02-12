#pragma once

#ifndef _DOSTAWA_H_
#define _DOSTAWA_H_



#include <iostream>
#include "towar.h"
#include "main.h"

using namespace std;


struct dostawa{
    char nrPZ[10];
    artykul *listaArt;
    int ilosc;
    };

void przyjmijDostawe(artykul *tab_art, int *n_art, string plik); //wczytuje plik z dostawa i dodaje ja na stan
bool sprawdzDostawe();
void wyswietlListeDostaw();

bool sprawdzDostawe(char* nrPZ){ //czy byla wprowadzona
    ifstream plikOdczyt;
    dostawa d[10];
    bool flaga=true;
    plikOdczyt.open("dostawy.bin", ios::binary | ios::in);
    if(plikOdczyt.good()==true){
        int i;
        for(i=0; ;i++){
            plikOdczyt.read(reinterpret_cast<char*>(&d[i]),sizeof(d[i]));
            if(plikOdczyt.eof()) break;
            if(strcmp(d[i].nrPZ, nrPZ)==0)
            {
                flaga=false;
                break;
            }
        }
    }
    plikOdczyt.close();

    return flaga;
}
void wyswietlListeDostaw(){
    ifstream plikOdczyt;
    dostawa d[10];
    //bool flaga=true;
    plikOdczyt.open("dostawy.bin", ios::binary | ios::in);
    if(plikOdczyt.good()==true){
        int i;
        cout<<"Lista dostaw"<<endl;
        for(i=0; ;i++){
            plikOdczyt.read(reinterpret_cast<char*>(&d[i]),sizeof(d[i]));
            if(plikOdczyt.eof()) break;
            cout<<i<<") Nr PZ: "<<d[i].nrPZ<<endl;
        }
    }
    else
        cout<<"Brak dostaw!"<<endl;
    plikOdczyt.close();
}

void przyjmijDostawe(artykul *tab_art, int *n_art, string plik){
    wczytajTowary(tab_art, n_art, "data.bin");
    fstream plikOdczyt;
    dostawa przyjetaDostawa;
    logInfo("wczytano dostawe z: " + plik);
    plikOdczyt.open(plik, ios::in| ios::app);
    cout<<setprecision(2);
    cout<<fixed;
    if (plikOdczyt.good())
    {
        string nrPZ;
        getline(plikOdczyt, nrPZ);
        strcpy(przyjetaDostawa.nrPZ, nrPZ.c_str());
        if(sprawdzDostawe(przyjetaDostawa.nrPZ))
        {
            string PZilosc;
            getline(plikOdczyt, PZilosc);
            przyjetaDostawa.ilosc=stoi(PZilosc);
            przyjetaDostawa.listaArt=new artykul[przyjetaDostawa.ilosc];
            int i=0;
            string liniaTekstu;
            for(i=0;i<przyjetaDostawa.ilosc; i++)   {
                if(!getline(plikOdczyt, liniaTekstu)) break;
                istringstream ss( liniaTekstu );
                string ilosc, cena, nazwa, kategoria;
                getline( ss, nazwa, ',' );
                getline( ss, kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                strcpy(przyjetaDostawa.listaArt[i].nazwa, nazwa.c_str());
                strcpy(przyjetaDostawa.listaArt[i].kategoria, kategoria.c_str());
                przyjetaDostawa.listaArt[i].ilosc=stoi(ilosc);
                przyjetaDostawa.listaArt[i].cena=stod(cena);
                strcpy(przyjetaDostawa.listaArt[i].miejsce.ID, generujNoweID().c_str());
                dodajTowar(tab_art, n_art, przyjetaDostawa.listaArt[i]);
            if (plikOdczyt.eof()) break;
            }
        ofstream plikListaDostawy;
        plikListaDostawy.open("dostawy.bin", ios::binary | ios::out| ios::app);
        plikListaDostawy.write(reinterpret_cast<char*>(&przyjetaDostawa), sizeof(przyjetaDostawa));
        plikListaDostawy.close();
        }
        else
            cout<<"Bylo!"<<endl;
        plikOdczyt.close();
      }
      else cout <<"brak pliku"<<endl;
}

#endif // _DOSTAWA_H_


