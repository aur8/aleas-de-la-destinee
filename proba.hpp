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
