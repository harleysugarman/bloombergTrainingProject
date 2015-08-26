CPP = g++
OFLAG = -o

base: Launcher.cpp Order.h Order.cpp CommodityMarketSystem.h \
CommodityMarketSystem.cpp Database.h
	$(CPP) Launcher.cpp Order.cpp CommodityMarketSystem.cpp $(OFLAG) base
