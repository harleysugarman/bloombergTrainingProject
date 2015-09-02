#include "Printer.h"
#include "Order.h"
#include <iostream>
using namespace std;

Printer::Printer() { }

Printer::~Printer() { }

 // Prints a welcome message to the console
 void Printer::printWelcomeMessage() {
  cout << "Welcome to the Bloomberg Commodity Marketplace." << endl;
  cout << "The database has been initialized as empty." << endl;
  cout << "Please enter your command below (or QUIT to exit):" << endl;
}

/*
 * Prints a post confirmation. Example:
 * 1 DB SELL GOLD 1000000 1174.6 HAS BEEN POSTED
 */
void Printer::printPostConfirmation(Order order) {
  cout << order.getID() << " " << order.getDealer() << " ";
  cout << order.getSide() << " " << order.getCommodity() << " ";
  cout << order.getAmount() << " " << order.getPrice() << " ";
  cout << "HAS BEEN POSTED" << endl;
}

/*
 * Prints an order's information. Example:
 * 1 DB SELL GOLD 1000000 1174.6
 */
void Printer::printOrderInfo(Order order) {
  cout << order.getID() << " " << order.getDealer() << " ";
  cout << order.getSide() << " " << order.getCommodity() << " ";
  cout << order.getAmount() << " " << order.getPrice() << endl;
}

/*
 * Print's a dealer's trade report. Example:
 * BOUGHT 250000 GOLD @ 1174.6 FROM DB
 */
void Printer::printTradeReport(string boughtOrSold, int amount, Order order) {
  cout << boughtOrSold << " " << amount << " " << order.getCommodity();
  cout << " @ " << order.getPrice() << " FROM " << order.getDealer() << endl;
}

// Prints a "REVOKED" confirmation message for an order
void Printer::printRevokedOrder(int orderID) {
  cout << orderID << " HAS BEEN REVOKED" << endl;
}

// Prints a "FILLED" confirmation message for an order
void Printer::printFilledStatus(int orderID) {
  cout << orderID << " HAS BEEN FILLED" << endl;
}

// General-purpose function for printing error messages
void Printer::printError(string errorText) {
  cout << "ERROR: " << errorText << endl;
}
