#pragma once
// Milestone 1 - Utilities Interface
// Utilities.h
// Template Provided by Chris Szalwinski 
// v1.0 - 24/10/2015
// v2.0 - 23/02/2016
//Phillyp Henning 
//055829147

#include <string>
#include <fstream>

namespace ms1{
	class Utilities {
		size_t field_width;           // maximum field width needed 
		static char delimiter;        // field delimiter character
		static std::ofstream logFile; // log file
	public:
		Utilities();
		void setFieldWidth(size_t);
		size_t getFieldWidth() const;
		const std::string nextToken(const std::string&, size_t&, bool&);
		static void setDelimiter(const char);
		static void setLogFile(const char*);
		static std::ofstream& getLogFile();
	};
}