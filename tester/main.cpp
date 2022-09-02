/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:57:20 by jekim             #+#    #+#             */
/*   Updated: 2022/09/02 15:26:11 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./includes/input_initiator.hpp"

int main() {
    Input_initiator input_initiator;

    Test_inputs test_inputs = input_initiator.create_inputs_rand(test_dataType_all());
    
    for (size_t i = 0; i < SHORT_INPUTS_SIZE ; i++)
        std::cout << test_inputs.int_bucket->short_inputs[i] << " " << std::endl;
    return 0;
}