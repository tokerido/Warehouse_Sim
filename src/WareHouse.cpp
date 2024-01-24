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
void WareHouse::start()
{
 void open();
 std::cout << "Warehouse is open!" << std::endl;
}
const vector<BaseAction*> &WareHouse::getActionsLog() const
{
    //TODO
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
    std::cout << "Customer " << customerId << " doesn't exist.";
}
Volunteer &WareHouse::getVolunteer(int volunteerId) const
{
    for (const auto& volunteer : volunteers) {
        if (volunteer->getId() == volunteerId)
        {
            return *volunteer;
        }
    }
    std::cout << "Volunteer " << volunteerId << " doesn't exist.";
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
    std::cout << "Order " << orderId << " doesn't exist.";
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


