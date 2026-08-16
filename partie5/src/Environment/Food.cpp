#include "Food.hpp"
#include<iostream>
#include"Utility/Utility.hpp"
#include "Application.hpp"

Quantity Food::foodTotal(0.0);

Food::Food(ToricPosition pos, Quantity quant)
{
    setPosition(pos);
    quantite=quant;
    foodTotal+=quant;
}
Food::Food(ToricPosition pos, Quantity quant, std::string texture1, bool poison1)
{
    setPosition(pos);
    quantite=quant;
    foodTotal+=quant;
    texture = texture1;
    poison = poison1;
}

Quantity Food:: takeQuantity(Quantity quantite_donnee)
{
    if (quantite_donnee<= quantite) {       
         quantite-=quantite_donnee;
         foodTotal-=quantite_donnee;
         return quantite_donnee;

    } else {
        Quantity a=quantite;
        foodTotal-=quantite;
        quantite=0;
        return a;
    }
}

void Food:: drawOn(sf::RenderTarget& target) const
{
    auto const foodSprite = buildSprite(getPosition().toVec2d(), quantite/2, getAppTexture(texture));
    target.draw(foodSprite);


    if(isDebugOn() and quantite!=0) {
        auto const text = buildText(to_nice_string(quantite), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black, 0);
        target.draw(text);
    }
}

Food:: ~Food(){
    if(quantite>0){
        foodTotal-=quantite;
    }
}
bool Food:: getPoison() const{

    return poison;
}

Quantity Food:: getQuantity() const{
    return quantite;
}

Quantity Food:: getTotalFood(){
    return foodTotal;
}






