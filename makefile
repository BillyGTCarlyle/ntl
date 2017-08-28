# Copyright (C) 2017 Stephan Kreutzer, Billy Carlyle
#
# This file is part of NTL.
#
# NTL is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# NTL is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NTL.  If not, see <http://www.gnu.org/licenses/>.



.PHONY: all clean



all: ntl



ntl: main.cpp parser.o render.o equation.o
	g++ main.cpp -lpodofo parser.o render.o equation.o -o ntl -Wall -Werror

parser.o: parser.h parser.cpp
	g++ parser.cpp -c -Wall -Werror

render.o: render.h render.cpp
	g++ render.cpp -c -Wall -Werror

equation.o: equation.h equation.cpp
	g++ equation.cpp -c -Wall -Werror

clean:
	rm -f ./ntl
	rm -f ./render.o
	rm -f ./parser.o
	rm -f ./equation.o
