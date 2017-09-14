/*
 * This file contains the implementation for the rotator_track controller test.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <pthread.h>
#include "SAL_rotator.h"
#include "ccpp_sal_rotator.h"
#include "os.h"
#include "sharedInfo.h"
#include "rotator/Rotator.h"

using namespace DDS;
using namespace rotator;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
  OS_API_EXPORT
  void* test_rotator_track_controller(void* argument);
}

void* test_rotator_track_controller(void* argument)
{ 
  os_time delay_10ms = { 0, 10000000 };
  
  int cmdId = -1;
  int timeout = 1;
  rotator_command_trackC SALInstance;
  SAL_rotator mgr = SAL_rotator();
  sharedInfo *rotatorSim = (sharedInfo *) argument;
  
  mgr.salProcessor("rotator_command_track");
  cout << "=== rotator_track controller ready ===" << endl;

  bool stop = rotatorSim->getStop();
  while (!stop) {
    // receive command
    cmdId = mgr.acceptCommand_track(&SALInstance);
    if (cmdId > 0) {
        //cout << "=== command track received = " << endl;
       cout << "command_sent: angle:" << SALInstance.angle << "; velocity:" << SALInstance.velocity << "; tai:" << SALInstance.tai << endl;
       rotatorSim->getRotator().setPosition(SALInstance.angle);
       
       if (timeout > 0) {
          mgr.ackCommand_track(cmdId, SAL__CMD_INPROGRESS, 0, "Ack : OK");
          os_nanoSleep(delay_10ms);
       }       
       mgr.ackCommand_track(cmdId, SAL__CMD_COMPLETE, 0, "Done : OK");
    }
    os_nanoSleep(delay_10ms);
    stop = rotatorSim->getStop();
  }

  /* Remove the DataWriters etc */
  mgr.salShutdown();
  cout << "==== Tracking Command subscriber closed successfully ====" << endl;
  //return 0;
}

/*
int main (int argc, char *argv[])
{
  return test_rotator_track_controller();
}
*/
