// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include <exception>
#include <iomanip>
#include <memory>
#include <vector>
#include "CustomerOrder.h"
#include "CustomerItem.h"
#include "Item.h"
#include "Utilities.h"


	size_t CustomerOrder::field_width;

	CustomerOrder::CustomerOrder(const std::string& custOrder){
		/*
			custOrder contains the information for a single customer order.
			Task 1 : initializes the number of customer items to 0 and the pointer to customerArray to a safe address.
			Task 2 : Using a Utilities object extract the tokens from custOrder
			Task 3 : Report an exception if any tokens are returned empty
			Task 4 : The constructor allocates dynamic memory for *order
			Task 5 : Sets field_width to the Utilities objects field_width only if the Utilities field_width is greater.

			* custOrder layout*
			customer name field | product name field | Item name field
			*/
		nOrders = 0; order = nullptr;  //  Task 1.

		Utilities zoolander;
		std::vector<std::string> token;
		size_t pos = 0; bool isMore = true;
			for (unsigned int counter = 0; isMore; counter++){ //  Task 2 Begins

				name = zoolander.nextToken(custOrder, pos, isMore);

				if (isMore) { product = zoolander.nextToken(custOrder, pos, isMore); }

				while (isMore){
					token.push_back(zoolander.nextToken(custOrder, pos, isMore));
				}

				order = new CustomerItem[token.size()];  //  Task 4.

				for (unsigned int i = 0; i < token.size(); i++){
					order[i] = CustomerItem(token[i]);
				}

				if (field_width < zoolander.getFieldWidth()){ //  Task 5.
					field_width = zoolander.getFieldWidth();
				}
				nOrders = token.size();
			}
	} //Task 2 Ends. 

	
	CustomerOrder::CustomerOrder(const CustomerOrder& pCustomerOrder){
		//DO NOT USE report exception if used.
		std::cerr << ("Oops. Wrong call. Please check CustomerOrder::CustomerOrder(const CustomerOrder& pCustomerOrder) isn't being called by mistake. Thanks."); 
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& pCustomerOrder) NOEXCEPT
	  : name(pCustomerOrder.name),
	    product(pCustomerOrder.product),
	    nOrders(pCustomerOrder.nOrders)
	{	
		//Assign class data members from the source object to the oject being created. 
		//Assign source data members to default.
		
		order = new CustomerItem[nOrders];

		for (unsigned int i = 0; i < nOrders; i++){
			order[i] = pCustomerOrder.order[i];
		}
		pCustomerOrder.order = nullptr;
		pCustomerOrder.name = ""; pCustomerOrder.product = ""; pCustomerOrder.nOrders = 0;
	}
	CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& pCustomerOrder )NOEXCEPT {
		// Task 1 : A conditional statement that performs no operation if you try to assign the object to itself
		// Task 2 : Free the current objects dynamic memory data members; 
		// Task 3 : Assign the rValue data member to the current objects data members. 
		// Task 4 : Free the rValue 
		if (this != &pCustomerOrder) { // Task 1.
			delete[] order; //Task 2.
		}
			name = pCustomerOrder.name; product = pCustomerOrder.product; nOrders = pCustomerOrder.nOrders;
			order = pCustomerOrder.order; // Task 3.

			pCustomerOrder.order = nullptr; //Task 4.
			pCustomerOrder.name = ""; pCustomerOrder.product = ""; pCustomerOrder.nOrders = 0;
		
		return std::move(*this);
	}
	CustomerOrder::~CustomerOrder(){
	//deletes dynamic memory in use by the current object.
		delete[] order;
	}
	unsigned int CustomerOrder::noOrders() const{
	//returns the number of customer items in the current object. 
		return nOrders;
	}
	const std::string& CustomerOrder::operator[](unsigned int i) const{
	// Task 1 : returns a reference to the name of customer item i.
	// Task 2 : reports exception if index is out of bounds. 
		if( i < nOrders){
			return order[i].getName(); // Task 1. 
		}
		else{
			throw std::string("Current CustomerOrder index is out of bounds."); //Task 2.
		}
	}
	void CustomerOrder::fill(Item& item){
	// searches through the customer items and fills those order for the customer 
	// Task 1 : custitems identified by item if any have not been filled.
	// Task 2 : increment code for each customer item filled. This keeps the item code unqiue for each order.

		for (unsigned int i = 0; i < nOrders; i++){
			if (order[i].asksFor(item) && !order[i].isFilled()){
				 order[i].fill(item.getCode()); // Task 1.
				item++; //Task 2. 
			}
		}
	}
	void CustomerOrder::remove(Item& item){
	// Searches through the customer order and removes those items identified by the name of item
	//Does not alter the item's code.
		for (unsigned int i = 0; i < nOrders; i++){
			if (order[i].asksFor(item) && !order[i].isFilled()) {
				nOrders--;
			}
		}
	}
	bool CustomerOrder::empty() const{
		//return true if the current object is in a safe empty state.
		return (order == nullptr) ? true : false;
	}
	void CustomerOrder::display(std::ostream& os) const{
		/*  Display customer order
			the name of the customer left-justified in a field of width field_width
			the name of the product left-justified in a field of width field_width
			each customer item on a separate line
		*/
		if (!empty()) {
			os << std::setw(field_width) << std::setfill(' ') << std::left << name << " :  " << product << std::endl;
			for (unsigned int i = 0; i < nOrders; i++) {
				order[i].display(os);
			}
		}
	}
