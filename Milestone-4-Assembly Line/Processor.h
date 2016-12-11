#ifndef  PROCESSOR_H_
#define PROCESSOR_H_

// Assembly Line Milestone - Processor Interface
// Processor.h
// Chris Szalwinski
// v1.0 - 30/11/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <functional>
#include "CustomerOrder.h"
#include "Task.h"

class Item;
class OrderManager;

class Processor : public Task {
	Item* item_;                        // address of item processed by this task 
	std::deque<CustomerOrder> waiting;  // orders to be processed
	std::deque<CustomerOrder> process;  // orders being processed
	std::deque<CustomerOrder> complete; // orders completed 
	unsigned int num_end_slots;         // number of currently empty end slots
	bool is_a_filler;                   // type of processor (filler, retriever)
	std::function<Task::Quality(int)> inspector; // inspects the quality
	static int sizeOfItem;
public:
	Processor(const std::string& record, std::function<Task::Quality(int)>);
	void load(Item&);
	void accept(CustomerOrder&&);
	void pass(int);
	void advance();
	bool empty() const;
	bool readyToShip() const;
	bool readyToPass() const;
	void ship(OrderManager&);
	void display(std::ostream&) const;
	const std::string& operator[](unsigned int) const;
};

#endif