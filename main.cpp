
//projekt indywidualny by Robert Dzienio
#include "main.h"

using namespace std;

int main(){
    //printHello();
    int n=50;
    int n_dst=50;
    artykul *lista=new artykul[n];
    dostawa *listaDostaw= new dostawa[n_dst];
    //wybierzMenu(lista, n, listaDostaw, &n_dst);
    int wybor;
    while(true){
        printMenu();
        cin>>wybor;
        clearScreen();
        switch(wybor){
            case 1:{
                menuTowary(lista, n);
                break;}
            case 2:
                menuDostawy(lista, n, listaDostaw, &n_dst);
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
    n_dst=50;

    delete listaDostaw;
    delete lista;
}
