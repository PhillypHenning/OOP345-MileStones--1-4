#pragma once
// CustomerOrder Milestone - Item Interface
// Item.h
// Template provided by Chris Szalwinski
// v1.0 - 9/11/2015
// v2.0 - 23/02/2016
// Phillyp Henning
// 055829147

#include <iostream>
#include <string>


const unsigned int CODE_WIDTH = 5;

namespace ms2{
	class Item{
	private:
		std::string name;          // name of the component
		std::string filler;        // name of the filler task
		std::string remover;       // name of the remover task 
		std::string description;   // detailed description
		unsigned int code;         // next shipping label
		static size_t field_width; // current maximum field width
	public:
		Item(const std::string& = std::string());
		bool empty() const;
		Item& operator++(int);
		unsigned int getCode() const;
		const std::string& getName() const;
		const std::string& getFiller() const;
		const std::string& getRemover() const;
		void display(std::ostream&, bool = false) const;
	};
}