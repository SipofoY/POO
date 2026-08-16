#include "Loader.hpp"
#include "Anthill.hpp"
#include "Food.hpp"
#include "Termite.hpp"
#include "Utility/Utility.hpp"
#include <sstream>

void loadMap(std::string const& filepath){

    std::ifstream file(filepath);
    std::string maison = "anthill";
    std::string term = "termite";
    std::string nour = "food";

    std::string posx;
    std::string posy;
    std::string space;
    std::string quantite;
    bool erreur=false;

    std::string nom;
    if (file) {
        std::string line;

        while(std::getline(file, line)){
            std::stringstream p(line);
            std::cout << line << std::endl;
           // std::cout << test << std::endl;
            if (line[0] == '#' or line.empty() or line[0] == '\r'){
                continue;
            }
            else {
                for (size_t i(0); i< maison.size() ; ++i){
                    if (line[i] != maison[i]){
                         erreur=true;
                    }
                }
                if (!erreur){
                        p >> nom >> posx >> posy;
                        //std::cout << nom << posx <<posy << std::endl;
                        int x2 = std::stoi(posx);
                        int y2 = std::stoi(posy);
                         Vec2d nouvpos(x2, y2);
                        getAppEnv().addAnthill(new Anthill(nouvpos));
                }
                else {
                    erreur=false;

                    for (size_t i(0); i< term.size() ; ++i){
                        if (line[i]!= term[i]){
                         erreur=true;
                        }
                    }
                    if (!erreur) {
                       p >> nom >> posx >> posy;
                       //std::cout << nom << posx <<posy << std::endl;
                       int x1 = std::stoi(posx);
                       int y1 = std::stoi(posy);
                        Vec2d nouvpos1(x1, y1);
                        getAppEnv().addAnimal(new Termite(nouvpos1));
                    }
                    else {
                        erreur=false;

                        for (size_t i(0); i< nour.size() ; ++i){
                            if (line[i] != nour[i]){
                                 erreur=true;
                            }
                        }
                        if (!erreur){
                            std::string quantit;
                            p >> nom;
                            p >> posx;
                            p >> posy;

                            int x3 = std::stoi(posx);
                            int y3 = std::stoi(posy);
                            Vec2d nouvpos3(x3, y3);
                            size_t var = nour.size() + posx.size() + posy.size() + 3;
                            for (size_t i(var); i<line.size(); ++i){
                                quantit.push_back(line[i]);

                            //std::cout << "test = " <<"-"<< var <<"-" << quantit<< std::endl;

                            getAppEnv().addFood(new Food(nouvpos3, std::stoi(quantit)));
                            }
                        }
                        else{
                            std::cout << "ligne erronée" << std::endl;
                        }
                    }
                }
            }
        }
        file.close();

    } else {
        std::cerr << "Erreur impossible d'ouvrir le fichier"<< std::endl;
        }
}
