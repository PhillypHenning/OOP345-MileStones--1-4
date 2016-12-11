//Phillyp Henning
//055829147

#include <algorithm>
#include <vector>
#include "task.h"
#include "taskManager.h"
#include "ItemManager.h"

	void TaskManager::validate(std::ostream& os){
		/*
		Validates each task against all of the other tasks in the base class container.
		Inserts a message into the os if not all tasks have been validated <--Throws exception?
		*/
		for (size_t i = 0; i < std::vector<Task>::size(); i++){
			for (size_t n = 0; n < std::vector<Task>::size(); n++){
				if (i != n){ //So you don't validate a container with itself. 
					std::vector<Task>::at(i).validate(std::vector<Task>::at(n));
				}
			}
		}


	}
	void TaskManager::validate(const ItemManager& itemManager, std::ostream& os){
		/*
		Task 1 : Checks that the task assigned to handle each item managed by itemManager are tasks in the base class container.
		Task 2 : if a task is not in the container then insert a message into os that the task is not available
		*/
		int n = 0;

		for (size_t n = 0; n < itemManager.size(); n++){
			for (size_t i = 0; i < std::vector<Task>::size(); i++){
				if (itemManager.at(n).getName() == std::vector<Task>::at(i).getName()){ break; } //Task 1 . Item.name was found in the task object. Breaks out of i.
				if (n == std::vector<Task>::size() - 1){ os << itemManager.at(n).getName() << " is unavailable." << std::endl; } //Task 2.
			}
		}
		for (size_t n = 0; n < itemManager.size(); n++){
			for (size_t i = 0; i < std::vector<Task>::size(); i++){
				if (itemManager.at(n).getRemover() == std::vector<Task>::at(i).getName()){ break; } //Item.remover was found in the task object. Breaks out of i.  
				if (i == std::vector<Task>::size() - 1){ os << itemManager.at(n).getRemover() << " is unavailable." << std::endl; } // Task 2.
			}
		}
	}
	void TaskManager::display(std::ostream& os) const{
		//inserts into os descriptions of the tasks stored in tasks
		for (size_t i = 0; i < std::vector<Task>::size(); i++){
			std::vector<Task>::at(i).display(os);
		}
	}

	

