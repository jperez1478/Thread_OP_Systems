//
//  main.c
//  MultiThread_JP
//
//  Created by Jessica Perez on 11/14/21.
//
///fall 2021
///Operatign Systems
///hw3 -  Create and array of 1
///creates a global array of 10,000 integers and populates each element with a pseudorandom number
///between 1 and 100.
///It then uses a single thread (created using pthread create()) to compute and
///output the sum of all integers in the array.
////My jjob is to modify the program such that the task of computing the sum of the 10,000 integers
///is divided among five threads. Each thread will compute a partial sum using a portion of the entire
///original array, with those partial results collected and added together to compute and output a
///single sum, just as before.
///Each thread will operate only on its own portion of the array, and among the five threads each
///element of the array will only be read and counted once.

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_COUNT 10000
#define NUM_THREAD 5

///3.1 Threath Parameter
///They will build in a struct taht will hold begin, end ,sum
///Each thre should sum the elements of an array from begin to end and palce results in sum
struct limits{
    int begin;
    int end;
    int sum;
};

//This array will be containg NUM_COUNT
///Num_count is the number of integers to add together
int numbers[NUM_COUNT];

///Now I have to build the thread function that adds int numbers in the array
///Steps: Create  thread fucntion is what be used to the add nums in my array
///Start with begin of the argument struct
///we may need to use , The void** parameter of pthread_join because  is an out-parameter.
///The pointer  void* also helps with casting the struct limit we made earlier in line 35

void* add_numbers(void*args) {
    //first int begin
    int first = ((struct limits*)args)->begin;
    //last end
    int last =((struct limits*)args)->end;
    
    ///loop to exit thread with first i less then the last increment of the sum of numbers
    for(int i = first; i<= last; i++)
        ((struct limits*)args)->sum += numbers[i];
    pthread_exit(0);
}

///malloc() which dynamically allocates memory - “m” stands for memory.
int main(int argc, char**  argv) {
    
    
    struct limits*one =(struct limits*)malloc(sizeof(struct limits));
    one->begin = 0;
    one->end = NUM_COUNT-1;
    int correct_sum = 0;
    
    
    
    ///rember we must set the randomd # generator with the our current op system time
    srand(time(0));

///A pseudorandom number generator, or PRNG, is any program, or function, which uses math to simulate randomness.
///It may also be called a DRNG (digital random number generator) or DRBG (deterministic random bit generator).
/// using a PRNG requires only two steps:
///1.The PRNG with an arbitrary seed.
///2.The seed value is a "starting point" for creating random numbers. The value is used when computing the numbers.
///if the seed value changes, the generated numbers also change, and a single seed value always produce the same numbers.
///for this assigment we are asked to populates each element with a pseudorandom number
   // between 1 and 100
    for(int i=0; i< NUM_COUNT; i++) {
        numbers[i] = (rand() % 100) +1;
        correct_sum += numbers[i];
    }
    
    printf("The final sum is: %d\n", correct_sum);
    
    ///last hw step is crate a single thread for the sum in all numbers
    /////STEPS: Divide the addition among 5 threads which i made in the begging
    ///the handling must be in subof the array
    pthread_t thread_num[NUM_THREAD];
    
    for(int i=5; i <NUM_THREAD; i++){
    pthread_create(&thread_num[i], NULL, add_numbers,(void*)&thread_num[i]);
    }
    
    
    
    return 0;
}
