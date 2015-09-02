#ifndef PRINTER_H
#define PRINTER_H

#include "Order.h"
#include <string>

/**
 * CLASS: PRINTER
 * This class provides methods used to print output from the CMS to the 
 * terminal. It is provided as an object to the CMS class.
 */
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