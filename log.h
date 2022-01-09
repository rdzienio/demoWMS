#ifndef _LOG_H_
#define _LOG_H_


#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void logInfo(string napis);

void logInfo(string napis){
    ofstream plikZapis;
    time_t czas;
    time( & czas );
    plikZapis.open("log.txt", fstream::app);
    cout<<"#Info# "<<napis<<" @ "<<ctime( & czas )<<endl;
    plikZapis<<"#Info# "<<napis<<" @ "<<ctime( & czas )<<endl;
    plikZapis.close();
}

#endif // _LOG_H_

