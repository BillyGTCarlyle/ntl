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
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>
#include <vector>
#include "parser.h"

using namespace PoDoFo;

PdfPage* currentPage;

void DrawTitle(std::string documentTitle, char* fileName){
	PdfStreamedDocument document(fileName);
	PdfPage* titlePage;
	titlePage = document.CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
		if(!titlePage){
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	}
	currentPage = titlePage;
	PdfFont* dateFont;	
	PdfPainter titlePainter;
	PdfFont* titleFont;
	//Draw Title
	titleFont = document.CreateFont("Arial");
	titleFont->SetFontSize(30);
	titlePainter.SetPage(currentPage);
	titlePainter.SetFont(titleFont);
	titlePainter.DrawText((currentPage->GetPageSize().GetWidth() / 2) - (titleFont->GetFontMetrics()->StringWidth(documentTitle) / 2), currentPage-> GetPageSize().GetHeight() - 75, documentTitle );

	//Draw Date
	titlePainter.SetPage(currentPage);

	dateFont = document.CreateFont("Arial");

	if(!dateFont){
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	}
	dateFont->SetFontSize(18.0);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y");
	auto dateStr = oss.str();
	
	titlePainter.SetFont(dateFont);
	titlePainter.DrawText(currentPage->GetPageSize().GetWidth() - 98, currentPage->GetPageSize().GetHeight() - 20, dateStr);
	titlePainter.FinishPage();

	//Document information
	document.GetInfo()->SetCreator(PdfString("Billy Carlyle"));
	document.GetInfo()->SetAuthor(PdfString("Billy Carlyle"));

	document.Close();
}

/*void DrawListItem(std::string listItem, char* fileName){	
 *	PdfStreamedDocument document(fileName);
 *	PdfFont* listItemFont;
 *	listItemFont = document.CreateFont("Arial");
 *	listItemFont->SetFontSize(18.0);
 *	PdfPainter listItemPainter;
 *	listItemPainter.SetPage(currentPage);
 *
 *	//Draw bullet point
 *	listItemPainter.Circle(20.0, currentPage->GetPageSize().GetHeight() - 40.0, 3.0);
 *	//Draw text
 *	listItemPainter.SetFont(listItemFont);
 *	listItemPainter.DrawText(30, currentPage->GetPageSize().GetHeight() - 40, listItem);
 *	listItemPainter.FinishPage();
 *
 *	document.Close();
 *
 *}
 */
