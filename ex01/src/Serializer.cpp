/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:54:20 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/28 00:09:01 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// Constructeur privé
Serializer::Serializer() {}

// Constructeur de copie privé
Serializer::Serializer(const Serializer &src) {
    (void)src;
}

// Destructeur privé
Serializer::~Serializer() {}

// Opérateur d'affectation privé
Serializer &Serializer::operator=(const Serializer &rhs) {
    (void)rhs;
    return *this;
}

// Méthode pour sérialiser un pointeur Data en uintptr_t, reinterpret_cast car on veut la valeur en bit du pointeur
// contrairement à ex00 où on manipulait des valeurs numériques entre types scalaires
// pas de verification ni à la compilation ni à l'éxécution
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

// Méthode pour désérialiser un uintptr_t en pointeur Data, reinterpret_cast car on veut la valeur en bit du pointeur
// contrairement à ex00 où on manipulait des valeurs numériques entre types scalaires
// pas de verification ni à la compilation ni à l'éxécution
Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}