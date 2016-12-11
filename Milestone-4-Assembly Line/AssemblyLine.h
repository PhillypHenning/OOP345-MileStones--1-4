#pragma once
// Assembly Line Milestone - Assembly Line Interface
// AssemblyLine.h
// Chris Szalwinski
// v1.0 - 30/11/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <vector>

class Processor;
class ItemManager;
class OrderManager;

class AssemblyLine : public std::vector<Processor> {
public:
	// initialize
	void push_back(Processor&&);
	void validate(std::ostream&);
	void validate(ItemManager&, std::ostream&);
	void loadItem(ItemManager&);
	// processing
	void loadOrders(OrderManager&, const std::string&, std::ostream&);
	bool process(OrderManager&, unsigned int);
	// reporting
	void display(std::ostream&) const;
};