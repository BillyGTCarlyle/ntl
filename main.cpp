#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>
#include <vector>
#include "parser.h"
#include "render.h"
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
	if(argv[1] == "help"){
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

