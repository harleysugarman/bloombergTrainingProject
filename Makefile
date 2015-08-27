CPP = g++
OFLAG = -o
CXXFLAGS = -std=c++0x

base: Launcher.cpp Order.h Order.cpp CommodityMarketSystem.h \
      CommodityMarketSystem.cpp Printer.h Printer.cpp Database.h
	$(CPP) $(CXXFLAGS) Launcher.cpp Order.cpp \
                           CommodityMarketSystem.cpp Printer.cpp \
                           $(OFLAG) base
