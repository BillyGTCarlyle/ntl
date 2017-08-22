#ifndef parser_h
#pragma once
#define parser_h
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void parser(char* filePath, char* fileName);
extern std::vector<std::string> words;
#endif
