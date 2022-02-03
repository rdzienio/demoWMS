#ifndef _DOSTAWA_H_
#define _DOSTAWA_H_



#include <iostream>

#include "towar.h"

using namespace std;


struct dostawa{
    char nrPZ[10];
    artykul *listaArt;
    int ilosc;
    };

void wyswietlPZ(dostawa PZ);
dostawa przyjmijDostawe(artykul *tab_art, int *n_art, string plik); //wczytuje plik z dostawa i dodaje ja na stan
void zapiszDostawe(dostawa nowaDostawa, dostawa *tab_dst, int *n);
void wczytajListeDostaw(dostawa *tab_dst, int *n);
void wyswietlListePrzyjetychDostaw();

void wyswietlListePrzyjetychDostaw(){
    ifstream plikOdczyt;
    dostawa d[10];
    dostawa tmp;
    int n;
    bool flaga=false;
    plikOdczyt.open("dostawy.bin", ios::binary | ios::in);
    if(plikOdczyt.good()==true){
        logInfo("wczytano dostawy");
        int i;
        for(i=0; ;i++){
            plikOdczyt.read(reinterpret_cast<char*>(&d[i]),sizeof(d[i]));
            if(plikOdczyt.eof()) break;
        }
        n=i;
    }
    plikOdczyt.close();
    cout<<0<<") Nr PZ: "<<d[0].nrPZ<<endl;
    for(int j=1; j<n; j++){
        flaga=false;
        for(int k=0; k<j; k++){
            if(j!=k && strcmp(d[j].nrPZ, d[k].nrPZ)==0)
            {
                flaga=true;
                break;
            }
        }
        if(flaga==true)
            cout<<j<<") Nr PZ: "<<"d00p[a"<<endl;
        else
            cout<<j<<") Nr PZ: "<<d[j].nrPZ<<endl;
    }
}


void wczytajListeDostaw(dostawa *tab_dst, int *n){
    ifstream plikOdczyt;
    plikOdczyt.open("dostawy.bin", ios::binary | ios::in);
    if(plikOdczyt.good()==true){
        logInfo("wczytano dostawy");
        int i;
        for(i=0; ;i++){
            plikOdczyt.read(reinterpret_cast<char*>(&tab_dst[i]),sizeof(tab_dst));
            if(plikOdczyt.eof()) break;
        }
        //logInfo("i: " + i);
        *n=i;
    }
    plikOdczyt.close();
}

void zapiszDostawe(dostawa nowaDostawa, dostawa *tab_dst, int *n){
    wczytajListeDostaw(tab_dst, n);
    bool flaga=false;
    for(int i=0; i<*n; i++){
        if(strcmp(nowaDostawa.nrPZ, tab_dst[i].nrPZ)==0)
            {
                flaga=true;
                break;
            }
    }
    if(flaga!=true){
        ofstream plikZapis;
        plikZapis.open("dostawy.bin", ios::binary | ios::out| ios::app);
        plikZapis.write(reinterpret_cast<char*>(&nowaDostawa), sizeof(nowaDostawa));
        string nrPZ=nowaDostawa.nrPZ;
        logInfo("zapisano dostawe: " + nrPZ);
        plikZapis.close();
    }
    else
    {
        string nrPZ=nowaDostawa.nrPZ;
        logInfo("dostawa [" + nrPZ + "] juz byla wprowadzona!");
    }
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
        string nrPZ;
        getline(plikOdczyt, nrPZ);
        strcpy(przyjetaDostawa.nrPZ, nrPZ.c_str());
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
			string ilosc, cena, nazwa, kategoria;

                getline( ss, nazwa, ',' );
                getline( ss, kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                strcpy(art.nazwa, nazwa.c_str());
                strcpy(art.kategoria, kategoria.c_str());
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
    string nrPZ=PZ.nrPZ;
    if(nrPZ.empty() || PZ.ilosc<1){
    cout<<"Nie bylo jeszcze dostawy!"<<endl;
    return;
    }
    cout<<"Dokument PZ: "<<PZ.nrPZ<<"\t"<<PZ.ilosc<<"\t"<<PZ.listaArt[0].nazwa<<endl;
    wypiszTowary(PZ.listaArt, PZ.ilosc);
}

#endif // _DOSTAWA_H_


