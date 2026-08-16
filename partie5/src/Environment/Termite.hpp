#ifndef TERMITE_HPP
#define TERMITE_HPP
#include "Animal.hpp"
#include "Ant.hpp"



class Termite: public Animal
{
public:
    /*! @brief Constructeur de termite prennant un Toricposition en argument
     *  @param le Toricposition represente la position
*/
    Termite(ToricPosition pos);

    /*! @return la vitesse de la termite
*/
    int getSpeed() const override;

    /*!  @brief méthode de dessin général, valable pour toutes les termites
     *   @param un sf:: Time, qui indique le découlement du temps
*/

    void drawOn(sf::RenderTarget& target) const override;

    /*! @brief méthode qui fait évoluer (et donc se déplacer) la termite à chaque dt
     *  @param un sf::Time, qui indique le découlement du temps
*/
    void update(sf::Time dt) override;

    /*! @return un bool pour savoir si c'est un ennemi
     *  @param un pointeur sur Animal qui sera potentiellement un ennemi
*/
    bool isEnemy(Animal const* animal) const override;

    /*! @return un bool sera utilise à la méthode isEnemy pour savoir si c'est un ennemi
     *  @param un pointeur sur une Termite qui ne sera pas un ennemi
*/
    bool isEnemyDispatch(Termite const*) const override;

    /*! @return un bool sera utilise à la méthode isEnemy pour savoir si c'est un ennemi
     *  @param un pointeur sur une fourmi qui sera un ennemi
*/
    bool isEnemyDispatch(Ant const*) const override;

    /*! @return la texture de la termite
*/
    std::string getTexture() const override;
    ~Termite();

private:
    sf::Time compteur;
};

#endif // TERMITE_HPP
