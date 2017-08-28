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

#ifndef equation_h
#pragma once
#define equation_h
#include <fstream>
#include <iostream>
#include <string>

void InitializeDocument(int eqNum, std::string eqString);
void DrawEquation(int eqNum, std::string eqString);
void EndEquation(int eqNum);

#endif
