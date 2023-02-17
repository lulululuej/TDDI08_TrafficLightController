#ifndef COUNTER_H
#define COUNTER_H

#include <systemc.h>

SC_MODULE(Counter) {
  int value;
  sc_out<int> trafficNS;
  sc_out<int> trafficSN;
  sc_out<int> trafficWE;
  sc_out<int> trafficEW;

  sc_out<int> timing;

  sc_event count_event;

  SC_HAS_PROCESS(Counter);
  Counter(sc_module_name name, int start = 0);
  void count_method();
  void event_trigger_thread();
};

#endif // COUNTER_H