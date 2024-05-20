# Warehouse_Sim

## Overview

Warehouse_Sim is a C++ simulation of a food warehouse management system set in the fictional country of SPLand during a war. This program simulates the complex operations of a warehouse distributing food supplies, integrating various functionalities to manage and streamline the efforts of volunteers and ensure efficient delivery to citizens in need.

The warehouse order handling policy is as follows:

![Workflow Diagram](https://github.com/tokerido/Warehouse_Sim/assets/155316070/5527fdb3-4efc-4f2c-9a2f-07ab481942d0)

## Key Components

### Volunteers
The system includes different volunteer roles, such as Collectors and Drivers:
- **Collectors** are responsible for gathering orders within the warehouse.
- **Drivers** ensure the delivery of orders to customers.
- Both roles include "limited" versions, where volunteers can only handle a specific number of orders before they exit the system.

### Customers
There are two types of customers in the system:
- **Soldier Customers** who are part of the military forces of SPLand.
- **Civilian Customers** who are regular inhabitants affected by the war.

Each customer type has unique attributes and requirements, influencing how orders are handled and delivered.

### Orders
Orders transition through several stages:
- **Pending**: Orders await assignment to a volunteer.
- **Collecting**: Assigned to collectors for gathering.
- **Delivering**: Assigned to drivers for delivery.
- **Completed**: Successfully delivered to the customer.

The system tracks each order's status and provides updates as it moves through these stages.

### Simulation Control
The simulation is initiated with a configuration file that sets the initial state of the warehouse, including pre-existing volunteer and customer data. The system responds to user commands to manipulate this environment, providing a dynamic, real-time simulation experience.

### Interactive Commands
Users can control the simulation through commands that allow:
- Adding and managing volunteers and customers.
- Placing and tracking orders.
- Progressing through simulation steps to see the impact of various actions.


## Copyright Notice

© 2024 by Nitai Edelberg and Ido Toker. All rights reserved.

This project is a part of academic work at Ben Gurion University. Unauthorized use, copying, or distribution is prohibited.
