#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Program which creates 5 threads which count to 20.000 each.
// The final output should be 100.000 but since the user forgot
//  to add locks the output is might be incorrect

// threads
pthread_t tid[5];
// mutex lock
pthread_mutex_t lock;
// global variable: Shared among all threads!! Watch out when using it
int counter;

void *doSomeThing(void *arg)
{
    // each thread has its own local i variable
    int i;
    // add the lock and unlock to fix the problem

    // pthread_mutex_lock(&lock);
    for (i = 1; i <= 20000; i++)
    {
        counter++;
    };
    // pthread_mutex_unlock(&lock);
    printf("Thread finished counter %d\n", counter);
    return NULL;
}

int main(void)
{
    int i = 0;
    int err;
    counter = 0;

    // initiallize the lock
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    // create 2 threads
    while (i < 5)
    {
        // pthread_create(&Thread_var, NULL, &&Thread_function, &Thread_args);
        // Thread function takes onl 1 argument. Want to pass multiple pass a struct!
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }

    // join can be done in a while loop
    for (i = 0; i < 5; i++)
    {
        pthread_join(tid[i], NULL); // Force main to wait for thread i
        printf("thread %d finished\n", i);
    }
    pthread_mutex_destroy(&lock); // Destroy --> Free the lock after serving its use
    printf("Main finished counter value %d == 100000?\n", counter);

    return 0;
}
