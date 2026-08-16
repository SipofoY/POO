#ifndef STATS_HPP
#define STATS_HPP
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include <memory>
#include <vector>
#include <string>
#include "Graph.hpp"


class Stats: public Drawable, public Updatable
{
public:
    Stats();
    void setActive(int id);
    std::string getCurrentTitle() const;
    int GetID() const;
    void next();
    void previous();
    void reset();
    void setID();
    void addGraph(
      int id,
      const std::string &title,
      const std::vector<std::string> &series,
      double min,
      double max,
      const Vec2d &size
    );
    virtual void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;

private:
    struct Graphique {
        std::string Title;
        std::unique_ptr<Graph> graph;
        int id;
    };

    //std::vector<std::unique_ptr<Graph>> Graphes;
    //std::vector<std::string> Title;
    std::vector<Graphique> ensemble_graphes;
    int identifiant_actif;

};

#endif // STATS_HPP
