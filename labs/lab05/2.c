#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Knapsack_Exhaustive(int weights[],int values[],int N,int W){
    int max_value = 0;
    int best_mask = 0;

    long long total_N = 1LL << N; // calculate 2^N (using 2^N is 2 XOR N)
    for(long long mask = 0; mask <= total_N; mask++){
        int current_weight = 0;
        int current_value = 0;

        for(int i = 0; i < N; i++){
            if((mask >> i) & 1){
                current_weight = current_weight + weights[i];
                current_value = current_value + values[i];
            }
        }

        if (current_weight <= W && current_value > max_value)
        {
            max_value = current_value;
            best_mask = mask;
        }
    }
    printf("N = %2d | Max Value = %d\n",N ,max_value);
    printf("Best mask : %d\n",best_mask);
}


int main(){
    int N_Values[] = {10, 15, 20, 22, 25, 28, 30};
    int total_test = 7;

    int weights[30];
    int values[30];

    for(int t = 0; t < total_test; t++){
        int N = N_Values[t];
        int W = N * 5;

        srand(42);
        for (int i = 0; i < N; i++){
            weights[i] = (rand() % 20) + 1; // random weight from 1-20
            values[i] = (rand() % 90) + 10; // random value from 10-90
        }

        clock_t start = clock();
        Knapsack_Exhaustive(weights,values,N,W);
        clock_t end = clock();

        double second = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Time used: %.4f second\n\n",second);
    }
    
}