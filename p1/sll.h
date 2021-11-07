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
#include <exception>


namespace sable {

template<typename T>
class sll {
private:
	struct node {
		T data;
		struct node *next;
	};


protected:

	struct node *head = nullptr;
	struct node *tail = nullptr;

	std::size_t nodes = 0;

	inline std::size_t append(T t);
	inline std::size_t prepend(T t);
	T rm_head(void);


public:
	inline ~sll(void);

	std::size_t del(std::size_t n);
	T get(std::size_t n);
	inline std::size_t size(void) const { return nodes; }
};


template<typename T>
inline sll<T>::~sll(void)
{
	struct node *tmp;
	while (head) {
		tmp  = head;
		head = tmp->next;
		delete tmp;
	}
	tail = nullptr;
	nodes = 0;
}

template<typename T>
inline std::size_t sll<T>::append(T t)
{
	struct node *tmp = new struct node;

	tmp->data = t;
	tmp->next = nullptr;

	tail = (tail) ? tail->next = tmp : head = tmp;
	return ++nodes;
}

template<typename T>
std::size_t sll<T>::del(std::size_t n)
{
	if (!nodes) throw std::out_of_range("empty sll");
	if (n > nodes - 1) throw std::out_of_range("invalid index");


	struct node *prv, *tmp = head;

	if (!n) {
		// special case where
		// we remove the head
		head = tmp->next;
	} else {
		while (n-- && tmp->next) {
			prv = tmp;
			tmp = tmp->next;
		}
		prv->next = tmp->next;

		// we don't want a dangling tail
		// if we're removing the last node
		if (tmp == tail) tail = prv;
	}

	delete tmp;

	// when there are <= 1 nodes, head and tail point to the same
	// thing: either head or nullptr
	if (--nodes <= 1) {
		tail = head;
	}

	return nodes;
}

template<typename T>
T sll<T>::get(std::size_t n)
{
	if (!nodes) throw std::out_of_range("empty sll");
	if (n > nodes - 1) throw std::out_of_range("invalid index");


	struct node *tmp = head;
	while (n--) tmp = tmp->next;

	return tmp->data;
}

template<typename T>
inline std::size_t sll<T>::prepend(T t)
{
	struct node *tmp = new struct node;

	tmp->data = t;
	tmp->next = head;

	head = (tail) ? tmp : tail = tmp;
	return ++nodes;
}

template<typename T>
T sll<T>::rm_head(void)
{
	if (!head) throw std::out_of_range("empty sll");

	struct node *tmp = head;
	T data = tmp->data;

	head = (tmp->next) ? tmp->next : tail = tmp->next;
	--nodes;

	delete tmp;
	return data;
}

}


#endif /* ECE264_P1_H_ */
