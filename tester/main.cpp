/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:57:20 by jekim             #+#    #+#             */
/*   Updated: 2022/09/01 20:31:54 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./includes/input_initiator.hpp"

int main() {
    Input_initiator a;

    Test_inputs b = a.create_inputs_rand();
    (void) b;
    // std::cout << b << std::endl;
    return 0;
}