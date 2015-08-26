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
  
  // Instruction execution
  void postOrder(string dealer, vector<string> args);
  bool validatePostArgs(vector<string> postArgs);

  void revokeOrder(string dealer, vector<string> args);
  bool validateRevokeArgs(vector<string> postArgs);

  void checkOrder(string dealer, vector<string> args);
  bool validateCheckArgs(vector<string> postArgs);

  void listOrders(string dealer, vector<string> args);
  bool validateListArgs(vector<string> postArgs);

  void aggressOrders(string dealer, vector<string> args);
  bool validateAggressArgs(vector<string> postArgs);

  void executeInstruction(string dealer, string instruction, 
                          vector<string> args);

  // Helper functions
  vector<string> createCommandArray(string command);
  void printErrorMessage(string errorMessage);
  void printOutputMessage();
  bool isPureIntegerString(string s);
  bool isPureDoubleString(string s);
  
 public:
  CommodityMarketSystem();
  ~CommodityMarketSystem();
  void processInput(string command);
};

#endif // COMMODITYMARKETSYSTEM_H
