#include "include/player.h"
#include <iostream>

void Player::display_abilities() const {
    std::cout << "Force : " << m_str << std::endl;
    std::cout << "Dextérité : " << m_dex << std::endl;
    std::cout << "Constitution : " << m_con << std::endl << std::endl;
}

void Player::add_value_to_ability(int &ability, const std::string& ability_name){
    if (m_ability_points_left == 0){
        return;
    }
    std::cout << "[Entrez le nombre de points à ajouter en " << ability_name << ".]" << std::endl;
    unsigned int points_to_add;
    std::cin >> points_to_add;
    if (points_to_add < 0 || points_to_add > m_ability_points_left){
        std::cout << "La valeur n'est pas valide." << std::endl << std::endl;
        return;
    }
    ability += (int)points_to_add;
    m_ability_points_left -= points_to_add;
    std::cout << std::endl;
};

void Player::generate_name() {
    std::string new_name;
    std::cout << "[Comment se nomme votre personnage ?]" << std::endl;
    std::cin >> new_name;
    m_name = new_name;
    std::cout << std::endl;
}

void Player::generate_stats() {
    std::cout << "[Déterminez les caractéristiques de " << m_name << ". Vous disposez de 15 points à répartir dans 3 caractéristiques : Force, Dextérité et Constitution.]" << std::endl << std::endl;
    while (m_ability_points_left > 0){
        std::cout << "[Il reste " << m_ability_points_left << " points à répartir pour " << m_name << ".]" << std::endl;
        display_abilities();
        add_value_to_ability(m_str, "Force");
        add_value_to_ability(m_dex, "Dextérité");
        add_value_to_ability(m_con, "Constitution");
    }
    if (m_ability_points_left == 0){
        std::cout << std::endl << "[Plus de point à allouer. Les caractéristiques finales sont : ]" << std::endl;
        display_abilities();
    }
}
