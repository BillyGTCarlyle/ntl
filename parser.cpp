#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "parser.h"

using namespace std;

const regex newLineEx("\\\\");
const regex highlightEx(":: (.*) ::");
const regex titleEx("#t (.*)");
const regex listTitleEx("#l(.*)");
const regex listItemEx("^ (.*)");
const regex lineEx("#b");
smatch matchTitle;
smatch matchNewLine;
smatch matchListTitle;
smatch matchListItem;
smatch matchHighlight;
smatch matchDrawLine;
void parser(char* filePath){
	vector<string> words;
	vector<string> lines;
	string inLine;
	string word;
	string space = " ";
	size_t pos = 0;
	ifstream inFile(filePath);
	// Open input file
	if(inFile.is_open()){
		while(getline(inFile,inLine)){
			lines.push_back(inLine);
			if(regex_search(inLine, matchTitle, titleEx)){
				cout << "Title is " << matchTitle.str(1) << endl;
			}else if(regex_search(inLine, matchDrawLine, lineEx)){
				cout << "Line detected" << endl;
			}else if(regex_search(inLine, matchListItem, listItemEx)){
				cout << "Item: " << matchListItem.str(1) << endl;
			}else if(regex_search(inLine, matchHighlight, highlightEx)){
				cout << "Highlighted text: " << matchHighlight.str(1) << endl;
			}
			while((pos = inLine.find(space)) != string::npos){
				word = inLine.substr(0, pos);
				words.push_back(word);
				
				inLine.erase(0, pos + space.length());
			}
			words.push_back(word);
		}
		cout << words[0] << endl;
		cout << words[2] << endl;
		inFile.close();
	}else{
		cout << "Error loading file" << endl;
	}
}
