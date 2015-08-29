#include "Printer.h"
#include "Order.h"
#include <iostream>
using namespace std;

Printer::Printer() { }

Printer::~Printer() { }

void Printer::printWelcomeMessage() {
  cout << "Welcome to the Bloomberg Commodity Marketplace." << endl;
  cout << "The database has been initialized as empty." << endl;
  cout << "Please enter your command below (or QUIT to exit):" << endl;
}

void Printer::printPostConfirmation(Order order) {
  cout << order.getID() << " " << order.getDealer() << " ";
  cout << order.getSide() << " " << order.getCommodity() << " ";
  cout << order.getAmount() << " " << order.getPrice() << " ";
  cout << "HAS BEEN POSTED" << endl;
}

void Printer::printOrderInfo(Order order) {
  cout << order.getID() << " " << order.getDealer() << " ";
  cout << order.getSide() << " " << order.getCommodity() << " ";
  cout << order.getAmount() << " " << order.getPrice() << endl;
}

void Printer::printTradeReport(string boughtOrSold, int amount, Order order) {
  cout << boughtOrSold << " " << amount << " " << order.getCommodity();
  cout << " @ " << order.getPrice() << " FROM " << order.getDealer() << endl;
}

void Printer::printRevokedOrder(int orderID) {
  cout << orderID << " HAS BEEN REVOKED" << endl;
}

void Printer::printFilledStatus(int orderID) {
  cout << orderID << " HAS BEEN FILLED" << endl;
}

void Printer::printError(string errorText) {
  cout << "ERROR: " << errorText << endl;
}
