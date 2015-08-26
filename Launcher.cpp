#include "Order.h"
#include "CommodityMarketSystem.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void printWelcomeMessage() {
  cout << "Welcome to the Bloomberg Commodity Marketplace." << endl;
  cout << "The database has been initialized as empty." << endl;
  cout << "Please enter your command below (or QUIT to exit):" << endl;
}

int main() {
  CommodityMarketSystem cms;
  printWelcomeMessage();
  while (true) {
    string command;
    cout << "> ";
    getline(cin, command);
    if (command.compare("QUIT") == 0) break;
    cms.processInput(command);
  }
  return 0;
}
