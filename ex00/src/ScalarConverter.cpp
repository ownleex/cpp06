/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:30:15 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/28 01:36:52 by ayarmaya         ###   ########.fr       */
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


    // Vérifie si c'est un char
    if (literal.length() == 1 && !std::isdigit(literal[0]))
        return CHAR;


    // Vérifie si c'est un int
    bool isInteger = true;
    size_t i = 0;

        // Gestion du signe 
    if (literal[0] == '-' || literal[0] == '+')
        i++;

    for (; i < literal.length(); i++) {
        if (!std::isdigit(literal[i])) { 
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
    i = 0;

        // Gestion du signe 
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
        } else if (!std::isdigit(literal[i])) {
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

        // Gestion du signe 
    if (literal[0] == '-' || literal[0] == '+')
        i++;

    for (; i < literal.length(); i++) {
        if (literal[i] == '.') {
            if (hasDecimal) {
                isDouble = false;
                break;
            }
            hasDecimal = true;
        } else if (!std::isdigit(literal[i])) {
            isDouble = false;
            break;
        }
    }
    
    if (isDouble && hasDecimal)
        return DOUBLE;
    return INVALID;
}

bool ScalarConverter::isPseudoLiteral(const std::string& literal) {
    return literal == "nan" || literal == "nanf" || 
           literal == "+inf" || literal == "+inff" || 
           literal == "-inf" || literal == "-inff" || 
           literal == "inf" || literal == "inff";
}

// Méthode pour afficher tous les types de conversion avec gestion des cas impossibles
void ScalarConverter::printAll(Type type, bool notPossible, char charValue, int intValue, float floatValue, double doubleValue) {
    // Affichage de la conversion en char
    std::cout << "char: ";

        // Vérification si la conversion est impossible ou si la valeur est hors de la plage ASCII valide (0-127)
    if (notPossible || doubleValue < 0 || doubleValue > 127)
        std::cout << "impossible";

        // Vérification si le caractère n'est pas affichable (codes ASCII < 32 ou > 126)
    else if (doubleValue < 32 || doubleValue > 126)
        std::cout << "Non displayable";
        
        // Affichage du caractère entre guillemets simples
    else
        std::cout << "'" << charValue << "'";
    std::cout << std::endl;


    // Affichage de la conversion en int
    std::cout << "int: ";

        // Vérification si la conversion est impossible ou si la valeur dépasse les limites d'un int (INT_MAX/INT_MIN)
    if (notPossible || doubleValue > INT_MAX || doubleValue < INT_MIN)
        std::cout << "impossible";

        // Affichage de la valeur entière
    else
        std::cout << intValue;
    std::cout << std::endl;


    // Affichage de la conversion en float
    std::cout << "float: ";
        // Cas spécial pour les pseudo-littéraux (nan, inf, -inf)
    if (type == PSEUDOLITERAL) {
        // Vérification si c'est NaN (Not a Number)
        if (std::isnan(floatValue))
            std::cout << "nanf";
            
        // Vérification si c'est l'infini (positif ou négatif)
        else if (std::isinf(floatValue))
            std::cout << (floatValue > 0 ? "inff" : "-inff");
    } 

        // Si la conversion est impossible pour d'autres raisons
    else if (notPossible)
        std::cout << "impossible";

        // Affichage de la valeur
    else {
        // Configuration de la précision d'affichage
        std::cout.precision(7);

        // Si le float est un nombre entier, affichage avec .0f
        if (floatValue == static_cast<int>(floatValue))
            std::cout << floatValue << ".0f";

        // Sinon affichage normal avec le suffixe f
        else
            std::cout << floatValue << "f";
    }
    std::cout << std::endl;


    // Affichage de la conversion en double
    std::cout << "double: ";

        // Cas spécial pour les pseudo-littéraux (nan, inf, -inf)
    if (type == PSEUDOLITERAL) {
        // Vérification si c'est NaN (Not a Number)
        if (std::isnan(doubleValue))
            std::cout << "nan";

        // Vérification si c'est l'infini (positif ou négatif)
        else if (std::isinf(doubleValue))
            std::cout << (doubleValue > 0 ? "inf" : "-inf");
    } 

        // Si la conversion est impossible pour d'autres raisons
    else if (notPossible)
        std::cout << "impossible";

        // Affichage de la valeur
    else {
        // Configuration de la précision d'affichage
        std::cout.precision(7);

        // Si le double est un nombre entier, affichage avec .0
        if (doubleValue == static_cast<int>(doubleValue))
            std::cout << doubleValue << ".0";
            
        // Sinon affichage normal
        else
            std::cout << doubleValue;
    }
    std::cout << std::endl;
}

// Méthode principale pour la conversion dans le type détecté
// Utilise static_cast car c'est la méthode appropriée entre types scalaires
// vérifié à la compilation
void ScalarConverter::convert(const std::string& literal) {
    // Détection du type du littéral d'entrée
    Type type = detectType(literal);
    
    bool notPossible = false;
    char charValue = 0;
    int intValue = 0;
    float floatValue = 0.0f; 
    double doubleValue = 0.0;

    // Traitement selon le type détecté
    switch (type) {
        case CHAR:
            // Pour un caractère, récupération directe du premier caractère
            charValue = literal[0];

            // Conversion vers les autres types avec static_cast
            intValue = static_cast<int>(charValue);
            floatValue = static_cast<float>(charValue);
            doubleValue = static_cast<double>(charValue);
            break;
            
        case INT: {
            // Conversion d'une chaîne vers long pour vérifier les débordements
            long longValue = std::strtol(literal.c_str(), NULL, 10);
            
            // Vérification des débordements ou valeurs hors limites d'un int
            if (errno == ERANGE || longValue > INT_MAX || longValue < INT_MIN) {
                // Si trop grand pour un int, on essaie en float d'abord
                errno = 0;
                floatValue = std::strtof(literal.c_str(), NULL);
                
                if (errno == ERANGE) {
                    // Si le float déborde, on essaie en double
                    errno = 0;
                    doubleValue = std::strtod(literal.c_str(), NULL);
                    
                    if (errno == ERANGE)
                        // Si même le double déborde, tout est impossible
                        notPossible = true;
                } 
                else {
                    // Le float fonctionne, on convertit aussi en double
                    doubleValue = static_cast<double>(floatValue);
                }
            } 
            else {
                // Conversion réussie, stockage avec static_cast vers les autres types
                intValue = static_cast<int>(longValue);
                charValue = static_cast<char>(intValue);
                floatValue = static_cast<float>(intValue);
                doubleValue = static_cast<double>(intValue);
            }
            break;
        }

        case FLOAT: {
            // Suppression du suffixe 'f' ou 'F' pour la conversion
            std::string fstr = literal.substr(0, literal.length()-1);
                
            // Conversion sécurisée vers float
            errno = 0;
            floatValue = std::strtof(fstr.c_str(), NULL);
            
            // Vérification des erreurs de conversion pour float
            if (errno == ERANGE) {
                // Si le float est en overflow, essayer en double
                errno = 0;
                doubleValue = std::strtod(fstr.c_str(), NULL);
                
                // Si le double est aussi en overflow, alors tout est impossible
                if (errno == ERANGE) 
                    notPossible = true;
            }
            else {
                // Conversion réussie, stockage avec static_cast vers les autres types
                charValue = static_cast<char>(floatValue);
                intValue = static_cast<int>(floatValue);
                doubleValue = static_cast<double>(floatValue);
            }
            break;
        }
        
        case DOUBLE: {
            // Conversion sécurisée vers double
            errno = 0;
            doubleValue = std::strtod(literal.c_str(), NULL);
            
            // Vérification des erreurs de conversion
            if (errno == ERANGE)
                notPossible = true;
            else {
                // Conversion réussie, stockage avec static_cast vers les autres types
                charValue = static_cast<char>(doubleValue);
                intValue = static_cast<int>(doubleValue);
                floatValue = static_cast<float>(doubleValue);
            }
            break;
        }
        
        case PSEUDOLITERAL: {
            // Traitement des pseudo-littéraux spéciaux
            if (literal == "nan" || literal == "nanf") {
                // NaN (Not a Number) pour double et float
                doubleValue = std::numeric_limits<double>::quiet_NaN();
                floatValue = std::numeric_limits<float>::quiet_NaN();
            } 
            else if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff") {
                // Infini positif pour double et float
                doubleValue = std::numeric_limits<double>::infinity();
                floatValue = std::numeric_limits<float>::infinity();
            } 
            else if (literal == "-inf" || literal == "-inff") {
                // Infini négatif pour double et float
                doubleValue = -std::numeric_limits<double>::infinity();
                floatValue = -std::numeric_limits<float>::infinity();
            }
            // Les conversions vers char et int sont impossibles pour les pseudo-littéraux
            notPossible = true;
            break;
        }
        
        default:
            // Type invalide, toutes les conversions sont impossibles
            notPossible = true;
    }

    // Affichage de tous les résultats de conversion
    printAll(type, notPossible, charValue, intValue, floatValue, doubleValue);    
}