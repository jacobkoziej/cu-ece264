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
#include <vector>

#include "sll.h"


namespace sable {
using namespace std;

/*
 * processor -- take input from a stream to manipulate integer, double,
 * and string stacks/queues and emit processed inputs to an output
 * stream.
 */
class processor {
private:
	istream *in;
	ostream *out;

	map <string, sll<int>*>    ilist;
	map <string, sll<double>*> dlist;
	map <string, sll<string>*> slist;


	/*
	 * Create a stack/queue using processed tokens.
	 * The tokens should include both the name and type of list.
	 */
	void create(const vector<string> &tokens);

	/*
	 * Translate an input name token into a stack/queue data type
	 * and name.
	 */
	inline void get_ident(const string &in, char &type, string &name);

	/*
	 * Check if a named stack/queue already exists.
	 */
	template <typename T>
	inline bool key_check(map<string, T> m, string key)
	{
		return m.find(key) != m.end();
	}

	/*
	 * Pop a value from a stack/queue using a processed token.
	 * The token should include both the name and data type.
	 */
	void pop(const vector<string> &tokens);

	/*
	 * Push a value onto a stack/queue using a processed token.
	 * The token should include both the name and data type.
	 */
	void push(const vector<string> &tokens);


public:
	/*
	 * Initialize the input and output streams.
	 */
	processor(istream *in, ostream *out);

	~processor(void);

	/*
	 * Process the predefined input stream to manipulate integer,
	 * double, and string stacks/queues and emit processed inputs
	 * to the predefined output stream.
	 */
	void process(void);
};

}


#endif /* ECE264_P1_PROCESSOR_H_ */
