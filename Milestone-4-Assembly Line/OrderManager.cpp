// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include <algorithm>
#include "CustomerOrder.h"
#include "ItemManager.h"
#include "OrderManager.h"


	CustomerOrder&& OrderManager::extract() {
		// Task 1 : move a customerOrder from the back of the base class container
		return std::move(std::vector<CustomerOrder>::back());
	}
	void OrderManager::validate(const ItemManager& itemManager, std::ostream& os){
	/*
		 Task 1 : checks that the items requested in the customer orders are available,
		 Task 2 : inserting a message into os for any item that is not available. 
	*/
	for (size_t i = 0; i < std::vector<CustomerOrder>::size(); i++){ // For each CustomerOrder 
		for (size_t g = 0; g < std::vector<CustomerOrder>::at(i).noOrders(); g++){ //For each CustomerOrder.order
			for (size_t n = 0; n < itemManager.size(); n++){ //For each item

				if (std::vector<CustomerOrder>::at(i)[g] == itemManager.at(n).getName()){ break; } //Task 1.
				//If the item @ n was found the break moves it on to the next order g.
				if (n == itemManager.size()-1){ std::cout << std::vector<CustomerOrder>::at(i)[g] << " is unavailable." << std::endl; }  //Task 2.
				}
			}
		}
	}
	void OrderManager::display(std::ostream& os) const{
		//inserts into os descriptions of each customer order in the base class container
		for (size_t i = 0; i < std::vector<CustomerOrder>::size(); i++){
			std::vector<CustomerOrder>::at(i).display(os);
		}
	
	}
