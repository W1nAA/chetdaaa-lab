#include <stdio.h>

int max(int a, int b){
    if(a > b){
        return a;
    }else return b;
}

int main(){
    int n;
    scanf("%d",&n);

    int x[n];
    int dp_true[n];
    int dp_false[n];

    for(int i=0; i < n; i++){
        scanf("%d", &x[i]);
        dp_true[i] = 1;
        dp_false[i] = 1;
    }

    for(int i=0; i < n; i++){
        for(int j=0; j < i; j++){
            if(x[j] < x[i]){
                dp_true[i] = max(dp_true[i],dp_false[j] + 1);
            } else if(x[j] > x[i]){
                dp_false[i] = max(dp_false[i],dp_true[j] + 1);
            }
        }
    }

    for(int i=0; i < n; i++){
        printf("%d ",dp_true[i]);
    }
    printf("\n");

    for(int i=0; i < n; i++){
        printf("%d ",dp_false[i]);
    }
    printf("\n");
} 