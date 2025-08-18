/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:13:59 by jomendes          #+#    #+#             */
/*   Updated: 2025/03/04 12:14:00 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_H
# define WHATEVER_H

# include <iostream>

template <typename T>

void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>

T max(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T>

T min(T a, T b) {
    return (a < b) ? a : b;
}

#endif