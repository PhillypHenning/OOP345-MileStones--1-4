// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include <iomanip>
#include <functional>
#include "Item.h"
#include "Utilities.h"


	size_t Item::field_width; 

	Item::Item(const std::string& item)
		: description("no deatiled description"),
		code(1)  //  Task 1.
	{
		/*
			Receives either nothing or a reference to a string that contains all the information to a single item.
			Task 1 : sets description to "no detailed description" & code to (1)
			Task 2 : Extracts tokens from string using a Utilities object.
			Task 3 : Reports an exception if tokens 1 to 3 fail to return a token.
			Task 4 : Resets field_width if the size of the token exceeds the current value
			*item Layout*
			name | filler | remover | code | detailed description
		*/
		Utilities extract;
		size_t pos = 0; bool isMore = true;
		name = extract.nextToken(item, pos, isMore);  //  Task 2.

		if (field_width < extract.getFieldWidth()) {  //  Task 4.
			field_width = extract.getFieldWidth();
		}

		//isMore is default true, and set to false within nextToken if the item string is at the end. 
		
			filler = extract.nextToken(item, pos, isMore); 
			remover = extract.nextToken(item, pos, isMore); 
			try {  code = stoi(extract.nextToken(item, pos, isMore));  }
			catch (...) {  code = 1; }
			description = extract.nextToken(item, pos, isMore);

		if (name.empty() || filler.empty() || remover.empty()) { throw std::string("***No Token found before the delimiter ***"); } // Task 3. 
	}
	bool Item::empty() const{
	// returns true if the current Item is in a safe empty state.
		return name.empty() && filler.empty()
		&& remover.empty() && description.empty();
	}
	Item& Item::operator++(int n){
	//Increments the code to be printed on the next insertion and returns the value before incrementation.
			Item temp(*this);
			code++;
			return std::ref(temp);
		}
	unsigned int Item::getCode() const{
	// returns a reference to the Item::code
		return code;
	}
	const std::string& Item::getName() const{
	// returns a reference to the Item::name
		return name;
	}
	const std::string& Item::getFiller() const{
	// returns a reference to the Item::filler
		return filler;
	}
	const std::string& Item::getRemover() const{
		return remover;
	}
	void Item::display(std::ostream& os, bool more) const{
	/*
		Inserts into the os the Item objects;
			1. name
			2. code
			3. 'From' followed by the filler 
			4. 'To' followed by the remover
			5. ':' followed by the Detailed description
	*/
		os << std::setfill(' ');
		os << std::setw(field_width) << std::left << name << "[" << std::right << std::setw(CODE_WIDTH) << std::setfill('0') << code << "]" << std::setfill(' ');
			if (more) {
				os << " From " <<
					std::setw(field_width) << std::left << std::setfill(' ') << filler << " To " << remover << std::endl <<
					std::setw(field_width + CODE_WIDTH + 3) << std::right << ": " << description;
			}
			os << std::endl;

	}
