#include <stdio.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int main() {
    int n;
    scanf("%d", &n);

    int B[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    int dp[n + 1];
    dp[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        int skip = dp[i + 1];
        
        int take = (int)B[i] + 1; 
        
        int next_idx = i + B[i] + 1; 
        
        if (next_idx < n) {
            take += dp[next_idx];
        }
        
        dp[i] = max(skip, take);
    }

    printf("%d\n", dp[0]);

    return 0;
}