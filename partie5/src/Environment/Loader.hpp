#ifndef LOADER_HPP
#define LOADER_HPP

#include "Utility/Utility.hpp"
#include"Application.hpp"
#include <iostream>
#include <fstream>

    /*! @brief fonction qui à partir d'un fichier text va placer les elements indiquer dans ce fichier selon une forme bien défini
     *  @param un std::string qui represente le chemin du fichier à lire
*/
void loadMap(std::string const& filepath);

#endif // LOADER_HPP
