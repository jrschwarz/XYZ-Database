#pragma once

#include "WordRec.h"

using namespace std;

class WordRecsListNode {

	friend class WordRecsList;

private:

	WordRecsListNode * pLeft = NULL;
	WordRec * pData;
	WordRecsListNode * pRight = NULL;

public:


};