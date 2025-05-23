/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:30:25 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/23 16:41:16 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <cmath>
#include <limits>
#include <iostream>

class ScalarConverter {
public:
    // Le seul point d'entrée public
    static void convert(const std::string &literal);

private:
    // Constructeur privé pour empêcher l'instanciation
    ScalarConverter();
    // Destructeur privé
    ScalarConverter(const ScalarConverter &src);
    // Constructeur de copie privé
    ScalarConverter& operator=(const ScalarConverter &rhs);
    // Opérateur d'affectation privé
    ~ScalarConverter();

    // Types possibles pour l'entrée
    enum Type {
        CHAR,
        INT,
        FLOAT,
        DOUBLE,
        PSEUDOLITERAL,
        INVALID
    };

    // Méthodes statiques privées pour la détection et conversion
    // static pour pouvoir être appelée par une methode public static
    static Type detectType(const std::string &literal);
    static bool isPseudoLiteral(const std::string &literal);
    static void printAll(Type type, bool notPossible, char charValue, int intValue, float floatValue, double doubleValue);

};

#endif
