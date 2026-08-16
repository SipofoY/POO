#include "Stats.hpp"


void Stats:: addGraph(int id, const std::string &title,const std::vector<std::string> &series, double min, double max, const Vec2d& size){

    ensemble_graph[id].reset(new Graph(series, size, min, max));
    libelle[id] = title;

}


