#ifndef ORDER_H
#define ORDER_H

#include <string>

/**
 * CLASS: ORDER
 * This class stores information about a single order and provides getters/
 * setters for any relevant information.
 */
class Order {
  int id;
  std::string dealer;
  std::string commodity;
  std::string side;
  int amount;
  double price;
 public:
  Order(int idParam, std::string dealerParam, std::string commodityParam,
        std::string sideParam, int amountParam, double priceParam);
  ~Order();
  void updateAmount(int newAmount);
  // Getters
  int getID();
  std::string getDealer();
  std::string getCommodity();
  std::string getSide();
  int getAmount();
  double getPrice();
};

#endif // ORDER_H
