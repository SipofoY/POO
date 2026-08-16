#include "Termite.hpp"
#include "Application.hpp"


Termite::Termite(ToricPosition pos)
    :Animal(pos, getAppConfig().termite_hp, getAppConfig().termite_lifespan)
{}

void Termite:: move(sf::Time dt){

    Vec2d dir;
    RotationProbs al = computeRotationProbs();
    Intervals thetas = computeRotationProbs().first;
    Probs probas = computeRotationProbs().second;
    std::piecewise_linear_distribution<> dist(thetas.begin(), thetas.end(), probas.begin());
    temps = temps + dt;
    Vec2d vecteur_vitesse = getAppConfig().termite_speed * dir.fromAngle(direction);
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
        auto const text = buildText(to_nice_string(pointvie), getPosition().toVec2d()+Vec2d(0,10), getAppFont(), 15, sf::Color::Red, 0);
        target.draw(text);
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

    Animal* proche=getAppEnv().getClosestEnemy(this);
    double point=proche->getPointVie();

    if (proche == nullptr) std::cout<<"is no enemy"<<std::endl;
    else std::cout<<"is enemy"<<std::endl;
    //std::cout<<proche->getPosition()<<std::endl;
    if (Idle){
        Animal::move(dt);
        if(proche!=nullptr){
            Attack=true;
        }
    }

    if (Attack){

        while(compteur<=getAppConfig().termite_attack_delay){
                compteur = compteur + dt.asSeconds();
                point-=getAppConfig().termite_strength;
                setpointdevie(point);

        }

        if (compteur >= getAppConfig().termite_attack_delay){
            Attack = false;
            compteur=0;

        }

    }

}






