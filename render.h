#ifndef render_h
#pragma once
#define render_h
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <podofo/podofo.h>
#include <vector>
#include <string>
#include "parser.h"

void DrawTitle(std::string documentTitle, const char* pszFilename);
#endif
