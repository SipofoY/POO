#ifndef FOOD_HPP
#define FOOD_HPP
#include"Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/System.hpp>
#include<SFML/Graphics.hpp>

class Food: public Positionable
{
public:
    /*! @brief Constructeur prennant un Toricposition et un Quantity et un deuxième constructeur avec la texture et un bool pour savoir si il y a du poison
     *  @param un Toricposition qui represente la position et quantity qui represente la quantité
*/
    Food(ToricPosition pos, Quantity quant);
    Food (ToricPosition pos, Quantity quant, std::string texture1, bool poison1);

    /*! @return la quantité restante après le prelevement de quantité
     *  @param un Quantity qui represente la quantité à prelevé
*/
    Quantity takeQuantity(Quantity quantite_donnee);


    /*!  @brief méthode de dessin général, valable pour toutes les nourritures
     *   @param un sf:: Time, qui indique le découlement du temps
*/
    void drawOn(sf::RenderTarget& target) const;

    /*! @return la quantité de nourriture totale
*/
    static  Quantity getTotalFood();

    /*! @return la quantité de nourriture
*/
    Quantity getQuantity() const;

    /*!@return un bool pour savoir si il y a du poison
*/
    bool getPoison() const;

    /*! @brief destructeur de nourriture
*/
    ~Food();


private:
    Quantity quantite;
    static Quantity foodTotal;
    std:: string texture;
    bool poison;

};


#endif // FOOD_HPP
