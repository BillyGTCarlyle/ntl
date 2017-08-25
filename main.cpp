/*
 * Copyright (c) 2017 Billy Carlyle
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

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>
#include <vector>
#include "parser.h"
using namespace PoDoFo;

void PrintHelp(){
	//If the user doesn't know what arguments are required
	std::cout << "Usage:" << std::endl;
	std::cout << "  ntp [outputfile.pdf] [inputfile.ntl]" << std::endl << std::endl;
}
int main( int argc, char* argv[] ){
	/*
	 * argv[1] should be output file name, OR help,
	 * argv[2] should be input file name.
	 */
	if( argc != 3 ){
		PrintHelp();
		return -1;
	}
	if(std::string(argv[1]) == "help"){
		PrintHelp();
		return -1;
	}

	try {
		parser(argv[2], argv[1]);
	}catch(const PdfError & eCode){
        
	eCode.PrintErrorMsg();
	return eCode.GetError();
	}
	/*
	* The PDF was created sucessfully.
	*/
	std::cout << std::endl
		<< "Created PDF document " << argv[1] << std::endl << std::endl;
	
	return 0;
}

