#include "Stats.hpp"
#include <iostream>


Stats::Stats()
{

}

void Stats:: setActive(int id){
    identifiant_actif=id;
}

int Stats:: GetID() const{
    return identifiant_actif;
}


std::string Stats:: getCurrentTitle() const {
   std::string title = "Element pas trouvé";
   if(ensemble_graphes.size()>0){
       for(unsigned int i(0); i<ensemble_graphes.size();++i){
                if(ensemble_graphes[i].id==identifiant_actif){
                    title = ensemble_graphes[identifiant_actif].Title;
                }
        }
    }
   return title;
}



void Stats:: next(){
    if (identifiant_actif==ensemble_graphes.size()-1){
        identifiant_actif=0;
    }
    else {
        identifiant_actif+=1;
    }
}

void Stats:: previous(){
    identifiant_actif-=1;

    if(identifiant_actif<0){
        identifiant_actif=ensemble_graphes.size()-1;
    }

}

void Stats:: reset(){
    for(auto& elem: ensemble_graphes){
        elem.graph.reset();
    }
}


void Stats:: addGraph(int id, const std::string &title, const std::vector<std::string> &series, double min, double max, const Vec2d &size)
{
    bool Id_test(false);
    if(ensemble_graphes.size()>0){
        for(auto& elem: ensemble_graphes){
            if(elem.id == id){
                Id_test=true;
                elem.graph.reset(new Graph(series, size, min, max));
                elem.Title=title;
            }
        }
    }
    if(!Id_test){
        ensemble_graphes.push_back({title, std::make_unique<Graph>(series, size, min, max), id});
    }

    identifiant_actif=id;


//    Graph nouveau(series, size, min, max);

//    if (ensemble_graphes.size()>0  and ensemble_graphes[id].graph!=nullptr) {
//        ensemble_graphes[id].graph.reset(new Graph(nouveau));
//        ensemble_graphes[id].Title=title;
//        identifiant_actif=id;
//    }
}

void Stats::drawOn(sf::RenderTarget &target) const{
    for(unsigned int i(0); i< ensemble_graphes.size(); ++i){
            if(ensemble_graphes[i].id==identifiant_actif){
                ensemble_graphes[i].graph->drawOn(target);
            }
    }
}

void Stats:: update(sf::Time dt){

}














