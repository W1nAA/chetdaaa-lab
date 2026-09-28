#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char orderId[10];
    int priceInCents;
} Order;

void countingSort(Order orders[], int n) {
    if (n <= 1) return;

    int minPrice = orders[0].priceInCents;
    int maxPrice = orders[0].priceInCents;

    for (int i = 1; i < n; i++) {
        if (orders[i].priceInCents < minPrice) minPrice = orders[i].priceInCents;
        if (orders[i].priceInCents > maxPrice) maxPrice = orders[i].priceInCents;
    }

    int range = maxPrice - minPrice + 1;

    int *count = (int *)calloc(range, sizeof(int));
    Order *output = (Order *)malloc(n * sizeof(Order));

    for (int i = 0; i < n; i++) {
        count[orders[i].priceInCents - minPrice]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int pos = count[orders[i].priceInCents - minPrice] - 1;
        output[pos] = orders[i];
        count[orders[i].priceInCents - minPrice]--;
    }

    for (int i = 0; i < n; i++) {
        orders[i] = output[i];
    }

    free(count);
    free(output);
}

int main() {
    int n;

    printf("Enter number of orders: ");
    scanf("%d", &n);

    Order *orders = (Order *)malloc(n * sizeof(Order));

    printf("Enter Order Details:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d", orders[i].orderId ,&orders[i].priceInCents);
    }
    countingSort(orders, n);

    printf("\nSorted Orders:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", orders[i].orderId, orders[i].priceInCents);
    }

    free(orders);

    return 0;
}