#pragma once

#include "FileListNode.h"

#include <string>

using namespace std;

class FileList {

private:

	FileListNode * pFirst;
	FileListNode * pLast;

public:

	FileList()
	{
		pFirst = new FileListNode;
		if (!pFirst) throw "Error: Out of memory.";
		pLast = new FileListNode;
		if (!pLast) throw "Error: Out of memory.";

		pFirst->pPrev = NULL;
		pFirst->pData = NULL;
		pFirst->pNext = pLast;

		pLast->pPrev = pFirst;
		pLast->pData = NULL;
		pLast->pNext = NULL;
	}

	virtual ~FileList()
	{
		
	}

	void removeList (){

		clearAll(true);
		delete pFirst;
		delete pLast;
	}

	void add(FileRec * pFile) {

		FileListNode * pNewNode = new FileListNode;
		pNewNode->pData = pFile;

		insertNodeAtBottom(pNewNode);
		
	}

	string getAll()
	{
		string result;
		FileListNode * pCurrent;
		pCurrent = pFirst->pNext;

		while (pCurrent->pData != NULL)
		{
			//Do what you want to each item in the list here:
			// In this case I'm collecting all the data into a single string.
			result += pCurrent->pData->fileName + '\n';

			pCurrent = pCurrent->pNext;
		}

		return result;
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

private:

	void removeNode(FileListNode * pRemove, bool ownedByList = false)
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

	void insertNodeAtBottom(FileListNode * pNewNode)
	{
		insertAbove(pNewNode, pLast);
	}

	void insertAbove(FileListNode *pNewNode, FileListNode *pLocation)
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