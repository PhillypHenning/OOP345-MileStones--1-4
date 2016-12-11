// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include "ItemManager.h"
#include "Item.h"


	void ItemManager::display(std::ostream& os, bool more) const{
		/*
		Inserts into os descriptions of each item stored in the base class container. 
		The bool parameter specifies whether a full description of the item should be inserted.
		*/
		for (size_t i = 0; i < std::vector<Item>::size(); i++){
			std::vector<Item>::at(i).display(os, more);
		}
	}
