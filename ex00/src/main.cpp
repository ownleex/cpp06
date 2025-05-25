/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:31:18 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/26 01:31:57 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>  
#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: ./convert [valeur]" << std::endl;
        return 1;
    }

    ScalarConverter::convert(argv[1]);

    return 0;
}