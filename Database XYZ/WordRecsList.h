#pragma once

#include "WordRec.h"
#include "WordRecsListNode.h"
#include <vector>

using namespace std;

class WordRecsList {

private:

	WordRecsListNode * pRoot = NULL;

public:

	void add(WordRec * pWordRec){
		
		WordRecsListNode * pNewNode = new WordRecsListNode;
		if (pNewNode == NULL) throw (string) "ERROR: Out of memory!";

		pNewNode->pData = pWordRec;

		addNode(pNewNode, pRoot);

	}

	string getAll()
	{
		string result;
		result = getStringFromTree(pRoot);
		return result;
	}

	string findWord(string word) {

		string result;
		vector<LineRec*> foundLineRecs = getLineRecs(word);

		if (foundLineRecs.size() == 0) throw (string) "ERROR: Word not found!";

		for (unsigned int i = 0; i < foundLineRecs.size(); i++) {

			result += foundLineRecs[i]->line + '\n';
			result += foundLineRecs[i]->fileName + ' ' + '[' + intToString(foundLineRecs[i]->lineNumber) + ']' + "\n\n";

		}

		return result;
	}

	void clearAll(bool ownedByList = false)
	{
		while (!isEmpty()) clearAllLeafNodes(pRoot);
	}

	bool isEmpty()
	{
		return pRoot == NULL;
	}

private:

	vector<LineRec*> getLineRecs(string key) {

		vector<LineRec*> vLineRecs;
		WordRecsListNode * pCurRoot = pRoot;

		while (pCurRoot != NULL) {

			pCurRoot = find(key, pCurRoot);

			if (pCurRoot != NULL && !(pCurRoot->pData->pLineRec->isFound())) {

				vLineRecs.push_back(pCurRoot->pData->pLineRec);
				pCurRoot->pData->pLineRec->setFound(true);
			}
			else break;

		}

		for (unsigned int i = 0; i < vLineRecs.size(); i++) {

			vLineRecs[i]->setFound(false);
		}

		return vLineRecs;
	}

	WordRecsListNode * &  find(string key, WordRecsListNode * &  pCurRoot)
	{
		if (pCurRoot == NULL) return pCurRoot;
		if (pCurRoot->pData->word == key && !(pCurRoot->pData->pLineRec->found)) return pCurRoot;
		if (key < pCurRoot->pData->word)
		{
			return find(key, pCurRoot->pLeft);
		}
		else
		{
			return find(key, pCurRoot->pRight);
		}
	}

	string getStringFromTree(WordRecsListNode * pointerToCurrentRoot)
	{
		if (pointerToCurrentRoot == NULL) return "";
		
		string result;
		result += getStringFromTree(pointerToCurrentRoot->pLeft);
		result += pointerToCurrentRoot->pData->word + "\n";
		result += getStringFromTree(pointerToCurrentRoot->pRight);
		return result;
	}

	void addNode(WordRecsListNode * pNewNode, WordRecsListNode * & pointerToCurrentRoot)
	{
		if (pointerToCurrentRoot == NULL)
		{
			pointerToCurrentRoot = pNewNode;
			return;
		}
		if (pNewNode->pData->word < pointerToCurrentRoot->pData->word)
		{
			//left
			addNode(pNewNode, pointerToCurrentRoot->pLeft);
		}
		else
		{
			//right
			addNode(pNewNode, pointerToCurrentRoot->pRight);
		}

	}

	void clearAllLeafNodes(WordRecsListNode * & pCurRoot)
	{
		if (pCurRoot == NULL) return;
		if ((pCurRoot->pLeft == NULL) && (pCurRoot->pRight == NULL))
		{
			removeNode(pCurRoot);
			return;
		}
		clearAllLeafNodes(pCurRoot->pLeft);
		clearAllLeafNodes(pCurRoot->pRight);
		return;
	}

	WordRecsListNode * &  getLeftMostNode(WordRecsListNode * &  pCurRoot)
	{
		if (pCurRoot->pLeft == NULL) return pCurRoot;
		return getLeftMostNode(pCurRoot->pLeft);
	}

	bool removeNode(WordRecsListNode * & pRemove)
	{
		if ((pRemove->pLeft == NULL) && (pRemove->pRight == NULL))
		{
			delete pRemove;
			pRemove = NULL;
		}
		else if ((pRemove->pLeft != NULL) && (pRemove->pRight == NULL))
		{
			WordRecsListNode * pTemp = pRemove;
			pRemove = pRemove->pLeft;
			//delete pTemp->pData; // if BST owned the data
			delete pTemp;
		}
		else if ((pRemove->pLeft == NULL) && (pRemove->pRight != NULL))
		{
			WordRecsListNode * pTemp = pRemove;
			pRemove = pRemove->pRight;
			delete pTemp;
		}
		else //if ((pRemove->pLeft != NULL) && (pRemove->pRight != NULL))
		{
			WordRecsListNode * & leftMost = getLeftMostNode(pRemove->pRight);
			WordRec * pTemp = leftMost->pData;
			leftMost->pData = pRemove->pData;
			pRemove->pData = pTemp;
			removeNode(leftMost);
		
		}
		return true;
	}

};