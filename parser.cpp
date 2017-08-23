/*
 * Copyright (c) 2017 Billy Carlyle
 *
 * This file is part of NTL.
 *  
 *   Ntl is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   NTL is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with NTL.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "parser.h"
#include "render.h"

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
void parser(char* filePath, char* fileName){
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
				DrawTitle(matchTitle.str(1), fileName);
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
