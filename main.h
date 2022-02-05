#pragma once

#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <windows.h>
#include <limits>
#include "towar.h"
#include "dostawa.h"
#include "wysylka.h"

using namespace std;

void printHello();
void printMenu();
void clearScreen();
void menuTowary(artykul *tab, int n);
void menuDostawy(artykul *tab_art, int n_art, dostawa *tab_dst, int *n_dst);
void menuWysylki(artykul *tab_art, int n_art, dostawa *tab_dst, int *n_dst);

void menuWysylki(artykul *tab_art, int n_art){
    int wybor;
    clearScreen();
    while(true){
        printHello();
        cout<<"1) Wyswietl liste wysylek."<<endl;
        cout<<"2) Zrealizuj nowa wysylke."<<endl;
        cout<<"0) Powrot."<<endl;
        cin>>wybor;
        switch(wybor){
        case 1:
            clearScreen();
            printHello();
            wyswietlListeWysylek();
            system("pause");
            clearScreen();
            break;
        case 2:
            {
            clearScreen();
            printHello();
            string plik;
            cout<<"Podaj nazwe pliku WZ do wczytania: ";
            cin>>plik;
            wyslijWysylke(tab_art, &n_art, plik);
            system("pause");
            clearScreen();
            break;
            }
        case 0:
            clearScreen();
            return;
        default:
            continue;

        }
    }
}

void menuDostawy(artykul *tab_art, int n_art, dostawa *tab_dst, int *n_dst){
    int wybor;
    dostawa testDostawy;
    clearScreen();
    while(true){
        //cout<<"Dostawy | ";
        printHello();
        cout<<"1) Wyswietl liste dostaw."<<endl;
        cout<<"2) Przyjmij nowa dostawe."<<endl;
        cout<<"0) Powrot."<<endl;
        cin>>wybor;
        switch(wybor){
        case 1:
            clearScreen();
            printHello();
            wyswietlListeDostaw();
            system("pause");
            clearScreen();
            break;
        case 2:
            {
            clearScreen();
            printHello();
            string plik;
            cout<<"Podaj nazwe pliku PZ do wczytania: ";
            cin>>plik;
            przyjmijDostawe(tab_art, &n_art, plik);
            system("pause");
            clearScreen();
            break;
            }
        case 0:
            clearScreen();
            return;
        default:
            continue;

        }
    }
}

void menuTowary(artykul *tab, int n){
    int wybor;
    clearScreen();
    while(true){
        clearScreen();
        //cout<<"Artykuly | ";
        printHello();
        cout<<"1) Stan magazynu."<<endl;
        cout<<"2) Wczytaj dane z pliku."<<endl;
        cout<<"3) Dodaj artykul."<<endl;
        cout<<"4) Zapisz dane do pliku."<<endl;
        cout<<"5) Edytuj artykul."<<endl;
        cout<<"6) Zmien miejsce artykulu."<<endl;
        cout<<"7) Usun artykul."<<endl;
        cout<<"0) Powrot."<<endl;
        cin>>wybor;
        switch(wybor){
        case 1:
            clearScreen();
            printHello();
            wczytajTowary(tab, &n, "data.bin");
            wypiszTowary(tab, n);
            system("pause");
            clearScreen();
            break;
        case 2:
            {
                clearScreen();
                string plik;
                printHello();
                cout<<"Podaj nazwe pliku do wczytania: ";
                cin>>plik;
                wczytajTowary(tab, &n, plik);
                zapiszTowary(tab, n, "data.bin");
                system("pause");
                clearScreen();
                break;
            }
        case 3:
            {
                clearScreen();
                printHello();
                artykul test;
                getchar();
                cout<<"Podaj nazwe towaru: ";
                string nazwa;
                getline(cin, nazwa);
                strcpy(test.nazwa, nazwa.c_str());
                cout<<"Podaj kategorie: ";
                cin>>test.kategoria;
                cout<<"Podaj cene: ";
                cin>>test.cena;
                cout<<"Podaj ilosc: ";
                cin>>test.ilosc;
                cout<<"Podaj ID miejsca";
                cin>>test.miejsce.ID;
                cout<<dodajTowar(tab, &n, test);
                //zapiszTowary(tab, &n, "data.bin");
                system("pause");
                clearScreen();
                break;
            };
        case 4:
            {
                clearScreen();
                printHello();
                string plik;
                cout<<"Podaj nazwe pliku do zapisania: ";
                cin>>plik;
                zapiszTowary(tab, n, plik);
                system("pause");
                break;
            }
        case 5:
            clearScreen();
            printHello();
            edytujTowar(tab, n);
            break;
        case 6:
            clearScreen();
            printHello();
            zmienMiejsce(tab, n);
            break;
        case 7:
            wczytajTowary(tab, &n, "data.bin");
            clearScreen();
            wypiszTowary(tab, n);
            int idx;
            cout<<"Podaj nr pozycji do usuniecia: ";
            cin>>idx;
            usunTowar(idx);
        case 0:
            clearScreen();
            return;
        default:
            continue;

        }
    }
}

void printHello(){
cout<<"#############################################################\n";
cout<<"# System wspomagajacy zarzadzanie magazynem WMS by RDzienio #\n";
cout<<"#############################################################\n";
}

void printMenu(){
    printHello();
    cout<<"1) Zawartosc magazynu."<<endl;
    cout<<"2) Dostawa."<<endl;
    cout<<"3) Wysylka."<<endl;
    cout<<"0) Koniec."<<endl;
}

void clearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }

  #endif // _MAIN_H_
