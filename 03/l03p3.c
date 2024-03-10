/**
Sa se citeaca un sir de numere de la tastatura. Sa se calculeze suma numerelor prime din sir.
Exemplu: pentru sirul [2,62,7,4,45,1], programul va afisa valoarea 10.
*/

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int isPrime(int number)
{
    int i;

    for (i = 2; i <= number / 2; i++) {
        if (number % i == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void computeSum(int *array, int size, int *sum)
{
    int i, tempSum = 0;


    for (i = 0; i < size; i++) {
        if (isPrime(array[i]) == TRUE) {
            tempSum += array[i];
        }
    }

    *sum = tempSum;
}


int readArray(int *size, int *array)
{
    int i, sz;

    printf("Size: \n");
    if (scanf("%d", &sz) != 1) {
        printf("Error reading size!\n");
        return FALSE;
    }

    printf("Array:\n");
    for (i = 0; i < sz; i++) {
        if (scanf("%d", &array[i]) != 1) {
            printf("Error reading element %d!\n", i);
            return  FALSE;
        }
    }

    *size = sz;
    return TRUE;
}

int main()
{
    int sum = 0, size;
    int *array;

    array = (int *)malloc(sizeof(int) * 150);

    if (readArray(&size, array) == TRUE) {
        computeSum(array, size, &sum);
        printf("%d\n", sum);
    }

    return 0;
}