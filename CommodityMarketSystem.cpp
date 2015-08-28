#include "Database.h"
#include "CommodityMarketSystem.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

CommodityMarketSystem::CommodityMarketSystem() {
  currentOrderNumber = 0;
  printer.printWelcomeMessage();
}

CommodityMarketSystem::~CommodityMarketSystem() {
  for (map<int, Order*>::iterator i = orders.begin(); i != orders.end(); i++) {
    delete i->second;
  }
  orders.clear();
}

void CommodityMarketSystem::processInput(string command) {
  if (command.length() == 0 || command.length() > 255) {
    printer.printError("INVALID_MESSAGE");
    return;
  }
  vector<string> commandArray = createCommandArray(command);
  string dealer = commandArray[0];
  if (isValidDealer(dealer)) {
    string instruction = commandArray[1];
    vector<string> args(commandArray.begin()+2, commandArray.end());
    executeInstruction(dealer, instruction, args);
  }
  else printer.printError("UNKNOWN_DEALER");
}

void CommodityMarketSystem::executeInstruction(string dealer, 
                                               string instruction,
                                               vector<string> args) {
  if (instruction.compare("POST") == 0) {
    postOrder(dealer, args);
  }
  else if (instruction.compare("REVOKE") == 0) {
    revokeOrder(dealer, args);
  }
  else if (instruction.compare("CHECK") == 0) {
    checkOrder(dealer, args);
  }
  else if (instruction.compare("LIST") == 0) {
    listOrders(dealer, args);
  }
  else if (instruction.compare("AGGRESS") == 0) {
    aggressOrders(dealer, args);
  }
  else {
    printer.printError("INVALID_MESSAGE");
  }
}

void CommodityMarketSystem::postOrder(string dealer, vector<string> args) {
    if (validatePostArgs(args)) {
      string side = args[0];
      string commodity = args[1];
      int amount = stoi(args[2]);
      double price = stod(args[3]);
      Order *order = new Order(++currentOrderNumber, dealer, commodity, 
                              side, amount, price);
      orders[currentOrderNumber] = order;
      printer.printPostConfirmation(*order);
    }
}

bool CommodityMarketSystem::validatePostArgs(vector<string> postArgs) {
  // check correct number of arguments
  if (postArgs.size() != 4) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  // check string arguments
  string side = postArgs[0];
  string commodity = postArgs[1];
  if (!isValidSide(side)) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  if (!isValidCommodity(commodity)) {
    printer.printError("UNKNOWN_COMMODITY");
    return false;
  }
  // check numeric arguments
  string amountString = postArgs[2];
  string priceString = postArgs[3];
  if (!isPureIntegerString(amountString) || !isPureDoubleString(priceString)) {
    printer.printError("INVALID_MESSAGE");
    return false;    
  }
  // all arguments valid - return true
  return true;
}

void CommodityMarketSystem::revokeOrder(string dealer, vector<string> args) {
  if (validateRevokeArgs(args)) {
    int orderID = stoi(args[0]);
    if (!isAuthorized(dealer, orders[orderID])) {
      printer.printError("UNAUTHORIZED");
      return;
    }
    delete orders[orderID];
    orders.erase(orderID);
    printer.printRevokedOrder(orderID);
  }
}

bool CommodityMarketSystem::validateRevokeArgs(vector<string> postArgs) {
  if (postArgs.size() != 1 || !isPureIntegerString(postArgs[0])) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  int orderID = stoi(postArgs[0]);
  if (!isValidOrder(orderID)) {
    printer.printError("UNKNOWN_ORDER");
    return false;
  }
  return true;
}

void CommodityMarketSystem::checkOrder(string dealer, vector<string> args) {
  if (validateCheckArgs(args)) {
    int orderID = stoi(args[0]);
    if (!isAuthorized(dealer, orders[orderID])) {
      printer.printError("UNAUTHORIZED");
      return;
    }
    Order *order = orders[orderID];
    if (order->getAmount() == 0) {
      printer.printFilledStatus(orderID);
    }
    else {
      printer.printOrderInfo(*order);
    }
  }
}

bool CommodityMarketSystem::validateCheckArgs(vector<string> postArgs) {
  if (postArgs.size() != 1 || !isPureIntegerString(postArgs[0])) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  int orderID = stoi(postArgs[0]);
  if (!isValidOrder(orderID)) {
    printer.printError("UNKNOWN_ORDER");
    return false;
  }
  return true;
}

void CommodityMarketSystem::listOrders(string dealer, vector<string> args) {
  if (validateListArgs(args)) {
    string commodityFilter = "";
    string dealerFilter = "";
    if (args.size() >= 1) {
      commodityFilter = args[0];
    }
    if (args.size() == 2) {
      dealerFilter = args[1];
    }
    set<Order*> ordersToPrint = filterOrders(commodityFilter, dealerFilter);
    for (Order *order : ordersToPrint) {
      if (order->getAmount() != 0) {
        printer.printOrderInfo(*order);
      }
    }
  }
}

