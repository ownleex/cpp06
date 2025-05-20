/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:58:54 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/20 23:46:00 by ayarmaya         ###   ########.fr       */
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
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;

    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;

    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
        
    else
        std::cout << "Type inconnu" << std::endl;
}

// Fonction pour identifier le type réel via une référence
void identify(Base& p) {
    // Utiliser dynamic_cast et capturer les exceptions
    // car dynamic_cast sur référence lance une exception std::bad_cast en cas d'échec
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (std::bad_cast&) {}
    
    std::cout << "Type inconnu" << std::endl;
}

// Fonction pour générer aléatoirement une instance de A, B ou C
Base* generate(void) {
    // Initialiser le générateur de nombres aléatoires
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    
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
    
    std::cout << "\nIdentification par pointeur: ";
    identify(instance);
    
    std::cout << "Identification par référence: ";
    identify(*instance);
    
    // Libération de la mémoire
    delete instance;
    
    return 0;
}