#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
#include "WareHouse.h"

class WareHouse;

class Parse{

    public:
        Parse (const string &configFilePath);
        vector<Customer*> &getCustomersList() const;
        vector<Customer*> &getVolunteersList() const;

    private:
        vector<Customer*> customersList;
        vector<Volunteer*> volunteersList;
};