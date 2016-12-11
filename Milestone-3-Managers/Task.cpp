#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "Task.h"
#include "Utilities.h"



		size_t Task::field_width; 

	Task::Task(const std::string& pRecord){
		//pRecord is a single record retrieved from the task file specified by the user.
		//Task 1 : Initializes the number of product slots to a default of 1.
		//Task 2 : sets the address of the nextTasks to a safe empty state.
		//Task 3 : Using the Utilities object, extracts each token from the record. 
		//Task 4 : Once the Utilities object extracts all the tokens it retreives the max field width needed by the extracted tokens. 
		//^Continued : If that field width is greater than field_width the constructor resets this class variable to the value retreived. 
		
		slots = 1; //  Task 1.
		pNextTask[passed] = nullptr; //   Task 2. 
		pNextTask[redirect] = nullptr; //  Task 3.
		

		Utilities extract;
		size_t pos = 0;
		std::string token;
		bool isMore = true;
		for (int i = 0; isMore; i++){ //  Task 3.
			token = extract.nextToken(pRecord, pos, isMore);

			if (!token.empty()){
				switch (i){ //While the loop runs each part is seperated into it's proper place. 
				case 0: //The name of the current token. 
					name = token;
					break;
				case 1: //The number of slots.
					if (isMore){
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
			if (field_width < extract.getFieldWidth()){
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
	unsigned int Task::getSlots() const{
		return stoi(slots);
	}
	void Task::display(std::ostream& os) const{  
		//  Task 1 : if the task has been validated uses the pointer(s) to the next Task.
		//  Task 2 : If it hasn't been validated uses the name of the next Task and appends a note that validation is still required. 
		if (pNextTask[passed]){	
				std::cout << "Task Name      :  " << std::setw(field_width + 3) << "[" + name + "]" << "[" + slots + "]" << std::endl;
				std::cout << "  Continue to  :  " << std::setw(field_width + 3) << "[" + nextTask[passed] + "]" << std::endl;
				if (!nextTask[redirect].empty()){
					std::cout << "  Redirect to  :  " << std::setw(field_width + 3) << "[" + nextTask[redirect] + "]" << std::endl;
			}
		}
		else{//  Task 2.
			if (nextTask[passed].empty()){ //Separate message if there is no nextTask[].
				std::cout << "Task Name      :  " << std::left << std::setw(field_width + 3) << "[" + name + "]" << "[1]" << std::endl;
			}
			else{
				std::cout << "Task Name      :  " << std::left << std::setw(field_width + 3) << "[" + name + "]" << "[" + slots + "]" << std::endl;
				std::cout << "  Continue to  :  " << std::left << std::setw(field_width + 6) << "[" + nextTask[passed] + "]" << "*** to be validated ***" << std::endl;

					if (!nextTask[redirect].empty()){
						std::cout << "  Redirect to  :  " << std::left << std::setw(field_width + 6) << "[" + nextTask[redirect] + "]" << "*** to be validated ***" << std::endl;
				
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
		return task_a.getName().compare(task_b.getName()) ? 0 : 1;
	}
	const Task* Task::getNextTask(Quality pValid) const{
		//  Task 1 : returns the address of the next task associated with the parameter received. 
		//  Task 2 : Report an exception if the address of pNextTask for a non-empty next task name corresponding
		//to quality has not been resolved. 
		int vi;
			if (pNextTask[0] == nullptr){ //Task 2.
				throw std::string("*** Validate [" + nextTask[passed] + "]  @  [" + name + "] ***");
			}

			switch (pValid){ //Task 1.
			case 1:  //1=redirect
				vi = passed;
				break;
			case 0:  //0 = passed
				vi = redirect;
				break;
			}			 		
		return pNextTask[vi];
	}

