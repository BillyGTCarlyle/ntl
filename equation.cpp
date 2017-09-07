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
#include "render.h"

void InitializeDocument(int eqNum, std::string eqString){
	//Create and set up document
	std::string Number = std::to_string(eqNum);
	std::ofstream output(Number+".tex", std::ofstream::out);
	output << "\\documentclass{article} \n";
	output << "\\usepackage{amsmath} \n";
	output << "\\usepackage{amsthm} \n";
	output << "\\usepackage{amssymb} \n";
	output << "\\usepackage{bm} \n";
	output << "\\usepackage[active,displaymath,textmath,tightpage]{preview} \n";
	output << "\\pagestyle{empty} \n";
	output << "\\begin{document} \n";
	output.close();
	//Start rendering the actual equation
	DrawLatexEquation(eqNum, eqString);
}

void DrawLatexEquation(int eqNum, std::string eqString){
	std::string Number = std::to_string(eqNum);
	std::ofstream output(Number+".tex", std::ofstream::out | std::ofstream::app);
	//Write user-written LaTeX to document
	output << "$ ";
	output << eqString << "\n";
	output << " $";
	output.close();
	//End the document and build the pdf
	EndEquation(eqNum);
}

void EndEquation(int eqNum){
	std::string Number = std::to_string(eqNum);
	std::ofstream output(Number+".tex", std::ofstream::out | std::ofstream::app);
	//End the document and close the file
	output << "\\end{document}";
	output.close();
	system(("pdflatex "+Number+".tex").c_str());
	//DrawEquation(eqNum);
}

