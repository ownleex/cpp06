/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:54:20 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/18 22:54:22 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

// Constructeur privé
Serializer::Serializer() {}

// Destructeur privé
Serializer::~Serializer() {}

// Constructeur de copie privé
Serializer::Serializer(const Serializer &src) {
    (void)src;
}

// Opérateur d'affectation privé
Serializer &Serializer::operator=(const Serializer &rhs) {
    (void)rhs;
    return *this;
}

// Méthode pour sérialiser un pointeur vers Data en uintptr_t
uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

// Méthode pour désérialiser un uintptr_t en pointeur vers Data
Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}