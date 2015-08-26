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
  currentOrderNumber = 1;
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

void CommodityMarketSystem::printErrorMessage(string errorMessage) {
  cout << "ERROR: " << errorMessage << endl;
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
    cout << dealer << " POST" << endl;
    // string side = args[0];
    // string commodity = args[1];
    // int amount = stoi(args[2]);
    // double price = stod(args[3]);
}

void CommodityMarketSystem::revokeOrder(string dealer, vector<string> args) {
  cout << dealer << " REVOKE" << endl;
}

void CommodityMarketSystem::checkOrder(string dealer, vector<string> args) {
  cout << dealer << " CHECK" << endl;
}

void CommodityMarketSystem::listOrders(string dealer, vector<string> args) {
  cout << dealer << " LIST" << endl;
}

void CommodityMarketSystem::aggressOrders(string dealer, vector<string> args) {
  cout << dealer << " AGGRESS" << endl;
  // vector<int> order_ids;
  // vector<int> order_amounts;
}