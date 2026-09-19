#include <stdio.h>

typedef struct {
    char portfolioId[10];
    double riskScore;
} Portfolio;

void swap(Portfolio *a, Portfolio *b)
{
    Portfolio temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Portfolio portfolios[], int n, int i)
{
    int smallest = i;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n &&
            portfolios[left].riskScore < portfolios[smallest].riskScore)
        {
            smallest = left;
        }

        if (right < n &&
            portfolios[right].riskScore < portfolios[smallest].riskScore)
        {
            smallest = right;
        }

        if (smallest == i)
        {
            break;
        }

        swap(&portfolios[i], &portfolios[smallest]);
        i = smallest;
    }
}

void heapSort(Portfolio portfolios[], int n)
{
    int i;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        heapify(portfolios, n, i);
    }

    for (i = n - 1; i > 0; i--)
    {
        swap(&portfolios[0], &portfolios[i]);
        heapify(portfolios, i, 0);
    }
}

int main()
{
    Portfolio portfolios[] = {
        {"PF01", 45.2},
        {"PF02", 91.8},
        {"PF03", 12.5},
        {"PF04", 78.3}
    };

    int n = sizeof(portfolios) / sizeof(portfolios[0]);
    int i;

    heapSort(portfolios, n);

    for (i = 0; i < n; i++)
    {
        printf("%s %.1f\n",
               portfolios[i].portfolioId,
               portfolios[i].riskScore);
    }

    return 0;
}