/*
 * processor.cc -- process input commands
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

#include "processor.h"

#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "sll.h"


namespace sable {
using namespace std;

inline void processor::get_ident(const string &in, char &type, string &name)
{
	type = in[0];
	name = in;
	name.erase(0, 1);
}

processor::processor(istream *in, ostream *out)
{
	if (!in) throw invalid_argument("no input stream");
	if (!out) throw invalid_argument("no output stream");

	this->in  = in;
	this->out = out;
}

void processor::process(void)
{
	string cmd, token;
	vector <string> tokens;

	while (getline(*in, cmd)) {
		*out << "PROCESSING COMMAND: " << cmd << '\n';

		stringstream tmp(cmd);
		while (getline(tmp, token, ' ')) tokens.push_back(token);

		tokens.clear();
	}
}

}
