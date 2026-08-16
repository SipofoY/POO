#include "AntSoldier.hpp"

AntSoldier::AntSoldier(Vec2d position1, Uid fourmil)
    :Ant(position1, fourmil,getAppConfig().ant_soldier_hp,getAppConfig().ant_soldier_lifespan )//que mettre comme arguments
{}
AntSoldier::AntSoldier(ToricPosition position1, Uid fourmil)
    :Ant(position1.toVec2d(), fourmil,getAppConfig().ant_soldier_hp,getAppConfig().ant_soldier_lifespan)
{}

void AntSoldier::drawOn(sf::RenderTarget& target) const{
    drawnAnt(target,getAppConfig().ant_soldier_texture);
}
void AntSoldier::update(sf::Time dt){
    updatAnt(dt);


}
