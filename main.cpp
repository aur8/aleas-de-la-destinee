
#include "include/player.h"
#include "include/rooms.h"
#include "include/story.h"
#include "proba.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>

int main() {
  Player player1;
  story_begin();
  player1.generate_name();
  player1.generate_stats();
  player1.generate_hp();

  bool isFinished = false;

  // // GEOMETRIQUE
  // // double success_probability = 0.3; // Probabilité de succès
  // // int random_value_geometric = generate_geometric(success_probability);
  // // std::cout << random_value_geometric << std::endl;

  // // POISSON
  // double mean = 3.0; // Moyenne de la loi de Poisson
  // int random_value_poisson = generate_poisson(mean);
  // std::cout << random_value_poisson << std::endl;

  // // GAMMA
  // double alpha = 4;  // Paramètre de forme de la loi gamma
  // double beta = 0.8; // Inverse de la moyenne de la loi gamma
  // double random_value_gamma = generate_gamma(alpha, beta);
  // std::cout << random_value_gamma << std::endl;

  // // pareto
  // double xm = 26;
  // double alpha = 13;
  // double random_value_pareto = generate_pareto(alpha, xm);
  // std::cout << random_value_pareto << std::endl;

  while (player1.m_isDone == false) {
    salle1(player1.m_con, player1);
  }

  std::cout << "Vous ressortez du donjon, riche de " << player1.m_gold
            << " pièces d'or..." << std::endl;
  std::cout << "Fin du jeu." << std::endl;

  return 0;
}