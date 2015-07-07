#pragma once

#include <string>
#include "LineRec.h"

using namespace std;

class WordRec {

	friend class WordRecsList;

private:

	string word;
	LineRec * pLineRec;

public:

	void setWord(string newWord) {

		word = newWord;
	}

	void setPointerToLineRec(LineRec * pNewLineRec) {

		pLineRec = pNewLineRec;
	}
};