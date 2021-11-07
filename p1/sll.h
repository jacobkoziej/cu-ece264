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
	inline T rm_head(void);


public:
	virtual inline ~sll(void);

	virtual inline T pop(void) = 0;
	virtual inline std::size_t push(T t) = 0;
	inline std::size_t size(void) const { return nodes; }
};

template<typename T>
class stack : public sll<T> {
public:
	virtual inline T pop(void) { return this->rm_head(); }
	virtual inline std::size_t push(T t) { return this->prepend(t); }
};

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
inline std::size_t sll<T>::prepend(T t)
{
	struct node *tmp = new struct node;

	tmp->data = t;
	tmp->next = head;

	head = (tail) ? tmp : tail = tmp;
	return ++nodes;
}

template<typename T>
inline T sll<T>::rm_head(void)
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
