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

#include "render.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>
#include <vector>

using namespace PoDoFo;

PdfPage* currentPage = nullptr;
PdfStreamedDocument* pDocument = nullptr;

int InitDocument(char* fileName){
	if (fileName == nullptr){
		throw new std::invalid_argument("fileName == nullptr in InitDocument().");
	}
	if (pDocument != nullptr){
		delete pDocument;
		pDocument = nullptr;
	}
	pDocument = new PdfStreamedDocument(fileName);
	return 0;
}

void DrawTitle(std::string documentTitle){
	if (pDocument == nullptr){
		throw new std::logic_error("DrawTitle() called before InitDocument().");
	}
	PdfPage* titlePage = pDocument->CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
		if(!titlePage){
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	}
	currentPage = titlePage;
	PdfFont* dateFont;	
	PdfPainter titlePainter;
	PdfFont* titleFont;
	//Draw Title
	titleFont = pDocument->CreateFont("Arial");
	titleFont->SetFontSize(30);
	titlePainter.SetPage(currentPage);
	titlePainter.SetFont(titleFont);
	titlePainter.DrawText((currentPage->GetPageSize().GetWidth() / 2) - (titleFont->GetFontMetrics()->StringWidth(documentTitle) / 2), currentPage-> GetPageSize().GetHeight() - 75, documentTitle );

	//Draw Date
	titlePainter.SetPage(currentPage);

	dateFont = pDocument->CreateFont("Arial");

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
	pDocument->GetInfo()->SetCreator(PdfString("Billy Carlyle"));
	pDocument->GetInfo()->SetAuthor(PdfString("Billy Carlyle"));
}

void DrawListItem(std::string listItem){	
	if (pDocument == nullptr){
		throw new std::logic_error("DrawListItem() called before InitDocument().");
	}
	PdfPage* listItemPage = pDocument->CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
	if(!listItemPage){
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	}
	currentPage = listItemPage;
	PdfFont* listItemFont;
	listItemFont = pDocument->CreateFont("Arial");
	listItemFont->SetFontSize(18.0);
	PdfPainter listItemPainter;
	listItemPainter.SetPage(currentPage);
	listItemPainter.SetFont(listItemFont);
	listItemPainter.SetColor(0,0,0);
	//Draw bullet point
	listItemPainter.Circle(20.0, currentPage->GetPageSize().GetHeight() - 40.0, 10.0);
	//Draw text
	listItemPainter.DrawText(50.0, currentPage->GetPageSize().GetHeight() - 40, listItem);
	listItemPainter.FinishPage();
}

int CloseDocument(){
	if (pDocument == nullptr){
		return 1;
	}
	pDocument->Close();
	delete pDocument;
	pDocument = nullptr;
	return 0;
}
