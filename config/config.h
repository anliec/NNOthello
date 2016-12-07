#ifndef CONFIG_H
#define CONFIG_H

// General constants
const double PI =  3.1415926535897932;

//Board config
const unsigned BOARD_SIZE_X = 8;
const unsigned BOARD_SIZE_Y = 8;

// Neural network
const unsigned int NB_LAYERS = 3;
const unsigned int LAYER_SIZES[NB_LAYERS] = {BOARD_SIZE_X*BOARD_SIZE_Y, 8, 1};

//comment to disable Intel IPP function
#define USE_INTEL_IPP

class config
{
public:

  // Threads
  static unsigned short NB_THREADS;

  // Neurale network weight modification probability
  static double NN_WEIGHT_CHANGE_PROBABILITY; // 10% chance of change by weight
  static double NN_WEIGHT_CHANGE_AVERAGE_VALUE; // the average value added to a weight is 0
  static double NN_WEIGHT_CHANGE_SDANTARD_DEVIATION; // the value added to a weight as a standart deviation of 0.05

};

#endif // CONFIG_H
