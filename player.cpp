#include "include/player.h"
#include "proba.hpp"
#include <iostream>

void Player::display_abilities() const {
  std::cout << "Force : " << m_str << std::endl;
  std::cout << "Dextérité : " << m_dex << std::endl;
  std::cout << "Constitution : " << m_con << std::endl << std::endl;
}

AbilityState Player::getNextAbilityState(AbilityState currentState) {
  // Définir les probabilités de transition pour chaque état
  const double transitionProbabilities[3][3] = {
      {0.7, 0.2, 0.1}, // Probabilités de transition depuis l'état 0 (Faible)
      {0.3, 0.5, 0.2}, // Probabilités de transition depuis l'état 1 (Moyenne)
      {0.1, 0.4, 0.5} // Probabilités de transition depuis l'état 2 (Élevée)
  };

  // Générer un nombre aléatoire entre 0 et 1
  double randomValue = generate_uniform_real();

  // Trouver la nouvelle transition basée sur le nombre aléatoire
  double cumulativeProbability = 0.0;
  int nextState = 0;

  for (int i = 0; i < 3; ++i) {
    cumulativeProbability += transitionProbabilities[currentState][i];
    if (randomValue <= cumulativeProbability) {
      nextState = i;
      break;
    }
  }

  return static_cast<AbilityState>(nextState);
}

void Player::add_value_to_ability(int &ability,
                                  const std::string &ability_name) {
  // if (m_ability_points_left == 0){
  //     return;
  // }
  // std::cout << "[Entrez le nombre de points à ajouter en " << ability_name <<
  // ".]" << std::endl; unsigned int points_to_add; std::cin >> points_to_add;
  // if (points_to_add < 0 || points_to_add > m_ability_points_left){
  //     std::cout << "La valeur n'est pas valide." << std::endl << std::endl;
  //     return;
  // }
  // ability += (int)points_to_add;
  // m_ability_points_left -= points_to_add;
  // std::cout << std::endl;

  if (m_ability_points_left == 0) {
    return;
  }

  std::cout << "[Entrez le nombre de points à ajouter en " << ability_name
            << ".]" << std::endl;
  unsigned int points_to_add;
  std::cin >> points_to_add;

  if (points_to_add < 0 || points_to_add > m_ability_points_left) {
    std::cout << "La valeur n'est pas valide." << std::endl << std::endl;
    return;
  }

  ability += (int)points_to_add;
  m_ability_points_left -= points_to_add;

  // Mettre à jour l'état de la chaîne de Markov
  m_ability_state = getNextAbilityState(m_ability_state);

  std::cout << std::endl;
}

void Player::generate_hp() {
  double constitution_percentage =
      m_con / 20.0; // Convertir la constitution en pourcentage

  int max_hp = generate_binomial(
      20, constitution_percentage); // Lancer 20 dés pipés selon la constitution

  m_hp = max_hp;
  std::cout << "Points de vie (HP) : " << m_hp << std::endl << std::endl;
}

void Player::generate_name() {
  std::string new_name;
  std::cout << "[Comment se nomme votre personnage ?]" << std::endl;
  std::cin >> new_name;
  m_name = new_name;
  std::cout << std::endl;
}

// void Player::generate_stats() {
//     std::cout << "[Déterminez les caractéristiques de " << m_name << ". Vous
//     disposez de 15 points à répartir dans 3 caractéristiques : Force,
//     Dextérité et Constitution.]" << std::endl << std::endl; while
//     (m_ability_points_left > 0){
//         std::cout << "[Il reste " << m_ability_points_left << " points à
//         répartir pour " << m_name << ".]" << std::endl; display_abilities();
//         add_value_to_ability(m_str, "Force");
//         add_value_to_ability(m_dex, "Dextérité");
//         add_value_to_ability(m_con, "Constitution");
//     }
//     if (m_ability_points_left == 0){
//         std::cout << std::endl << "[Plus de point à allouer. Les
//         caractéristiques finales sont : ]" << std::endl; display_abilities();
//     }
// }

void Player::generate_stats() {
  std::cout << "[Déterminez les caractéristiques de " << m_name
            << ". Vous disposez de 15 points à répartir dans 3 "
               "caractéristiques : Force, Dextérité et Constitution.]"
            << std::endl
            << std::endl;

  AbilityState currentState =
      AbilityState::Low; // État initial de la chaîne de Markov

  while (m_ability_points_left > 0) {
    std::cout << "[Il reste " << m_ability_points_left
              << " points à répartir pour " << m_name << ".]" << std::endl;
    display_abilities();

    add_value_to_ability(m_str, "Force");
    currentState = getNextAbilityState(
        currentState); // Mettre à jour l'état de la chaîne de Markov

    add_value_to_ability(m_dex, "Dextérité");
    currentState = getNextAbilityState(
        currentState); // Mettre à jour l'état de la chaîne de Markov

    add_value_to_ability(m_con, "Constitution");
    currentState = getNextAbilityState(
        currentState); // Mettre à jour l'état de la chaîne de Markov
  }

  if (m_ability_points_left == 0) {
    std::cout
        << std::endl
        << "[Plus de point à allouer. Les caractéristiques finales sont : ]"
        << std::endl;
    display_abilities();
  }
}

AbilityState m_ability_state;

AbilityState get_ability_state(const std::string &ability_name) {
  if (ability_name == "Force") {
    return STATE_FORCE;
  } else if (ability_name == "Dextérité") {
    return STATE_DEXTERITY;
  } else if (ability_name == "Constitution") {
    return STATE_CONSTITUTION;
  }
  // Retourner un état par défaut si la caractéristique n'est pas reconnue
  return STATE_FORCE;
}

std::string get_ability_from_state(AbilityState state) {
  switch (state) {
  case STATE_FORCE:
    return "Force";
  case STATE_DEXTERITY:
    return "Dextérité";
  case STATE_CONSTITUTION:
    return "Constitution";
  }
  // Retourner une caractéristique par défaut si l'état n'est pas reconnu
  return "Force";
}
