// Manager Milestone - Main Program
// Milestome_3.cpp
// Chris Szalwinski
// v1.0 - 16/11/2015
// v2.0 - 15/01/2016
//Phillyp Henning
//055829147

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Task.h"
#include "TaskManager.h"
#include "CustomerOrder.h"
#include "OrderManager.h"
#include "Item.h"
#include "ItemManager.h"
#include "Utilities.h"

#define DEBUG

template<typename M, typename T>
void loadFromFile(const char*, M&, std::ostream&);
template<>
void loadFromFile<TaskManager, Task>(const char*, TaskManager&, std::ostream&);

int main(int argc, char** argv) {
	// process command line arguments
#ifdef DEBUG
	argc = 5;
	argv[0] = "w7";
	argv[1] = "CleanFileMalformedData.dat";
	argv[2] = "CleanCustomerOrderFileWmal.dat";
	argv[3] = "CleanItemFileWmal.dat";
	argv[4] = "|";
#endif
	
	
	if (argc != 5) {
		std::cerr << "*** invalid number of arguments ***\n"
			<< "Usage: " << argv[0] << " tasks_file order_file item_file delimiter\n";
		exit(1);
	}
	std::cout << "Command Line Arguments\n----------------------\n";
	std::cout << "Task File Specified           = " << argv[1] << "\n";
	std::cout << "Customer Order File Specified = " << argv[2] << "\n";
	std::cout << "Item File Specified           = " << argv[3] << "\n";
	std::cout << "File Record Field Delimiter   = " << argv[4][0] << "\n\n";
	Utilities::setDelimiter(argv[4][0]);
	// end of command line processing

	// Load, accept, validate and display the Tasks
	//
	std::cout << "Building the Network of Tasks\n-----------------------------\n";
	TaskManager taskManager;
	loadFromFile<TaskManager, Task>(argv[1], taskManager, std::cerr);
	taskManager.display(std::cout);
	std::cout << "\nValidating the Set of Tasks\n---------------------------\n";
	taskManager.validate(std::cerr);
	std::cout << "\nList of Accepted Tasks\n----------------------\n";
	taskManager.display(std::cout);

	// Load, accept and display the Customer Orders
	//
	std::cout << "\n*** Load and Accept the Customer Orders ***\n";
	OrderManager orderManager;
	loadFromFile<OrderManager, CustomerOrder>(argv[2], orderManager, std::cerr);
	std::cout << "\nList of Accepted Customer Orders\n--------------------------------\n";
	orderManager.display(std::cout);

	// Load, accept and display the Items in Stock
	//
	std::cout << "\n*** Load and accept the Items in Stock ***\n";
	ItemManager itemManager;
	loadFromFile<ItemManager, Item>(argv[3], itemManager, std::cerr);
	std::cout << "\nList of In-Stock Items\n----------------------\n";
	itemManager.display(std::cout, true);

	// Validate the Items in the Customer Orders
	orderManager.validate(itemManager, std::cout);

	// Validate the Tasks in each Item in Stock
	taskManager.validate(itemManager, std::cerr);

	// Fill the Customer Orders with the Items in Stock
	std::cout << "\n*** Fill the Customer Orders ***\n";
	for (auto i = itemManager.begin(); i != itemManager.end(); i++) {
		for (auto s = orderManager.begin(); s != orderManager.end(); s++)
				s->fill(*i);
	}

	// Display the Processed Customer Orders
	std::cout << "\nList of Processed Customer Orders\n---------------------------------\n";
	orderManager.display(std::cout);

	// Terminate
	std::cout << "\nDone!\nPress Enter Key to Exit ... ";
	char c;
	std::cin.get(c);
}

template<typename M, typename T>
void loadFromFile(const char* fileName, M& manager, std::ostream& os) {
	std::ifstream file(fileName);
	if (!file) {
		os << "*** Cannot open file named " << fileName << " ***\n";
		exit(1);
	}
	while (file) {
		std::string record;
		std::getline(file, record);
		if (file) {
			try {
				std::unique_ptr<T> entry(new T(record));
				if (!entry->empty())
					manager.push_back(std::move(*entry));
			}
			catch (const std::string& msg) {
				os << msg << std::endl;
			}
		}
	}
}

template<>
void loadFromFile<TaskManager, Task>(const char* fileName, TaskManager& manager, std::ostream& os) {
	std::ifstream file(fileName);
	if (!file) {
		os << "*** Cannot open file named " << fileName << " ***\n";
		exit(1);
	}
	while (file) {
		std::string record;
		std::getline(file, record);
		if (file) {
			try {
				std::unique_ptr<Task> entry(new Task(record));
				if (!entry->getName().empty())
					manager.push_back(std::move(*entry));
			}
			catch (const std::string& msg) {
				os << msg << std::endl;
			}
		}
	}
}
	