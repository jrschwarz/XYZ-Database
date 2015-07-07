#pragma once

#include <string>
#include <vector>
#include "misc.h"
#include "DataBase.h"

class Transducer{

private:

	Database XYZ;

public:

	string transduce(string command) {

		string result;
		vector<string> token = tokenize(command);

		if (token[0] == "HELP" || token[0] == "H") {

			result += "Commands: \n";
			result += "-------------------------\n";
			result += "\tHELP (H)\n";
			result += "\tADD_FILE <filename.txt>\n";
			result += "\tFIND_WORD <word>\n";
			result += "\tCLEAR (C)\n";
			result += "\tQUIT (Q)\n";
		}
		else if (token[0] == "ADD_FILE") {

			XYZ.addFile(token[1]);
			result = "File added.\n";
		}
		else if (token[0] == "FIND_WORD") {

			result = XYZ.findWord(token[1]);
		}
		else if (token[0] == "CLEAR" || token[0] == "C") {

			XYZ.clearFiles();
			result = "All files cleared!\n";
		}
		else if (token[0] == "QUIT" || token[0] == "Q") {

			result = "Good Bye!\n";
		}
	/*	else if (token[0] == "DISPLAY" || token[0] == "D") {

			result = XYZ.display();
		}*/
		else {

			throw (string) "Invalid command!";
		}


		return result;
	}

};