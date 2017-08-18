#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>

using namespace PoDoFo;

void PrintHelp(){
    std::cout << "Usage:" << std::endl;
    std::cout << " ntp [outputfile.pdf]" << std::endl << std::endl;
}

void DrawDate( const char* pszFilename, const char* documentTitle ) {
    if(!documentTitle){
	documentTitle = "Document";
    }
    PdfStreamedDocument document( pszFilename );
    PdfPage* pPage;
    PdfPainter painter;
    PdfFont* dateFont;
    PdfFont* titleFont;

    pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );

    if( !pPage ){
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    painter.SetPage( pPage );

    dateFont = document.CreateFont( "Arial" );
    titleFont = document.CreateFont( "Arial" );
    
    /*
     * If the PdfFont object cannot be allocated return an error.
     */
    if( !dateFont ){
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }
    if( !titleFont ){
    	PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    dateFont->SetFontSize( 18.0 );


    /* Get current date for top of page. */
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y");
    auto dateStr = oss.str();

    painter.SetFont( dateFont );
    painter.DrawText( pPage->GetPageSize().GetWidth() - 98, pPage->GetPageSize().GetHeight() - 20, dateStr );
    painter.SetColorCMYK(0.5, 0.2, 0.0, 0.3);
    titleFont->SetFontSize( 30.0 );
    painter.SetFont( titleFont );
    painter.DrawText( pPage->GetPageSize().GetWidth() / 2, pPage-> GetPageSize().GetHeight() - 75, documentTitle );

    painter.FinishPage();

    document.GetInfo()->SetCreator ( PdfString("Billy Carlyle") );
    document.GetInfo()->SetAuthor  ( PdfString("Billy Carlyle") );
    document.GetInfo()->SetTitle   ( PdfString(documentTitle) );
    document.GetInfo()->SetSubject ( PdfString("Testing the PoDoFo PDF Library") );
    document.GetInfo()->SetKeywords( PdfString("Test;PDF;Hello World;") );

    /*
     * The last step is to close the document.
     */
    document.Close();
}

int main( int argc, char* argv[] )
{
    /*
     * Check if a filename was passed as commandline argument.
     * If more than 1 argument or no argument is passed,
     * a help message is displayed and the example application
     * will quit.
     */
    if( argc != 3 )
    {
        PrintHelp();
        return -1;
    }

       try {
        /*
         * Call the drawing routing which will create a PDF file
         * with the filename of the output file as argument.
         */
         DrawDate( argv[1], argv[2]);
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

