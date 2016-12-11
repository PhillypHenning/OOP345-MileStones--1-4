// CustomerOrder Milestone - Main Program
// Milestone_2.cpp
// Chris Szalwinski
// v1.0 - 9/11/2015
// v1.1 - 9/11/2015 - customerOrder -> customerOrders for g++ 5.2 compatability (CS)
// v1.2 - 16/11/2015 - add <cstdlib> for exit (CS)
// v2.0 - 15/01/2016
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <memory>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Item.h"

#define DEBUG

using namespace ms2;

template<typename T>
void loadFromFile(const char*, std::vector<T>&, std::ostream&);

int main(int argc, char** argv) {
	// process command line arguments
#ifdef DEBUG
	argc = 4;
	argv[0] = "w7";
	argv[1] = "CleanCustomerOrderFileWmal.txt";
	argv[2] = "CleanItemFileWmal.txt";
	argv[3] = "|";
#endif
	
	if (argc != 4) {
		std::cerr << "*** invalid number of arguments ***\n"
			<< "Usage: " << argv[0] << " customer_order_file item_file delimiter\n";
		exit(1);
	}
	std::cout << "Command Line Arguments\n----------------------\n";
	std::cout << "Customer Order File Specified = " << argv[1] << "\n";
	std::cout << "Item File Specified           = " << argv[2] << "\n";
	std::cout << "File Record Field Delimiter   = " << argv[3][0] << "\n\n";
	ms1::Utilities::setDelimiter(argv[3][0]);
	// end of command line processing

	// Load, Accept and Display the Customer Orders
	//
	std::cout << "\n*** Load and Accept the Customer Orders ***\n";
	std::vector<ms2::CustomerOrder> customerOrders;
	loadFromFile(argv[1], customerOrders, std::cerr);
	std::cout << "\nList of Accepted Customer Orders\n--------------------------------\n";
	for (auto& s : customerOrders)
		s.display(std::cout);

	// Load, Accept and Display the Items in Stock
	//
	std::cout << "\n*** Load and Accept the Items in Stock ***\n";
	std::vector<Item> items;
	loadFromFile(argv[2], items, std::cerr);
	std::cout << "\nList of Items in Stock\n----------------------\n";
	for (auto& i : items)
		i.display(std::cout, true);

	// Fill the Customer Orders with the Items in Stock
	//
	std::cout << "\n*** Process the Customer Orders ***\n";
	for (auto& i : items)
	for (auto& s : customerOrders)
		s.fill(i);

	// Display the Processed Customer Orders
	//
	std::cout << "\nList of Processed Customer Orders\n---------------------------------\n";
	for (auto& s : customerOrders)
		s.display(std::cout);


	// Terminate
	//
	std::cout << "\nDone!\nPress Enter Key to Exit ... ";
	char c;
	std::cin.get(c);
}

template<typename T>
void loadFromFile(const char* fileName, std::vector<T>& collection, std::ostream& os) {
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
					collection.push_back(std::move(*entry));
			}
			catch (const std::string& msg) {
				os << msg << std::endl;
			}
		}
	}
}