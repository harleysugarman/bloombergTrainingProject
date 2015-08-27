CPP = g++
OFLAG = -o

base: Launcher.cpp Order.h Order.cpp CommodityMarketSystem.h \
CommodityMarketSystem.cpp Printer.h Printer.cpp Database.h
	$(CPP) Launcher.cpp Order.cpp CommodityMarketSystem.cpp Printer.cpp \
	$(OFLAG) base

