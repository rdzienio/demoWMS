#ifndef _DOSTAWA_H_
#define _DOSTAWA_H_



#include <iostream>

#include "towar.h"

using namespace std;


struct dostawa{
    string nrPZ;
    artykul *listaArt;
    int ilosc;
    };

void wyswietlPZ(dostawa PZ);
dostawa przyjmijDostawe(artykul *tab_art, int *n_art, string plik); //wczytuje plik z dostawa i dodaje ja na stan
void zapiszDostawe(dostawa nowaDostawa, dostawa *tab_dst, int *n);


void zapiszDostawe(dostawa nowaDostawa, dostawa *tab_dst, int *n){
    ofstream plikZapis;
    plikZapis.open("dostawy.bin", ios::binary | ios::out| ios::app);
    plikZapis.write(reinterpret_cast<char*>(&nowaDostawa), sizeof(nowaDostawa));
    logInfo("zapisano dostawe: " + nowaDostawa.nrPZ);
    *n=1;
    plikZapis.close();
}

dostawa przyjmijDostawe(artykul *tab_art, int *n_art, string plik){
    wczytajTowary(tab_art, n_art, "data.bin");
    fstream plikOdczyt;
    dostawa przyjetaDostawa;
    logInfo("wczytano dostawe z: " + plik);
    plikOdczyt.open(plik, ios::in| ios::app);
    cout<<setprecision(2);
    cout<<fixed;
    //wypiszTowary(tab_art, *n_art);
    if (plikOdczyt.good())
    {
        getline(plikOdczyt, przyjetaDostawa.nrPZ);
        string PZilosc;
        getline(plikOdczyt, PZilosc);
        przyjetaDostawa.ilosc=stoi(PZilosc);
        przyjetaDostawa.listaArt=new artykul[przyjetaDostawa.ilosc];
		//int i=0;
		string liniaTekstu;
        for(int i=0;i<przyjetaDostawa.ilosc; i++){
            artykul art;
            if(!getline(plikOdczyt, liniaTekstu)) break;
			istringstream ss( liniaTekstu );
			string ilosc, cena;

                getline( ss, art.nazwa, ',' );
                //cout<<art.nazwa;
                getline( ss, art.kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                art.ilosc=stoi(ilosc);
                art.cena=stod(cena);
                dodajTowar(tab_art, n_art, art);
            if (plikOdczyt.eof()) break;
        }
        //*n=i;
        plikOdczyt.close();
      }
      else cout <<"brak pliku"<<endl;
      return przyjetaDostawa;
}


void wyswietlPZ(dostawa PZ){
    if(PZ.nrPZ.empty()){
    cout<<"Nie bylo jeszcze dostawy!"<<endl;
    return;
    }
    cout<<"Dokument PZ: "<<PZ.nrPZ<<endl;
    wypiszTowary(PZ.listaArt, PZ.ilosc);
}

#endif // _DOSTAWA_H_


