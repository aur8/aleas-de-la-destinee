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
  // std::random_device rd;
  // std::mt19937 gen(rd());
  // std::uniform_real_distribution<double> dist(0.0, 1.0);

  // double u = dist(gen); // Génère un nombre aléatoire entre 0 et 1

  srand(static_cast<unsigned int>(
      time(0))); // Initialisation du générateur de nombres aléatoires

  double u = generate_uniform_real();

  // Utilise la méthode inverse de la fonction de répartition de la loi
  // géométrique
  int x = std::ceil(std::log(1.0 - u) / std::log(1.0 - success_prob));

  return x;
}

int generate_poisson(double mean) {
  // std::random_device rd;
  // std::mt19937 gen(rd());
  // std::uniform_real_distribution<double> dist(0.0, 1.0);

  srand(static_cast<unsigned int>(
      time(0))); // Initialisation du générateur de nombres aléatoires

  double L = std::exp(-mean);
  int k = 0;
  double p = 1.0;

  do {
    k++;
    double u = generate_uniform_real();
    p *= u;
  } while (p >= L);

  return k - 1;
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

  return 0;
}