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
    std::cout << "Usage:" << std::endl;
    std::cout << "  ntp [outputfile.pdf]" << std::endl << std::endl;
}
int main( int argc, char* argv[] ){
    /*
     * Check if a filename was passed as commandline argument.
     * If more than 1 argument or no argument is passed,
     * a help message is displayed and the example application
     * will quit.
     */
    if( argc != 4 ){
        PrintHelp();
        return -1;
    }

       try {
        /*
         * Call the drawing routing which will create a PDF file
         * with the filename of the output file as argument.
         */
	parser(argv[3], argv[1]);
    } catch( const PdfError & eCode ) {
        /*
         * We have to check if an error has occurred.
         * If yes, we return and print an error message
         * to the commandline.
         */
        eCode.PrintErrorMsg();
        return eCode.GetError();
    }

    /*
     * The PDF was created sucessfully.
     */
    std::cout << std::endl
              << "Created PDF document " << argv[2] << std::endl << std::endl;
    
    return 0;
}

