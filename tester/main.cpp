/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:57:20 by jekim             #+#    #+#             */
/*   Updated: 2022/09/02 14:30:22 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./includes/input_initiator.hpp"

int main() {
    Input_initiator input_initiator;

    Test_inputs test_inputs = input_initiator.create_inputs_rand(test_dataType_all());
    (void) test_inputs;
    // std::cout << b << std::endl;
    return 0;
}