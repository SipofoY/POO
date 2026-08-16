#include "Anthill.hpp"
#include "Random/Random.hpp"
#include "AntSoldier.hpp"
#include "AntWorker.hpp"


Anthill::Anthill(ToricPosition position)
{
    setPosition(position);
    identifiant = createUid();
    stock = {};
}

Anthill :: Anthill (Vec2d position, Uid id){
    ToricPosition pos(position);
    setPosition(pos);
    identifiant = id;
    stock = {};
}
void Anthill :: drawOn(sf::RenderTarget& target) const
{
    auto const anthill = buildSprite(getPosition().toVec2d(), 50.0, getAppTexture(getAppConfig().anthill_texture));
    target.draw(anthill);
    if (isDebugOn()) {
        auto const text = buildText(to_nice_string(stock), getPosition().toVec2d()+Vec2d(0,20.0), getAppFont(), 15, sf::Color::Black, 0);
        target.draw(text);
        auto const id=buildText(to_nice_string(identifiant), getPosition().toVec2d()+Vec2d(0, 35.0), getAppFont(), 15, sf::Color::Magenta, 0 );
        target.draw(id);
    }
}
Prob Anthill:: probworker()
{
    return getAppConfig().anthill_worker_prob_default;
}

void Anthill::update(sf::Time dt)
{
   sf::Time max= sf::seconds(getAppConfig().anthill_spawn_delay);
   temps=temps+dt;

    if (temps>max) {
        double pro = uniform(0,1);
        if ((pro >= 0) and (pro <= probworker())) {
            getAppEnv().addAnimal(new AntWorker(getPosition().toVec2d(), get_id()));
           temps=sf::Time::Zero;

        } else {
            getAppEnv().addAnimal(new AntSoldier(getPosition().toVec2d(), get_id()));
            temps=sf::Time::Zero;
        }
    }
}

Uid Anthill:: get_id() const{
    return identifiant;
}

void Anthill:: setstock(double food){
    stock = stock + food;

}

double Anthill:: getStock() {
    return stock;
}


