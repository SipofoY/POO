#include "Anthill.hpp"
#include"Application.hpp"
#include "Random/Random.hpp"
#include "AntWorker.hpp"
#include "AntSoldier.hpp"
Anthill::Anthill(ToricPosition position)
{
    setPosition(position);
    identifiant = createUid();
    stock = {};
}
void Anthill :: drawOn(sf::RenderTarget& target) const{

    auto const anthill = buildSprite(getPosition().toVec2d(), 50.0, getAppTexture(getAppConfig().anthill_texture));
    target.draw(anthill);
    if (isDebugOn()){
        auto const text = buildText(to_nice_string(stock), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Magenta, 0);
        target.draw(text);
    }
}
Uid Anthill :: get_id(){

    return identifiant;
}
void Anthill:: setstock(double food){
    stock = stock + food;

}

Prob Anthill:: probworker(){

    return getAppConfig().anthill_worker_prob_default;
}
void Anthill::update(sf::Time dt){
    sf::Time max =  sf::seconds(getAppConfig().anthill_spawn_delay);
    temps = temps + dt;
    if (temps > max ){

            getAppEnv().addAnimal(new AntWorker(getPosition().toVec2d(), createUid()));
            temps = sf::Time::Zero;

/*            getAppEnv().addAnimal(new AntSoldier(getPosition().toVec2d(), createUid()));
            temps = sf::Time::Zero;
        */

    }


}




