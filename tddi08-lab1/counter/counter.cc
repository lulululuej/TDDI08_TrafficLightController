#include <iostream>
#include "counter.h"

using std::cout;
using std::endl;

Counter::Counter(sc_module_name name, int start)
  : sc_module(name), value(start)
{
  // at the start of the simulation and only once
  SC_THREAD(event_trigger_thread);

  // cannot contain any wait statements
  SC_METHOD(count_method);
  dont_initialize();
  sensitive << count_event;
}

void Counter::count_method()
{
  value++;
  if(timing == 0) {
    timing = 1;
  }
  else {
    timing = 0;
  }
  
  trafficNS = round(((double) rand() / (RAND_MAX)));
  trafficSN = round(((double) rand() / (RAND_MAX)));
  trafficWE = round(((double) rand() / (RAND_MAX)));
  trafficEW = round(((double) rand() / (RAND_MAX)));
  
  // sc_time_stamp() obtain the current time an an sc_time obj
  /*cout << sc_time_stamp() << ": NS = " << trafficNS << 
                              " SN = " << trafficSN <<
                              " WE = " << trafficWE <<
                              " EW = " << trafficEW << endl;*/
}

// is an infinite loop
void Counter::event_trigger_thread()
{
  for (;;) {               // Loop infinitely.
    wait(1, SC_SEC);       // Wait one second.
    count_event.notify();  // Trigger count_method.
  }
}
