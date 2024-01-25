#include "../include/Volunteer.h"
#include "../include/WareHouse.h"
#include "../include/Order.h"
#include <iostream>

Volunteer::Volunteer(int id, const string &name) : id(id), name(name), completedOrderId(NO_ORDER), activeOrderId(NO_ORDER) {}
int Volunteer::getId() const
{
    return id;
}
const string &Volunteer::getName() const
{
    return name;
}
int Volunteer::getActiveOrderId() const 
{
    return activeOrderId; 
}
int Volunteer::getCompletedOrderId() const 
{
    return completedOrderId;
}
bool Volunteer::isBusy() const
{
    return activeOrderId != NO_ORDER;
}



CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown): Volunteer(id, name), coolDown(coolDown), timeLeft(0){}
CollectorVolunteer *CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this); //???
}
void CollectorVolunteer::step()
{
    if (timeLeft != 0 && decreaseCoolDown()){
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}
int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}
int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}
bool CollectorVolunteer::decreaseCoolDown()
{
    --timeLeft;
    return timeLeft == 0;
}
bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
}
bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (!isBusy() && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING);
}
void CollectorVolunteer::acceptOrder(const Order &order)
{
    try {
        if(!canTakeOrder(order)){
            throw "Can't accept order!";
        } else {
            activeOrderId = order.getId();
            timeLeft = coolDown;
        }
    }
    catch(const char* exp){
        std::cout << "Error : " << exp <<" Order ID : " << order.getId() << std::endl;
    }
}
string CollectorVolunteer::toString() const
{
    string output;
    // print id
    output += "VoulunteerID: " + getId();
    output += "\n";

    // print isBusy
    bool busy = isBusy();
    output += "isBusy: " + busy;
    output += "\n";

    // print order id (if necessary)
    if (!busy)
    {
        output += "OrderID: None";
        output += "\n";
    } else
    {
        output += "OrderID: " + getActiveOrderId();
        output += "\n";
    }

    // print time left
        if (!busy)
    {
        output += "TimeLeft: None";
        output += "\n";
    } else
    {
        output += "TimeLeft: " + getTimeLeft();
        output += "\n";
    }

    // print orders left
        output += "OrdersLeft: No Limit";
        
    return output;
}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown ,int maxOrders): CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders){}
LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    //TODO
}
bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    return (!isBusy() && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING);
}
void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    --ordersLeft;
}
int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}
int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}
string LimitedCollectorVolunteer::toString() const
{
    string output;
    // print id
    output += "VoulunteerID: " + getId();
    output += "\n";

    // print isBusy
    bool busy = isBusy();
    output += "isBusy: " + busy;
    output += "\n";

    // print order id (if necessary)
    if (!busy)
    {
        output += "OrderID: None";
        output += "\n";
    } else
    {
        output += "OrderID: " + getActiveOrderId();
        output += "\n";
    }

    // print time left
        if (!busy)
    {
        output += "TimeLeft: None";
        output += "\n";
    } else
    {
        output += "TimeLeft: " + getTimeLeft();
        output += "\n";
    }

    // print orders left
        output += "OrdersLeft: " + ordersLeft;
        output += "\n";
        
    return output;
}




DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep): Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0){}
DriverVolunteer *DriverVolunteer::clone() const
{
    //TODO
}
int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}
int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}
int DriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}
bool DriverVolunteer::decreaseDistanceLeft()
{
    distanceLeft = distanceLeft - distancePerStep;
    return distanceLeft <= 0;
}
bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}
bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    return (!isBusy() && order.getDistance() <= maxDistance && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING);
}
void DriverVolunteer::acceptOrder(const Order &order)
{
    try {
        if(!canTakeOrder(order)){
            throw "Can't accept order!";
        } else {
            activeOrderId = order.getId();
            distanceLeft = order.getDistance();
        }
    }
    catch(const char* exp){
        std::cout << "Error : " << exp <<" Order ID : " << order.getId() << std::endl;
    }

}
void DriverVolunteer::step()
{
    if (distanceLeft > 0 && decreaseDistanceLeft()){
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
        distanceLeft = 0;
    }
}
string DriverVolunteer::toString() const
{
    string output;
    // print id
    output += "VoulunteerID: " + getId();
    output += "\n";

    // print isBusy
    bool busy = isBusy();
    output += "isBusy: " + busy;
    output += "\n";

    // print order id (if necessary)
    if (!busy)
    {
        output += "OrderID: None";
        output += "\n";
    } else
    {
        output += "OrderID: " + getActiveOrderId();
        output += "\n";
    }

    // print time left
        if (!busy)
    {
        output += "TimeLeft: None";
        output += "\n";
    } else
    {
        output += "TimeLeft: " + getDistanceLeft();
        output += "\n";
    }

    // print orders left
        output += "OrdersLeft: No Limit";

    return output;
}


LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders): DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders){}
LimitedDriverVolunteer *LimitedDriverVolunteer:: clone() const
{
    //TODO
}
int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}
int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}
bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    return ordersLeft > 0;
}
bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    return (!isBusy() && order.getDistance() <= getMaxDistance() && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING);
}
void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    --ordersLeft;
}
string LimitedDriverVolunteer::toString() const
{
    string output;
    // print id
    output += "VoulunteerID: " + getId();
    output += "\n";

    // print isBusy
    bool busy = isBusy();
    output += "isBusy: " + busy;
    output += "\n";

    // print order id (if necessary)
    if (!busy)
    {
        output += "OrderID: None";
        output += "\n";
    } else
    {
        output += "OrderID: " + getActiveOrderId();
        output += "\n";
    }

    // print time left
        if (!busy)
    {
        output += "TimeLeft: None";
        output += "\n";
    } else
    {
        output += "TimeLeft: " + getDistanceLeft();
        output += "\n";
    }

    // print orders left
        output += "OrdersLeft: " + ordersLeft;
        output += "\n";

    return output;
}
