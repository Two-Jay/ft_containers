/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:57:20 by jekim             #+#    #+#             */
/*   Updated: 2022/07/09 17:39:59 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>
#include "vector.hpp"
#include <map>
#include <list>
#include <iostream>
#include <vector>

int main (void) {
    // write testcases for ft::vector
    // push_back numbers from 0 to 10 by 2
    // and print the size of the vector
    // and the content of the vector (use the iterator) in a single line separated by a space

    ft::vector<int> vec;
    for (int i = 0; i < 10; i += 2) {
        vec.push_back(i);
    }
    std::cout << vec.size() << " ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}