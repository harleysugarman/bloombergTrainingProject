#ifndef COMMODITYMARKETSYSTEM_H
#define COMMODITYMARKETSYSTEM_H

#include "Printer.h"
#include "Order.h"
#include <map>
#include <vector>
#include <string>
#include <set>

/**
 * CLASS: COMMODITY MARKET SYSTEM
 * This class is in charge of processing and storing order information.
 * Detailed notes on each command can be found in the initial assignment.
 */
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
  void aggressOrder(std::string dealer, int orderID, int amount);
  bool validateAggressArgs(std::vector<std::string> postArgs);

  void executeInstruction(std::string dealer, std::string instruction, 
                          std::vector<std::string> args);

  // Helper functions
  std::vector<std::string> createCommandArray(std::string command);
  std::set<Order*> filterOrders(std::string commodityFilter, 
                                std::string dealerFilter);
  bool isValidCommodity(std::string commodity);
  bool isValidSide(std::string side);
  bool isValidDealer(std::string dealerID);
  bool isValidOrder(int orderID);
  bool isAuthorized(std::string requestingDealer, Order* order);
  bool isPureIntegerString(std::string s);
  bool isPureDoubleString(std::string s);
  
 public:
  CommodityMarketSystem();
  ~CommodityMarketSystem();
  void processInput(std::string command);
};

#endif // COMMODITYMARKETSYSTEM_H
