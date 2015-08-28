#ifndef COMMODITYMARKETSYSTEM_H
#define COMMODITYMARKETSYSTEM_H

#include "Printer.h"
#include "Order.h"
#include <map>
#include <vector>
#include <string>
#include <set>

class CommodityMarketSystem {
  // Bookkeeping, terminal printer, and data
  int currentOrderNumber;
  std::map<int, Order*> orders;
  Printer printer;
  
  // Instruction validation and execution
  void postOrder(std::string dealer, std::vector<std::string> args);
  bool validatePostArgs(std::vector<std::string> postArgs);

  void revokeOrder(std::string dealer, std::vector<std::string> args);
  bool validateRevokeArgs(std::vector<std::string> postArgs);

  void checkOrder(std::string dealer, std::vector<std::string> args);
  bool validateCheckArgs(std::vector<std::string> postArgs);

  void listOrders(std::string dealer, std::vector<std::string> args);
  bool validateListArgs(std::vector<std::string> postArgs);

  void aggressOrders(std::string dealer, std::vector<std::string> args);
  bool validateAggressArgs(std::vector<std::string> postArgs);

  void executeInstruction(std::string dealer, std::string instruction, 
                          std::vector<std::string> args);

  // Helper functions
  std::vector<std::string> createCommandArray(std::string command);
  std::set<Order*> filterOrders(std::string commodityFilter, 
                                std::string dealerFilter);
  bool isPureIntegerString(std::string s);
  bool isPureDoubleString(std::string s);
  
 public:
  CommodityMarketSystem();
  ~CommodityMarketSystem();
  void processInput(std::string command);
};

#endif // COMMODITYMARKETSYSTEM_H
