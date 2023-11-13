/* Dillon Geary 2023/10/03 
Shell outline by Dr. Blythe*/


#include <iostream>
#include <csignal>
#include<string>
#include <unistd.h>
#include<cstring>
#include "Command.hpp"
#include <sys/wait.h>
#include <cstdio>
#include<sys/types.h>
#include<signal.h>


void signalHandler(int sigNum)
{
    cout<<"Completed: PID= "<< getpid()<< " : "<< endl;
}

int main(void)
{
    Command com;
    int num=1; // keep track of number fo commands. 
    
    // prompt for and read in first command. 
    cout << ">>>> ";
    com.read();
    sigset_t block_set; //next 3 lines is for handling backgrounded programs while running non backgrounded programs.
    sigemptyset(&block_set);
    sigaddset(&block_set,SIGCHLD);
    while(com.name() != "exit")
    {

        if(com.pipeOut())// if it need to be piped
        {
            string s;
            int cnt =0;
            int pid = fork();         
            if(pid!=0){
            if(!com.backgrounded()){//if it is not backgrounded
                if(sigprocmask(SIG_BLOCK, &block_set,NULL)==-1){ /// block all interrupts to not cause an interrupt from this function
                    perror("sigprocmask");
                    return 1;
                }
                waitpid(pid,NULL,0); //wait for child to execute
                }
            else{
                if(sigprocmask(SIG_UNBLOCK, &block_set,NULL)==-1){//enable intterupt for this child
                    perror("sigprocmask");
                    return 1;
                }
                signal(SIGCHLD,signalHandler);
            }
            }
            else{
                int pipeInfo[2], inFi = 0 ;
                cout << num++ << ")" << com ;
                while(com.pipeOut()){// while I am piping commands
                    int myPipe= pipe(pipeInfo); //create the pipe
                    int pid1= fork(); //create a child to execute
                    if (pid1==0){ //if I am the child
                        if(inFi != 0){ // I am not stdin
                            dup2(inFi,fileno(stdin)); //change input to this file
                            close(inFi); //close it
                        }
                        if( pipeInfo[1] != 1){//if not stdout
                            dup2(pipeInfo[1],fileno(stdout)); //change output to the info
                            close(pipeInfo[1]);
                        }
                    char* *args=new char*[com.numArgs()+1];// build a char array for the execution
                    for(int i=0; i<com.numArgs();i++){
                        args[i]=new char[com.args()[i].length()+1];
                        args[i]=strcpy(args[i],com.args()[i].c_str());
                    }
                    args[com.numArgs()]=NULL;
                    execvp(args[0],args);//execute this instruction
                    }
                    close(pipeInfo[1]);
                    inFi=pipeInfo[0]; //save the old one for the next one if more pipes
                    com.read();
                    cout<<com;
                }
                cout<<endl;
                if(inFi!=0) 
                    dup2(inFi,0);

                char* *args=new char*[com.numArgs()+1];
                for(int i=0; i<com.numArgs();i++){
                    args[i]=new char[com.args()[i].length()+1];
                    args[i]=strcpy(args[i],com.args()[i].c_str());
                }
                args[com.numArgs()]=NULL;
                execvp(args[0],args);
            }     
        }
        else{
            cout << num++ << ")" << com << endl;
            int pid = fork();
            if(pid!=0){ //same is up there
            if(!com.backgrounded()){
                if(sigprocmask(SIG_BLOCK, &block_set,NULL)==-1){
                    perror("sigprocmask");
                    return 1;
                }
                waitpid(pid,NULL,0);
                }
            else{
                if(sigprocmask(SIG_UNBLOCK, &block_set,NULL)==-1){
                    perror("sigprocmask");
                    return 1;
                }
                signal(SIGCHLD,signalHandler);
            }
            }
            else{
                if(com.redirIn()){//redirect file out
                    FILE *fp1 = fopen(com.inputRedirectFile().c_str(),"r");
                    dup2(fileno(fp1),fileno(stdin));
                }
                if(com.redirOut()){//redirect file in
                    FILE *fpo = fopen(com.outputRedirectFile().c_str(),"w");
                    dup2(fileno(fpo),fileno(stdout));
                }
                if(com.name()=="cd"){ //change directories
                    chdir(com.args()[1].c_str());
                }
                else { //execute the command line
                    char* *args=new char*[com.numArgs()+1];
                    for(int i=0; i<com.numArgs();i++){
                        args[i]=new char[com.args()[i].length()+1];
                        args[i]=strcpy(args[i],com.args()[i].c_str());
                    }
                    args[com.numArgs()]=NULL;
                    execvp(args[0],args);
                }
            }       
        }
	    cout << ">>>> ";
        com.read();
    }

    cout << "Thank you for using mini-shell. We now return you to your regularly scheduled shell!" << endl;
}
