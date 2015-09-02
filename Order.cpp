#include "order.h"
using namespace std;

Order::Order(int idParam, string dealerParam, string commodityParam,
             string sideParam, int amountParam, double priceParam) {
  id = idParam;
  dealer = dealerParam;
  commodity = commodityParam;
  side = sideParam;
  amount = amountParam;
  price = priceParam;
}

Order::~Order() { }

// Setter for amount
void Order::updateAmount(int newAmount) {
  amount = newAmount;
}

// Getters
int Order::getID() {
  return id;
}

string Order::getDealer() {
  return dealer;
}

string Order::getCommodity() {
  return commodity;
}

string Order::getSide() {
  return side;
}

int Order::getAmount() {
  return amount;
}

double Order::getPrice() {
  return price;
}
