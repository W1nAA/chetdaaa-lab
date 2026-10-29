#include <stdio.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int main()
{
    int n, T;

    scanf("%d %d", &n, &T);

    int t[n + 1];
    int v[n + 1];
    int dp[n + 1][T + 1];

    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &t[i], &v[i]);
    }

    for (int w = 0; w <= T; w++)
    {
        dp[0][w] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= T; w++)
        {
            if (t[i] > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                dp[i][w] = max(
                    dp[i - 1][w],
                    dp[i - 1][w - t[i]] + v[i]
                );
            }
        }
    }

    printf("%d\n", dp[n][T]);

    return 0;
}