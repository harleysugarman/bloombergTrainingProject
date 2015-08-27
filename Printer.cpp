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
	cout << "PRINT POST" << endl;
}

void Printer::printOrderInfo(Order order) {

}

void Printer::printTradeReport() {

}

void Printer::printRevokedOrder(Order order) {

}

void Printer::printError(string errorText) {
	cout << "ERROR: " << errorText << endl;
}