#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//to control the chopsticks and philosophers
pthread_mutex_t chopsticks[5];
pthread_t philosophers[5];

void *philosopher(void *);
void think(int);
void grabChopstik(int);
void eatTheDinner(int);
void dropChopstick(int);
void even(int);
void odd(int );

//Philosopher Function
//Input (Integer)
//This part control all functions with this order
void *philosopher(void *philosopherNumber) {
    while (1) {
        think(philosopherNumber);
        grabChopstik(philosopherNumber);
        eatTheDinner(philosopherNumber);
        dropChopstick(philosopherNumber);
    }
}
//Think function
//Input (Integer)
//give a time to philosophers to think
void think(int numberOfPhilosopher){
    //can create a waiting time from 2 to 6
    int waitingTime =  2 + rand()%4;
    printf("The %d.Philosopher is THINKING for %d second.\n",numberOfPhilosopher , waitingTime );
    sleep(waitingTime);
    
}

//Grabchopstick Function
//Input (Integer)
//controls the chopsticks and help to grab a chopstick with controlling the number of philosopher
void grabChopstik(int numberOfPhilosopher ){
    //number of the left stick
    int leftChopstick = (numberOfPhilosopher + 1) % 5;
    //number of the right stick
    int rightChopstick = numberOfPhilosopher;

    //to control wheter even or odd
    if(numberOfPhilosopher % 2 == 0){
        //if even philoshoper firt right stick and then left
        even(numberOfPhilosopher);
        
    }
    else if(numberOfPhilosopher % 2 == 1){
        //if odd philoshoper firt left stick and then right
        odd(numberOfPhilosopher);
           }
    
}

//Even function
//Input (Integer)
//IF the  philosopher number is even to grab the chopstick
void even(int numberOfPhilosopher) {
    
    int leftChopstick = (numberOfPhilosopher + 1) % 5;
    //number of the right stick
    int rightChopstick = numberOfPhilosopher;
    
    printf("The %d.Philosopher is WAITING to grab the chopstick %d\n", numberOfPhilosopher, rightChopstick);
    pthread_mutex_lock(&chopsticks[rightChopstick]);
    printf("The %d.Philosopher GRABBED chopstick %d\n", numberOfPhilosopher, rightChopstick);
    printf("The %d.Philosopher is WAITING to pick up chopstick %d\n", numberOfPhilosopher, leftChopstick);
    pthread_mutex_lock(&chopsticks[leftChopstick]);
    printf("The %d.Philosopher GRABBED chopstick %d\n", numberOfPhilosopher, leftChopstick);

    
}
//Odd Funciton
//Input (Integer)
//IF the  philosopher number is odd to grab the chopstick
void odd(int numberOfPhilosopher){
    int leftChopstick = (numberOfPhilosopher + 1) % 5;
    //number of the right stick
    int rightChopstick = numberOfPhilosopher;

    printf("The %d.Philosopher is WAITING to grab the chopstick %d\n", numberOfPhilosopher, leftChopstick);
    pthread_mutex_lock(&chopsticks[leftChopstick]);
    printf("The %d.Philosopher GRABBED the chopstick %d\n", numberOfPhilosopher, leftChopstick);
    printf("The %d.Philosopher is WAITING to grab the chopstick %d\n", numberOfPhilosopher, rightChopstick);
    pthread_mutex_lock(&chopsticks[rightChopstick]);
    printf("The %d.Philosopher GRABBED the chopstick %d\n", numberOfPhilosopher, rightChopstick);

}
//eatTheDinner Function
//Input (Integer)
//to give a time while eating
void eatTheDinner(int numberOfPhilosopher){
    //can create a waiting time from 2 to 6
    int waitingTime = 2 + rand()%4;
    printf("The %d.Philosopher is EATING for %d second.\n",numberOfPhilosopher , waitingTime );
    //to wait a few second
    sleep(waitingTime);
}

//dropChopstick Function
//Input (Integer)
//to gave back the chopsticks
//It helps to unlock the mutex
void dropChopstick(int numberOfPhilosopher) {
    //leaving the fork after eating the fork
    printf("The %d.Philosopher GAVE BACK the chopstick\n", numberOfPhilosopher);
    //number of the left stick
    int leftChopstick = (numberOfPhilosopher + 1) % 5;
    //number of the right stick
    int  rightChopstick = numberOfPhilosopher;
    
    //to go out from the critical section
    pthread_mutex_unlock(&chopsticks[leftChopstick]);
    pthread_mutex_unlock(&chopsticks[rightChopstick]);
}


int main() {
    int j;
    for (j = 0; j < 5; ++j) {
        /*This part initialize the mutex for each chopstick*/
        /*birinci parametresi mutex nesnesinin adresi, ikinci parametresi mutex
        ozelliklerinin degerlerine iliskin yapinin adresidir*/
        pthread_mutex_init(&chopsticks[j], NULL);
    }
    
    
    for (j = 0; j < 5; ++j) {
        /*   create  fonksiyonu  ile  yeni  bir  thread  olusturup  bu  thread  calistirilabilir hale getirilir.
         İlk parametre: pthread_t tip adresidir.
         İkinci parametre: yeni thread in icermesini istedigimiz belli nitelikleri icerebilir. oncelik vb.
         ucuncu parametre: bir fonksiyon isaretcisidir. Her thread bir fonksiyon baslatir. Bu parametre (fonksiyon adresi) ile kernel, thread in hangi fonksiyonu baslattigini bilir.
         dorduncu parametre: void tipinde bir isaretcidir. Bu pointer ile fonksiyon birden fazla parametre kabul edebilir.*/
        pthread_create(&philosophers[j], NULL, philosopher, (void *)(j));
    }
    
    /*Threadler  arasi  senkronizasyon  için pthread_join(..)  fonksiyonu  kullanilir
    parametre  olarak  ilgili  threadin  ID’si  verilir*/
    for (j = 0; j < 5; ++j) {
        pthread_join(philosophers[j], NULL);
    }
    return 0;
}


