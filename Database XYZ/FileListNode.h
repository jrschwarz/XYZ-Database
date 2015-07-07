#pragma once

#include "FileRec.h"

using namespace std;

class FileListNode {

	friend class FileList;

private:

	FileListNode * pPrev;
	FileRec * pData;
	FileListNode * pNext;

};