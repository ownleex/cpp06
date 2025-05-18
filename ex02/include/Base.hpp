/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 22:58:28 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/18 22:58:29 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

class Base {
public:
    // Destructeur virtuel public comme demandé dans le sujet
    virtual ~Base();
};

// Classes dérivées
class A : public Base {};
class B : public Base {};
class C : public Base {};

// Fonctions à implémenter
Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif