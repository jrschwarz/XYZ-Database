#pragma once

#include <string>

using namespace std;

class LineRec {

	friend class LineRecsList;
	friend class WordRecsList;

private:

	string line;
	string fileName;
	int lineNumber;
	bool found = false;

public:

	void setLine(string newLine) {

		line = newLine;
	}

	void setFileName(string newFileName) {

		fileName = newFileName;
	}

	void setLineNumber(int newLineNumber) {

		lineNumber = newLineNumber;
	}

	void setFound(bool isFound) {

		found = isFound;
	}

	bool isFound() {

		return found;
	}


};