/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:30:15 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/23 14:45:10 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// Constructeur privé
ScalarConverter::ScalarConverter() {}

// Destructeur privé
ScalarConverter::~ScalarConverter() {}

// Constructeur de copie privé
ScalarConverter::ScalarConverter(const ScalarConverter &src) {
    (void)src;
}

// Opérateur d'affectation privé
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs) {
    (void)rhs;
    return *this;
}

// Méthode pour détecter le type du littéral
ScalarConverter::Type ScalarConverter::detectType(const std::string &literal) {
    // Vérification des pseudo-littéraux
    if (isPseudoLiteral(literal))
        return PSEUDOLITERAL;

    // Si c'est un seul caractère et non un chiffre, c'est un char
    if (literal.length() == 1 && !isdigit(literal[0]))
        return CHAR;


    // Vérifie si c'est un int
    bool isInteger = true;
    size_t i = 0;
    
    // Gestion du signe négatif
    if (literal[0] == '-' || literal[0] == '+')
        i++;
        
    for (; i < literal.length(); i++) {
        if (!isdigit(literal[i])) {
            isInteger = false;
            break;
        }
    }
    
    if (isInteger)
        return INT;


    // Vérifie si c'est un float
    bool isFloat = true;
    bool hasDecimalPoint = false;
    bool hasF = false;
    
    i = 0;
    // Gestion du signe négatif
    if (literal[0] == '-' || literal[0] == '+')
        i++;
        
    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDecimalPoint) {
                isFloat = false;
                break;
            }
            hasDecimalPoint = true;
        } else if (literal[i] == 'f' || literal[i] == 'F') {
            if (i != literal.length() - 1 || hasF) {
                isFloat = false;
                break;
            }
            hasF = true;
        } else if (!isdigit(literal[i])) {
            isFloat = false;
            break;
        }
    }
    
    if (isFloat && hasF)
        return FLOAT;


    // Vérifie si c'est un double
    bool isDouble = true;
    hasDecimalPoint = false;
    
    i = 0;
    // Gestion du signe négatif
    if (literal[0] == '-' || literal[0] == '+')
        i++;
        
    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDecimalPoint) {
                isDouble = false;
                break;
            }
            hasDecimalPoint = true;
        } else if (!isdigit(literal[i])) {
            isDouble = false;
            break;
        }
    }
    
    if (isDouble && hasDecimalPoint)
        return DOUBLE;

    return INVALID;
}

// Méthode pour vérifier si c'est un pseudo-littéral
bool ScalarConverter::isPseudoLiteral(const std::string &literal) {
    return literal == "nan" || literal == "nanf" || 
           literal == "+inf" || literal == "+inff" || 
           literal == "-inf" || literal == "-inff" ||
           literal == "inf" || literal == "inff";
}

// Méthode pour convertir en char
void ScalarConverter::convertToChar(double value, bool notPossible) {
    std::cout << "char: ";
    if (notPossible || std::isnan(value) || std::isinf(value)) {
        std::cout << "impossible" << std::endl;
    } else if (value < 0 || value > 127) {
        std::cout << "impossible" << std::endl;
    } else if (value < 32 || value > 126) {
        std::cout << "Non displayable" << std::endl;
    } else {
        char charValue = static_cast<char>(value);
        std::cout << "'" << charValue << "'" << std::endl;
    }
}

// Méthode pour convertir en int
void ScalarConverter::convertToInt(double value, bool notPossible) {
    std::cout << "int: ";
    if (notPossible || std::isnan(value) || std::isinf(value)) {
        std::cout << "impossible" << std::endl;
    } else if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min()) {
        std::cout << "impossible" << std::endl;
    } else {
        int intValue = static_cast<int>(value);
        std::cout << intValue << std::endl;
    }
}

