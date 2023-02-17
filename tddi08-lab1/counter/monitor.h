#ifndef MONITOR_H
#define MONITOR_H

#include <systemc.h>
#include <fstream>

using std::ofstream;

SC_MODULE(Monitor) {
  sc_in<int> trafficNS;
  sc_in<int> trafficSN;
  sc_in<int> trafficWE;
  sc_in<int> trafficEW;

  sc_in<int> timing;

  sc_in<int> lightNS;
  sc_in<int> lightSN;
  sc_in<int> lightWE;
  sc_in<int> lightEW;

  sc_event printf_event;

  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name, char *outfile);
  ~Monitor();

  void monitor_method();
  void printf_method();
  ofstream *out;
};

#endif // MONITOR_H
