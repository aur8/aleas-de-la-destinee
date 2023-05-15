#include <cmath>
#include <iostream>
#include <random>

struct personnage {
  int m_pdv;
  int m_force;
  int m_constitution;
  int m_agilite;

  personnage(int pdv, int force, int constitution, int agilite)
      : m_pdv(pdv), m_force(force), m_constitution(constitution),
        m_agilite(agilite) {}
};

double generate_uniform_real() {
  return static_cast<double>(rand()) / RAND_MAX;
}

int generate_geometric(double success_prob) {

  srand(static_cast<unsigned int>(
      time(0))); // Initialisation du générateur de nombres aléatoires

  double u = generate_uniform_real(); // génère un nombre aléatoire suivant une
                                      // loi uniforme

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

int main() {

  // GEOMETRIQUE
  double success_probability = 0.3; // Probabilité de succès
  int random_value_geometric = generate_geometric(success_probability);
  std::cout << random_value_geometric << std::endl;

  // POISSON
  double mean = 3.0; // Moyenne de la loi de Poisson
  int random_value_poisson = generate_poisson(mean);
  std::cout << random_value_poisson << std::endl;

  // GAMMA
  double alpha = 2.0; // Paramètre de forme de la loi gamma
  double beta = 1.0;  // Inverse de la moyenne de la loi gamma
  double random_value_gamma = generate_gamma(alpha, beta);
  std::cout << random_value_gamma << std::endl;

  return 0;
}