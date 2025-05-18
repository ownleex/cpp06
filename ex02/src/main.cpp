/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:58:54 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/18 22:58:57 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>

int main() {
    // Générer une instance aléatoire
    Base* instance = generate();
    
    std::cout << "\nIdentification par pointeur: ";
    identify(instance);
    
    std::cout << "Identification par référence: ";
    identify(*instance);
    
    // Libération de la mémoire
    delete instance;
    
    return 0;
}