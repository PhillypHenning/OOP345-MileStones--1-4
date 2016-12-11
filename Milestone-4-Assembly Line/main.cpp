// Assembly Line Milestone - Main Program
// Milestome_4.cpp
// Chris Szalwinski
// v1.0 - 30/11/2015
// v2.0 - 15/01/2016
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Task.h"
#include "TaskManager.h"
#include "CustomerOrder.h"
#include "OrderManager.h"
#include "Item.h"
#include "ItemManager.h"
#include "Utilities.h"
#include "Processor.h"
#include "AssemblyLine.h"

#define DEBUG

template<typename M, typename T>
void loadFromFile(const char*, M&, std::ostream&);
template<>
void loadFromFile<TaskManager, Task>(const char*, TaskManager&, std::ostream&);
template<>
void loadFromFile<AssemblyLine, Processor>(const char*, AssemblyLine&, std::ostream&);

int main(int argc, char** argv) {
#ifdef DEBUG
	argc = 8;
	argv[1] = "CleanFileMalformedData.dat";
	argv[2] = "CleanCustomerOrderFileWmal.dat";
	argv[3] = "CleanItemFileWmal.dat";
	argv[4] = "Power Supply";
	argv[5] = "500";
	argv[6] = "|";
	argv[7] = "FTLine.log";
#endif
	// process command line arguments
	if (argc != 8) {
		std::cerr << "*** invalid number of arguments ***\n"
			<< "Usage: " << argv[0]
			<< " tasks_file order_file item_file entry_task pause delimiter log_file\n";
		exit(1);
	}
	std::cout << "Command Line Arguments\n----------------------\n";
	std::cout << "Task File Specified           = " << argv[1] << "\n";
	std::cout << "Customer Order File Specified = " << argv[2] << "\n";
	std::cout << "Item File Specified           = " << argv[3] << "\n";
	std::cout << "Entry Task                    = " << argv[4] << "\n";
	std::cout << "Pause After n steps         n = " << argv[5] << "\n";
	std::cout << "File Record Field Delimiter   = " << argv[6][0] << "\n";
	std::cout << "Log File                      = " << argv[7] << "\n\n";
	Utilities::setDelimiter(argv[6][0]);
	Utilities::setLogFile(argv[7]);
	std::string entryProcessor = argv[4];
	unsigned int pause = std::atol(argv[5]);
	// end of command line processing

	// Load, accept, validate and display the Active Tasks
	std::cout << "Building the Assembly Line\n--------------------------\n";
	AssemblyLine assemblyLine;
	loadFromFile<AssemblyLine, Processor>(argv[1], assemblyLine, std::cerr);
	assemblyLine.display(std::cout);
	std::cout << "\nValidating the Set of Tasks\n---------------------------\n";
	assemblyLine.validate(std::cerr);
	std::cout << "\nActive Tasks\n------------\n";
	assemblyLine.display(std::cout);

	// Load, accept and display the Customer Orders
	std::cout << "\n*** Load and Accept the Customer Orders ***\n";
	OrderManager orderManager;
	loadFromFile<OrderManager, CustomerOrder>(argv[2], orderManager, std::cerr);
	std::cout << "\nAccepted Customer Orders\n------------------------\n";
	orderManager.display(std::cout);

	// Load, accept and display the Items in Stock
	std::cout << "\n*** Load and accept the Stock Items ***\n";
	ItemManager itemManager;
	loadFromFile<ItemManager, Item>(argv[3], itemManager, std::cerr);
	std::cout << "\nStock Items\n-----------\n";
	itemManager.display(std::cout, true);

	// Validate the Items in the Customer Orders
	orderManager.validate(itemManager, std::cout);

	// Validate the Tasks in each Available Item
	assemblyLine.validate(itemManager, std::cerr);

	// Load the Items into the Assembly Line
	assemblyLine.loadItem(itemManager);

	// Display the Status of each Processor
	std::cout << "\nStatus of Each Processor\n------------------------\n";
	assemblyLine.display(std::cout);

	// Load the Customer Orders into the entry processor
	assemblyLine.loadOrders(orderManager, entryProcessor, std::cerr);
	// Display the Customer Orders that were not imported
		if (!orderManager.empty()) {
			std::cout << "\nNot-Imported Customer Orders\n----------------------------\n";
			orderManager.display(std::cout);
		}
	
	// Activate the Assembly Line
	bool done;
	OrderManager completed;
	do {
		done = assemblyLine.process(completed, pause);
		if (!done) {
			std::cout << "Enter n or N to halt processing ... ";
			char c;
			std::cin.get(c);
			if (c != '\n') std::cin.ignore(2000, '\n');
			if (c == 'n' || c == 'N') done = true;
		}
	} while (!done);

	// Display the completed Customer Orders
	std::cout << "\nCompleted Customer Orders\n-------------------------\n";
	completed.display(std::cout);

	// Display the Available Items
	std::cout << "\nAvailable Items\n---------------\n";
	itemManager.display(std::cout);

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

template<>
void loadFromFile<AssemblyLine, Processor>(const char* fileName, AssemblyLine& manager, std::ostream& os) {
	std::ifstream file(fileName);
	if (!file) {
		os << "*** Cannot open file named " << fileName << " ***\n";
		exit(1);
	}
	int pass = 50;
	auto inspect = [=](int x) { return x < pass ? Task::redirect : Task::passed; };
	while (file) {
		std::string record;
		std::getline(file, record);
		if (file) {
			try {
				std::unique_ptr<Processor> entry(new Processor(record, inspect));
				if (!entry->getName().empty())
					manager.push_back(std::move(*entry));
			}
			catch (const std::string& msg) {
				os << msg << std::endl;
			}
		}
	}
}