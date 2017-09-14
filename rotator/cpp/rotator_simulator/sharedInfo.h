/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sharedInfo.h
 * Author: saluser
 *
 * Created on May 12, 2017, 9:36 AM
 */

#ifndef SHAREDINFO_H
#define SHAREDINFO_H

#include "rotator/Rotator.h"

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
    sharedInfo();
    sharedInfo(const sharedInfo& orig);
    virtual ~sharedInfo();
    void setStop(bool stop);
    bool getStop();
    void setPositionTopic(char *position_topic);
    char *getPositionTopic();
    
    Rotator getRotator();
    
private:
    Rotator rotator;    
    bool stop;
    char *position_topic;
    pthread_mutex_t sharedInfoMutex;
};

#endif /* SHAREDINFO_H */

