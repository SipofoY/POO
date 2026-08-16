#include "Environment.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include "Random/Random.hpp"
#include "Animal.hpp"
int Animal ::getSpeed() const{
    return getAppConfig().animal_default_speed;
}
Angle Animal :: getDirection() const{

    return direction;
}
void Animal :: setDirection(Angle angle){
    direction = angle;

}
bool Animal :: isDead(){

    if ((pointvie <= 0) or (esperancevie <= 0)){
        return true;
    } else {return false;}
}
/*void Animal::drawOn(sf::RenderTarget& target) const{
    auto const animal = buildSprite(getPosition().toVec2d(), 50.0, getAppTexture(getAppConfig().animal_default_texture), getDirection()/DEG_TO_RAD);
    target.draw(animal);
    if (isDebugOn()){
    Vec2d li;
    sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
    Vec2d depart = li.fromAngle(direction);
    ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
    ligne[1] = { getPosition().toVec2d() + depart * 100, sf::Color::Blue };
    target.draw(ligne);}

}
*/
RotationProbs Animal::computeRotationProbs(){
    std::pair <Intervals, Probs> produit({ -180, -100, -55, -25, -10, 0, 10, 25, 55, 100, 180},{0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000});

    RotationProbs nouv = produit;
    return nouv;
}

Animal::Animal(double pointvie1 , int esperancevie1, Vec2d position1){
    pointvie = pointvie1;
    setPosition(position1);
    esperancevie = esperancevie1;
    direction= uniform(0.0, TAU);
}
Animal :: Animal(double pointvie1, int esperancevie1){

    pointvie = pointvie1;
    esperancevie = esperancevie1;
}
Animal::Animal(double pointvie1, Vec2d position1){

    pointvie = pointvie1;
    setPosition(position1);
    esperancevie = getAppConfig().animal_default_lifespan;
    direction= 0;


}
void Animal:: move(sf::Time dt){
    Vec2d vecteur_vitesse;
    Vec2d dir;
    RotationProbs al = computeRotationProbs();
    Intervals thetas = computeRotationProbs().first;
    Probs probas = computeRotationProbs().second;
    std::piecewise_linear_distribution<> dist(thetas.begin(), thetas.end(), probas.begin());
    temps = temps + dt;
    vecteur_vitesse = getSpeed() * dir.fromAngle(direction);
    if (temps > sf::seconds(getAppConfig().animal_next_rotation_delay)){
            direction = direction + dist(getRandomGenerator()) * DEG_TO_RAD;
            temps = sf::Time::Zero;
            }
    vecteur_vitesse = getSpeed() * dir.fromAngle(direction);
    auto dx = vecteur_vitesse * dt.asSeconds();
    ToricPosition nouvpos(getPosition().x() + dx.x(), getPosition().y() + dx.y());
    setPosition(nouvpos);


}



/*void Animal::update(sf::Time dt){

    move(dt);
    if (isDead()){
        return;
    }
}
*/



