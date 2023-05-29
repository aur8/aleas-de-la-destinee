#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>

double generate_uniform_real();
int generate_geometric(double success_prob);
int generate_poisson(double mean);
double generate_gamma(double alpha, double beta);
double generate_exponentielle(double lambda);
int generate_binomial(int n, double p);
double generate_laplace(double mu, double b);
double generate_pareto(double alpha, double xm);
