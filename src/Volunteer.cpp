#include "../include/Volunteer.h"
#include "../include/WareHouse.h"

 bool isBusy() const;

Volunteer:: Volunteer(int id(0), const string &name()){
    isBusy(false);
    
}

int Volunteer:: getId() const {return id;};
const string Volunteer:: &getName() const {return &name;};



