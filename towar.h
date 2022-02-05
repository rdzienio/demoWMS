#pragma once

#ifndef _TOWAR_H_
#define _TOWAR_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "log.h"
#include "miejsce.h"
//#include "dostawa.h"

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
void edytujTowar(artykul *tab, int n);
void zmienMiejsce(artykul *tab, int n);
void usunTowar(int idx);
bool wyslijTowar(artykul *tab_art, int *n_art, artykul doWysylki);
void generujZamowienie(artykul braki);

void generujZamowienie(artykul braki){
    static int autoNr=1;
    ifstream f("auto-zamowienie.txt");
    if(f.good())
    {   ofstream plikZapis;
        plikZapis.open("AUTO-zamowienie.txt", ios::app);
        plikZapis<<braki.nazwa<<","<<braki.kategoria<<","<<braki.ilosc<<","<<braki.cena<<"\n";
        plikZapis.close();
    }
    else{
        ofstream plikZapis;
        stringstream ss;
        ss<<"AUTO-ZAM-"<<(autoNr++);
        plikZapis.open("AUTO-zamowienie.txt");
        plikZapis<<ss.str()<<endl;;
        plikZapis<<"<ilosc pozycji>"<<endl;
        plikZapis<<braki.nazwa<<","<<braki.kategoria<<","<<braki.ilosc<<","<<braki.cena<<"\n";
        plikZapis.close();
    }
}

bool wyslijTowar(artykul *tab_art, int *n_art, artykul doWysylki){
    string nazwa=doWysylki.nazwa;
    logInfo("wyslano towar: " + nazwa);
    bool flaga=false;
    bool zamowienie=false; //0-nie generowano zamowienia; 1-wygenerowano
    //cout<<*n<<endl;
    for(int i=0; i<*n_art; i++){
        if(strcmp(tab_art[i].nazwa, doWysylki.nazwa)==0){
                if(tab_art[i].ilosc>=doWysylki.ilosc)
                    {
                    tab_art[i].ilosc-=doWysylki.ilosc;
                    flaga=true;
                    break;
                    }
                    else{
                        logInfo("Nie wystarczajaca ilosc towaru [" +nazwa + "dodaje do zamowienia!");
                        doWysylki.ilosc-=tab_art[i].ilosc;
                        generujZamowienie(doWysylki);
                        flaga=true;
                        zamowienie=true;
                        break;
                    }
        }
    }
    if(flaga==false)
        {

            logInfo("Nie ma takiego towaru [" +nazwa+ "dodaje do zamowienia!");
            generujZamowienie(doWysylki);
            zamowienie=true;

    }
    zapiszTowary(tab_art, *n_art, "data.bin");
    return zamowienie;

}

void usunTowar(int idx){
    string deleteline;
    string line;

    ifstream fin;
    fin.open("data.bin");
    ofstream temp;
    temp.open("temp.txt");
    int i=0;
    while (getline(fin, line))
    {
        //std::string id(line.begin(), line.begin() + line.find(" "));
        if (idx!=i)
            {temp << line << endl;}
        i++;
    }

    temp.close();
    fin.close();
    remove("data.bin");
    rename("temp.txt", "data.bin");
}


void zmienMiejsce(artykul *tab, int n){
    wczytajTowary(tab, &n, "data.bin");
    system("CLS");
    wypiszTowary(tab, n);
    //
    //printHello();
    int wybor;
    cout<<"Wybierz nr pozycji do zmiany: ";
    cin>>wybor;
    for(int i=0; i<n; i++){
        if(wybor==i){
                getchar();
                cout<<"Podaj nowa miejsce dla towaru: ";
                string ID;
                getline(cin, ID);
                for(int j=0; j<n; j++){
                    if(strcmp(tab[j].miejsce.ID, ID.c_str())==0 && strcmp(tab[j].nazwa, tab[i].nazwa)!=0){
                        cout<<"Wybrane miejsce jest zajete przez inny towar!"<<endl;
                        system("pause");
                        return;
                    }
                    else if(strcmp(tab[j].miejsce.ID, ID.c_str())==0 && strcmp(tab[j].nazwa, tab[i].nazwa)==0){
                            //cout<<"jestem tutaj!"<<endl;
                        if(tab[j].miejsce.maxIlosc>=(tab[j].ilosc+tab[i].ilosc)){
                            tab[j].ilosc+=tab[i].ilosc;
                            zapiszTowary(tab, n, "data.bin");
                            usunTowar(i);
                            cout<<"Miejsce zostalo zaktualizowane!"<<endl;
                            system("pause");
                            return;
                        }
                        else{
                            cout<<"Towar sie nie zmiesci w tym miejscu!"<<endl;
                            system("pause");
                            return;
                        }
                    }
                }
                strcpy(tab[i].miejsce.ID, ID.c_str());
                cout<<"Podaj maksymalna ilosc towaru w tym miejscu: ";
                cin>>tab[i].miejsce.maxIlosc;
                cout<<"Artykul zaktualizowany!"<<endl;
                zapiszTowary(tab, n, "data.bin");
                break;
        }
    }
    system("pause");

}

void edytujTowar(artykul *tab, int n){
    wczytajTowary(tab, &n, "data.bin");
    system("CLS");
    wypiszTowary(tab, n);

    //printHello();
    int wybor;
    cout<<"Wybierz nr artykulu do edycji: ";
    cin>>wybor;
    for(int i=0; i<n; i++){
        if(wybor==i){
                getchar();
                cout<<"Podaj nowa nazwe towaru: ";
                string nazwa;
                getline(cin, nazwa);
                strcpy(tab[i].nazwa, nazwa.c_str());
                cout<<"Podaj nowa kategorie: ";
                cin>>tab[i].kategoria;
                cout<<"Podaj nowa cene: ";
                cin>>tab[i].cena;
                cout<<"Artykul zaktualizowany!"<<endl;
                break;
        }
    }
    system("pause");
    zapiszTowary(tab, n, "data.bin");
}

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

