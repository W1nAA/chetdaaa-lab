#include <stdio.h>
#include <string.h>

typedef struct
{
    char portfolioId[10];
    double riskScore;
} Portfolio;

void swapport(Portfolio *a, Portfolio *b)
{
    Portfolio temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Portfolio portfolios[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && portfolios[left].riskScore < portfolios[smallest].riskScore)
        smallest = left;

    if (right < n && portfolios[right].riskScore < portfolios[smallest].riskScore)
        smallest = right;

    if (smallest != i)
    {
        swapport(&portfolios[i], &portfolios[smallest]);
        heapify(portfolios, n, smallest);
    }
}

void heapSort(Portfolio portfolios[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(portfolios, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swapport(&portfolios[0], &portfolios[i]);
        heapify(portfolios, i, 0);
    }
}

int main()
{
    Portfolio portfolios[] = {
        {"PF01", 45.2},
        {"PF02", 91.8},
        {"PF03", 12.5},
        {"PF04", 78.3}};
    int n = 4;

    heapSort(portfolios, n);

    printf("Output หลังจัดเรียง (Highest -> Lowest):\n");
    for (int i = 0; i < n; i++)
    {
        printf("[%s: %.1f] ", portfolios[i].portfolioId, portfolios[i].riskScore);
    }
    return 0;
}