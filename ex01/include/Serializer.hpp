/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:54:02 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/18 22:54:04 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
private:
    // Constructeur privé pour empêcher l'instanciation
    Serializer();
    // Destructeur privé
    ~Serializer();
    // Constructeur de copie privé
    Serializer(const Serializer &src);
    // Opérateur d'affectation privé
    Serializer &operator=(const Serializer &rhs);

public:
    // Méthode pour sérialiser un pointeur vers Data en uintptr_t
    static uintptr_t serialize(Data* ptr);
    
    // Méthode pour désérialiser un uintptr_t en pointeur vers Data
    static Data* deserialize(uintptr_t raw);
};

#endif