#include <drivers/driver.h>
using namespace OS::drivers;

Driver::Driver(){
}
Driver::~Driver(){
}
void Driver::Activate(){
}
void Driver::DeActivate(){
}
int Driver::Reset(){
    return 0;
}

DriverManager::DriverManager(){
    numDrivers=0;
}
DriverManager::~DriverManager(){
}
void DriverManager::addDriver(Driver* drv){
   driver[numDrivers]=drv;
   numDrivers++;
}
void DriverManager::ActivateAll(){
    for(int i=0;i<numDrivers;i++)
        driver[i]->Activate();
}
