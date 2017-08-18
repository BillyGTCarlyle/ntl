#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
int main(int argc, char* argv[]){
	string inLine;
	string outLine;
	string breakLine = "//";
	string beginCommand = "`";
	size_t pos = 0;
	if(argc < 2){
		cout << "Incorrect usage." << endl;
		cout << "Correct usage: ntl [source file]" << endl;
	}
	char *filePath = argv[1];
	ifstream inFile (filePath);
	// Open the input file
	if(inFile.is_open()){
		while(getline(inFile,inLine)){
			// Check for // delimiter
			while((pos = inLine.find(breakLine)) != string::npos){
				outLine = inLine.substr(0, pos);
				cout << outLine << endl;
				inLine.erase(0, pos + breakLine.length());
			}
			cout << inLine << endl;
		inFile.close();
		}
	}else{
		cout << "Error loading file" << endl;
	}
	cout << inLine << endl;
	return 0;
	
}
