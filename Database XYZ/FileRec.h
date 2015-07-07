#pragma once

#include <string>

using namespace std;

class FileRec {

	friend class FileList;

private:

	string fileName;

public:

	void setFileName(string newFileName) {

		fileName = newFileName;
	}
};