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


SimulateStep::SimulateStep(int numOfSteps)
{
    
}


AddOrder::AddOrder(int id) : customerId(id){}
void AddOrder::act(WareHouse &wareHouse)
{
    int orderId(wareHouse.setOrderId());
    int distance(wareHouse.getCustomer(customerId).getCustomerDistance());
    Order newOrder(orderId,customerId,distance);
    wareHouse.addOrder(&newOrder);
}

string AddOrder::toString() const
{
    //todo
} 
AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);//????
}

AddCustomer::AddCustomer(string customerName, string customerType, int distance, int maxOrders) : customerName(customerName),distance(distance),maxOrders(maxOrders)
{
    if (customerType == "solider")
    {
        AddCustomer::customerType = CustomerType::Soldier;
    }
    
}
void AddCustomer::act(WareHouse &wareHouse) 
{
    int CustomerId = wareHouse.setCustomerId();

    wareHouse
}