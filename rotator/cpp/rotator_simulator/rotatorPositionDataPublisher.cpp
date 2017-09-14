/*
 * This file contains the implementation for the 'rotator_PositionPublisher' executable.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include "SAL_rotator.h"
#include "ccpp_sal_rotator.h"
#include "os.h"
#include <stdlib.h>
#include "sharedInfo.h"

//#include "example_main.h"

using namespace DDS;
using namespace rotator;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
  OS_API_EXPORT
  void* SALTelemetryPublisher(void* argument);
}

void* SALTelemetryPublisher(void* argument)
{
  os_time delay_1s = { 1, 0 };
  rotator_PositionC myData;
  long iseq;

  sharedInfo *rotatorSim = (sharedInfo *) argument;
  // Publish Events
  //create Topic
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
  int rotatorID = 1;
  if (getenv("LSST_rotator_ID") != NULL) {
     sscanf(getenv("LSST_rotator_ID"),"%d",&rotatorID);
  } 
  SAL_rotator mgr = SAL_rotator(rotatorID);
#else
  SAL_rotator mgr = SAL_rotator();
#endif

  mgr.salTelemetryPub(rotatorSim->getPositionTopic());
  bool stop = rotatorSim->getStop();
  Rotator rotator;
  
  while (!stop) {

    rotator = rotatorSim->getRotator();
    myData.Calibrated[0] = rotator.getPosition();
    myData.Raw[0] = (long) rotator.getPosition()*1E6;
    
    //myData.Calibrated[1] = rotatorSim->rotator.getPosition();
    //myData.Raw[1] = (long) rotatorSim->rotator.getPosition()*1E6;
    
    mgr.putSample_Position(&myData);
    stop = rotatorSim->getStop();
    os_nanoSleep(delay_1s);
  }

  /* Remove the DataWriters etc */
  mgr.salShutdown();
  cout << "==== Position publisher closed successfully ====" << endl;

}


/*
int OSPL_MAIN (int argc, char *argv[])
{
  return SALTelemetryPublisher ("rotator_Position");
}
*/

