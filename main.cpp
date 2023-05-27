#include "proba.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>

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

double generate_exponentielle(double lambda) {
  double u = generate_uniform_real();

  return -1 / lambda * log(1 - u);
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

int generate_poisson(double lambda) {

  int k = 0;
  double p = 1.0;

  while (p > exp(-lambda)) {
    double u = generate_uniform_real();
    p *= u;
    k++;
  }

  return k - 1;
}

double generate_gamma(double alpha, double beta) {
  double sum = 0.0;
  for (int i = 0; i < alpha; i++) {
    double exponential_value = generate_exponentielle(1.0 / beta);
    sum += exponential_value;
  }

  return sum;
}

int generate_binomial(int n, double p) {
  double u = generate_uniform_real(); // génère un nombre aléatoire suivant
                                      // une loi uniforme

  int count = 0;
  // méthode de Bernoulli en effectuant des tirages aléatoires répétés avec une
  // probabilité de succès donnée
  for (int i = 0; i < n; ++i) {
    if (u < p) {
      count++;
    }
  }

  return count;
}

double generate_laplace(double mu, double b) {

  double u = generate_uniform_real();
  ; // Génère un nombre aléatoire entre 0 et 1

  if (u < 0.5) {
    return mu + b * std::log(2.0 * u);
  } else {
    return mu - b * std::log(2.0 * (1.0 - u));
  }
}

double generate_pareto(double alpha, double xm) {

  double u = generate_uniform_real(); // Génère un nombre aléatoire entre 0 et 1

  return xm * std::pow(1.0 - u, -1.0 / alpha);
}

void salle2(double success_prob, double dexterite) {
  std::string word = "abracadabra"; // Mot à deviner
  int attempts = generate_geometric(success_prob) -
                 1; // Génère le nombre d'essais autorisés en lien avec une
                    // caractéristique du perso

  int time_limit = generate_geometric(dexterite / 100);

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
  }
}

void salle3(double alpha, double beta) {
  double regen = generate_gamma(alpha, beta);
}

int main() {

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
  double success_probability = 0.25; // Probabilité de succès
  int dexterite = 10;                // Limite de temps en secondes
  salle2(success_probability, dexterite);

  return 0;
}
