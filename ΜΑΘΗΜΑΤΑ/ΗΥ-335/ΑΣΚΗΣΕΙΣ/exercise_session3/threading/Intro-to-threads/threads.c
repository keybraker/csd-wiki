#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//compile requires -pthread param

	

/* Simple thread program. Main creates 2 threads which count to FF and 	  waits for the threads to terminate before main terminating itself.
   Special functions to note
   -------> Mutexes
   -------> thread_join
*/

//threads array
pthread_t tid[2];
//mutex lock variable
pthread_mutex_t lock;

//global variable: Shared among all threads!! Watch out when using it!
//same applies when a passing as argument a pointer  value , struct
int counter;

//thread function
void* doSomeThing(void *arg)
{
	// Local variables having different memory for each thread 
    unsigned long i = 0;
    int thread_name;

    // LOCK needed cause the global variable is modified
    // ONLY 1 thread allowed in here.
    // First thread which comes takes the LOCK
	pthread_mutex_lock(&lock);	
    counter += 1;
    thread_name = counter;
    pthread_mutex_unlock(&lock);
    // UNLOCK
    // Release the LOCK after modifying the global var so that other threads can access this space
    
	printf("\n Job %d started\n", thread_name);
    for(i=0; i<(0xFFFFFFFF);i++);
    printf("\n Job %d finished\n", thread_name);
    return NULL;
    //thread terminates after using a return or reaching the end of this function 
}

int main(void){
    int i = 0;
    int err;
    // initiallize the lock
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    //create 2 threads
    while(i < 2)
    {
	// pthread_create(&Thread_var, NULL, &&Thread_function, &Thread_args);
	// Thread function takes onl 1 argument. Want to pass multiple? pass a struct!	
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
    // join may also be done in a while loop
    pthread_join(tid[0], NULL);	  //Force main to wait for thread tid[0]. Only when thread finishes main may continue after this point
    pthread_join(tid[1], NULL);	  //Force main to wait for thread tid[1].
    pthread_mutex_destroy(&lock); //Destroy --> Free the lock after serving its purpose
    printf(" main exiting\n");
    return 0;
}
