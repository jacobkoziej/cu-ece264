/*
 * processor.h -- process input commands
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

#ifndef ECE264_P1_PROCESSOR_H_
#define ECE264_P1_PROCESSOR_H_

#include <istream>
#include <map>
#include <ostream>
#include <string>

#include "sll.h"


namespace sable {
using namespace std;

class processor {
private:
	istream *in;
	ostream *out;

	map <string, sll<int>*>    ilist;
	map <string, sll<double>*> dlist;
	map <string, sll<string>*> slist;


	inline void get_ident(const string &in, char &type, string &name);


public:
	processor(istream *in, ostream *out);
	void process(void);
};

}


#endif /* ECE264_P1_PROCESSOR_H_ */
