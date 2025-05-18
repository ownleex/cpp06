/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:54:36 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/18 22:54:38 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

int main() {
    // Création d'une instance de Data
    Data* original = new Data;
    original->s1 = "Bonjour";
    original->n = 42;
    original->s2 = "Monde";

    std::cout << "Données originales:" << std::endl;
    std::cout << "Adresse: " << original << std::endl;
    std::cout << "s1: " << original->s1 << std::endl;
    std::cout << "n: " << original->n << std::endl;
    std::cout << "s2: " << original->s2 << std::endl;
    std::cout << std::endl;

    // Sérialisation du pointeur
    uintptr_t serialized = Serializer::serialize(original);
    std::cout << "Valeur sérialisée: " << serialized << std::endl;
    std::cout << std::endl;

    // Désérialisation
    Data* deserialized = Serializer::deserialize(serialized);
    
    std::cout << "Données désérialisées:" << std::endl;
    std::cout << "Adresse: " << deserialized << std::endl;
    std::cout << "s1: " << deserialized->s1 << std::endl;
    std::cout << "n: " << deserialized->n << std::endl;
    std::cout << "s2: " << deserialized->s2 << std::endl;
    std::cout << std::endl;

    // Vérification que les adresses sont identiques
    std::cout << "Les adresses sont " << (original == deserialized ? "identiques" : "différentes") << std::endl;

    // Libération de la mémoire
    delete original;

    return 0;
}