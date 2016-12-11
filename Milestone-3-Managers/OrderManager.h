#pragma once
// Manager Milestone - OrderManager Interface
// OrderManager.h
// Chris Szalwinski
// v1.0 - 14/11/2015
// v2.0 - 23/02/2016
#include <iostream>
#include <vector>

	class ItemManager;
	class CustomerOrder;

	class OrderManager : public std::vector<CustomerOrder> {
	public:
		//CustomerOrder&& extract();
		void validate(const ItemManager&, std::ostream&);
		void display(std::ostream&) const;
	};
