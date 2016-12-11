// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include <algorithm>
#include "Task.h"
#include "TaskManager.h"
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
	
	for (unsigned int i = 0; i < itemManager.size(); i++){
		for (unsigned int n = 0; n < std::vector<Task>::size(); n++){
			if (itemManager.at(i).getRemover() == this->at(n).getName()){
				break;
			}
			else if (n == std::vector<Task>::size() - 1){
				os << itemManager.at(i).getRemover() << " is unavailable" << std::endl;
			}
		}
	}
}
	void TaskManager::display(std::ostream& os) const{
		//inserts into os descriptions of the tasks stored in tasks
		for (size_t i = 0; i < std::vector<Task>::size(); i++){
			std::vector<Task>::at(i).display(os);
		}
	}

	

