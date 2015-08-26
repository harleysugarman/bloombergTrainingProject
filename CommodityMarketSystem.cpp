#include "Database.h"
#include "Order.h"
#include "CommodityMarketSystem.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;

CommodityMarketSystem::CommodityMarketSystem() {
  currentOrderNumber = 0;
}

CommodityMarketSystem::~CommodityMarketSystem() { }

void CommodityMarketSystem::processInput(string command) {
  if (command.length() > 255) {
    printErrorMessage("INVALID_MESSAGE");
    return;
  }
  vector<string> commandArray = createCommandArray(command);
  string dealer = commandArray[0];
  if (find(begin(DealerIDs), end(DealerIDs), dealer) != end(DealerIDs)) {
    string instruction = commandArray[1];
    vector<string> args(commandArray.begin()+2, commandArray.end());
    executeInstruction(dealer, instruction, args);
  }
  else printErrorMessage("UNKNOWN_DEALER");
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
    printErrorMessage("INVALID_MESSAGE");
  }
}

void CommodityMarketSystem::postOrder(string dealer, vector<string> args) {
    if (validatePostArgs(args)) {
      string side = args[0];
      string commodity = args[1];
      int amount = stoi(args[2]);
      double price = stod(args[3]);
      Order order(++currentOrderNumber, dealer, commodity, side, amount, price);
      orders.push_back(order);
      printOutputMessage();
      // Make new order, print output message
      // cout << dealer << " " << side " " << commodity << " " << endl;
    }
}

bool CommodityMarketSystem::validatePostArgs(vector<string> postArgs) {
  // check correct number of arguments
  if (postArgs.size() != 4) {
    printErrorMessage("INVALID_MESSAGE");
    return false;
  }
  // check string arguments
  string side = postArgs[0];
  string commodity = postArgs[1];
  if (find(begin(Sides), end(Sides), side) == end(Sides)) {
    printErrorMessage("INVALID_MESSAGE");
    return false;
  }
  if (find(begin(Commodities), end(Commodities), commodity) == end(Commodities)) {
    printErrorMessage("UNKNOWN_COMMODITY");
    return false;
  }
  // check numeric arguments
  string amountString = postArgs[2];
  string priceString = postArgs[3];
  if (!isPureIntegerString(amountString) || !isPureDoubleString(priceString)) {
    printErrorMessage("INVALID_MESSAGE");
    return false;    
  }
  // all arguments valid - return true
  return true;
}

void CommodityMarketSystem::revokeOrder(string dealer, vector<string> args) {
  cout << dealer << " REVOKE" << endl;
}

bool CommodityMarketSystem::validateRevokeArgs(vector<string> postArgs) {
  return false;
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

void CommodityMarketSystem::printErrorMessage(string errorMessage) {
  cout << "ERROR: " << errorMessage << endl;
}

void CommodityMarketSystem::printOutputMessage() {

}

bool CommodityMarketSystem::isPureIntegerString(string s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

bool CommodityMarketSystem::isPureDoubleString(string s) {
    char* endptr = 0;
    strtod(s.c_str(), &endptr);
    return !(*endptr != '\0' || endptr == s);
}
