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

        while(std::getline(file, line)){// Nous verifions que le fichier puisse être ouvert
            std::stringstream p(line);
            if (line[0] == '#' or line.empty() or line[0] == '\r'){//nous regardons si la lgne commence par un "#" ou si la ligne est vide
                continue;
            }
            else {
                for (size_t i(0); i< maison.size() ; ++i){
                    if (line[i] != maison[i]){//nous regardons si le premier mot est maison et si oui on ajoute une maison a la position donnée
                         erreur=true;
                    }
                }
                if (!erreur){
                        p >> nom >> posx >> posy;
                        int x2 = std::stoi(posx);
                        int y2 = std::stoi(posy);
                         Vec2d nouvpos(x2, y2);
                        getAppEnv().addAnthill(new Anthill(nouvpos));
                }
                else {// si le premier  mot n'est pas maison nous allons tester avec les autres possibilités pour les ajouter à l'environnement
                    erreur=false;

                    for (size_t i(0); i< term.size() ; ++i){
                        if (line[i]!= term[i]){
                         erreur=true;
                        }
                    }
                    if (!erreur) {
                       p >> nom >> posx >> posy;
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
                            size_t var = nour.size() + posx.size() + posy.size() + 3;// ici nous faisons cela pour avoir la position de la quantité de la nourriture dans la ligne
                            for (size_t i(var); i<line.size(); ++i){ //puis nous allons affecter cette quantité a une vaiable qui va être converti en int grâce a stoi
                                quantit.push_back(line[i]);


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

    } else {// nous affichons un message d'erreur si le fichier ne peut pas etre ouvert
        std::cerr << "Erreur impossible d'ouvrir le fichier"<< std::endl;
        }
}
