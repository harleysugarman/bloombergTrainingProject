#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

class Order {
  int id;
  string dealer;
  string commodity;
  string side;
  int amount;
  double price;
 public:
  Order(int idParam, string dealerParam, string commodityParam,
        string sideParam, int amountParam, double priceParam);
  ~Order();
  void updateAmount(int newAmount);
  // Getters
  int getID();
  string getDealer();
  string getCommodity();
  string getSide();
  int getAmount();
  double getPrice();
};

#endif // ORDER_H
