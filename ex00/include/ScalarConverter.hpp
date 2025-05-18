/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:30:25 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/18 21:41:18 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>

class ScalarConverter
{
private:
    // Constructeur privé pour empêcher l'instanciation
    ScalarConverter();
    // Destructeur privé
    ~ScalarConverter();
    // Constructeur de copie privé
    ScalarConverter(const ScalarConverter &src);
    // Opérateur d'affectation privé
    ScalarConverter &operator=(const ScalarConverter &rhs);

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
    static Type detectType(const std::string &literal);
    static void convertToChar(double value, bool impossible);
    static void convertToInt(double value, bool impossible);
    static void convertToFloat(double value, bool impossible);
    static void convertToDouble(double value, bool impossible);
    static bool isPseudoLiteral(const std::string &literal);

public:
    // Méthode statique publique pour la conversion
    static void convert(const std::string &literal);
};

#endif