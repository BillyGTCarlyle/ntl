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

#include <iostream>
#include <sstream>
#include <fstream>
#include "parser.h"
#include "equation.h"


void InitializeDocument(int eqNum, std::string eqString){
	//Create and set up document
	std::string Number = std::to_string(eqNum);
	std::ofstream output(Number+".tex");
	output << "\\documentclass{article} \n";
	output << "\\usepackage{amsmath} \n";
	output << "\\usepackage{amsthm} \n";
	output << "\\usepackage{amssymb} \n";
	output << "\\usepackage{bm} \n";
	output << "\\usepackage[active,displaymath,textmath,tightpage]{preview} \n";
	output << "\\pagestyle{empty} \n";
	output << "\\begin{document} \n";
	//Start rendering the actual equation
	DrawEquation(eqNum, eqString);
}

void DrawEquation(int eqNum, std::string eqString){
	
	//End the document
	EndEquation();
}

void EndEquation(){
	output << "\\end{document}";
}
