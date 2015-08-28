#ifndef PRINTER_H
#define PRINTER_H

#include "Order.h"
#include <string>

class Printer {
 public:
  Printer();
  ~Printer();
  void printWelcomeMessage();
  void printPostConfirmation(Order order);
  void printOrderInfo(Order order);
  void printTradeReport(std::string boughtOrSold, int amount, Order order);
  void printRevokedOrder(int orderID);
  void printFilledStatus(int orderID);
  void printError(std::string errorText);
};

#endif // PRINTER_H