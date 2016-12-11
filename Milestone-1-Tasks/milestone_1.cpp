// Milestone 1 - Task Manager - Main Program
// milestone_1.cpp
// Template Provided by Chris Szalwinski 
// v1.0 - 24/10/2015
// v2.0 - 15/01/2016
//Phillyp Henning 
//055829147
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Task.h"
#include "Utilities.h"

using namespace ms1;

#define DEBUG //Debug only. 

void loadFromFile(const char*, std::vector<Task>&, std::ostream&);

int main(int argc, char** argv) {
#ifdef DEBUG //Debugging purposes only.
	argc = 3;
	argv[0] = "ms1";
	//argv[1] = "CleanFileSolution.txt"; 
	//argv[1] = "CleanFileWithWhiteSpace.txt";
	argv[1] = "CleanFileMalformedData.txt";
	argv[2] = "|";
#endif

	// process command line arguments
	if (argc != 3) {
		std::cerr << "*** invalid number of arguments ***\n"
			<< "Usage: " << argv[0] << " tasks_file delimiter\n";
		exit(1);
	}
	std::cout << "Command Line Arguments\n----------------------\n";
	std::cout << "Tasks File Specified          = " << argv[1] << "\n";
	std::cout << "File Record Field Delimiter   = " << argv[2][0] << "\n\n";
	Utilities::setDelimiter(argv[2][0]);
	// end of command line processing

	// Load, Accept and Display the Tasks
	//
	std::cout << "\n*** Load and Accept the Tasks ***\n";
	std::vector<Task> tasks;
	loadFromFile(argv[1], tasks, std::cerr);
	std::cout << "\nList of Accepted Tasks\n----------------------\n";
	for (auto& t : tasks)
		t.display(std::cout); 

	// Check nextTask
	//
	std::cout << "\nCheck Follow-On Tasks\n---------------------\n";
	int nerr = 0;
	for (auto& t : tasks) {
		try {
			std::cout << t.getNextTask(Task::passed)->getName() << std::endl;
			std::cout << t.getNextTask(Task::redirect)->getName() << std::endl;
		}
		catch (const std::string& msg) {
			std::cerr << msg << std::endl;
			nerr++;
			if (nerr > 3) {
				std::cerr << "*** Further checks suspended ***" << std::endl;
				break;
			}
		}
	}

	// Validate the Tasks
	//
	std::cout << "\nValidating the Accepted Tasks\n-----------------------------\n";
	bool valid = true;
	for (auto i = 0u; i < tasks.size() && valid; i++) {
		bool invalid = true;
		for (auto j = 0u; j < tasks.size() && invalid; j++) {
			if (tasks[i].validate(tasks[j]))
				invalid = false;
		}
		valid = !invalid;
	}
	if (!valid)
		std::cerr << "*** Not all Tasks have been validated ***\n";
	for (auto& t : tasks)
		t.display(std::cout);

	// Terminate
	//
	std::cout << "\nDone!\nPress Enter Key to Exit ... ";
	char c;
	std::cin.get(c);
}

void loadFromFile(const char* fileName, std::vector<Task>& taskSet, std::ostream& os) {
	std::ifstream file(fileName);
	if (!file) {
		os << "*** Cannot open file named " << fileName << " ***\n";
		exit(1);
	}
	while (file) {
		std::string record;
		std::getline(file, record);
		if (file) {
			try {
				std::unique_ptr<Task> entry(new Task(record));
				if (!entry->getName().empty())
					taskSet.push_back(std::move(*entry));
			}
			catch (const std::string& msg) {
				os << msg << std::endl;
			}
		}
	}
}