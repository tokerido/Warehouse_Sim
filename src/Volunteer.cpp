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


CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown): Volunteer(id, name), coolDown(coolDown){}
CollectorVolunteer *CollectorVolunteer::clone() const{} //override?
void CollectorVolunteer::step(){} //override?
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
    
}