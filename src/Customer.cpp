#include "../include/WareHouse.h"
#include "../include/Customer.h"
int numOrders;



Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(0), &name(),locationDistance(2), maxOrders(3) {
    numOrders = 0;
}
const string& Customer::getName() const
{
    return name;
}
int Customer:: getId() const
{
    return id;
}
int Customer:: getCustomerDistance() const
{
    return locationDistance;
}
int Customer:: getMaxOrders() const
{
    return maxOrders;
}
int Customer:: getNumOrders() const
{
    return numOrders;
}
bool Customer:: canMakeOrder() const
{
    return maxOrders > numOrders;
}
//vector<int> Customer:: &getOrders() const;
// int addOrder(int orderId); 