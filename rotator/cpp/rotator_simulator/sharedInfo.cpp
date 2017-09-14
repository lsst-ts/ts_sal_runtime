/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sharedInfo.cpp
 * Author: Andres Anania
 * 
 * Created on May 12, 2017, 9:36 AM
 */

#include "sharedInfo.h"

sharedInfo::sharedInfo() {
    this->stop = false;
    this->position_topic = "rotator_Position";
    this->rotator = Rotator();
    pthread_mutex_init(&this->sharedInfoMutex, NULL);       
}

sharedInfo::sharedInfo(const sharedInfo& orig) {
}

sharedInfo::~sharedInfo() {
    pthread_mutex_destroy(&this->sharedInfoMutex);
}

void sharedInfo::setStop(bool stop){
    pthread_mutex_lock(&this->sharedInfoMutex);
    this->stop = stop;
    pthread_mutex_unlock(&this->sharedInfoMutex); 
}
bool sharedInfo::getStop(){
    pthread_mutex_lock(&this->sharedInfoMutex);
    bool stop = this->stop;
    pthread_mutex_unlock(&this->sharedInfoMutex); 
    return stop;
}

void sharedInfo::setPositionTopic(char *position_topic){
    pthread_mutex_lock(&this->sharedInfoMutex);
    this->position_topic = position_topic;
    pthread_mutex_unlock(&this->sharedInfoMutex);
}
char *sharedInfo::getPositionTopic(){
    pthread_mutex_lock(&this->sharedInfoMutex);
    char *position = this->position_topic;
    pthread_mutex_unlock(&this->sharedInfoMutex);
    return position;
}

Rotator sharedInfo::getRotator(){
    return this->rotator;
}