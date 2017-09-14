/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rotator.cpp
 * Author: saluser
 * 
 * Created on May 11, 2017, 12:30 PM
 */

#include "Rotator.h"


#include <stdio.h>

Rotator::Rotator() {
    pthread_mutex_init(&rotator_mutex, NULL);
    pthread_mutex_lock(&rotator_mutex);
    for(int i=0;i<50;i++) { this->position[i] = -150.0; }
    pthread_mutex_unlock(&rotator_mutex);
}

Rotator::Rotator(const Rotator& orig) {
}

Rotator::~Rotator() {
    pthread_mutex_destroy(&this->rotator_mutex);
}

void Rotator::initRotator(){
    pthread_mutex_lock(&rotator_mutex);
    this->position[0] = -150.0;
    pthread_mutex_unlock(&rotator_mutex);
}

double Rotator::getPosition(){
    pthread_mutex_lock(&rotator_mutex);
    double pos = this->position[0];
    pthread_mutex_unlock(&rotator_mutex);
    return pos;
}

bool Rotator::setPosition(double position){
    pthread_mutex_lock(&rotator_mutex);
    int n = 50;
    if(this->position[n-1]==-150){
        for(int i=0; i<n; i++)
            this->position[i]=position;
    }else{
        for(int i=1; i < 50; i++){
            this->position[i]=this->position[i-1];
        }
        this->position[0]=position*0.001+this->position[0]*0.999;
        
    }
    printf("command_received: angle=%lf\n", this->position[0]);
    pthread_mutex_unlock(&rotator_mutex);

    return true;
}