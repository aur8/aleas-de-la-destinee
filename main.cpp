#include "proba.hpp"
#include "player.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>
#include "include/player.h"
#include "include/story.h"
#include "include/rooms.h"


int main() {
    Player player1;
    story_begin();
    player1.generate_name();
    player1.generate_stats();
    player1.generate_hp();

    bool isFinished = false;

  // GEOMETRIQUE
  // double success_probability = 0.3; // Probabilité de succès
  // int random_value_geometric = generate_geometric(success_probability);
  // std::cout << random_value_geometric << std::endl;

  // POISSON
  double mean = 3.0; // Moyenne de la loi de Poisson
  int random_value_poisson = generate_poisson(mean);
  std::cout << random_value_poisson << std::endl;

  // GAMMA
  double alpha = 2.0; // Paramètre de forme de la loi gamma
  double beta = 1.0;  // Inverse de la moyenne de la loi gamma
  double random_value_gamma = generate_gamma(alpha, beta);
  std::cout << random_value_gamma << std::endl;

  // SALLE 2


  while (isFinished == false){
      salle1(4, player1);

  }

  return 0;
}