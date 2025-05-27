/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:31:18 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/27 23:52:44 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
    
    if (argc != 2) {
        
        std::cout << "Usage: ./convert [valeur]" << std::endl;
        return 1;
    }

    std::string literal = argv[1];
    
    ScalarConverter::convert(literal);

    return 0;
}