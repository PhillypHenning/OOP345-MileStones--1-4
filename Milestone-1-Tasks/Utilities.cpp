#include <iostream>
#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "Utilities.h"

namespace ms1{
	char Utilities::delimiter;
	std::ofstream Utilities::logFile;

	Utilities::Utilities(){
		//initializes field_width to 1.
		field_width = 1;
	}
	void Utilities::setFieldWidth(size_t fw){
		//Resets field_width to fw.
		field_width = fw;
	}
	size_t Utilities::getFieldWidth() const{
		//returs the field_width of the current object.
		return this->field_width;
	}
	const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more){
		//Task 1 : Returns next token found 
		//Task 2 : sets more to true if the record contains more tokens after the extracted token, false otherwise. 
		//Task 3 : updates the current objects field_width data member if its current value is less than the size of the token extracted. 
		//Task 4 : Reports an exception if there are two delims with no token between them. 
		//Task 5 : Trims needless trailing whitespace.
		bool isValid = false;
		std::string token;
		try{
			for (int i = next_pos; i < 1000; i++){
				if (str[0] == delimiter){
					if (str[i + 1] == delimiter){ //  Task 4. Empty token between delimiters.
						next_pos = i + 1;
						throw std::string(str + "<-- *** no token found before the delimiter ***");
					} 
					else{ //No beginning token.
						field_width = str.size();
						throw std::string(str + " <-- *** no token found before the delimiter ***");
					}
				}
				if (str[i] == '\0'){ //Safety to not go over string length. 
					token = str.substr(next_pos, i - next_pos);

					if (field_width < i - next_pos){//  Task 3.
						field_width = i - next_pos;
					}

					more = false; // Task 2. Sets bool for continued extracting. 

					break; //Breaks out of for loop.
				}
				else if (str[i] == delimiter){
					token = str.substr(next_pos, i - next_pos);

					if (field_width < i - next_pos){ //  Task 3.
						field_width = i - next_pos;
					}

					next_pos = i + 1;

					more = true; // Task 2.

					break; //Breaks out of for loop.

				}
			}

			while (!isValid && !token.empty()){ //  Task 5. Trims whitespace
				if (token.at(0) == ' '){ token.erase(0, 1); }
				else if (token.back() == ' '){ token.erase(token.length() - 1, 1); }
				else{ isValid = true; }
			}
		}
		catch (const std::string& msg){ //Displays an error msg if something failed. 
			std::cout <<  msg << std::endl;
			more = false;
		}
		return token; //  Task 1. Returns the token extracted from the passed str 
	}
	void Utilities::setDelimiter(const char pDelim){
		//Resets delim for this class to pDelim.
		Utilities::delimiter = pDelim;
	}
	void Utilities::setLogFile(const char* logfile){
		//Opens logfile for writing and truncation. 
		logFile.close();
		logFile.open(logfile);
	}	
	std::ofstream& Utilities::getLogFile(){
		//returns a reference to the logfile.
		return logFile;
	}
}