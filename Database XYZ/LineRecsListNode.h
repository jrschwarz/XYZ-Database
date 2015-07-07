#pragma once

#include "LineRec.h"

using namespace std;

class LineRecsListNode {

	friend class LineRecsList;

private:

	LineRecsListNode * pPrev;
	LineRec * pData;
	LineRecsListNode * pNext;

};