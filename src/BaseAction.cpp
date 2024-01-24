#include "../include/BaseAction.h"
#include <iostream>



BaseAction::BaseAction()
{
    //TODO
}
ActionStatus BaseAction::getStatus() const
{
    return status;
}
void BaseAction::complete()
{
    status = ActionStatus::COMPLETED;
}
void BaseAction::error(string errorMsg)
{
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
    std::cout << "Error: " << errorMsg << std::endl;
}
string BaseAction::getErrorMsg() const
{
    return errorMsg;
}


SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse &wareHouse)
{

}


AddOrder::AddOrder(int id) : customerId(id){}

void AddOrder::act(WareHouse &wareHouse)
{
    int orderId(wareHouse.setOrderId());
    int distance(wareHouse.getCustomer(customerId).getCustomerDistance());
    Order *newOrder = new Order(orderId,customerId,distance);
    wareHouse.addOrder(newOrder);
}

string AddOrder::toString() const
{
    //todo
} 
AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);//????
}



AddCustomer::AddCustomer(string customerName, string customerType, int distance, int maxOrders) : customerName(customerName),distance(distance),maxOrders(maxOrders), customerType(convert(customerType)){}

const CustomerType AddCustomer::convert(string customerType)
{
    if (customerType == "solider")
    {
        return CustomerType::Soldier;
    } else {
        return CustomerType::Civilian;
    }
    
}
void AddCustomer::act(WareHouse &wareHouse) 
{
    int customerId = wareHouse.setCustomerId();
    if (customerType == CustomerType::Soldier)
    {
        SoldierCustomer *newSoliderCustomer = new SoldierCustomer(customerId, customerName, distance, maxOrders);
        wareHouse.addCustomer(newSoliderCustomer);
    } else {
        CivilianCustomer *newCvilianCustomer = new CivilianCustomer(customerId, customerName, distance, maxOrders);
        wareHouse.addCustomer(newCvilianCustomer);
    }
}
AddCustomer *AddCustomer::clone() const
{
    //TODO
}
string AddCustomer::toString() const
{
    //TODO
}



PrintOrderStatus::PrintOrderStatus(int id) : orderId(id){}

void PrintOrderStatus::act(WareHouse &wareHouse)
{
    wareHouse.getOrder(orderId).toString();
    // remember to make sure wareHouse throw an error if order doesn't exist
}
PrintOrderStatus *PrintOrderStatus::clone() const
{
    //TODO
}
string PrintOrderStatus::toString() const
{
    //TODO
}


PrintCustomerStatus::PrintCustomerStatus(int id) : customerId(id){}

void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    std::cout << "CustomerID: " << customerId << std::endl;
    vector<int> orderIds = wareHouse.getCustomer(customerId).getOrdersIds();
    for (int orderId : orderIds)
    {
        std::cout << "OrderID: " << orderId << std::endl;
        wareHouse.getOrder(orderId).printOrderStatus();
    }
    // remember to make sure wareHouse throw an error if customer doesn't exist
}
PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    //TODO
}
string PrintCustomerStatus::toString() const
{
    //TODO
}