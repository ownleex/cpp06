/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:30:15 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/23 17:16:50 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

//constructeur privé
ScalarConverter::ScalarConverter() {}

//destructeur privé
ScalarConverter::~ScalarConverter() {}

//constructeur de copie
ScalarConverter::ScalarConverter(const ScalarConverter &src) {
    (void)src;
}

//opérateur d'affectation
ScalarConverter& ScalarConverter::operator=(const ScalarConverter &rhs) { 
    (void)rhs;
    return *this;
}

// Méthode pour détecter le type du littéral
ScalarConverter::Type ScalarConverter::detectType(const std::string& literal) {
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

    //Vérifie si c'est float
    bool isFloat = true;
    bool hasDecimal = false;
    bool hasF = false;

    // Gestion du signe négatif
    i = 0;
    if (literal[0] == '-' || literal[0] == '+')
        i++;

    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDecimal) { 
                isFloat = false;
                break;
            }
            hasDecimal = true;
        } else if (literal[i] == 'f' || literal[i] == 'F') {
            if (i != literal.length()-1 || hasF) {
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
    hasDecimal = false;

    i = 0;
    // Gestion du signe négatif
    if (literal[0] == '-' || literal[0] == '+')
        i++;

    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDecimal) {
                isDouble = false;
                break;
            }
            hasDecimal = true;
        } else if (!isdigit(literal[i])) {
            isDouble = false;
            break;
        }
    }
    
    if (isDouble && hasDecimal)
        return DOUBLE;
    return INVALID;
}

bool ScalarConverter::isPseudoLiteral(const std::string& s) {
    return s == "nan" || s == "nanf" || 
           s == "+inf" || s == "+inff" || 
           s == "-inf" || s == "-inff" || 
           s == "inf" || s == "inff";
}

void ScalarConverter::printAll(Type type, bool notPossible, char charValue, int intValue, float floatValue, double doubleValue) {
    // Affichage char
    std::cout << "char: ";
    if (notPossible || std::isnan(doubleValue) || std::isinf(doubleValue) || doubleValue < 0 || doubleValue > 127)
        std::cout << "impossible";
    else if (doubleValue < 32 || doubleValue > 126)
        std::cout << "Non displayable";
    else
        std::cout << "'" << charValue << "'";
    std::cout << std::endl;

    // Affichage int
    std::cout << "int: ";
    if (notPossible || std::isnan(doubleValue) || std::isinf(doubleValue) || doubleValue > INT_MAX || doubleValue < INT_MIN)
        std::cout << "impossible";
    else
        std::cout << intValue;
    std::cout << std::endl;

    // Affichage float
    std::cout << "float: ";
    if (type == PSEUDOLITERAL) {
        if (std::isnan(floatValue))
            std::cout << "nanf";
        else if (std::isinf(floatValue))
            std::cout << (floatValue > 0 ? "inff" : "-inff");
    } else if (notPossible)
        std::cout << "impossible";
    else {
        std::cout.precision(7);
        if (floatValue == static_cast<int>(floatValue))
            std::cout << static_cast<int>(floatValue) << ".0f";
        else
            std::cout << floatValue << "f";
    }
    std::cout << std::endl;

    // Affichage double
    std::cout << "double: ";
    if (type == PSEUDOLITERAL) {
        if (std::isnan(doubleValue))
            std::cout << "nan";
        else if (std::isinf(doubleValue))
            std::cout << (doubleValue > 0 ? "inf" : "-inf");
    } else if (notPossible)
        std::cout << "impossible";
    else {
        std::cout.precision(7);
        if (doubleValue == static_cast<int>(doubleValue))
            std::cout << static_cast<int>(doubleValue) << ".0";
        else
            std::cout << doubleValue;
    }
    std::cout << std::endl;
}

// Methode principale pour la conversion dans le type détécté
// avec static_cast car c'est la methode appropriée entre types scalaires (cast verifié à la compilation)
void ScalarConverter::convert(const std::string& literal) {
    Type type = detectType(literal);
    bool notPossible = false;
    char charValue = 0;
    int intValue = 0;
    float floatValue = 0.0f;
    double doubleValue = 0.0;

    switch (type) {
        case CHAR:
            charValue = literal[0];
            intValue = static_cast<int>(charValue);
            floatValue = static_cast<float>(charValue);
            doubleValue = static_cast<double>(charValue);
            break;
        case INT: {
            char *endPtr = NULL;
            errno = 0;
            long longValue = std::strtol(literal.c_str(), &endPtr, 10);

            if (*endPtr != '\0') {
                notPossible = true; // input non convertible du tout
            } else if (errno == ERANGE || longValue > INT_MAX || longValue < INT_MIN) {
                // Trop grand pour un int, mais essayons en double
                char *endPtr = NULL;
                errno = 0;
                double temp = std::strtod(literal.c_str(), &endPtr);
                if (*endPtr != '\0' || errno == ERANGE) {
                    notPossible = true; // même double impossible
                } else {
                    doubleValue = temp;
                    floatValue = static_cast<float>(doubleValue);
                    // char et int: impossible
                    notPossible = false;
                    // Affichage géré plus bas : impossible pour char/int, mais valeurs pour float/double
                }
            } else {
                intValue = static_cast<int>(longValue);
                charValue = static_cast<char>(intValue);
                floatValue = static_cast<float>(intValue);
                doubleValue = static_cast<double>(intValue);
            }
            break;
        }

        case FLOAT: {
            std::string fstr = literal;
            if (fstr[fstr.length()-1] == 'f' || fstr[fstr.length()-1] == 'F')
                fstr = fstr.substr(0, fstr.length()-1);
            char *endPtr = NULL;
            errno = 0;
            float temp = std::strtof(fstr.c_str(), &endPtr);
            if (*endPtr != '\0' || errno == ERANGE)
                notPossible = true;
            else {
                floatValue = temp;
                charValue = static_cast<char>(floatValue);
                intValue = static_cast<int>(floatValue);
                doubleValue = static_cast<double>(floatValue);
            }
            break;
        }
        case DOUBLE: {
            char *endPtr = NULL;
            errno = 0;
            double temp = std::strtod(literal.c_str(), &endPtr);
            if (*endPtr != '\0' || errno == ERANGE)
                notPossible = true;
            else {
                doubleValue = temp;
                charValue = static_cast<char>(doubleValue);
                intValue = static_cast<int>(doubleValue);
                floatValue = static_cast<float>(doubleValue);
            }
            break;
        }
        case PSEUDOLITERAL: {
            if (literal == "nan" || literal == "nanf") {
                doubleValue = std::numeric_limits<double>::quiet_NaN();
                floatValue = std::numeric_limits<float>::quiet_NaN();
            } else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff") {
                doubleValue = std::numeric_limits<double>::infinity();
                floatValue = std::numeric_limits<float>::infinity();
            } else if (literal == "-inf" || literal == "-inff") {
                doubleValue = -std::numeric_limits<double>::infinity();
                floatValue = -std::numeric_limits<float>::infinity();
            }
            notPossible = true; // pour char et int
            break;
        }
        default:
            notPossible = true;
    }

    printAll(type, notPossible, charValue, intValue, floatValue, doubleValue);    
}
