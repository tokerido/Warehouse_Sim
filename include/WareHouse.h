#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(WareHouse &other);
        WareHouse(WareHouse &&other);
        WareHouse &operator=(WareHouse &other);
        WareHouse &operator=(WareHouse &&other);

        void start();
        const vector<BaseAction*> &getActionsLog() const;
        void addOrder(Order* order);
        void addCustomer(Customer* customer); // new func
        void addAction(BaseAction* action);
        void printActionsLogs();
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        void close();
        void open();
        int setCustomerId(); // new func
        int setVolunteerId(); // new func
        int setOrderId(); //new func
        void clear(); //new function
        void simulateOneStep(); // new func
        vector<string> split(const string& str); //new func
        ~WareHouse(); //new func

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter; //For assigning unique order IDs
};