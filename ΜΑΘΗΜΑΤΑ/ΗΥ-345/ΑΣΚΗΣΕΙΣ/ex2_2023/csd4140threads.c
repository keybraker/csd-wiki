#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//----------------------------*
//  Antonia Krasoudaki        |
//  csd4140                   |
//----------------------------*

int study_room[8];
int *wait_room[40];
int study_time;
int students_studied=0; 
int entered_study=0;
pthread_mutex_t mutex;
pthread_cond_t condEnter; 
int thread_num;

void print_study() {
    printf("\033[0;36mStudy room :  \033[0m");
    for (int i = 0; i < 8; i++) {
        printf("|  %d  ", study_room[i]);
    }
    printf("|\n");

}

void print_waiting(){
    int i=0;
    printf("\033[0;35mWaiting room : \033[0m ");

   while(wait_room[i] != NULL){
     printf("|  %d  ", *wait_room[i]);
            i++;
        }

    printf("|\n\n");
}

void fill_study(int student_id) {

    for (int i = 0; i < 8; i++) {
        if (study_room[i] == -1) {
            study_room[i] = student_id;
            entered_study++;
            return;
        }
    }
}

void fill_waiting(int student_id){
int i = 0;

    while (i < 40) {
        if (wait_room[i] == NULL) {
            wait_room[i] = malloc(sizeof(int)); 
            *wait_room[i] = student_id;
            return;
        }
        i++;
    }

}

void free_waiting(){
    int i = 0;

    if (wait_room[0] == NULL) { return; }

    free(wait_room[0]); 

    while (wait_room[i] != NULL) {
        wait_room[i] = wait_room[i + 1];
        i++;
    }
    
}


int is_study_empty(){
    int i,j=0;
    for( i = 0; i <8 ; i++){
        if(study_room[i]==-1){
            j++;
        }
    }
    if(i==j){
        return 1;
    }else {
        return 0;
    }
}

void free_study(int student_id) {
    for (int i = 0; i < 8; i++) {
        if (study_room[i] == student_id) {
            study_room[i] = -1;
            if(is_study_empty()==1){
                entered_study=0;
             }
        }
    }
}

void* routine(void *args) {

    pthread_mutex_lock(&mutex); 

     printf("\nStudent  %d was born \n", *(int*)args);

      while(entered_study>7 ){

        fill_waiting(*(int*)args);
        printf("\033[0;31mStudent %d can't enter study hall. It's full. \n \n\033[0m",*(int*)args);
         print_study();
         print_waiting();
        // If the study room is full, wait 
        pthread_cond_wait(&condEnter, &mutex);   

        }

    fill_study(*(int*)args);
    sleep(2);
    
    print_study();
    print_waiting();
    
    pthread_mutex_unlock(&mutex); 

   study_time = (5 + rand() % 11); // Simulate studying
   sleep(study_time);
   printf("\n Student %d finished studying after %d secs. \n ", *(int*)args  , study_time);

    pthread_mutex_lock(&mutex); // Lock the mutex for leaving the study room
    free_study(*(int*)args);
    

    students_studied++;
          if(entered_study==0){
            //if room is empty signal condition to stop waiting
                  for(int i=0 ; i < 8 ; i++){
                    sleep(2);
                    free_waiting();
                    pthread_cond_signal(&condEnter); 
                    sleep(2);        
                }  
          }

        pthread_mutex_unlock(&mutex); // Unlock the mutex for leaving
               
   if(students_studied==thread_num){
    printf("\nRooms after all students have studied : \n");
    print_study();
    print_waiting();
    exit(0);
   }

    free(args);
}

int main(int argc, char* argv[]) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condEnter, NULL);

    for (int j = 0; j < 8; j++) {
        study_room[j] = -1;
    }

    printf("Please enter the number of students that want to study\n");
    scanf("%d", &thread_num);

    if (thread_num < 20 || thread_num > 40) {
        printf("Error: invalid number of students\n");
        exit(0);
    }

    pthread_t* th = (pthread_t*)malloc(thread_num * sizeof(pthread_t));

    for (int i = 0; i < thread_num; i++) {
        int *a = malloc(sizeof(int));
        *a = i+1;

        if (pthread_create(th + i, NULL, &routine, a) != 0) {
            perror("Failed to create thread");
            return 1;
        }

        sleep(1);
       
    }

    for (int i = 0; i < thread_num; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condEnter);
    return 0;
}
