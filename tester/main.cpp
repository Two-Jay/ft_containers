/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:57:20 by jekim             #+#    #+#             */
/*   Updated: 2022/09/02 17:42:07 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "./includes/input_initiator.hpp"
#include "./includes/Container_test_runner.hpp"

int main() {
    Container_test_runner a;

    for (size_t i = 0; i < SHORT_INPUTS_SIZE; i++)
        std::cout << a.get_inputs().int_bucket.short_inputs[i] << std::endl;
    return 0;
}