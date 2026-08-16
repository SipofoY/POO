#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#include<SFML/System.hpp>
#pragma once
#include"Interface/Updatable.hpp"

class FoodGenerator: public Updatable
{
public:
    /*! @brief méthode qui fait évoluer la nourriture(donc elle crée a des position aléatoire et avec des quantités aléatoire aussi) à chaque dt
     *  @param un sf::Time, qui indique le découlement du temps
*/
    void update(sf::Time dt);

    /*! @brief constructeur, qui initialise le compteur
*/
    FoodGenerator();


private:
    sf::Time compteur;
};

#endif // FOODGENERATOR_HPP