bool CommodityMarketSystem::validateListArgs(vector<string> postArgs) {
  if (postArgs.size() > 2){
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  if (postArgs.size() >= 1) {
    string commodity = postArgs[0];
    if (!isValidCommodity(commodity)) {
      printer.printError("UNKNOWN_COMMODITY");
      return false;
    }
  }
  if (postArgs.size() == 2) {
    string dealer = postArgs[1];
    if (!isValidDealer(dealer)) {
      printer.printError("UNKNOWN_DEALER");
      return false;
    }
  }
  return true;
}

set<Order*> CommodityMarketSystem::filterOrders(string commodityFilter,
                                                string dealerFilter) {
  set<Order*> ordersToList;
  for (auto &order : orders) {
    // no filters set
    if (commodityFilter.empty() && dealerFilter.empty()) {
      ordersToList.insert(order.second);
    }
    // commodity filter set
    else if (dealerFilter.empty()) {
      if (commodityFilter.compare(order.second->getCommodity()) == 0) {
        ordersToList.insert(order.second);
      }
    }
    // both filters set
    else {
      if (commodityFilter.compare(order.second->getCommodity()) == 0 &&
          dealerFilter.compare(order.second->getDealer()) == 0) {
        ordersToList.insert(order.second);
      }
    }
  }
  return ordersToList;
}

void CommodityMarketSystem::aggressOrders(string dealer, vector<string> args) {
  if (validateAggressArgs(args)) {
    vector<int> ordersToAggress;
    vector<int> amountsToAggress;
    for (int i = 0; i < args.size(); i++) {
      if (i % 2 == 0) {
        ordersToAggress.push_back(stoi(args[i]));
      }
      if (i % 2 == 1) {
        amountsToAggress.push_back(stoi(args[i]));
      }
    }
    for (int i = 0; i < ordersToAggress.size(); i++) {
      aggressOrder(dealer, ordersToAggress[i], amountsToAggress[i]);
    }
  }
}

void CommodityMarketSystem::aggressOrder(string dealer, int orderID, int amount) {
  Order *order = orders[orderID];
  if (order->getAmount() >= amount) {
    int newBalance = order->getAmount() - amount;
    order->updateAmount(newBalance);
    bool aggressorIsSelling = (order->getSide().compare("BUY") == 0);
    string boughtOrSold = (aggressorIsSelling ? "SOLD" : "BOUGHT");
    printer.printTradeReport(boughtOrSold, amount, *order);
  }
  else {
    printer.printError("INVALID_MESSAGE");
  }
}

bool CommodityMarketSystem::validateAggressArgs(vector<string> postArgs) {
  if (postArgs.size() == 0 || postArgs.size() % 2 != 0) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  set<int> usedOrders;
  for (int i = 0; i < postArgs.size(); i++) {
    // check integer values
    if (!isPureIntegerString(postArgs[i])) {
      printer.printError("INVALID_MESSAGE");
      return false;      
    }
    // check order IDs
    if (i % 2 == 0) {
      if (!isValidOrder(stoi(postArgs[i]))) {
        printer.printError("UNKNOWN_ORDER");
        return false;
      }
      // cannot aggress on the same order twice in one command
      if (usedOrders.find(stoi(postArgs[i])) != usedOrders.end()) {
        printer.printError("INVALID_MESSAGE");
        return false;
      }
      usedOrders.insert(stoi(postArgs[i]));
    }
  }
  return true;
}

vector<string> CommodityMarketSystem::createCommandArray(string command) {
  vector<string> commandArray;
  stringstream ss(command);
  string word;
  while (ss >> word) {
    commandArray.push_back(word);
  }
  return commandArray;
}

bool CommodityMarketSystem::isValidCommodity(string commodity) {
  return !(find(begin(Commodities), end(Commodities), commodity) == end(Commodities));
}

bool CommodityMarketSystem::isValidSide(string side) {
  return !(find(begin(Sides), end(Sides), side) == end(Sides));
}

bool CommodityMarketSystem::isValidDealer(string dealerID) {
  return !(find(begin(DealerIDs), end(DealerIDs), dealerID) == end(DealerIDs));
}

bool CommodityMarketSystem::isValidOrder(int orderID) {
  return !(orders.find(orderID) == orders.end());
}

bool CommodityMarketSystem::isAuthorized(string requestingDealer, Order* order) {
  return (requestingDealer.compare(order->getDealer()) == 0);
}

bool CommodityMarketSystem::isPureIntegerString(string s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

bool CommodityMarketSystem::isPureDoubleString(string s) {
    char* endptr = 0;
    strtod(s.c_str(), &endptr);
    return !(*endptr != '\0' || endptr == s);
}
