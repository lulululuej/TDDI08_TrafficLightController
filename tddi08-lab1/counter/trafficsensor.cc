#include "trafficsensor.h"

using std::cout;
using std::endl;

Trafficsensor::Trafficsensor(sc_module_name name)
  : sc_module(name)
{
  lightNS.initialize(0);
  lightSN.initialize(0);
  lightWE.initialize(0);
  lightEW.initialize(0);

  SC_METHOD(traffic_sensor);
  dont_initialize();
  sensitive << timing;
  SC_METHOD(print_method);
  dont_initialize();
  sensitive << print_event;
}

int num_ns = 0;
int num_sn = 0;
int num_we = 0;
int num_ew = 0;
int time_ns = 0;
int time_sn = 0;
int time_we = 0;
int time_ew = 0;

void Trafficsensor::traffic_sensor()
{
  int lightns, lightsn, lightwe, lightew;  
  int NS = trafficNS->read();
  int SN = trafficSN->read();
  int WE = trafficWE->read();
  int EW = trafficEW->read();

  int clock = timing->read();

  cout << "clock: " << clock << endl;
  cout << "trafficNS: " << NS << " trafficSN: " << SN << " trafficWE: " << WE << " trafficEW: " << EW << endl;
  
  if (NS == 1) {
    ++num_ns;
  }
  if (SN == 1) {
    ++num_sn;
  }
  if (WE == 1) {
    ++num_we;
  }
  if (EW == 1) {
    ++num_ew;
  }

  //cout << "numNS: " << num_ns << " numSN: " << num_sn << " numWE: " << num_we << " numEW: " << num_ew << endl;

  if (num_ns == 0) {
    lightNS == 0;
  }
  if (num_sn == 0) {
    lightSN == 0;
  }
  if (num_we == 0) {
    lightWE == 0;
  }
  if (num_ew == 0) {
    lightEW == 0;
  }

  if ( (num_ns + num_sn) >= (num_we + num_ew) ) {
    lightWE = 0;
    lightEW = 0;
    time_we = 0;
    time_ew = 0;
    if (num_ns > 0) {
      lightNS = 1;
      ++time_ns;
      num_ns = 0;
    }
    if (num_sn > 0) {
      lightSN = 1;
      ++time_sn;
      num_sn = 0;
    }
  }
  else {
    lightNS = 0;
    lightSN = 0;
    time_ns = 0;
    time_sn = 0;
    if (num_we > 0) {
      lightWE = 1;
      ++time_we;
      num_we = 0;
    }
    if (num_ew > 0) {
      lightEW = 1;
      ++time_ew;
      num_ew = 0;
    }
  }

  /* timeout */
  if( ( (lightNS == 1 && time_ns > 5) || (lightSN == 1 && time_sn > 5) ) && (num_we > 0 || num_ew > 0) ) {
    lightNS = 0;
    lightSN = 0;
    time_ns = 0;
    time_sn = 0;
    if (num_we > 0) {
      lightWE = 1;
      ++time_we;
      num_we = 0;
    }
    if (num_ew > 0) {
      lightEW = 1;
      ++time_ew;
      num_ew = 0;
    }
  }
  if( ( (lightWE == 1 && time_we > 5) || (lightEW == 1 && time_ew > 5) ) && (num_ns > 0 || num_sn > 0) ) {
    lightWE = 0;
    lightEW = 0;
    time_we = 0;
    time_ew = 0;
    if (num_ns > 0) {
      lightNS = 1;
      ++time_ns;
      num_ns = 0;
    }
    if (num_sn > 0) {
      lightSN = 1;
      ++time_sn;
      num_sn = 0;
    }
  }
  print_event.notify(SC_ZERO_TIME);
}

void Trafficsensor::print_method() {
  cout << "lightNS: " << lightNS << " lightSN: " << lightSN << " lightWE: " << lightWE << " lightEW: " << lightEW << endl;
  cout << "timeNS: " << time_ns << " timeSN: " << time_sn << " timeWE: " << time_we << " timeEW: " << time_ew << endl;
}