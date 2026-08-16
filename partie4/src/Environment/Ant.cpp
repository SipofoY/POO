#include "Ant.hpp"
#include "Pheromone.hpp"
#include <vector>
#include <cmath>


Ant :: Ant(Vec2d position1, Uid fourmil, double pointvie, int esperancevie)
    :Animal(pointvie,esperancevie, position1),
    fourmilliere(fourmil)
{}
Ant::Ant(Vec2d position1, Uid fourmil)
    :Animal(getAppConfig().animal_default_lifespan, position1),
      fourmilliere(fourmil)
{}



int Ant::getSpeed() const{
    return getAppConfig().ant_speed;
}
void Ant::drawnAnt(sf::RenderTarget& target,const std::string texture ) const
{
    auto const ant = buildSprite(getPosition().toVec2d(), 50.0, getAppTexture(texture), getDirection()/DEG_TO_RAD);
    target.draw(ant);
    ToricPosition postext(getPosition().x(), getPosition().y() + 3);

    if (isDebugOn()) {
        Vec2d li;
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
        Vec2d depart = li.fromAngle(getDirection());
        ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
        ligne[1] = { getPosition().toVec2d() + depart * 100, sf::Color::Blue };
        target.draw(ligne);
        auto const circle =buildAnnulus(this->getPosition().toVec2d(), 15.0, sf::Color::Blue, 4.0);
        target.draw(circle);
        auto const text = buildText(to_nice_string(pointvie), postext.toVec2d(), getAppFont(), 15, sf::Color::Red, 0);
        target.draw(text);
    }

    if(getAppConfig().getProbaDebug()) {
       affichage_probabilite(target);
    }
}
void Ant:: spreadPheromones()
{
    double distance=toricDistance(lastSpreadPher,this->getPosition());
    double instances=distance*getAppConfig().ant_pheromone_density;

    Vec2d pheromoneToAnt = lastSpreadPher.toricVector(this->getPosition()).normalised();

    for (int i(0); i<instances; ++i){
        lastSpreadPher+=pheromoneToAnt*(1.0/getAppConfig().ant_pheromone_density);
        getAppEnv().addPheromone(new Pheromone(lastSpreadPher,getAppConfig().ant_pheromone_energy));
    }
}

void Ant::affichage_probabilite(sf::RenderTarget& target)const {
    Intervals intervals({-180, -100, -55, -25, -10,  0, 10, 25,  55, 100, 180 });
    auto const intervalProbs = computeRotationProbs();
    // pour intervalProbs (first désigne l'ensemble des angles)

    for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
        // "second" designe l'ensemble des probabilités
        auto const msg = std::to_string(intervalProbs.second[i]).substr(2, 4);
        auto const angle = intervalProbs.first[i];
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 250;

        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }

    auto const quantities = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), intervals);

    for (std::size_t i = 0; i < quantities.size(); ++i) {
        auto const msg = std::to_string(quantities[i]).substr(0, 4);
        auto const angle = intervals[i];
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 200;

        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Red);
        target.draw(text);
    }

}


void Ant::move(sf::Time dt){
    Animal::move(dt);
    spreadPheromones();
}
void Ant:: updatAnt(sf::Time dt){
    move(dt);

    if (isDead()){
        return;
    }

}
Uid Ant :: get_id() const{

    return fourmilliere;
}
RotationProbs Ant:: computeRotationProbs() const{

    Intervals ensemble_angles({   -180,   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 });
    Intervals Pm({ 0.0000, 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000 });

    Quantities Q=getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(this->getPosition(), this->getDirection(), ensemble_angles);

    Intervals P_phi(ensemble_angles.size(), 0.0);

    for(unsigned int i(0); i<ensemble_angles.size(); ++i){
        P_phi[i]=(1.0/(1.0+exp(-getAppConfig().beta_d*(Q[i]-getAppConfig().q_zero))));
    }

    /*double somme(0);

    for(auto& element: P_phi){
        somme+=element;
    }

    for(auto& elem: P_phi){ //normaliser P_phi
        elem/=somme;
    }*/

    for(auto& elem:P_phi){ //trouver P_phi^alpha
        for(int i(0); i< getAppConfig().alpha; ++i){
            elem=elem*elem;
        }
    }

    double somme2(0);
    for(unsigned int i(0); i<Pm.size(); ++i){
        somme2+=P_phi[i]*Pm[i];
    }

    Intervals Pm_prime(Pm.size(), 0.0);
    for(unsigned int i(0); i<Pm.size(); ++i){
        Pm_prime[i]=((1/somme2)*Pm[i]*P_phi[i]);
    }

    RotationProbs ret(ensemble_angles, Pm_prime);
    return ret;
}


bool Ant::isEnemy(Animal const* animal) const {
     return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Ant::isEnemyDispatch(Termite const*) const{
    return true;
}

bool Ant::isEnemyDispatch(Ant const*ant) const{
    if ((this->get_id()!= ant->get_id()) or (ant->get_id()!= this-> get_id())){
        return true;
}else{
        return false;
    }}
Ant::Ant(ToricPosition pos, Uid fourmil)
    :Animal(pos), fourmilliere(fourmil)
{}





