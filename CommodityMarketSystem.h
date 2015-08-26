#ifndef COMMODITYMARKETSYSTEM_H
#define COMMODITYMARKETSYSTEM_H

#include "Order.h"
#include <vector>
#include <string>
using namespace std;

class CommodityMarketSystem {
  // Bookkeeping and data
  int currentOrderNumber;
  vector<Order> orders;
  
  // Instructions
  void postOrder(string dealer, vector<string> args);
  void revokeOrder(string dealer, vector<string> args);
  void checkOrder(string dealer, vector<string> args);
  void listOrders(string dealer, vector<string> args);
  void aggressOrders(string dealer, vector<string> args);
  
  // Helper functions
  void printErrorMessage(string errorMessage);
  vector<string> createCommandArray(string command);
  void executeInstruction(string dealer, string instruction, 
                          vector<string> args);
  void printOutputMessage();
  
 public:
  CommodityMarketSystem();
  ~CommodityMarketSystem();
  void processInput(string command);
};

#endif // COMMODITYMARKETSYSTEM_H
