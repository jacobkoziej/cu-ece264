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

/*
 * sll -- singly-linked list
 *        simple-linked list
 *        sabley-linked list!?
 *
 * sll is an abstract class that implements the base functionality of
 * needed for either a stack or queue, namely appending/prepending nodes
 * as well as removing nodes from the head.
 */
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

	/*
	 * Append a node to the head of the linked list.
	 */
	inline std::size_t append(T t);

	/*
	 * Prepend a node to the tail of the linked list.
	 */
	inline std::size_t prepend(T t);

	/*
	 * Remove the current head of the linked list.
	 */
	inline T rm_head(void);


public:
	virtual inline ~sll(void);

	/*
	 * Pure virtual pop() meant to be implemented by the derived
	 * stack/queue.
	 */
	virtual inline T pop(void) = 0;

	/*
	 * Pure virtual push() meant to be implemented by the derived
	 * stack/queue.
	 */
	virtual inline std::size_t push(T t) = 0;

	/*
	 * Return the number of nodes in the linked list.
	 */
	inline std::size_t size(void) const { return nodes; }
};

/*
 * stack -- derived stack class from sll that implements
 * pop() and push()
 */
template<typename T>
class stack : public sll<T> {
public:
	virtual inline T pop(void) { return this->rm_head(); }
	virtual inline std::size_t push(T t) { return this->prepend(t); }
};

/*
 * queue -- derived queue class from sll that implements
 * pop() and push()
 */
template<typename T>
class queue : public sll<T> {
public:
	virtual inline T pop(void) { return this->rm_head(); }
	virtual inline std::size_t push(T t) { return this->append(t); }
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
}

template<typename T>
inline std::size_t sll<T>::append(T t)
{
	struct node *tmp = new struct node;

	tmp->data = t;
	tmp->next = nullptr;

	// append to the existing tail if it exists,
	// else the new node becomes the new head/tail
	tail = (tail) ? tail->next = tmp : head = tmp;
	return ++nodes;
}

template<typename T>
inline std::size_t sll<T>::prepend(T t)
{
	struct node *tmp = new struct node;

	tmp->data = t;
	tmp->next = head;

	// prepend to the existing head if it exists,
	// else the new node becomes the new head/tail
	head = (head) ? tmp : tail = tmp;
	return ++nodes;
}

template<typename T>
inline T sll<T>::rm_head(void)
{
	if (!head) throw std::out_of_range("empty sll");

	struct node *tmp = head;
	T data = tmp->data;

	// move the head to the next node if it exists
	head = (tmp->next) ? tmp->next : tail = nullptr;
	--nodes;

	delete tmp;
	return data;
}

}


#endif /* ECE264_P1_SLL_H_ */
