# Commodity Market System

## Basic Information
- Name: Harley Sugarman
- Project Title: Commodity Market System
- Parts Implemented: base

## Instructions
- Unzip archive folder into its own directory
- Build executable using `make`
- Make sure the 'cms' executable file has been created
- Run base project using `./cms base`

## Implementation Overview

### Order.h/.cpp
This class stores information about a single order and provides getters and 
setters for any relevant information.

### CommodityMarketSystem.h/.cpp
This class is in charge of processing and storing order information. Detailed 
notes on each command can be found in the initial assignment. Most 
documentation can be found within the code, with most complexities noted using 
inline comments. Notice that the only public method accessible for users of 
this class is `processInput(string command)`. This is intentional so that 
clients of this class cannot either intentionally or unintentionally alter the 
contents of the order database.

### Printer.h/.cpp
This class provides methods used to print output from the CMS to the terminal. 
It is provided as an object to the CMS class.

### Database.h
This header file provides a list of valid dealer IDs, commodities, and order 
sides (BUY/SELL).

### Launcher.cpp
This file provides the code used to create and launch a CMS instance and 
process the input.

## Known issues/other notes
Developed on a Macbook Pro using C++11