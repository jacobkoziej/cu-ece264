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
	inline ~sll(void);
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

}


#endif /* ECE264_P1_H_ */
