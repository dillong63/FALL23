/* Dillon Geary */
#include "AirportAnimator.hpp"
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include<pthread.h>
#include<sys/sem.h>
#include<sys/ipc.h>//for a key from system;
#define NUM_SEMS 1
using namespace std;

int sem_idrun, sem_idpas;
struct sembuf command[1]; //sembuf for runway
struct sembuf commandpas[1]; //sembuf for passengers
pthread_t thr[8];
int tours;
int ic=0;

void* run(void *arg){
    int *pln = (int*) arg;
    while(tours>0){
        tours--;
        for(int i=1;i<13;i++){//board passengers
            commandpas[0].sem_num = 0;
            commandpas[0].sem_op = -1;//one less available passenger makes planes wait for more if not enough
            commandpas[0].sem_flg = 0;
            semop(sem_idpas,commandpas,1);
            AirportAnimator::updatePassengers(*pln, i);
            sleep(rand()%3);
        }
        AirportAnimator::updateStatus(*pln, "TAXI");
        AirportAnimator::taxiOut(*pln);

        command[0].sem_num =0;
        command[0].sem_op =-1;
        command[0].sem_flg =0;
        semop(sem_idrun,command,1);//request to use the runway
        AirportAnimator::updateStatus(*pln, "TKOFF");
        AirportAnimator::takeoff(*pln);
        command[0].sem_num =0;
        command[0].sem_op =+1;
        command[0].sem_flg =0;
        semop(sem_idrun,command,1);// frees up the runway
        AirportAnimator::updateStatus(*pln,"TOUR");
        sleep(15+rand()%30);
        AirportAnimator::updateStatus(*pln,"LNDRQ");
        command[0].sem_num =0;
        command[0].sem_op =-1;
        command[0].sem_flg =0;
        semop(sem_idrun,command,1);//requests to use runway
        AirportAnimator::updateStatus(*pln,"LAND");
        AirportAnimator::land(*pln);
        command[0].sem_num =0;
        command[0].sem_op =+1;
        command[0].sem_flg =0;
        semop(sem_idrun,command,1);//frees up runway for others to use

        AirportAnimator::updateStatus(*pln, "TAXI");
        AirportAnimator::taxiIn(*pln);

        AirportAnimator::updateStatus(*pln, "DEPLN");
        for(int passenger=11; passenger>=0; passenger--)
        {
            commandpas[0].sem_num = 0;
            commandpas[0].sem_op = +1;
            commandpas[0].sem_flg = 0;
            semop(sem_idpas,commandpas,1); //adds passenger back to pool
            AirportAnimator::updatePassengers(*pln, passenger);
            sleep(1);
        }
    
        AirportAnimator::updateStatus(*pln, "DEPLN");
        ic++;
        AirportAnimator::updateTours(ic);
        if(tours<=0){
            AirportAnimator::updateStatus(*pln, "DONE"); //if done update status
        }
        
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    if((argc!=3)){
        cerr<<"Not enough arguments";;
        return -1;
    }
    int *plane;
    tours=atoi(argv[2]);
    sem_idpas=semget(IPC_PRIVATE,NUM_SEMS,IPC_CREAT|IPC_EXCL|0666);//create sem for runway
    sem_idrun=semget(IPC_PRIVATE,NUM_SEMS,IPC_CREAT|IPC_EXCL|0666);//create sem forr passengers
    if (sem_idpas ==-1||sem_idrun ==-1){
        cerr<<"ERROR";
        return -1;
    }
    semctl(sem_idpas,0,SETVAL,atoi(argv[1]));//set sem to num passengers
    semctl(sem_idrun,0,SETVAL,1);//set sem to 1 for runway
    AirportAnimator::init();
    for(int i=0;i<8;i++) //creates thread
    {
        plane = new int(i);
        pthread_create(&thr[i-1],NULL,run,(void *) plane);
    }
    for(int i=0;i<8;i++)//joins threads
    {
        pthread_join(thr[i-1],NULL);
    }
    AirportAnimator::end();
    return 0;
}
