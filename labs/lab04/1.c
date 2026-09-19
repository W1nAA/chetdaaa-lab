#include <stdio.h>

typedef struct {
    char portfolioId[10];
    double riskScore;
} Portfolio;

void swapPortfolio(Portfolio *a, Portfolio *b)
{
    Portfolio temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Portfolio portfolios[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n &&
        portfolios[left].riskScore > portfolios[largest].riskScore)
    {
        largest = left;
    }

    if (right < n &&
        portfolios[right].riskScore > portfolios[largest].riskScore)
    {
        largest = right;
    }

    if (largest != i)
    {
        swapPortfolio(&portfolios[i], &portfolios[largest]);
        heapify(portfolios, n, largest);
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
        swapPortfolio(&portfolios[0], &portfolios[i]);
        heapify(portfolios, i, 0);
    }
}

int main()
{
    int n;
    int i;

    printf("Enter number of portfolios: ");
    scanf("%d", &n);

    Portfolio portfolios[n];

    printf("Enter portfolio ID and risk score:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s %lf",
              portfolios[i].portfolioId,
              &portfolios[i].riskScore);
    }

    heapSort(portfolios, n);

    printf("\nSorted portfolios:\n");

    for (i = 0; i < n; i++)
    {
        printf("%s %.1f\n",
               portfolios[i].portfolioId,
               portfolios[i].riskScore);
    }

    return 0;
}