// Méthode pour convertir en float - VERSION CORRIGÉE
void ScalarConverter::convertToFloat(double value, bool notPossible) {
    std::cout << "float: ";
    if (notPossible) {
        std::cout << "impossible" << std::endl;
        return;
    }
    
    float floatValue = static_cast<float>(value);
    
    if (std::isnan(floatValue)) {
        std::cout << "nanf" << std::endl;
    } else if (std::isinf(floatValue)) {
        if (floatValue > 0)
            std::cout << "inff" << std::endl;
        else
            std::cout << "-inff" << std::endl;
    } else {
        // Améliorer l'affichage pour préserver la précision quand c'est possible
        std::cout.precision(7); // Précision par défaut pour float
        
        // Vérifier si c'est un nombre entier
        if (floatValue == static_cast<int>(floatValue) && floatValue >= std::numeric_limits<int>::min() && floatValue <= std::numeric_limits<int>::max()) {
            std::cout << static_cast<int>(floatValue) << ".0f" << std::endl;
        } else {
            std::cout << floatValue << "f" << std::endl;
        }
    }
}

// Méthode pour convertir en double - VERSION CORRIGÉE
void ScalarConverter::convertToDouble(double value, bool notPossible) {
    std::cout << "double: ";
    if (notPossible) {
        std::cout << "impossible" << std::endl;
        return;
    }
    
    if (std::isnan(value)) {
        std::cout << "nan" << std::endl;
    } else if (std::isinf(value)) {
        if (value > 0)
            std::cout << "inf" << std::endl;
        else
            std::cout << "-inf" << std::endl;
    } else {
        // Améliorer l'affichage pour préserver la précision
        std::cout.precision(15); // Précision par défaut pour double
        
        // Vérifier si c'est un nombre entier
        if (value == static_cast<int>(value) && value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max()) {
            std::cout << static_cast<int>(value) << ".0" << std::endl;
        } else {
            std::cout << value << std::endl;
        }
    }
}

// Méthode principale de conversion
void ScalarConverter::convert(const std::string &literal) {
    Type type = detectType(literal);
    double value = 0.0;
    bool notPossible = false;

    // Conversion dans le type détécté puis en double car c'est le type le plus précis
    // avec static_cast car c'est la methode appropriée entre types scalaires (cast verifié à la compilation)
    switch (type) {
        case CHAR:
            value = static_cast<double>(literal[0]);
            break;
        case INT:
            {
                char *endPtr = NULL;
                errno = 0;
                long longValue = std::strtol(literal.c_str(), &endPtr, 10);
                if (*endPtr != '\0') {
                    notPossible = true;
                } else if (errno == ERANGE || longValue > std::numeric_limits<int>::max() ||  longValue < std::numeric_limits<int>::min()) {
                    // Le nombre est trop grand pour un int, mais on peut quand même
                    // essayer de le convertir en double pour les autres types
                    errno = 0;
                    value = std::strtod(literal.c_str(), &endPtr);
                    if (errno == ERANGE) {
                        notPossible = true;
                    }
                } else {
                    value = static_cast<double>(longValue);
                }
            }
            break;
        case FLOAT:
            {
                // CORRECTION : Pour les floats, on convertit d'abord en double directement
                // en enlevant le suffixe 'f' pour éviter la perte de précision
                std::string floatStr = literal;
                if (floatStr[floatStr.length() - 1] == 'f' || floatStr[floatStr.length() - 1] == 'F') {
                    floatStr = floatStr.substr(0, floatStr.length() - 1);
                }
                
                char *endPtr = NULL;
                errno = 0;
                value = std::strtod(floatStr.c_str(), &endPtr);
                if (*endPtr != '\0' || errno == ERANGE) {
                    notPossible = true;
                }
            }
            break;
        case DOUBLE:
        case PSEUDOLITERAL:
            {
                char *endPtr = NULL;
                errno = 0;
                value = std::strtod(literal.c_str(), &endPtr);
                if (*endPtr != '\0' || (errno == ERANGE && !std::isinf(value))) {
                    notPossible = true;
                }
            }
            break;
        case INVALID:
            notPossible = true;
            break;
    }

    // Conversions dans les différents types et affichage
    convertToChar(value, notPossible);
    convertToInt(value, notPossible);
    convertToFloat(value, notPossible);
    convertToDouble(value, notPossible);
}