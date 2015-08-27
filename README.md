File Structure:

Order.h/.cpp
class with:
  - id
  - dealer
  - commodity
  - sell/buy
  - number of contracts
  - price per contract

CommodityMarketSystem.h/.cpp
class that:
  - creates orders
  - checks if orders can be filled
  -

Database.h
  - Contains enumerated values for all types

Launcher.cpp
  - Creates CMS
  - Launches app

TODO:
- Store order map on the heap