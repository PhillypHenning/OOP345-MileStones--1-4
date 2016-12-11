// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include "AssemblyLine.h"
#include "Processor.h"
#include "ItemManager.h"
#include "Item.h"
#include "OrderManager.h"
#include <stdlib.h>



// initialize
void AssemblyLine::push_back(Processor&& processor){
	//moves processor to the back of the base class container
	std::vector<Processor>::push_back(std::move(processor));
}
void AssemblyLine::validate(std::ostream& os ){
	/*  Task 1 : checks if each follow-on processor in the base class container is a processor in the 
		container (the code for this function is similar to the code for TaskManager::validate().
		Task 2 : This function inserts a message into os if any follow on processor is not validated.  */

	for (size_t i = 0; i < std::vector<Processor>::size(); i++) {
		for (size_t n = 0; n < std::vector<Processor>::size(); n++) {
				std::vector<Processor>::at(i).validate(std::vector<Processor>::at(n)); // Task 1 & 2, Task 2 is done within the std::vector<Processor>::at(i).validate(...)		
		}
	}
}
void AssemblyLine::validate(ItemManager& itemManager, std::ostream& os){
	  /*  Task 1 : checks that the tasks (that is, processors) assigned to each item managed by itemManager are tasks (that is, processors) in the base class container. 
	      Task 2 : If a task is not in the container, then this function inserts a message into os that that task is not available. */
	for (size_t i = 0; i < itemManager.size(); i++) {
		for (size_t n = 0; n < std::vector<Processor>::size(); n++) {
			if (itemManager[i].getFiller() == this->at(n).getName()) { break; } // Task 1.																						
			else if (n == std::vector<Processor>::size()- 1) { os << itemManager.at(i).getFiller() << " is unavailable." << std::endl; } // Task 2.
			}
		}
	}	
void AssemblyLine::loadItem(ItemManager& item) {
	for (unsigned int i = 0; i < this->size(); i++) {
		for (unsigned int n = 0; n < item.size(); n++) {
			if (this->at(i).getName() == item.at(n).getFiller()
				|| this->at(i).getName() == item.at(n).getRemover()) {
				this->at(i).load(item.at(n));
				break;
			}
		}
	}
}
// processing
void AssemblyLine::loadOrders(OrderManager& orderManager, const std::string& entryProcessor, std::ostream& os) {
	for (unsigned int i = 0; i < orderManager.size(); i++) {
		for (unsigned int n = 0; n < this->size(); n++) {
			if (this->at(n).getName() == entryProcessor) {
				this->at(n).accept(std::move(orderManager.at(i)));
				break;
			}
		}
	}
}
bool AssemblyLine::process(OrderManager& finishing, unsigned int n) {
	/*  Task 1 : advances the assembly line by n steps, but stopping once all processing has been completed.
		Task 2 : In each step, this function advances the orders on each processor by a single slot.
		Task 3 : At the end of each step, this function checks if each processor
				a) : is ready to ship
				b) : or ready to inspect any order.
		Task 4 : If a processor is ready to ship an order, this function ships the order to the finishing manager.
		Task 5 : If a processor is ready to inspect an order, this function instructs the inspector to evaluate the order and passes
		the order to the processor determined by the inspector.
		Task 6 : This function passes a random number between 0 and 100 as the argument to the inspector.
		Task 7 : This function returns true if all of the processors are empty; false otherwise.  */

	for (unsigned int i = 0; i < n; i++) { //  Task 1 - Partial
		for (unsigned int ford = 0; ford < size(); ford++) {
			if (i == 5 && ford == 1) { 
				std::cout << " Hello"; }
			std::vector<Processor>::at(ford).advance(); // Task 2.
			if (std::vector<Processor>::at(ford).readyToShip()) { // Task 4.
				std::vector<Processor>::at(ford).ship(finishing);
			}
			if (std::vector<Processor>::at(ford).readyToPass()) { // Task 5.
				std::vector<Processor>::at(ford).pass(rand() % 100 + 1); // Task 6. Something wrong in here
			}
		}
	}
	bool isMore = true;
	for (size_t n = 0; n < this->size(); n++) { // Task 7.
		if (!std::vector<Processor>::at(n).empty()) {
			isMore = false;
			break;
		}
	}
	return isMore;
}
// reporting
void AssemblyLine::display(std::ostream& os) const {
	//  inserts descriptions of the processors in the base class contianer into os
	for (size_t i = 0; i < std::vector<Processor>::size(); i++) {
		this->at(i).display(os);
	}
}
