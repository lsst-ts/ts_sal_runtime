/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rotator.h
 * Author: Andres Anania
 *
 * Created on May 11, 2017, 12:30 PM
 */

#ifndef ROTATOR_H
#define ROTATOR_H

#include <pthread.h>

class Rotator {
public:
    Rotator();
    Rotator(const Rotator& orig);
    virtual ~Rotator();
    
    
    void initRotator();
    
    bool calculateMotion(); //Calculate Velocity and Acceleration based on the position
    
    bool setVelocity(double velocity);
    double getVelocity();
    
    bool setAcceleration(double acceleration);
    double getAcceleration();
    
    bool setPosition(double position);  //This will be used for the first algorithm (second order digital filter). When having a more real kinematics model it should be deleted.
    double getPosition();
    
    bool setTai(double tai);
    double getTai();
    
    unsigned int executeCmd(double cmdPosition, double cmdVelocity, double cmdTai); //Execute commands received
    
private:
    
    double position[50]; //In degrees
    double velocity[5]; //In degress/sec
    double acceleration[5]; //In degress/sec^2
    double tai[5];
    pthread_mutex_t rotator_mutex;
    
};

#endif /* ROTATOR_H */

