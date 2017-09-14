/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sharedInfo.h
 * Author: Andres Anania
 * Description: Create struct to share information between threads and requirement definitions
 * Created on May 11, 2017, 2:09 PM
 */

#ifndef SHAREDINFO_H
#define SHAREDINFO_H

#include "rotator/Rotator.h"

#ifdef __cplusplus
extern "C" {
#endif

//Requirements definitions
#define max_slew_velocity 3.5 // deg/sec
#define min_slew_velocity -3.5 // deg/sec

#define max_track_velocity 0.068 // deg/sec.
#define min_track_velocity -0.068 // deg/sec
    
#define max_acceleration 1.0 // deg/sec^2
#define min_acceleration -1.0 // deg/sec^2
    
#define max_position 90.0 // deg/sec
#define min_position -90.0 // deg/sec
    
class sharedInfo {
    public:
        Rotator rotator;    
        bool stop=false;
        char *position_topic;
} ;


#ifdef __cplusplus
}
#endif

#endif /* SHAREDINFO_H */

