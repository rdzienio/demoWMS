#ifndef _WYSYLKA_H_
#define _WYSYLKA_H_

#include <iostream>
#include <fstream>

using namespace std;

struct wysylka{
    char nrWZ[10];
    artykul *listaArt;
    int ilosc;
    };

void wyswietlListeWysylek();
void wyslijWysylke(artykul *tab_art, int *n_art, string plik);
bool sprawdzWysylke(char* nrWZ);

bool sprawdzWysylke(char* nrWZ){
    ifstream plikOdczyt;
    wysylka d[10];
    bool flaga=true;
    plikOdczyt.open("wysylki.bin", ios::binary | ios::in);
    if(plikOdczyt.good()==true){
        int i;
        for(i=0; ;i++){
            plikOdczyt.read(reinterpret_cast<char*>(&d[i]),sizeof(d[i]));
            if(plikOdczyt.eof()) break;
            if(strcmp(d[i].nrWZ, nrWZ)==0)
            {
                flaga=false;
                break;
            }
        }
    }
    plikOdczyt.close();

    return flaga;
}

void wyswietlListeWysylek(){
    ifstream plikOdczyt;
    wysylka d[10];
    bool flaga=true;
    plikOdczyt.open("wysylki.bin", ios::binary | ios::in);
    if(plikOdczyt.good()==true){
        int i;
        cout<<"Lista wysylek"<<endl;
        for(i=0; ;i++){
            plikOdczyt.read(reinterpret_cast<char*>(&d[i]),sizeof(d[i]));
            if(plikOdczyt.eof()) break;
            cout<<i<<") Nr WZ: "<<d[i].nrWZ<<endl;

        }
    }
    else
        cout<<"Brak dostaw!"<<endl;
    plikOdczyt.close();
}

void wyslijWysylke(artykul *tab_art, int *n_art, string plik){
    wczytajTowary(tab_art, n_art, "data.bin");
    fstream plikOdczyt;
    wysylka nowaWZ;
    logInfo("wczytano wysylke z: " + plik);
    plikOdczyt.open(plik, ios::in| ios::app);
    cout<<setprecision(2);
    cout<<fixed;
    if (plikOdczyt.good())
    {
        string nrWZ;
        getline(plikOdczyt, nrWZ);
        strcpy(nowaWZ.nrWZ, nrWZ.c_str());
        if(sprawdzWysylke(nowaWZ.nrWZ))
        {
            string ilosc;
            getline(plikOdczyt, ilosc);
            nowaWZ.ilosc=stoi(ilosc);
            nowaWZ.listaArt=new artykul[nowaWZ.ilosc];
            int i=0;
            string liniaTekstu;
            for(i=0;i<nowaWZ.ilosc; i++)   {
                if(!getline(plikOdczyt, liniaTekstu)) break;
                istringstream ss( liniaTekstu );
                string ilosc, cena, nazwa, kategoria;
                getline( ss, nazwa, ',' );
                getline( ss, kategoria, ',' );
                getline( ss, ilosc, ',' );
                getline( ss, cena, ',' );
                strcpy(nowaWZ.listaArt[i].nazwa, nazwa.c_str());
                strcpy(nowaWZ.listaArt[i].kategoria, kategoria.c_str());
                nowaWZ.listaArt[i].ilosc=stoi(ilosc);
                nowaWZ.listaArt[i].cena=stod(cena);
                wyslijTowar(tab_art, n_art, nowaWZ.listaArt[i]);
            if (plikOdczyt.eof()) break;
            }
        ofstream plikListaDostawy;
        plikListaDostawy.open("wysylki.bin", ios::binary | ios::out| ios::app);
        plikListaDostawy.write(reinterpret_cast<char*>(&nowaWZ), sizeof(nowaWZ));
        plikListaDostawy.close();
        }
        else
            cout<<"Bylo!"<<endl;
        plikOdczyt.close();
      }
      else cout <<"brak pliku"<<endl;
}


#endif // _WYSYLKA_H_
