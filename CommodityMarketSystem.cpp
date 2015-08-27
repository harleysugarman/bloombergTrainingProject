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
  for (map<int, Order*>::iterator i = orders.begin(); i != orders.end(); ++i) {
    delete (*i).second;
    orders.erase(i);
  }
}

void CommodityMarketSystem::processInput(string command) {
  if (command.length() > 255) {
    printer.printError("INVALID_MESSAGE");
    return;
  }
  vector<string> commandArray = createCommandArray(command);
  string dealer = commandArray[0];
  if (find(begin(DealerIDs), end(DealerIDs), dealer) != end(DealerIDs)) {
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
      Order* order = new Order(++currentOrderNumber, dealer, commodity, 
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
  if (find(begin(Sides), end(Sides), side) == end(Sides)) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  if (find(begin(Commodities), end(Commodities), commodity) == end(Commodities)) {
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
    if (!(dealer.compare(orders[orderID]->getDealer()) == 0)) {
      printer.printError("UNAUTHORIZED");
      return;
    }
    // TODO: DELETE ORDER
    orders.erase(orderID);
    printer.printRevokedOrder(*orders[orderID]);
  }
}

bool CommodityMarketSystem::validateRevokeArgs(vector<string> postArgs) {
  if (postArgs.size() != 1 || !isPureIntegerString(postArgs[0])) {
    printer.printError("INVALID_MESSAGE");
    return false;
  }
  int orderID = stoi(postArgs[0]);
  if (orders.find(orderID) == orders.end()) {
    printer.printError("UNKNOWN_ORDER");
    return false;
  }
  return true;
}

void CommodityMarketSystem::checkOrder(string dealer, vector<string> args) {
  cout << dealer << " CHECK" << endl;
}

bool CommodityMarketSystem::validateCheckArgs(vector<string> postArgs) {
  return false;
}

void CommodityMarketSystem::listOrders(string dealer, vector<string> args) {
  cout << dealer << " LIST" << endl;
}

bool CommodityMarketSystem::validateListArgs(vector<string> postArgs) {
  return false;
}

void CommodityMarketSystem::aggressOrders(string dealer, vector<string> args) {
  cout << dealer << " AGGRESS" << endl;
  // vector<int> order_ids;
  // vector<int> order_amounts;
}

bool CommodityMarketSystem::validateAggressArgs(vector<string> postArgs) {
  return false;
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

bool CommodityMarketSystem::isPureIntegerString(string s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

bool CommodityMarketSystem::isPureDoubleString(string s) {
    char* endptr = 0;
    strtod(s.c_str(), &endptr);
    return !(*endptr != '\0' || endptr == s);
}
