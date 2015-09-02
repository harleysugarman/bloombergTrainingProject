#include "CommodityMarketSystem.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void runCMS();

int main(int argc, char* argv[]) {
  if (argc == 2 && strcmp(argv[1], "base") == 0) {
    runCMS();
    return 0;
  }
  if (argc == 3 && strcmp(argv[1], "ext1") == 0) {
    cout << "EXTENSION 1 NOT IMPLEMENTED" << endl;
    return 1;
  }
  if (argc == 3 && strcmp(argv[1], "ext2") == 0) {
    cout << "EXTENSION 2 NOT IMPLEMENTED" << endl;
    return 2;
  }
  cout << "INVALID PROGRAM CALL" << endl;
  return 3;
}

void runCMS() {
  CommodityMarketSystem cms;
  string command = "";
  while (true) {
    cout << "> ";
    getline(cin, command);
    if (command.compare("QUIT") == 0) break;
    cms.processInput(command);
  }
}