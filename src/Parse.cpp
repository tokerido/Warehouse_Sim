#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../include/Parse.h"
#include "../include/WareHouse.h"
#include "../include/Customer.h"
#include "../include/Volunteer.h"

struct Customer {
    std::string name;
    std::string type;
    int distance;
    int maxOrders;
};

struct Volunteer {
    std::string name;
    std::string role;
    int coolDown; // Only for collectors
    int maxDistance; // Only for drivers
    int distancePerStep; // Only for drivers
    int maxOrders; // Optional
};

Parse::Parse(const string &configFilePath, WareHouse wareHouse) {
    // Specify the file path
    std::string file_path = configFilePath;

    // Open the file
    std::ifstream file(file_path);

    // Check if the file is open successfully
    try {
        if (!file.is_open()) {
            throw "Error opening the file: ";
        }
    }
    catch(const char* exp){
        std::cout <<  exp << file_path << std::endl;
    }

    // Create vectors to store data
    std::vector<Customer> customers;
    std::vector<Volunteer> volunteers;

    std::string line;

    // Read each line from the file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;

        // Read the type of entry (customer or volunteer)
        iss >> type;

        if (type == "customer") {
            Customer customer;
            iss >> customer.name >> customer.type >> customer.distance >> customer.maxOrders;
            customers.push_back(customer);
        } else if (type == "volunteer") {
            Volunteer volunteer;
            iss >> volunteer.name >> volunteer.role;

            if (volunteer.role == "driver" | volunteer.role == "limited_driver") {
                iss >> volunteer.maxDistance >> volunteer.distancePerStep;
            } else {
                iss >> volunteer.coolDown; // In case of collector
            }

            // Check if maxOrders is specified
            if (iss >> volunteer.maxOrders) {
                // maxOrders is specified
            } else {
                // maxOrders is not specified, set it to a default value
                volunteer.maxOrders = -1; // or any other suitable default value
            }

            volunteers.push_back(volunteer);
        }
    }

    // Close the file
    file.close();

    // Now, you can process the data stored in the vectors as needed

    for (const auto& customer : customers) {
        int id = wareHouse.setCustomerId();
        if (customer.type == "soldier"){      
            SoldierCustomer soldierCustomer(id, customer.name, customer.distance, customer.maxOrders);
            customersList.push_back(&soldierCustomer);
        } else {
            CivilianCustomer civilianCustomer(id, customer.name, customer.distance, customer.maxOrders);
            customersList.push_back(&civilianCustomer);
        }
    }

    vector<Volunteer*> volunteers;   
    for (const auto& volunteer : volunteers) {
        int id = wareHouse.setVolunteerId();
        if (volunteer.role == "collector"){
            CollectorVolunteer collectorVolunteer(id, volunteer.name, volunteer.coolDown);
            volunteersList.push_back(&collectorVolunteer);
        } else if (volunteer.role == "limited_collector"){
            LimitedCollectorVolunteer limitedCollectorVolunteer(id, volunteer.name, volunteer.coolDown, volunteer.maxOrders);
            volunteersList.push_back(&limitedCollectorVolunteer);
        } else if (volunteer.role == "driver"){
            DriverVolunteer driverVolunteer(id, volunteer.name, volunteer.maxDistance, volunteer.distancePerStep);
            volunteersList.push_back(&driverVolunteer);
        }else {
            LimitedDriverVolunteer limitedDriverVolunteer(id, volunteer.name, volunteer.maxDistance, volunteer.distancePerStep, volunteer.maxOrders);
        }
    }
}

const vector<Customer*> &Parse::getCustomersList() const
{
    return customersList;
}

const vector<Volunteer*> &Parse::getVolunteersList() const
{
    return volunteersList;
}
