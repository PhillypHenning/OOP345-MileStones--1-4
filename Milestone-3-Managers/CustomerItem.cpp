// Phillyp Henning
// 055829147

#include <iomanip>
#include <iostream>
#include "CustomerItem.h"
#include "Item.h"


	CustomerItem::CustomerItem(const std::string& pName){
	//  Task 1 : Sets name to the name received or to an empty state if no name was specified. 
	//	Task 2 : initalizes filled to false and code to 0.
		name = ""; 
		if (!pName.empty()){ //  Task 1.
			name = pName;
		}
		filled = false; code = 0; //  Task 2.
	}
	bool CustomerItem::asksFor(const Item& item) const{
	//returns true if the current objects asks for item	
		return name == item.getName()? true : false;
	 }
	bool CustomerItem::isFilled() const{
		//returns true if the current object's request has been filled'
		return filled;
	}
	void CustomerItem::fill(const unsigned int fill){
		code = fill; filled = true;
	}
	void CustomerItem::clear(){
		code = 0; filled = false;
	}
	const std::string& CustomerItem::getName() const{
		return name;
	}
	void CustomerItem::display(std::ostream& os) const{
		/*  Display customer order
		Task 1 : the symbol + or - identifying the fill status of the item request
		Task 2 : the code printed on the item if filled or 0 if not filled in a field width of CODE_WIDTH padded with 0s and enclosed within brackets
		Task 3 : the name of the customer item
		*/

		if (isFilled()){ os << " + "; }
		else{ os << " - "; }

		os << "[" << std::setw(CODE_WIDTH) << std::setfill('0')  << std::right << code << "]  " << name << std::endl;
	}


