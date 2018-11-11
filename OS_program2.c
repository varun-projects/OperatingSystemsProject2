/*
Author 
 
   Varum Garg   : varun_garg@student.uml.edu 
  
Date              : 03/18/2018
Course            : Operating Systems (Spring 2018)
File Name         : OS_program2.c , main program2 file 
Code Version      : 1.00 Beta final

*/



#include "prod_cons_MT.h"

// ------ extenral and global variables and structs
int PROD_NUM, CONS_NUM=0;
int BUFFER_SIZE;
queue Queue;               






// ================== Main Loop =======================
int main ( int argc, char *argv[]) {

    int FD =0;
    int lastID,cons_i,prod_i,P_i,C_i, I=0;  // for loop counters
    PROD_NUM  = atoi(argv[2]);              // user inputs Producer, Consumer and Queue size 
    CONS_NUM  = atoi(argv[3]);
    BUFFER_SIZE = atoi(argv[1]);
  

 
    init(&Queue , (size_t)BUFFER_SIZE) ;    // initialige global struct 
    math_buff(BUFFER_SIZE*2,CONS_NUM );     // math functions -- distribute data to given consumer threads  

    printf("Buffer Size: %d ", BUFFER_SIZE);                           // debugging 
    printf("Producers: %d , Consumers: %d\n\n", PROD_NUM, CONS_NUM);   // debugging 
   
    // Initialize thread IDs
    pthread_t ConsumerID[CONS_NUM];
    pthread_t ProducerID[PROD_NUM];
 


    for(prod_i=0; prod_i<PROD_NUM; prod_i++){
       
       printf("Main: started producer %d\n",prod_i);
       sleep(0.5);                                                                // for simulating real delay scenarios 
       FD = pthread_create( &ProducerID[prod_i], NULL, Producer_thread, &prod_i); // create producer threads 
       if(FD!=0){ perror("Failed producer Thread Creation"); exit(EXIT_FAILURE); } // Failure checker for failed thread action
    }
  
   // ----------  Create Thread  --------------------------
   for(cons_i=0; cons_i<(CONS_NUM-1); cons_i++){

        printf("Main: started consumer %d\n",cons_i);
        FD = pthread_create( &ConsumerID[cons_i], NULL, Consumer_thread, &cons_i);  // create consumer threads 
        if(FD!=0){ perror("Failed consumer Thread Creation"); exit(EXIT_FAILURE); } // Failure checker for failed thread action
        sleep(0.5);                                                                 // delay , give some to time to each thread to be created 
    }
        sleep(0.5);  
        lastID = CONS_NUM-1;                                       					// last consumer thread with different loop times
        printf("Main: started consumer %d\n",lastID);
        FD = pthread_create( &ConsumerID[lastID], NULL, Consumer_thread, &lastID);  // create hte last consumer thread that takes care the remaining data in the Queue
        if(FD!=0){ perror("Failed consumer Thread Creation"); exit(EXIT_FAILURE); }
        

  
   // ----------  Thread Finished  -------------------------
     for(int P_i=0; P_i<PROD_NUM; P_i++){
        printf("joined loop %d\n ",P_i);
       FD = pthread_join(ProducerID[P_i], NULL);                                          // wait for each consumer thread to be joined
       if(FD!=0){ perror("Failed producer Thread to Join"); exit(EXIT_FAILURE); }
       printf("MAIN: producer %d joined\n", P_i);
    }


      for(C_i=0; C_i<CONS_NUM; C_i++){
       FD = pthread_join(ConsumerID[C_i], NULL);                                         // wait for each consumer thread to be joined
       if(FD!=0){ perror("Failed consumer Thread to Join"); exit(EXIT_FAILURE);}
       printf("MAIN: consumer %d joined\n", C_i);
    }

 
    free(Queue.dataSpace);         // release memory back to the system
    pthread_exit(NULL);            // exits remaining threads
 

    // ------ end of main code ------
    printf("Main: Program Completed\n");

  return 0;
}







