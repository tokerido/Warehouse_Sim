#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

int main() {
    // Specify the file path
    std::string file_path = "configFileExample.txt";

    // Open the file
    std::ifstream file(file_path);

    // Check if the file is open successfully
    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << file_path << std::endl;
        return 1; // Exit with an error code
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

    // Example: Print the data
    for (const auto& customer : customers) {
        std::cout << "Customer: " << customer.name << ", Type: " << customer.type
                  << ", Distance: " << customer.distance << ", MaxOrders: " << customer.maxOrders << std::endl;
    }

    for (const auto& volunteer : volunteers) {
        std::cout << "Volunteer: " << volunteer.name << ", Role: " << volunteer.role;

        if (volunteer.role == "driver" | volunteer.role == "limited_driver") {
            std::cout << ", MaxDistance: " << volunteer.maxDistance << ", DistancePerStep: " << volunteer.distancePerStep;
        } else {
            std::cout << ", CoolDown: " << volunteer.coolDown;
        }

        std::cout << ", MaxOrders: " << volunteer.maxOrders << std::endl;
    }

    return 0;
}