/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:13:45 by jomendes          #+#    #+#             */
/*   Updated: 2025/03/04 14:51:59 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
Array<T>::Array() : data(nullptr), array_size(100) {
}

template <typename T>
Array<T>::Array(unsigned int n) : data(nullptr), array_size(n) {
	if (n == 0) {
        throw std::invalid_argument("Array size must be greater than zero!");
    }
    data = new T[array_size];
}

template <typename T>
Array<T>::~Array() {
	delete[] data;
}

template <typename T>
Array<T>::Array(const Array &copy) : array_size(copy.array_size) {
	if (array_size > 0) {
        data = new T[array_size];
        for (unsigned int i = 0; i < array_size; i++) {
            data[i] = copy.data[i];
        }
    }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other) {
	if (this != &other) {
		delete[] data;
		array_size = other.array_size;
		if (array_size > 0) {
			data = new T[array_size];
			for (unsigned int i = 0; i < array_size; i++) {
				data[i] = other.data[i];
			}
		}
		else
			data = nullptr;
	}
	return (*this);
}

template <typename T>
T& Array<T>::operator[](unsigned int index) {
	if (index >= array_size)
		throw Array::IndexOutOfBounds();
	return data[index];
}

template <typename T>
unsigned int Array<T>::size() const {
	return array_size;
}

template <typename T>
const char* Array<T>::IndexOutOfBounds::what() const throw() {
	return "Index out of bounds!";
}
