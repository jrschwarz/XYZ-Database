#pragma once

#include <string>
#include "FileList.h"
#include "LineRecsList.h"
#include "WordRecsList.h"
#include <vector>

using namespace std;

class Database {

private:

	FileList fileList;				//LinkedList
	LineRecsList lineRecsList;		//LinkedList
	WordRecsList wordRecsList;		//BST

public:

	Database()
	{
		ifstream fin;
		string input;

		fin.open("File_Names.txt");

		if (!fin.fail()) {

			while (!fin.eof()) {

				getline(fin, input);

				if(input != "") addFile(input);
			}
		}

	}

	~Database() {

		ofstream fout;

		fout.open("File_Names.txt");

		fout << fileList.getAll();

		fout.close();

		fileList.removeList();

	}

	void addFile(string fileName) {

		FileRec * pNewFile = new FileRec;
		pNewFile->setFileName(fileName);
		fileList.add(pNewFile);

		ifstream fin;
		int lineNumber = 1;
		string inputLine;

		fin.open(fileName);
		if (fin.fail()) throw (string) "ERROR: File couldn't open!";

		while (!fin.eof()) {

			getline(fin, inputLine);
			
			//build lineRec (new)
			LineRec * pLineRec = new LineRec;
			pLineRec->setFileName(fileName);
			pLineRec->setLine(inputLine);
			pLineRec->setLineNumber(lineNumber);

			//add to list of lineRecs
			lineRecsList.add(pLineRec);

			//convert string to all lowercase
			stringToLower(inputLine);

			vector<TomToken> words = tokenizeAlt2(inputLine);

			for(unsigned int i = 0; i < words.size(); i++) {
				
				//build wordRec
				WordRec * pWordRec = new WordRec;
				pWordRec->setWord(words[i].s);
				pWordRec->setPointerToLineRec(pLineRec);

				//Add it to the BST of WordRec
				wordRecsList.add(pWordRec);

			}

			lineNumber++;
		}

		fin.close();

	}

	string findWord(string word) {

		string result;

		stringToLower(word);

		result = wordRecsList.findWord(word);

		return result;
	}

	void clearFiles() {

		wordRecsList.clearAll(); 
		lineRecsList.clearAll();
		fileList.clearAll();
	}

	/*string display() {

		string result;
		
		result += fileList.getAll() + '\n';
		result += lineRecsList.getAll() + '\n';
		result += wordRecsList.getAll();
		
		return result;
	}*/
};