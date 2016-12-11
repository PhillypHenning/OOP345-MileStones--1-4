// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Item.h"
#include "OrderManager.h"
#include "Processor.h"
#include "Task.h"
#include "Utilities.h"


int Processor::sizeOfItem = 0;
std::function<Task::Quality(int)> inspector; 


Processor::Processor(const std::string& record, std::function<Task::Quality(int)> function):Task(record){
	/* The constructor passes a description::string to the Task base class 
	Initializes: 
		num_end_slots = # of slots in Task;
	*/
	item_ = nullptr; inspector = function; is_a_filler = true; num_end_slots = getSlots();
}
void Processor::load(Item& item){
	/* Sets item_ = item,
	Sets is_a_filler to true if the name of the processor is the
	name of the filler task for item, false otherwise. 
	*/
	
	item_ = &item;
	sizeOfItem++;
	if (this->getName() == item_->getFiller()) { is_a_filler = true; }
	else { is_a_filler = false; }
	
}  
void Processor::accept(CustomerOrder&& customerOrder){
	// moves order to the back of the waiting queue.
	waiting.push_back(std::move(customerOrder));
}
void Processor::pass(int i) {
	/* Moves the order at the front of the complete queue to the next processor.
	   If multiple next processors calls inspector to decide the choice
	   If there is no choice move the order to the next processor without inspecting the order.
	   Log the move */
		const Task* temp1;
		//If redirect has a value then inspector needs to decide
		if (Task::getNextTask(redirect)) {
			temp1 = getNextTask(inspector(i));
		}
		else {
			temp1 = Task::getNextTask(passed);
		}
		if (temp1 != nullptr) {
			Processor* temp2;
			temp2 = (Processor*)temp1;
			Utilities::getLogFile() << temp2->getName() << " was moved to the waiting queue" << std::endl;
			temp2->waiting.push_back(std::move(complete.front()));
			complete.pop_front();
		}
	}
void Processor::advance() {
	/*  Task 1 : Advances all customer orders attached to the processor by a single slot.
		Task 2 : This function decrements the number of end slots if the process queue is not empty and the number of end slots is not 0.
		Task 3 : For every customer order in the process queue this function either;
					A) fills one customer item request with the item requested if the processor is a filler task or,
					B) retreive the item if the process is a remover task (not a filler).
		Task 4 : If there are no empty end slots, this function moves the order in the last slot from the front of the process queue to the
					complete queue and adjusts the number of end slots to either 1 or the number of slots in the processor if the process queue is empty.
		Task 5 : Finally, this function moves an order, if any, from the front of the waiting queue to the back of the process queue  */
		if (!process.empty() && num_end_slots != 0) {
			num_end_slots--;
		} // Task 2

		if (!process.empty()) { //  Task 3.
			for (unsigned int i = 0; i < process.size(); i++) {
				if (this->is_a_filler && item_ != nullptr) {
					process.at(i).fill(*item_); // Task 3 A
				}
				else if(item_ != nullptr){
					process.at(i).remove(*item_); // Task 3 B
				}
			}
		}
		if (num_end_slots == 0) { //  Task 4.
			complete.push_back(std::move(process.front()));
			process.pop_front();
			if (process.empty()) {
				num_end_slots = getSlots();
			}
			else {
				num_end_slots = 1;
			}
		}

		if (!waiting.empty()) { //  Task 5.
			if (!waiting.empty()) {
				process.push_back(std::move(waiting.back()));
				waiting.pop_back();
			}
		}
	}
bool Processor::empty() const{
	//Returns true if all queries are empty, false otherwise. 
	return waiting.empty() && process.empty() && complete.empty();
}
bool Processor::readyToShip() const{
	bool rShip = false;
	if (!complete.empty()){
		if (!complete.front().empty() && !Task::getNextTask(passed)){
			rShip = true;
		}
	}
	return rShip;
}
bool Processor::readyToPass() const{
	bool rPass = false;
	if (!complete.empty()){
		if (!complete.front().empty() && Task::getNextTask(passed)){
			rPass = true;
		}
	}
	return rPass;
}
void Processor::ship(OrderManager& finished) {
	if (!complete.front().empty()) {
		finished.push_back(std::move(complete.front()));
		complete.pop_front();
	}
}
void Processor::display(std::ostream& os) const {
	/*  inserts into os a complete description of the current state of the processor as shown in the example below.  The descriptions includes
		a description of the processor's task
		whether the processor adds or removes its allocated item
		a short description of the item; --- if there is no item
		the customer orders in waiting
		the customer orders in process
		the customer orders completed  */

	this->Task::display(os);
	
	if (item_ == nullptr) { os << "  Item to add  :  ---" << std::endl; }
	else {
		for (int i = 0; i < sizeOfItem; i++) {
			if (item_ && getSlots() > 1) {
				os << " Item to add : " << item_[0].getName() << " [" << item_[0].getCode() << "]" << std::endl;
				sizeOfItem--;
				break;
			}
			else if(i == sizeOfItem - 1) { os << "  Item to add  :  ---" << std::endl; }
		}
	}
}
const std::string& Processor::operator[](unsigned int i)const {
	return item_[i].getFiller();
}
