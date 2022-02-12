
//projekt indywidualny WMS by Robert Dzienio
#include "main.h"

using namespace std;

int main(){
    int n=50;
    int n_dst=50;
    artykul *lista=new artykul[n];
    dostawa *listaDostaw= new dostawa[n_dst];
    int wybor;
    system("chcp 1250>>null");
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
                menuWysylki(lista, n);
                break;
            case 0:
                cout<<"Good bye!"<<endl;

    delete listaDostaw;
    delete lista;
                return 0;
            default:
                continue;
        }
    }
}
