#include <iostream>
#include <windows.h>
#include <limits>
#include "towar.h"
#include "dostawa.h"

using namespace std;

void printHello();
void printMenu();
void clearScreen();
//int wybierzMenu(artykul *tab, int n, dostawa *tab_dst, int *n_dst);
void menuTowary(artykul *tab, int n);
void menuDostawy(artykul *tab_art, int n_art, dostawa *tab_dst, int *n_dst);

void menuDostawy(artykul *tab_art, int n_art, dostawa *tab_dst, int *n_dst){
    int wybor;
    dostawa testDostawy;
    clearScreen();
    while(true){
        cout<<"Dostawy | ";
        printHello();
        cout<<"1) Wyswietl dostawe."<<endl;
        cout<<"2) Przyjmij nowa dostawe."<<endl;
        cout<<"0) Powrot."<<endl;
        cin>>wybor;
        switch(wybor){
        case 1:
            wyswietlPZ(testDostawy);
            //wypiszTowary(tab_art, n_art);
            system("pause");
            clearScreen();
            break;
        case 2:
            {
            string plik;
            cout<<"Podaj nazwe pliku do wczytania: ";
            cin>>plik;
            testDostawy=przyjmijDostawe(tab_art, &n_art, plik);
            zapiszDostawe(testDostawy, tab_dst, n_dst);
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
        //clearScreen();
        cout<<"Artykuly | ";
        printHello();
        cout<<"1) Stan magazynu."<<endl;
        cout<<"2) Wczytaj z pliku."<<endl;
        cout<<"3) Dodaj artykul."<<endl;
        cout<<"4) Zapisz do pliku."<<endl;
        cout<<"0) Powrot."<<endl;
        cin>>wybor;
        switch(wybor){
        case 1:
            clearScreen();
            wczytajTowary(tab, &n, "data.bin");
            wypiszTowary(tab, n);
            system("pause");
            clearScreen();
            break;
        case 2:
            {
                clearScreen();
                string plik;
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
                artykul test;
                //cin.ignore(std::numeric_limits<std::streamsize>::max());
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
                cout<<dodajTowar(tab, &n, test);
                //zapiszTowary(tab, &n, "data.bin");
                system("pause");
                clearScreen();
                break;
            };
        case 4:
            {
                clearScreen();
                string plik;
                cout<<"Podaj nazwe pliku do zapisania: ";
                cin>>plik;
                zapiszTowary(tab, n, plik);
                system("pause");
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

/*int wybierzMenu(artykul *tab, int n,  dostawa *tab_dst, int *n_dst){
    int wybor;
    while(true){
        printMenu();
        cin>>wybor;
        clearScreen();
        switch(wybor){
            case 1:{
                menuTowary(tab, n);
                break;}
            case 2:
                menuDostawy(tab, n, tab_dst, n_dst);
                break;
            case 3:
                cout<<"Brak wysylek"<<endl;
                break;
            case 0:
                cout<<"Good bye!"<<endl;
                return 0;
            default:
                continue;
        }
    }
}*/

void printHello(){
cout<<"System wspomagajacy zarzadzanie magazynem WMS by RDzienio\n";
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
