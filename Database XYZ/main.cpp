#include <iostream>
#include <fstream>
#include <time.h>
#include "Transducer.h"

using namespace std;

string getCommandFrom(ifstream & fin)
{
	string com;
	if (fin.eof())
	{
		com = "ENDBATCH";
	}
	else
	{
		getline(fin, com);
	}
	if (fin.eof() && com == "")
	{
		com = "ENDBATCH";
	}
	return com;
}

string metaHelp()
{
	string result;
	result += "Meta Commands:\n";
	result += "-------------------------\n";
	result += "\tBATCH <filename>\n";
	result += "\tENDBATCH\n";
	result += "\tREDIRECT <filename>\n";
	result += "\tDIRECT\n";
	result += "\tTON\n";
	result += "\tTOFF\n";
	result += "\tMETAHELP\n\n";
	return result;
}

void AdvancedCommandLineInterface(Transducer & t) {

	ifstream fin;
	ofstream fout;
	bool batchActive = false;
	bool redirectActive = false;
	bool timerOn = false;
	string com;
	cout << metaHelp();
	cout << t.transduce((string)"HELP") << endl;

	do
	{
		try {
			if (!batchActive)
			{
				cout << ">";
				getline(cin, com);
			}
			else
			{
				com = getCommandFrom(fin);
			}


			//META COMMANDS
			if (com.substr(0, 5) == "BATCH")
			{
				string filename = com.substr(6, 9999);
				fin.open(filename.c_str());
				batchActive = true;
			}
			else if (com == "ENDBATCH")
			{
				fin.close();
				fin.clear();
				batchActive = false;
			}
			else if (com.substr(0, 8) == "REDIRECT")
			{
				string filename = com.substr(9, 9999);
				fout.open(filename.c_str());
				redirectActive = true;
			}
			else if (com == "DIRECT")
			{
				fout.close();
				fout.clear();
				redirectActive = false;
			}
			else if (com == "TON")
			{
				timerOn = true;
			}
			else if (com == "TOFF")
			{
				timerOn = false;
			}
			else if (com == "METAHELP")
			{
				if (redirectActive)
				{
					fout << metaHelp();
				}
				else
				{
					cout << metaHelp();
				}
			}
			else
			{
				string transducerResults;
				clock_t startTime = clock();
				transducerResults = t.transduce(com);
				clock_t endTime = clock();
				clock_t elapsedTime = endTime - startTime;
				if (!redirectActive)
				{
					cout << transducerResults << endl;
					if (timerOn) cout << "[" << elapsedTime << "ms]" << endl;
				}
				else
				{
					fout << transducerResults << endl;
					if (timerOn) fout << "[" << elapsedTime << "ms]" << endl;
				}
			}
		}
		catch (string error) {

			cout << error << endl << endl;
		}

	} while ((com != "QUIT") && (com != "Q"));


}

int main() {

	Transducer transducer;
	AdvancedCommandLineInterface(transducer);
	return 0;
}