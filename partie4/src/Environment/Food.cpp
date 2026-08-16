#include "Food.hpp"
#include<iostream>
#include"Utility/Utility.hpp"
#include "Application.hpp"


Food::Food(ToricPosition pos, Quantity quant){
    setPosition(pos);
    quantite=quant;
}

Quantity Food:: takeQuantity(Quantity quantite_donnee){
    if (quantite_donnee<= quantite){
        quantite=quantite-quantite_donnee;
        return quantite;
    }
    else if (quantite_donnee > quantite) {
        std::cout <<"Erreur: on ne peut pas prelever plus de nourriture que celle qu'on a."<<std::endl;
        return 1;
    }
}

void Food:: drawOn(sf::RenderTarget& target) const{
    auto const foodSprite = buildSprite(getPosition().toVec2d(), quantite/2, getAppTexture(getAppConfig().food_texture));
    target.draw(foodSprite);

    if(isDebugOn()){
        auto const text = buildText(to_nice_string(quantite), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black, 0);
        target.draw(text);
    }
}
double Food:: getQuantity(){
    return quantite;
}










