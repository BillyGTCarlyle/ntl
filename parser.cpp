/*
 * Copyright (c) 2017 Billy Carlyle, Stephan Kreutzer
 *
 * This file is part of NTL.
 *
 *   NTL is free software: you can redistribute it and/or modify
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
#include "equation.h"

using namespace std;

//Initialize regular expressions
const regex newLineEx("//");
const regex highlightEx(":: (.*) ::");
const regex titleEx("#t (.*)");
const regex listTitleEx("#l(.*)");
const regex listItemEx("^ (.*)");
const regex lineEx("#b");
const regex equationEx("#e (.*)");
const regex regularLineEx("(.*)");
smatch matchTitle;
smatch matchNewLine;
smatch matchListTitle;
smatch matchListItem;
smatch matchHighlight;
smatch matchDrawLine;
smatch matchEquation;
smatch matchRegularLine;
int equationNumber = 0;
void parser(char* filePath){
	vector<string> words;
	vector<string> lines;
	string inLine;
	string word;
	string space = " ";
	size_t pos = 0;
	bool newPara = true;
	bool end = false;
	ifstream inFile(filePath);
	// Open input file
	if(inFile.is_open()){

		while(getline(inFile,inLine)){
			lines.push_back(inLine);
			if(regex_search(inLine, matchTitle, titleEx)){
				cout << "Title is " << matchTitle.str(1) << endl;
				InitDocument((matchTitle.str(1)+".pdf").c_str());
				DrawTitle(matchTitle.str(1));
			}else if(regex_search(inLine, matchDrawLine, lineEx)){
				cout << "Line detected" << endl;
			}else if(regex_search(inLine, matchListItem, listItemEx)){
				cout << "Item: " << matchListItem.str(1) << endl;
				DrawListItem(matchListItem.str(1));
			}else if(regex_search(inLine, matchHighlight, highlightEx)){
				cout << "Highlighted text: " << matchHighlight.str(1) << endl;
			}else if(regex_search(inLine, matchEquation, equationEx)){
				cout << "Equation in LaTeX: " << matchEquation.str(1) << endl;
				InitializeDocument(equationNumber, matchEquation.str(1));
				equationNumber++;
			}else if(regex_search(inLine, matchRegularLine, regularLineEx)){
				cout << "Regular line detected" << endl;
				while((pos = matchRegularLine.str(1).find(space)) != string::npos && !inFile.eof()){
					word = matchRegularLine.str(1).substr(0, pos);
					if(inFile.eof())
						end = true;
					DrawParagraph(word, newPara, end);
					inLine.erase(0, pos + space.length());
					if(newPara == true)
						newPara = false;

				}if(regex_search(inLine, matchNewLine, newLineEx)){
				newPara = true;
				}
			}else if(regex_search(inLine, matchNewLine, newLineEx)){
				newPara = true;
			}
		}
		cout << words[0] << endl;
		cout << words[2] << endl;
		CloseDocument();
		inFile.close();
	}else{
		cout << "Error loading file" << endl;
	}
}
