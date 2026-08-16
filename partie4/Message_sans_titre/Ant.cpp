#include "Ant.hpp"
#include "Pheromone.hpp"
#include <vector>
#include <cmath>

Ant::Ant(Vec2d position1, Uid fourmil)
    :Animal(getAppConfig().animal_default_lifespan, position1),

     fourmilliere(fourmil)
{}

Ant::Ant(Vec2d position1, Uid fourmil, double pointvie1, int esperancevie1)
    :Animal(pointvie1, esperancevie1, position1), fourmilliere(fourmil)
{}

Ant::Ant(ToricPosition pos, Uid fourmil)
    :Animal(pos), fourmilliere(fourmil)
{}

int Ant::getSpeed() const
{
    return getAppConfig().ant_speed;
}
void Ant::drawnAnt(sf::RenderTarget& target,const std::string texture ) const
{
    auto const ant = buildSprite(getPosition().toVec2d(), 50.0, getAppTexture(texture), getDirection()/DEG_TO_RAD);
    target.draw(ant);
    if (isDebugOn()) {
        Vec2d li;
        sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
        Vec2d depart = li.fromAngle(getDirection());
        ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
        ligne[1] = { getPosition().toVec2d() + depart * 100, sf::Color::Blue };
        target.draw(ligne);
    }
}
/*void Ant :: drawOn(sf::RenderTarget& target) const
{
    drawnAnt(target, getAppConfig().animal_default_texture);
    if (getAppConfig().getProbaDebug()){
        affichage_probabilite(target);

        ToricPosition pos=this->getPosition();
        Vec2d pos_enVec2d=pos.toVec2d();
        buildAnnulus(pos_enVec2d, getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5.5);
    }

}*/
void Ant:: spreadPheromones()
{
    double distance=toricDistance(lastSpreadPher,this->getPosition());
    double instances=distance*getAppConfig().ant_pheromone_density;

    Vec2d pheromoneToAnt = lastSpreadPher.toricVector(this->getPosition());

    for (int i(0); i<instances; ++i){
        lastSpreadPher+=pheromoneToAnt*(1.0/getAppConfig().ant_pheromone_density);
        getAppEnv().addPheromone(new Pheromone(lastSpreadPher,getAppConfig().ant_pheromone_energy));
    }
}

void Ant::move(sf::Time dt){
    Animal::move(dt);
    spreadPheromones();
}


void Ant::affichage_probabilite(sf::RenderTarget target) {
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

void Ant::updateAnt(sf::Time dt){
    move(dt);
    if (isDead()) {
        return;
    }
}

RotationProbs Ant:: computeRotationProbs(){
   std::pair<Intervals, Probs> produit({ 0.0000, 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000 },
                                        {   -180,   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 });

    Intervals ensemble_angles({   -180,   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 });
    Intervals Pm({ 0.0000, 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000 });

    Quantities Q=getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(this->getPosition(), this->getDirection(), ensemble_angles);

    Intervals P_phi;

    for(int i(0); i<ensemble_angles.size(); ++i){
        P_phi[i]=1/(1+exp(-getAppConfig().beta_d*(Q[i]-getAppConfig().q_zero)));
    }
    double somme(0);

    for(auto element: P_phi){
        somme+=element;
    }

    for(auto elem: P_phi){ //normaliser P_phi
        elem/somme;
    }



}

bool Ant::isEnemy(Animal const* animal) const {
     return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Ant::isEnemyDispatch(Termite const*) const{
    return true;
}

bool Ant::isEnemyDispatch(Ant const*) const{
    return false;
}









