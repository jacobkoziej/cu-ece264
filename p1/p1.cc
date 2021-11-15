/*
 * p1.cc -- programming assignment #1
 *          process an input file and output processing output to the
 *          specified output file
 * Copyright (C) 2021  Jacob Koziej <jacobkoziej@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "processor.h"


using namespace std;


int main(int argc, char **argv)
{
	(void) argc;
	static ifstream in;
	static ofstream out;
	static string   tmp;


	cout << "input file: ";
	cin >> tmp;
	in.open(tmp);
	if (!in) {
		cerr
			<< argv[0]
			<< ": '" << tmp << '\''
			<< " not found!\n";
		return EXIT_FAILURE;
	}

	cout << "output file: ";
	cin >> tmp;
	out.open(tmp);

	tmp.clear();


	sable::processor p1(&in, &out);
	p1.process();


	return EXIT_SUCCESS;
}
