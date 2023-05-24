#include "proba.hpp"

double generate_uniform_real() {
  return static_cast<double>(rand()) / RAND_MAX;
}

int generate_geometric(double success_prob) {

  srand(static_cast<unsigned int>(
      time(0))); // Initialisation du générateur de nombres aléatoires

  double u = generate_uniform_real(); // génère un nombre aléatoire suivant
                                      // une loi uniforme

  // Utilise la méthode inverse de la fonction de répartition de la loi
  // géométrique
  int x = std::ceil(std::log(1.0 - u) / std::log(1.0 - success_prob));

  return x;
}
int generate_poisson(double mean) {

  srand(static_cast<unsigned int>(
      time(0))); // Initialisation du générateur de nombres aléatoires

  double L = std::exp(-mean);
  int k = 0;
  double p = 1.0;

  do {
    k++;
    double u = generate_uniform_real(); // génère un nombre aléatoire suivant
                                        // une loi uniforme
    p *= u;
  } while (p >= L);

  return k - 1;
}

double generate_gamma(double alpha, double beta) {
  srand(static_cast<unsigned int>(
      time(0))); // Initialisation du générateur de nombres aléatoires

  // méthode de la somme de variables aléatoires exponentielles
  double sum = 0.0;
  for (int i = 0; i < alpha; ++i) {
    double u = generate_uniform_real(); // génère un nombre aléatoire suivant
                                        // une loi uniforme
    sum += -std::log(u);
  }

  return sum / beta;
}