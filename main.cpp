#include "main.h"

using namespace std;

int main(){
    //printHello();
    int n=50;
    int n_dst=50;
    artykul *lista=new artykul[n];
    dostawa *listaDostaw= new dostawa[n_dst];
    wybierzMenu(lista, n, listaDostaw, &n_dst);
    n_dst=50;

    delete listaDostaw;
    delete lista;
}
