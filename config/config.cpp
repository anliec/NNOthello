#include "config.h"

// Threads
unsigned short config::NB_THREADS = 4;

// Neurale network weight modification probability
double config::NN_WEIGHT_CHANGE_PROBABILITY = 0.5; // 50% chance of change by weight
double config::NN_WEIGHT_CHANGE_AVERAGE_VALUE = 0; // the average value added to a weight is 0
double config::NN_WEIGHT_CHANGE_SDANTARD_DEVIATION = 0.05; // the value added to a weight as a standart deviation of 0.05

