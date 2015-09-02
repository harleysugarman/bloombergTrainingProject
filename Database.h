#ifndef DATABASE_H
#define DATABASE_H

#include <string>

// Valid dealer IDs
const std::string DealerIDs[] = { "DB", "JPM", "UBS", "RBC", "BARX",
                             	  "MS", "CITI", "BOFA", "RBS", "HSBC" };

// Valid commodities
const std::string Commodities[] = { "GOLD", "SILV", "PORK", "OIL", "RICE" };

// Valid order sides
const std::string Sides[] = { "BUY", "SELL" };

#endif // DATABASE_H
