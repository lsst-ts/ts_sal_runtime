/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Andres Anania
 *
 * Created on May 11, 2017, 9:36 AM
 */

#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "sharedInfo.h"
#include "rotator/Rotator.h"
#include "rotatorTrackSubscriber.h"
#include "rotatorPositionDataPublisher.h"

using namespace std;

void commandLine(sharedInfo *thread_var);

/*
 * Main function
 */
int main(int argc, char** argv) {
    
    //Variables definition
    float dt = 1/20; //20 Hz
    sharedInfo *rotatorShrd = new sharedInfo(); //Variable to share rotator between different threads
    
    pthread_t subscriberThread;
    pthread_t publisherThread;
    
    //Starting subscriber thread for the tracking command
    int iret1 = pthread_create( &subscriberThread, NULL, test_rotator_track_controller, (void*) rotatorShrd);
    if(iret1){
        cout << "Error initializing the tracking command subscriber" << endl;
        rotatorShrd->setStop(true);
        exit(EXIT_FAILURE);
    }
    
    //Starting publisher thread for the position
    
    int iret2 = pthread_create( &publisherThread, NULL, SALTelemetryPublisher, (void*) rotatorShrd);
    if(iret2){
        cout << "Error initializing the tracking command subscriber" << endl;
        rotatorShrd->setStop(true);
        exit(EXIT_FAILURE);
    }
    
    commandLine(rotatorShrd); //Command line to interact with the user
    
    pthread_join(subscriberThread, NULL);
    pthread_join(publisherThread, NULL);
    //pthread_exit(NULL); 
    
    cout << "==== Simulator closed successfully ====" << endl;
    return 0;
}

/*
 * Command line to interact with the user
 */
void commandLine(sharedInfo *thread_var){
    
    cout << "==== Rotator simulator running ====" << endl;
    
    //Terminal to interact with the application
    string user_input;
    cout << "==== Commands ====" << endl << endl;
    for(int i=0; i<20; i++){
        cout << "Execute any of this commands:" << endl;
        cout << "   exit: close the application " << endl;
        cout << "   help: show the commands " << endl;
        cout << endl;
        cout << ">>";
        cin >> user_input; //Wait for input to close application
        cout << endl;
        if(user_input == "exit"){ 
            cout << "==== Closing simulator ====" << endl;
            thread_var->setStop(true);
            break; 
        }else if(user_input == "help"){
            continue;
        }
        else { 
            cout << "Command "  << user_input << " not valid, try again:" << endl ;
        }
    } 
}