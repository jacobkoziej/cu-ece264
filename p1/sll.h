/*
 * sll.h -- singly-linked list
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

#ifndef ECE264_P1_SLL_H_
#define ECE264_P1_SLL_H_

#include <cstddef>


namespace sable {

template<typename T>
class sll {
private:
	struct node {
		T data;
		struct node *next;
	};

	struct node *head = nullptr;
	struct node *tail = nullptr;

	std::size_t nodes = 0;


public:
	inline ~sll(void) { clear(); }

	inline std::size_t append(T t);
	inline void clear(void);
	inline std::size_t prepend(T t);
	inline std::size_t size(void) const { return nodes; }
};


template<typename T>
inline std::size_t sll<T>::append(T t)
{
	struct node *n = new struct node;

	n->data = t;
	n->next = nullptr;

	tail = (tail) ? tail->next = n : head = n;
	return ++nodes;
}

template<typename T>
inline void sll<T>::clear(void)
{
	struct node *tmp;
	while (head) {
		tmp  = head;
		head = tmp->next;
		delete tmp;
	}
	nodes = 0;
}

template<typename T>
inline std::size_t sll<T>::prepend(T t)
{
	struct node *n = new struct node;

	n->data = t;
	n->next = head;

	head = (tail) ? n : tail = n;
	return ++nodes;
}

}


#endif /* ECE264_P1_H_ */
