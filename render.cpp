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
 *   along with NTL.  If not, see <http://www.gnu.org/licenses/>.  */

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
PdfPainter painter;
double yCoordinate = 785.0;
double xCoordinate;

int InitDocument(const char* fileName){
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
	PdfFont* titleFont;
	//Draw Title
	titleFont = pDocument->CreateFont("Times New Roman");
	titleFont->SetFontSize(30);
	painter.SetPage(currentPage);
	painter.SetFont(titleFont);
	painter.SetColor(0,0,0);
	painter.DrawText((currentPage->GetPageSize().GetWidth() / 2) - (titleFont->GetFontMetrics()->StringWidth(documentTitle) / 2), currentPage-> GetPageSize().GetHeight() - 75, documentTitle );

	//Draw Date
	painter.SetPage(currentPage);

	dateFont = pDocument->CreateFont("Times New Roman");

	if(!dateFont){
		PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
	}
	dateFont->SetFontSize(18.0);

	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d-%m-%Y");
	auto dateStr = oss.str();
	
	painter.SetFont(dateFont);
	painter.DrawText(currentPage->GetPageSize().GetWidth() - (dateFont->GetFontMetrics()->StringWidth(dateStr)) - 20, currentPage->GetPageSize().GetHeight() - (dateFont->GetFontMetrics()->GetFontSize()) - 20, dateStr);

	//Document information
	pDocument->GetInfo()->SetCreator(PdfString("Billy Carlyle"));
	pDocument->GetInfo()->SetAuthor(PdfString("Billy Carlyle"));
	yCoordinate = (currentPage->GetPageSize().GetHeight() - 75.0);
	NewPage();
}

void DrawParagraph(std::string text, bool newPara){
	//if(yCoordinate < 40.0 || end){
	//	//regularPainter.FinishPage();
	//	NewPage();
	//}
	PdfFont* paraFont;
	paraFont = pDocument->CreateFont("Times New Roman");
	paraFont->SetFontSize(18.0);
	paraFont->SetUnderlined(false);
	painter.SetFont(paraFont);
	if(newPara == true){
		xCoordinate = 75.0;
		yCoordinate -= 18.0;
		std::cout << "New Paragraph created" << std::endl;
		painter.DrawText(xCoordinate, yCoordinate, text);
		xCoordinate += paraFont->GetFontMetrics()->StringWidth(text+" ");
	}else{
		if(xCoordinate < (currentPage->GetPageSize().GetWidth() - 85.0) - paraFont->GetFontMetrics()->StringWidth(text)){
			std::cout << "New word added to para" << std::endl;
			painter.DrawText(xCoordinate, yCoordinate, text);
			xCoordinate += paraFont->GetFontMetrics()->StringWidth(text+" ");
		}else{
			std::cout << "New word added to para" << std::endl;
			xCoordinate = 75.0;
			yCoordinate -= 18.0;
			painter.DrawText(xCoordinate, yCoordinate, text);
			xCoordinate += paraFont->GetFontMetrics()->StringWidth(text+" ");
		}
	}
}

void DrawHighlighted(std::string text, bool newPara){
	//if(yCoordinate < 40.0 || end){
	//	//highlightPainter.FinishPage();
	//	NewPage();
	//}
	PdfFont* highlightFont;
	highlightFont = pDocument->CreateFont("Times New Roman");
	highlightFont->SetUnderlined(true);
	//highlightFont->SetBold(true);
	highlightFont->SetFontSize(18.0);
	painter.SetFont(highlightFont);
	painter.SetColor(1,0,0);
	if(newPara == true){
		xCoordinate = 75.0;
		yCoordinate -= 18.0;
		std::cout << "New Paragraph created" << std::endl;
		painter.DrawText(xCoordinate, yCoordinate, text);
		xCoordinate += highlightFont->GetFontMetrics()->StringWidth(text+" ");
	}else{
		std::cout << "New word added to para" << std::endl;
		painter.DrawText(xCoordinate, yCoordinate, text);
		xCoordinate += highlightFont->GetFontMetrics()->StringWidth(text+" ");
	}
	painter.SetColor(0,0,0);
}

void DrawListItem(std::string listItem){
	if (pDocument == nullptr){
		throw new std::logic_error("DrawListItem() called before InitDocument().");
	}		
	PdfFont* listItemFont;
	listItemFont = pDocument->CreateFont("Times New Roman");
	listItemFont->SetFontSize(18.0);
	painter.SetFont(listItemFont);
	//Draw bullet point
	xCoordinate = 75.0;
	yCoordinate -= 18.0;
	painter.SetColor(0,0,0);
	painter.Circle(xCoordinate, yCoordinate + 5, 4.0);

	xCoordinate += 15;
	//Draw text
	painter.DrawText(xCoordinate, yCoordinate, listItem);
}

void DrawBreak(){
	yCoordinate -= 20.0;
	if (pDocument == nullptr){
		throw new std::logic_error("DrawBreak() called before InitDocument().");
	}
	painter.DrawLine(0.0, yCoordinate, currentPage->GetPageSize().GetWidth(), yCoordinate);
	yCoordinate -= 20.0;
}
/*void DrawEquation(int eqNum){
 *       //Takes equation PDF and appends it to the main document
 *       std::string Number = std::to_string(eqNum);
 *       PdfMemDocument equation((Number+".pdf").c_str());
}*/

void NewPage(){
	painter.FinishPage();
	PdfPage* newPage = pDocument->CreatePage(PdfPage::CreateStandardPageSize(ePdfPageSize_A4));
	currentPage = newPage;
	painter.SetPage(currentPage);
	yCoordinate = 785.0;
	xCoordinate = 75.0;
}

int CloseDocument(){
	painter.FinishPage();
	if (pDocument == nullptr){
		return 1;
	}
	pDocument->Close();
	delete pDocument;
	pDocument = nullptr;
	return 0;
}
