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

void processor::create(const vector<string> &tokens)
{
	char type;
	string name;
	get_ident(tokens[0], type, name);

	if (type == 'i') {
		if (key_check<sll<int>*>(ilist, name)) goto error;
		ilist[name] = (tokens[1] == "stack")
			? (sll<int>*) new stack<int>
			: (sll<int>*) new queue<int>;
	}
	if (type == 'd') {
		if (key_check<sll<double>*>(dlist, name)) goto error;
		dlist[name] = (tokens[1] == "stack")
			? (sll<double>*) new stack<double>
			: (sll<double>*) new queue<double>;
	}
	if (type == 's') {
		if (key_check<sll<string>*>(slist, name)) goto error;
		slist[name] = (tokens[1] == "stack")
			? (sll<string>*) new stack<string>
			: (sll<string>*) new queue<string>;
	}

	return;

error:
	*out << "ERROR: This name already exists!\n";
}

inline void processor::get_ident(const string &in, char &type, string &name)
{
	type = in[0];
	name = in;
	name.erase(0, 1);
}

void processor::pop(const vector<string> &tokens)
{
	char type;
	string name;
	get_ident(tokens[0], type, name);

	if (type == 'i') {
		if (!key_check<sll<int>*>(ilist, name)) goto dne;
		if (!ilist[name]->size()) goto empty;
		*out << "Value popped: " << ilist[name]->pop() << '\n';
	}
	if (type == 'd') {
		if (!key_check<sll<double>*>(dlist, name)) goto dne;
		if (!dlist[name]->size()) goto empty;
		*out << "Value popped: " << dlist[name]->pop() << '\n';
	}
	if (type == 's') {
		if (!key_check<sll<string>*>(slist, name)) goto dne;
		if (!slist[name]->size()) goto empty;
		*out << "Value popped: " << slist[name]->pop() << '\n';
	}

	return;

dne:
	*out << "ERROR: This name does not exist!\n";
	return;

empty:
	*out << "ERROR: This list is empty!\n";
}

void processor::push(const vector<string> &tokens)
{
	char type;
	string name;
	get_ident(tokens[0], type, name);

	if (type == 'i') {
		if (!key_check<sll<int>*>(ilist, name)) goto error;
		ilist[name]->push(stoi(tokens[1]));
	}
	if (type == 'd') {
		if (!key_check<sll<double>*>(dlist, name)) goto error;
		dlist[name]->push(stod(tokens[1]));
	}
	if (type == 's') {
		if (!key_check<sll<string>*>(slist, name)) goto error;
		slist[name]->push(tokens[1]);
	}

	return;

error:
	*out << "ERROR: This name does not exist!\n";
}

processor::processor(istream *in, ostream *out)
{
	if (!in) throw invalid_argument("no input stream");
	if (!out) throw invalid_argument("no output stream");

	this->in  = in;
	this->out = out;
}

processor::~processor(void)
{
	for (auto i : ilist)
		delete i.second;

	for (auto d : dlist)
		delete d.second;

	for (auto s : slist)
		delete s.second;
}

void processor::process(void)
{
	string cmd, token;
	vector <string> tokens;

	while (getline(*in, cmd)) {
		*out << "PROCESSING COMMAND: " << cmd << '\n';

		stringstream tmp(cmd);
		getline(tmp, cmd, ' ');
		while (getline(tmp, token, ' ')) tokens.push_back(token);

		if (cmd == "create") create(tokens);
		if (cmd == "push") push(tokens);
		if (cmd == "pop") pop(tokens);

		tokens.clear();
	}
}

}
