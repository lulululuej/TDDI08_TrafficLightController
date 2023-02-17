#ifndef TRAFFICSENSOR_H
#define TRAFFICSENSOR_H

#include <systemc.h>

SC_MODULE(Trafficsensor) {
  sc_in<int> trafficNS;
  sc_in<int> trafficSN;
  sc_in<int> trafficWE;
  sc_in<int> trafficEW;

  sc_in<int> timing;

  sc_out<int> lightNS;
  sc_out<int> lightSN;
  sc_out<int> lightWE;
  sc_out<int> lightEW;

  sc_event print_event;
  
  SC_HAS_PROCESS(Trafficsensor);
  Trafficsensor(sc_module_name name);

  void traffic_sensor();
  void print_method();
};

#endif // TRAFFICSENSOR_H