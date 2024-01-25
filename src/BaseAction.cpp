#include "../include/BaseAction.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
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
}
string BaseAction::getErrorMsg() const
{
    return errorMsg;
}


SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse &wareHouse)
{
    //TODO
}
string SimulateStep::toString() const
{
    //todo
} 
SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(*this);//????
}


AddOrder::AddOrder(int id) : customerId(id){}

void AddOrder::act(WareHouse &wareHouse)
{
    int distance;
    try
    {
       distance = wareHouse.getCustomer(customerId).getCustomerDistance();
       int orderId(wareHouse.setOrderId());
       Order *newOrder = new Order(orderId,customerId,distance);
       wareHouse.addOrder(newOrder);

       complete();
       wareHouse.addAction(this);
    }
    catch(const std::exception& e)
    {
        error("”Cannot place this order");
        std::cerr << e.what() << '\n';
    }
    

    
    
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
    complete();
    wareHouse.addAction(this);
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
    string output;

    try
    {
        output = wareHouse.getOrder(orderId).toString();
        std::cout << output << std::endl;

        complete();
        wareHouse.addAction(this);
    }
    catch(const std::runtime_error& e)
    {
        error("“Order doesn't exist");
        std::cerr << e.what() << std::endl;;
    }
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
    vector<int> orderIds;

    try
    {
        orderIds = wareHouse.getCustomer(customerId).getOrdersIds();
        string output = "CustomerID: " + customerId;
        output = "\n";

        for (int orderId : orderIds)
        {
            output += "OrderID: " + orderId;
            output += "\n";
            output += wareHouse.getOrder(orderId).printOrderStatus();
            output += "\n";
        }

        std::cout << output << std::endl;
        
        complete();
        wareHouse.addAction(this);
    }
    catch(const std::runtime_error& e)
    {
        error("Customer doesn't exist");
        std::cerr << e.what() << std::endl;
    }

    
}
PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    //TODO
}
string PrintCustomerStatus::toString() const
{
    //TODO
}


PrintVolunteerStatus::PrintVolunteerStatus(int id) : VolunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse)
{
    string output;
    try
    {
        output = wareHouse.getVolunteer(VolunteerId).toString();
        
        std::cout << output << std::endl;   
        
        complete();
        wareHouse.addAction(this);
    }
    catch(const std::runtime_error& e)
    {
        error("Volunteer doesn't exist");
        std::cerr << e.what() << std::endl;;
    }
 
}
PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    //TODO
}
string PrintVolunteerStatus::toString() const
{
    //TODO
}


PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog::act(WareHouse &wareHouse)
{
    string output;
    vector<BaseAction*> actionsLog = wareHouse.getActionsLog();
    for(BaseAction *action : actionsLog)
    {
        output += action->toString();
        output += "\n";
    }

    std::cout << output << std::endl;

    complete();
    wareHouse.addAction(this);
}
PrintActionsLog *PrintActionsLog::clone() const
{
    //TODO
}
string PrintActionsLog::toString() const
{
    //TODO
}