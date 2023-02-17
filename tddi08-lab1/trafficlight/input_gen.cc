#include "input_gen.h"
#include <cassert>

Generator::Generator(sc_module_name name, char *datafile)
  : sc_module(name)
{
  assert(datafile != 0);       // An input file should be given.

  in = new ifstream(datafile); // Open the input file.
  assert(*in);                 // Check that everything is OK.

  SC_THREAD(generate_thread);

  trafficNS.initialize(0);
  trafficSN.initialize(0);
  trafficWE.initialize(0);
  trafficEW.initialize(0);
}

Generator::~Generator()
{
  delete in;
}

void Generator::generate_thread()
{
  int ns, sn, we, ew;
  for (;;) {
    wait(1, SC_SEC);     // Generate new inputs every second.
    *in >> ns >> sn >> we >> ew; // Read from the input file.
    trafficNS->write(ns);
    trafficSN->write(sn);
    trafficWE->write(we);
    trafficEW->write(ew);
    cout << "ns:" << trafficNS << " sn:" << trafficSN << endl;
    cout << "we:" << trafficWE << " ew:" << trafficEW << endl;
  }
}
