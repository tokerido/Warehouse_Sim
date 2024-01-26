#include "../include/BaseAction.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include <iostream>

extern WareHouse* backup;

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
    string output = "simulateStep " + numOfSteps;

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    } 
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
    string output = "order " + customerId;

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }   
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
    string output = "customer " + customerName;

    if (customerType == CustomerType::Civilian)
    {
        output += " civilian ";
    } else
    {
        output += " solider ";
    }
    output += distance;
    output += " ";
    output += maxOrders;
    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    } 
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
        wareHouse.addAction(this);
        std::cerr << e.what() << std::endl;;
    }
}
PrintOrderStatus *PrintOrderStatus::clone() const
{
    //TODO
}
string PrintOrderStatus::toString() const
{
    string output = "orderStatus " + orderId;

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
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
        wareHouse.addAction(this);
        std::cerr << e.what() << std::endl;
    }

    
}
PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    //TODO
}
string PrintCustomerStatus::toString() const
{
    string output = "customerStatus " + customerId;

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
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
        wareHouse.addAction(this);
        std::cerr << e.what() << std::endl;
    }
 
}
PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    //TODO
}
string PrintVolunteerStatus::toString() const
{
    string output = "volunteerStatus " + VolunteerId;

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
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
    string output = "log ";

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
}


Close::Close(){};

void Close::act(WareHouse &wareHouse)
{
    complete();
    wareHouse.addAction(this);
    wareHouse.close();
    // make sure warehouse.close() do all the printing, free the memory and exit!!!
}
string Close::toString() const
{
        string output = "close";

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
}


BackupWareHouse::BackupWareHouse(){};

void BackupWareHouse::act(WareHouse &wareHouse)
{
    delete backup;
    backup = nullptr;
    backup = new WareHouse(wareHouse);
    complete();
    backup->addAction(this);
}
BackupWareHouse *BackupWareHouse::clone() const
{
    //TODO
}
string BackupWareHouse::toString() const
{
    string output = "backup ";

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
}


RestoreWareHouse::RestoreWareHouse(){}

void RestoreWareHouse::act(WareHouse &wareHouse)
{

    try
    {
        if(backup == nullptr)
        {
            throw "No backup available";
        } else
        {
            wareHouse.clear(); // make sure clear() delete everything
            wareHouse = *backup; // make sure operator "=" copies everything correctly
            complete();
            wareHouse.addAction(this);
        }   
    }
    catch(const std::exception& e)
    {
        error("No backup available");
        wareHouse.addAction(this);
        std::cerr << e.what() << '\n';
    }
}
RestoreWareHouse *RestoreWareHouse::clone() const
{
    //TODO
}
string RestoreWareHouse::toString() const
{
    string output = "restore ";

    if (getStatus() == ActionStatus::COMPLETED)
    {
        return output + " Completed";
    } else
    {
        return output + " Error: " + getErrorMsg();
    }
}