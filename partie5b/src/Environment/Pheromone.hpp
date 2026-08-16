#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP
#include "Positionable.hpp"
#include"Application.hpp"


class Pheromone: public Positionable
{
public:
    /*! @brief constructeur prenant en compte un ToricPosition et un double
     *  @param le Toricposition represente la position et le double la quantité de pheromone
*/
    Pheromone(ToricPosition pos, double Q);

    /*! @return un bool pour savoir si la quantité de pheromone est considérée comme négligeable
*/
    bool isNegligible();


    /*! @brief méthode qui fait évoluer les pheromonnes(donc elle décrémente la quantité) à chaque dt
     *  @param un sf::Time, qui indique le découlement du temps
*/
    void update(sf::Time dt);

    /*!  @brief méthode de dessin général, valable pour tous les pheromones
     *   @param un sf:: Time, qui indique le découlement du temps
*/
    void drawOn(sf::RenderTarget& target) const;

    /*! @return la quantité de pheromone
*/
    double getQuantite() const;

    /*! @brief destructeur de pheromones
*/
    ~Pheromone(){}

private:
    double quantite;
    sf::Color color=sf::Color::Green;
};

#endif // PHEROMONE_HPP
