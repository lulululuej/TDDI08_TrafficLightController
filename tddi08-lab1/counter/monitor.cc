#include <cassert>
#include "monitor.h"

Monitor::Monitor(sc_module_name name, char *outfile)
  : sc_module(name)
{
  assert(outfile != 0);
  out = new ofstream(outfile);
  assert(*out);

  SC_METHOD(monitor_method);
  dont_initialize();
  sensitive << timing;
  SC_METHOD(printf_method);
  dont_initialize();
  sensitive << printf_event;
}

Monitor::~Monitor()
{
  delete out;
}

void Monitor::monitor_method()
{
  printf_event.notify(SC_ZERO_TIME);
  //*out << "traffic_car (" << sc_time_stamp() << ") = " << NS << " " << SN << " " << WE << " " << EW << endl;
  //*out << "light___car (" << sc_time_stamp() << ") = " << lightns << " " << lightsn << " " << lightwe << " " << lightew << endl;
  //*out << "trafficlight(" << sc_time_stamp() << ") = " << lightns << endl;
}

void Monitor::printf_method() {
  int NS = trafficNS->read();
  int SN = trafficSN->read();
  int WE = trafficWE->read();
  int EW = trafficEW->read();
  int lightns = lightNS->read();
  int lightsn = lightSN->read();
  int lightwe = lightWE->read();
  int lightew = lightEW->read();
  *out << "traffic_car (" << sc_time_stamp() << ") = " << NS << " " << SN << " " << WE << " " << EW << endl;
  *out << "light___car (" << sc_time_stamp() << ") = " << lightns << " " << lightsn << " " << lightwe << " " << lightew << endl;
}
