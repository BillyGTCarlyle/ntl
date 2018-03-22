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

#ifndef render_h
#define render_h
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>
#include <vector>
#include <string>

int InitDocument(const char* fileName);
void DrawTitle(std::string documentTitle, bool end);
void DrawParagraph(std::string text, bool newPara, bool end);
void DrawHighlighted(std::string text, bool newPara, bool end);
void DrawListItem(std::string listItem, bool end);
void DrawEquation(int eqNum);
void DrawBreak(bool end);
void NewPage();
int CloseDocument();
#endif
