#pragma once

#include "LineRec.h"
#include "LineRecsListNode.h"

using namespace std;

class LineRecsList {

private:

	LineRecsListNode * pFirst;
	LineRecsListNode * pLast;

public:

	LineRecsList()
	{
		pFirst = new LineRecsListNode;
		if (!pFirst) throw "Error: Out of memory.";
		pLast = new LineRecsListNode;
		if (!pLast) throw "Error: Out of memory.";

		pFirst->pPrev = NULL;
		pFirst->pData = NULL;
		pFirst->pNext = pLast;

		pLast->pPrev = pFirst;
		pLast->pData = NULL;
		pLast->pNext = NULL;
	}

	virtual ~LineRecsList()
	{
		clearAll(true);
		delete pFirst;
		delete pLast;
	}

	void clearAll(bool ownedByList = false)
	{
		while (!isEmpty())
		{
			removeFirstItem(ownedByList);
		}
	}

	bool isEmpty()
	{
		return pFirst->pNext == pLast;
	}

	void add(LineRec * pLineRec) {

		LineRecsListNode * pNewNode = new LineRecsListNode;
		if (pNewNode == NULL) throw (string)"Error: Out of memory.";

		pNewNode->pData = pLineRec;

		insertNodeAtBottom(pNewNode);
	}

	string getAll()
	{
		string result;
		LineRecsListNode * pCurrent;
		pCurrent = pFirst->pNext;

		while (pCurrent->pData != NULL)
		{
			result += pCurrent->pData->line + '\n';
			result += pCurrent->pData->fileName + ' ' + '[' + intToString(pCurrent->pData->lineNumber) + ']' + "\n\n";

			pCurrent = pCurrent->pNext;
		}

		return result;
	}

private:

	void removeNode(LineRecsListNode * pRemove, bool ownedByList = false)
	{
		_ASSERT(pRemove != NULL);
		_ASSERT(pRemove->pData != NULL);

		//1
		pRemove->pPrev->pNext = pRemove->pNext;
		//2
		pRemove->pNext->pPrev = pRemove->pPrev;
		//3

		if (ownedByList)
		{
			delete pRemove->pData;
		}

		delete pRemove;
	}

	void removeFirstItem(bool ownedByList = false)
	{
		_ASSERT(pFirst->pNext->pData != NULL);
		removeNode(pFirst->pNext, ownedByList);
	}

	void insertNodeAtBottom(LineRecsListNode * pNewNode)
	{
		insertAbove(pNewNode, pLast);
	}

	void insertAbove(LineRecsListNode *pNewNode, LineRecsListNode *pLocation)
	{
		//1
		pNewNode->pPrev = pLocation->pPrev;
		//2
		pNewNode->pNext = pLocation;
		//3
		pLocation->pPrev = pNewNode;
		//4
		pNewNode->pPrev->pNext = pNewNode;
	}

};