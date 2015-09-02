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

/*
 * Process a string input by the user into an instruction, then execute 
 * instruction using the functions below.
 */
void CommodityMarketSystem::processInput(string command) {
  vector<string> commandArray = createCommandArray(command);
  if (commandArray.size() < 2) {
    printer.printError("INVALID_MESSAGE");
    return;
  }
  string dealer = commandArray[0];
  if (isValidDealer(dealer)) {
    string instruction = commandArray[1];
    vector<string> args(commandArray.begin()+2, commandArray.end());
    executeInstruction(dealer, instruction, args);
  }
  else printer.printError("UNKNOWN_DEALER");
}

/*
 * Checks to make sure instruction is valid, then calls the relevant
 * command.
 */
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

/****************************** POST ******************************/

/*
 * Post an order to the system. Create a new Order object using the given
 * arguments, then add the order to the CMS orders map. Increment 
 * currentOrderNumber.
 */
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

/****************************** END POST ******************************/

/****************************** REVOKE ******************************/

/*
 * Remove an order from the system. If the orderID is valid and the dealer 
 * issuing the command is authorized, delete the entry from the orders map.
 */
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

/****************************** END REVOKE ******************************/

/****************************** CHECK ******************************/

/*
 * Check on the status of an order. If the dealer is authorized and the user is 
 * valid, print either:
 * - the order information if the order has not yet been filled
 * - a filled message otherwise
 */
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

/****************************** END CHECK ******************************/

/****************************** LIST ******************************/

/*
 * List all orders that satisfy the given filters. The user may provide filters 
 * for the dealer and the commodity, and this function prints an order 
 * information message for every unfilled order that satisfies the given 
 * constraints.
 */
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

/****************************** END LIST ******************************/

/****************************** AGGRESS ******************************/

/*
 * Aggress on a given order. If the order number is valid, and the number of
 * units supplied is less than or equal to the number of units remaining in 
 * the order, make the transaction and update the orders map accordingly. Then 
 * print a success message to the terminal.
 */
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

/****************************** END AGGRESS ******************************/

/*
 *
 */
vector<string> CommodityMarketSystem::createCommandArray(string command) {
  vector<string> commandArray;
  stringstream ss(command);
  string word;
  while (ss >> word) {
    commandArray.push_back(word);
  }
  return commandArray;
}

// Helper: checks if a given commodity is valid
bool CommodityMarketSystem::isValidCommodity(string commodity) {
  return !(find(begin(Commodities), end(Commodities), commodity) == end(Commodities));
}

// Helper: checks if a given side is valid
bool CommodityMarketSystem::isValidSide(string side) {
  return !(find(begin(Sides), end(Sides), side) == end(Sides));
}

// Helper: checks if a given dealer is valid
bool CommodityMarketSystem::isValidDealer(string dealerID) {
  return !(find(begin(DealerIDs), end(DealerIDs), dealerID) == end(DealerIDs));
}

// Helper: checks if a given order ID is valid
bool CommodityMarketSystem::isValidOrder(int orderID) {
  return !(orders.find(orderID) == orders.end());
}

// Helper: checks if a given dealer is authorized on a given order
bool CommodityMarketSystem::isAuthorized(string requestingDealer, Order* order) {
  return (requestingDealer.compare(order->getDealer()) == 0);
}

// Helper: checks if a string is purely an integer. 
// Example: "123" is valid, "123.1", "123a" are not
bool CommodityMarketSystem::isPureIntegerString(string s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

// Helper: checks if a string is purely an integer of double.
// Example "123.1" is valid, "123.1.1", "123.1a" are not
bool CommodityMarketSystem::isPureDoubleString(string s) {
    char* endptr = 0;
    strtod(s.c_str(), &endptr);
    return !(*endptr != '\0' || endptr == s);
}
