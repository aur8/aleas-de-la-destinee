#include "player.h"
#include "proba.hpp"

#ifndef ALEAS_DE_LA_DESTINEE_ROOMS_H
#define ALEAS_DE_LA_DESTINEE_ROOMS_H

void salle1(double lambda, Player player);
void salle2(Player player);
void salle3(Player &player, int value);
void salle4(double alpha, double beta, Player &player);
void salle5(double mu, double b, Player &player);
void salle6(double alpha, double xm, Player &player);

struct Enemy {
  int health;
};

void salle1(double lambda, Player player) {
  double temps_attente = generate_exponentielle(lambda);

  std::this_thread::sleep_for(
      std::chrono::milliseconds(static_cast<int>(temps_attente * 1000)));

  std::cout << "Appuyez sur la touche X pour continuer." << std::endl;

  // Lire l'entrée de l'utilisateur
  char touche;
  std::cin >> touche;

  if (touche == 'X' || touche == 'x') {
    std::cout << "Bravo ! Vous pouvez passer à la salle suivante." << std::endl;
    salle2(player);
  } else {
    std::cout << "Mauvaise touche ! Essayez encore." << std::endl;
    salle1(lambda, player);
  }
}

void salle2(Player player) {
  double success_probability = 0.25; // Probabilité de succès

  std::string word = "abracadabra"; // Mot à deviner
  int attempts = 1; // Génère le nombre d'essais autorisés en lien avec une
                    // caractéristique du perso

  double time_limit = generate_exponentielle(
      player.m_dex /
      100.0); // Génère le temps limite selon une loi exponentielle en fonction
              // de la dextérité du joueur

  std::cout << "Vous avez " << attempts
            << " essai(s) pour écrire le mot suivant dans les " << time_limit
            << " secondes : " << word << std::endl;

  std::cout << "Vous avez " << attempts
            << " essai(s) pour écrire le mot suivant dans les " << time_limit
            << " secondes : " << word << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(1)); // Attend une seconde

  std::string guess;
  std::cout << "Début du jeu !" << std::endl;

  std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point current_time;

  while (attempts > 0) {
    current_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = current_time - start_time;

    if (elapsed_seconds.count() >= time_limit) {
      std::cout << "Temps écoulé !" << std::endl;
      break;
    }

    std::cin >> guess;

    if (guess == word) {
      std::cout << "Bravo, vous avez gagné !" << std::endl;
      double mean = 3.0; // Moyenne de la loi de Poisson
      int random_value_poisson = generate_poisson(mean);
      salle3(player, random_value_poisson);
      break;
    } else {
      attempts--;
      std::cout << "Mot incorrect. Il vous reste " << attempts << " essai(s)."
                << std::endl;
    }
  }

  if (attempts == 0) {
    std::cout << "Vous avez épuisé tous vos essais. Le mot était : " << word
              << std::endl;
    salle1(4, player);
  }
}

