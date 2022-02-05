#ifndef _MIEJSCE_H_
#define _MIEJSCE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct miejsce{
    char ID[10];
    int maxIlosc=999;
};

string generujNoweID(char oldID); //tworzymy ID wg wzorca, jesli E to paleta EURO a R to regal

string generujNoweID(){
    static int kolejnyNr=0;
    stringstream ss;
    ss<<"BUFF"<<(kolejnyNr++);
    return ss.str();
}



#endif // _MIEJSCE_H_
