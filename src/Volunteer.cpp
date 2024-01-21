#include "../include/Volunteer.h"
#include "../include/WareHouse.h"
#include "../include/Order.h"

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
// do i need to do something with the virtual funcs?


CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown): Volunteer(id, name), coolDown(coolDown), timeLeft(0){}
CollectorVolunteer *CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this); //???
}
void CollectorVolunteer::step()
{
    if (timeLeft != 0 && decreaseCoolDown()){
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
    if(!canTakeOrder(order)){
        //ERROR
    }
    activeOrderId = order.getId();
    timeLeft = coolDown;
}
string CollectorVolunteer::toString() const
{
    //TODO
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
    //TODO
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
    return (!isBusy() && order.distance <= maxDistance && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING);
    // HOW TO CHECK IF ORDER DISTANCE IS SMALLER THAN MAXDISTANCE???
}
void DriverVolunteer::acceptOrder(const Order &order)
{
    if(!canTakeOrder(order)){
        //ERROR
    }
    activeOrderId = order.getId();
    distanceLeft = order.distance;
}
void DriverVolunteer::step()
{
    if (distanceLeft > 0 && decreaseDistanceLeft()){
        activeOrderId = NO_ORDER;
        distanceLeft = 0;
    }
}
string DriverVolunteer::toString() const
{
    //TODO
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
    return (!isBusy() && order.distance <= maxDistance && hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING);
    // HOW TO CHECK IF ORDER DISTANCE IS SMALLER THAN MAXDISTANCE???
}
void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    if(!canTakeOrder(order)){
        //ERROR
    }
    activeOrderId = order.getId();
    distanceLeft = order.distance;
    --ordersLeft;
}
string LimitedDriverVolunteer::toString() const
{
    //TODO
}
