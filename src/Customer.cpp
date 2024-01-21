#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include "../include/Order.h"

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id), name(name),locationDistance(locationDistance), maxOrders(maxOrders) {
}
//getters 
const string &Customer:: getName() const {return name;};
int Customer:: getId() const {return id;};
int Customer:: getCustomerDistance() const {return locationDistance;};
int Customer:: getMaxOrders() const {return maxOrders;};
int Customer:: getNumOrders() const {return ordersId.size();};
const vector<int> &Customer::getOrdersIds() const {
    return ordersId;
}
//info
bool Customer:: canMakeOrder() const {
    return ordersId.size() < maxOrders;
};

//actions
int Customer::addOrder(int orderId) {
    if (canMakeOrder()) {
        ordersId.push_back(orderId);
        return orderId;
    }
    return -1;
}


//soldier Customer
SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders): Customer(id, name, locationDistance, maxOrders) {}
SoldierCustomer *SoldierCustomer::clone() const {
    return new SoldierCustomer(*this);
}
//Civilian Customer
CivilianCustomer::CivilianCustomer(int id, string name, int locationDistance, int maxOrders)
    : Customer(id, name, locationDistance, maxOrders) {}
CivilianCustomer *CivilianCustomer::clone() const {
    return new CivilianCustomer(*this);
}


