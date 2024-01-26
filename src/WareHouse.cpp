#include "../include/WareHouse.h"
#include "../include/Parse.h"
#include "../include/BaseAction.h"
#include "../include/Volunteer.h"
#include "../include/Customer.h"
#include "../include/Order.h"
#include <iostream>

WareHouse::WareHouse(const string &configFilePath): customerCounter(1), volunteerCounter(1), isOpen(false)
{
    Parse parse(configFilePath, *this);
    customers = parse.getCustomersList();
    volunteers = parse.getVolunteersList();
}
//rule of 5 implement: //continue with move!!!!!!!!!!!!!!!!!!!! the 2 of rule of 5.
//copy constructor:
WareHouse::WareHouse(const WareHouse &other):isOpen(other.isOpen), customerCounter(other.customerCounter),volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter) {
    for(BaseAction* action :other.actionsLog) {
        actionsLog.push_back(action);
    }
    for(Volunteer* volunteer:other.volunteers) {
        volunteers.push_back(volunteer);
    }
    for(Order* order:other.pendingOrders) {
        pendingOrders.push_back(order);
    }
    for(Order* order:other.inProcessOrders) {
        inProcessOrders.push_back(order);
    }
    for(Order* order:other.completedOrders) {
        completedOrders.push_back(order);
    }
    for(Customer* customer:other.customers) {
        customers.push_back(customer);
    }
}
//Destructor:
WareHouse::~WareHouse() {
    clear();
}
// Copy Assignment Operator:
WareHouse& WareHouse :: operator=(const WareHouse& other)
{
if(&other != this) 
{
isOpen = other.isOpen;
customerCounter = other.customerCounter;
volunteerCounter = other.volunteerCounter;
customerCounter = other.customerCounter;
clear();
for(BaseAction* action:other.actionsLog)
{
    BaseAction* action_clone = action ->clone();
    actionsLog.push_back(action_clone);
}
for(Volunteer* volunteer:other.volunteers)
{
    Volunteer* volunteer_clone = volunteer ->clone();
    volunteers.push_back(volunteer_clone);
}
for(Customer* customer:other.customers)
{
    Customer* customer_clone = customer ->clone();
    customers.push_back(customer_clone);
}
for(Order* order:other.pendingOrders)
{
    Order* newOrder= new Order(order->getId(),order->getCustomerId(), order->getDistance());
    pendingOrders.push_back(newOrder);
}
for(Order* order:other.inProcessOrders)
{
    Order* newOrder= new Order(order->getId(),order->getCustomerId(), order->getDistance());
    inProcessOrders.push_back(newOrder);
}
for(Order* order:other.completedOrders)
{
    Order* newOrder= new Order(order->getId(),order->getCustomerId(), order->getDistance());
    completedOrders.push_back(newOrder);
}

}
}
void WareHouse::start()
{
 void open();
 std::cout << "Warehouse is open!" << std::endl;
}
const vector<BaseAction*> &WareHouse::getActionsLog() const
{
    return actionsLog;
}
void WareHouse::addOrder(Order* order)
{
  pendingOrders.push_back(order);
}
void WareHouse::addCustomer(Customer* customer)
{
    customers.push_back(customer);
}
void WareHouse::addAction(BaseAction* action)
{
    //TODO
}
void WareHouse::printActionsLogs()
{
    //TODO
}
Customer &WareHouse::getCustomer(int customerId) const
{
    for(const auto& customer : customers){
        if (customer->getId() == customerId)
        {
            return *customer;
        }  
    }
    throw std::runtime_error("Customer doesn't exist");
}
Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (const auto& volunteer : volunteers) {
        if (volunteer->getId() == volunteerId)
        {
            return *volunteer;
        }
    }
    throw std::runtime_error("Volunteer doesn't exist");
}
Order &WareHouse::getOrder(int orderId) const
{
    for (const auto& order : pendingOrders){
        if (order->getId() == orderId)
        {
            return *order;
        }
    }
    for (const auto& order : inProcessOrders){
        if (order->getId() == orderId)
        {
            return *order;
        }
    }
    for (const auto& order : completedOrders){
        if (order->getId() == orderId)
        {
            return *order;
        }
    }
    throw std::runtime_error("Order doesn't exist");
}
void WareHouse::clear()
{
    while(!actionsLog.empty()) {
        delete actionsLog.back();
        actionsLog.pop_back();
    }
    while(!volunteers.empty()) {
        delete volunteers.back();
        volunteers.pop_back();
    }
    while(!pendingOrders.empty()) {
        delete pendingOrders.back();
        pendingOrders.pop_back();
    }
    while(!pendingOrders.empty()) {
        delete pendingOrders.back();
        pendingOrders.pop_back();
    }
    while(!inProcessOrders.empty()) {
        delete inProcessOrders.back();
        inProcessOrders.pop_back();
    }
     while(!completedOrders.empty()) {
        delete completedOrders.back();
        completedOrders.pop_back();
    }
    while(!customers.empty()) {
        delete customers.back();
        customers.pop_back();
    }
    
}
void WareHouse::close()
{
    isOpen = false;
    // TODO - FREE ALL MEMORY!!!!
}
void WareHouse::open()
{
    isOpen = true;
    // we should call all the actions here!
}
int WareHouse::setCustomerId()
{
    int output = customerCounter;
    ++customerCounter;
    return output;
}
int WareHouse::setVolunteerId()
{
    int output = volunteerCounter;
    ++volunteerCounter;
    return output;
}
int WareHouse::setOrderId()
{
    int output(orderCounter);
    ++orderCounter;
    return output;
}


