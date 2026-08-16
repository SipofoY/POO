#include "Termite.hpp"
#include "Application.hpp"


Termite::Termite(ToricPosition pos)
    :Animal(pos, getAppConfig().termite_hp, getAppConfig().termite_lifespan)
{}

void Termite:: move(sf::Time dt){
    Vec2d vecteur_vitesse;
    Vec2d dir;
    RotationProbs al = computeRotationProbs();
    Intervals thetas = computeRotationProbs().first;
    Probs probas = computeRotationProbs().second;
    std::piecewise_linear_distribution<> dist(thetas.begin(), thetas.end(), probas.begin());
    temps = temps + dt;
    vecteur_vitesse = getSpeed() * dir.fromAngle(direction);
    if (temps > sf::seconds(getAppConfig().animal_next_rotation_delay)) {
        direction = direction + dist(getRandomGenerator()) * DEG_TO_RAD;
        temps = sf::Time::Zero;
    }
    vecteur_vitesse = getAppConfig().termite_speed * dir.fromAngle(direction);
    auto dx = vecteur_vitesse * dt.asSeconds();
    ToricPosition nouvpos(getPosition().x() + dx.x(), getPosition().y() + dx.y());
    setPosition(nouvpos);

}

void Termite:: drawOn(sf::RenderTarget &target) const {
    auto const termite = buildSprite(getPosition().toVec2d(), 50.0, getAppTexture(getAppConfig().termite_texture), getDirection()/DEG_TO_RAD);
        target.draw(termite);
        if (isDebugOn()) {
            Vec2d li;
            sf::VertexArray ligne(sf::PrimitiveType::Lines, 2);
            Vec2d depart = li.fromAngle(direction);
            ligne[0] = { getPosition().toVec2d(), sf::Color::Black };
            ligne[1] = { getPosition().toVec2d() + depart * 100, sf::Color::Blue };
            target.draw(ligne);
        }
}

bool Termite::isEnemy(Animal const* animal) const {
     return !isDead() && !animal->isDead() && animal->isEnemyDispatch(this);
}

bool Termite::isEnemyDispatch(Termite const*) const {
    return false;
}

bool Termite::isEnemyDispatch(Ant const*) const {
    return true;
}
void Termite :: update(sf::Time dt){
    move(dt);
    compteur = 0;

    if (Attack == false and Idle == true){
    if ((toricDistance(getAppEnv().getClosestAnimal(getPosition())->getPosition(),getPosition()) <= getAppConfig().animal_sight_distance) and (isEnemy(getAppEnv().getClosestAnimal(getPosition())) == true)){
      Attack = true;
      Idle = false;
    }}
    do {
        if (compteur ==getAppConfig().termite_attack_delay and Attack ){
                Attack = false;
                Idle = true;
                compteur = 0;
            }
            compteur = compteur + 1;
            getAppEnv().getClosestAnimal(getPosition())-> setpointdevie(getAppConfig().termite_strength);
            move(sf::Time::Zero);

        }while(compteur<=getAppConfig().termite_attack_delay);
      //  std::cout<<"yann"<<std::endl;

      //  }
    }










