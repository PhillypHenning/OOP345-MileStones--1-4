// Phillyp Henning 
// 055829147
//Milestone - 4 - Assembly Line

#include <iomanip>
#include <stdio.h>
#include <string>
#include "Task.h"
#include "Utilities.h"

		size_t Task::field_width; 

		Task::Task(const std::string& pRecord) {
			//pRecord is a single record retrieved from the task file specified by the user.
			//Task 1 : Initializes the number of product slots to a default of 1.
			//Task 2 : sets the address of the nextTasks to a safe empty state.
			//Task 3 : Using the Utilities object, extracts each token from the record. 
			//Task 4 : Once the Utilities object extracts all the tokens it retreives the max field width needed by the extracted tokens. 
			//^Continued : If that field width is greater than field_width the constructor resets this class variable to the value retreived. 
			std::cout.flush();

			slots = "1"; //  Task 1.
			pNextTask[passed] = nullptr; //   Task 2. 
			pNextTask[redirect] = nullptr; //  Task 3.


			Utilities extract;
			size_t pos = 0;
			std::string token;
			bool isMore = true;
			for (int i = 0; isMore; i++) { //  Task 3.
				token = extract.nextToken(pRecord, pos, isMore);

				if (!token.empty()) {
					switch (i) { //While the loop runs each part is seperated into it's proper place. 
					case 0: //The name of the current token. 
						name = token;
						break;
					case 1: //The number of slots.
						if (isMore) {
							slots = token;
						}
						break;
					case 2: //Sets the optional third slot's next token.
						nextTask[passed] = token;
						break;
					case 3: //Sets the optional fourth slot's next token. 
						nextTask[redirect] = token;
						break;
					}
				}
				if (field_width < extract.getFieldWidth()) {
					field_width = extract.getFieldWidth(); //  Task 4.
				}
			}
		}
		
	bool Task::validate(const Task& pTask){
		//Validates the next task(s), stores upon installation
		//  Task 1 : Checks the name of each non-empty task against pTask and if it matches,
		//  Continued : stores the address of task in the pointer of the next particular task. 
		
		if (pTask.name == nextTask[passed]){ 
			pNextTask[passed] = &pTask;
		}
		else if (pTask.name == nextTask[redirect]){  
			pNextTask[redirect] = &pTask;
		}
		return (nextTask[passed].empty() || pNextTask[passed]) // Returns true only if both nextTasks are empty 
			&& (nextTask[redirect].empty() || pNextTask[redirect]);
	}
	const std::string& Task::getName() const{
		//Returns the name of the Task.
		return name;
	}
	unsigned int Task::getSlots() const {
		try {
			return stoi(slots);
		}
		catch (...) {
			return 1;
		}
	}
	void Task::display(std::ostream& os) const{  
		//  Task 1 : if the task has been validated uses the pointer(s) to the next Task.
		//  Task 2 : If it hasn't been validated uses the name of the next Task and appends a note that validation is still required. 
		if (pNextTask[passed]) {

			os << "Task Name    : " << std::left << std::setw(field_width + 3) << "[" + name + "]" << "[" + slots + "]" << std::endl;
			os << " Continue to : [" << pNextTask[passed]->name << "]" << std::endl;
			if (pNextTask[redirect]) {
				os << " Redirect to : [" << pNextTask[redirect]->name << "]" << std::endl;
			}
		}
		else {
			os << "Task Name    : " << std::left << std::setw(field_width + 3) << "[" + name + "]" << "[" + slots + "]" << std::endl;
			if (!nextTask[passed].empty()) {
				os << " Continue to : " << std::left << std::setw(field_width + 3) << "[" + nextTask[passed] + "]" << "*** to be validated ***" << std::endl;
				if (!nextTask[redirect].empty()) {
					os << " Redirect to : " << std::left << std::setw(field_width + 3) << "[" + nextTask[redirect] + "]" << "*** to be validated ***" << std::endl;
				}
			}
		}
	}
	size_t Task::getFieldWidth(){
		//Returns the field width currently stored for all objects.
		return field_width; 
	}
	bool operator==(const Task& task_a, const Task& task_b){
		//Returns true if task_a and Task_b share the same name. 
		return task_a.getName() == task_b.getName();
	}
	const Task* Task::getNextTask(Quality pValid) const {
		//  Task 1 : returns the address of the next task associated with the parameter received. 
		//  Task 2 : Report an exception if the address of pNextTask for a non-empty next task name corresponding
		//           to quality has not been resolved. 
		if (pNextTask[pValid] == nullptr) {
			if (nextTask[pValid] != "") {
				throw std::string("** Validate [" + nextTask[pValid] + "] @ [" + name + "] ***");
			}
		}
		return pNextTask[pValid];
	}

	const std::string& Task::operator[](unsigned int i) const {
		return nextTask[i];
	}

