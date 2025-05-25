/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:58:54 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/25 03:20:17 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>

// Fonction pour identifier le type réel via un pointeur
void identify(Base* p) {
    // Utiliser dynamic_cast et vérifier si le résultat est NULL
    // sur pointeur il renvoie NULL en cas d'echec
    // dynamic_cast car il gere le polymorphisme de class, vérifié à l'éxécution
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;

    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;

    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
        
    else
        std::cout << "Type inconnu" << std::endl;
}

// Fonction pour identifier le type réel via une référence
void identify(Base& p) {
    // Utiliser dynamic_cast et capturer les exceptions
    // car sur référence il lance une exception std::bad_cast en cas d'échec
    // dynamic_cast car il gere le polymorphisme de class, vérifié à l'éxécution
    try {
        dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}
    
    try {
        dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}
    
    try {
        dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
    
    std::cout << "Type inconnu" << std::endl;
}

// Fonction pour générer aléatoirement une instance de A, B ou C
Base* generate(void) {
    // Initialiser le générateur de nombres aléatoires
    std::srand(std::time(NULL));
    
    // Générer un nombre aléatoire entre 0 et 2
    int random = std::rand() % 3;
    
    // Créer une instance selon le nombre généré
    switch (random) {
        case 0:
            std::cout << "Création d'une instance de classe A" << std::endl;
            return new A();

        case 1:
            std::cout << "Création d'une instance de classe B" << std::endl;
            return new B();

        case 2:
            std::cout << "Création d'une instance de classe C" << std::endl;
            return new C();
            
        default:
            return NULL;
    }
}

int main() {
    // Générer une instance aléatoire
    Base* instance = generate();
    
    std::cout << "Identification par pointeur: ";
    identify(instance);
    
    std::cout << "Identification par référence: ";
    identify(*instance);
    
    // Libération de la mémoire
    delete instance;
    
    return 0;
}