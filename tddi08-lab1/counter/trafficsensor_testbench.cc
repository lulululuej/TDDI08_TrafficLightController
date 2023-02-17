#include <systemc.h>
#include "trafficsensor.h"
#include "counter.h"
#include "monitor.h"

int sc_main(int argc, char **argv)
{
    // The command-line arguments are as follows:
    // 1. the initial value of the counter and
    // 2. the simulation time (in seconds).
    assert(argc == 4);

    int init_value = atoi(argv[1]);
    sc_time sim_time(atof(argv[2]), SC_SEC);
    char *outfile = argv[3];

    // Create channels.
    sc_signal<int> trafficNS_sig;
    sc_signal<int> trafficSN_sig;
    sc_signal<int> trafficWE_sig;
    sc_signal<int> trafficEW_sig;
    sc_signal<int> clock_sig;
    sc_signal<int> lightNS_sig;
    sc_signal<int> lightSN_sig;
    sc_signal<int> lightWE_sig;
    sc_signal<int> lightEW_sig;

    // Instantiate modules.
    Trafficsensor trafficsensor("Trafficsensor");
    Counter counter("Counter");
    Monitor monitor("Monitor", outfile);

    // Connect the channels to the ports.
    trafficsensor(trafficNS_sig, trafficSN_sig, trafficWE_sig, trafficEW_sig, clock_sig, lightNS_sig, lightSN_sig, lightWE_sig, lightEW_sig);
    counter(trafficNS_sig, trafficSN_sig, trafficWE_sig, trafficEW_sig, clock_sig);
    monitor(trafficNS_sig, trafficSN_sig, trafficWE_sig, trafficEW_sig, clock_sig, lightNS_sig, lightSN_sig, lightWE_sig, lightEW_sig);
    // Start the simulation.
    sc_start(sim_time);

    return 0;
}