void salle3(Player &player, int value) {
  unsigned int enemies_nb = value;
  std::vector<Enemy> enemies(
      enemies_nb, {5}); // Initialisation des ennemis avec 5 points de vie

  std::cout << enemies_nb << " ennemis sont dans cette pièce !" << std::endl;

  bool player_turn = true; // Indicateur de tour du joueur

  while (enemies_nb > 0) {
    if (player_turn) {
      std::cout << "C'est à votre tour !" << std::endl;
      std::cout << "Choisissez une action : " << std::endl;
      std::cout << "1. Attaque au corps à corps (Force : " << player.m_str
                << ")" << std::endl;
      std::cout << "2. Attaque à distance (Dextérité : " << player.m_dex << ")"
                << std::endl;

      int choice;
      std::cin >> choice;

      int damage;
      if (choice == 1) {
        damage = player.m_str; // Dommages basés sur la force du joueur
      } else if (choice == 2) {
        damage = player.m_dex; // Dommages basés sur la dextérité du joueur
      } else {
        std::cout << "Action invalide. Veuillez choisir à nouveau."
                  << std::endl;
        continue;
      }

      // Attaque contre un ennemi aléatoire
      int target_index = std::rand() % enemies_nb;
      Enemy &target = enemies[target_index];
      target.health -= damage;

      if (target.health <= 0) {
        std::cout << "Vous avez vaincu un ennemi !" << std::endl;
        enemies_nb--;
        enemies.erase(enemies.begin() + target_index);
      }
    } else {
      std::cout << "C'est au tour des ennemis !" << std::endl;
      for (Enemy &enemy : enemies) {
        // Ennemis effectuant des dégâts réduits
        int damage = std::rand() % 2 + 1; // Dommages aléatoires entre 1 et 2
        player.m_hp -= damage;

        std::cout << "Vous subissez " << damage << " dégât(s) !" << std::endl;
        std::cout << "Points de vie actuels : " << player.m_hp << std::endl
                  << std::endl;

        if (player.m_hp <= 0) {
          std::cout << "Vous avez été vaincu par les ennemis..." << std::endl;
          return; // Sortir de la salle
        }
      }
    }

    player_turn = !player_turn; // Changer le tour du joueur
  }

  std::cout << "Tous les ennemis ont été vaincus ! Vous pouvez passer à la "
               "salle suivante."
            << std::endl;
  salle4(value, (value * 2.) / 10, player);
}

void salle4(double alpha, double beta, Player &player) {
  double regen = generate_gamma(alpha, beta);
  std::cout << "Vous vous reposez. Vous avez régénéré " << regen
            << " points de vie !" << std::endl;
  player.m_hp += static_cast<int>(regen); // Ajouter les points de vie régénérés

  std::cout << "Points de vie actuels : " << player.m_hp << std::endl
            << std::endl;

  std::cout << "Choisissez la valeur de 'b' pour la salle suivante (entre 1.0 "
               "et 5.0) : ";
  double b;
  std::cin >> b;
  // Vérification des limites pour 'b'
  b = std::max(1.0, std::min(5.0, b));

  salle5(5.0, b,
         player); // Appel de la salle 5 avec 'b' déterminé par le joueur
}

void salle5(double mu, double b, Player &player) {
  double damage = generate_laplace(mu, b);
  std::cout << "Vous entrez dans une salle piégée ! Vous subissez " << damage
            << " dégât(s) !" << std::endl;
  player.m_hp -=
      static_cast<int>(damage); // Réduire les points de vie du joueur

  if (player.m_hp <= 0) {
    std::cout << "Vous avez été vaincu..." << std::endl;
    return; // Sortir de la salle
  }

  std::cout << "Points de vie actuels : " << player.m_hp << std::endl
            << std::endl;
  // Interactions avec le joueur dans la salle (par exemple, choix d'actions)

  // Interaction avec le joueur pour déterminer la valeur de 'xm' pour la salle
  // suivante
  // std::cout << "Choisissez la valeur de 'xm' pour la salle suivante (entre "
  //              "10.0 et 50.0) : ";
  // double xm;
  // std::cin >> xm;
  // // Vérification des limites pour 'xm'
  // xm = std::max(10.0, std::min(50.0, xm));
  double xm = player.m_hp;
  salle6(1.5, xm,
         player); // Appel de la salle 6 avec 'xm' déterminé par le joueur
}

void salle6(double alpha, double xm, Player &player) {
  double reward = generate_pareto(alpha, xm);
  std::cout << "Vous trouvez un trésor ! Vous obtenez " << reward
            << " pièces d'or." << std::endl;
  player.m_gold += reward;

  std::cout << "Récompense actuelle : " << player.m_gold << std::endl
            << std::endl;

  player.m_isDone = true;
}

#endif // ALEAS_DE_LA_DESTINEE_ROOMS_H
