#pragma once

#ifndef _LOG_H_
#define _LOG_H_


#include <iostream>
#include <fstream>
#include <ctime>

//using namespace std;

void logInfo(std::string napis);

void logInfo(std::string napis){
    std::ofstream plikZapis;
    time_t czas;
    time( & czas );
    plikZapis.open("log.txt", std::fstream::app);
    //std::cout<<"#Info# "<<napis<<" @ "<<ctime( & czas )<<std::endl;
    plikZapis<<"#Info# "<<napis<<" @ "<<ctime( & czas )<<std::endl;
    plikZapis.close();
}

#endif // _LOG_H_

