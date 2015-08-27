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

}

void Printer::printTradeReport() {

}

void Printer::printRevokedOrder(int orderID) {
  cout << orderID << " HAS BEEN REVOKED" << endl;
}

void Printer::printError(string errorText) {
	cout << "ERROR: " << errorText << endl;
}