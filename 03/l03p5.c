#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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

int insert(int *v1, int n1, int c1, int *v2, int n2, int pos) {
    if (c1 < n1 + n2 || c1 < pos + n2)
        return -1;
    for (int i = n1 + n2 - 1; i > pos - 1; i--)
        v1[i] = v1[i - n2];
    for (int i = 0; i < n2; i++)
        v1[pos + i] = v2[i];
    return 0;
}
// 0 1 2 3 4 5 6 7
// 1 2 3 4 5 6 x x
int main()
{
    int n1, n2;
    int *v1, *v2;
    int capacity = 8;
    int pos;
    v1 = (int *)malloc(sizeof(int) * capacity);
    v2 = (int *)malloc(sizeof(int) * capacity);

    if (readArray(&n1, v1) == TRUE && readArray(&n2, v2) == TRUE) {
        printf("enter position:\n");
        scanf("%d", &pos);
        int res = insert(v1, n1, capacity, v2, n2, pos);
        if (res == 0) {
            printf("succes!\nthe new array size is %d\narray: \n", n1 + n2);
            for (int i = 0; i < n1 + n2; i++)
                printf("%d ", v1[i]);
            printf("\n");
        }
        else if (res == -1) {
            puts("ERROR, not enough memory");
            exit(-1);
        }
    }

    return 0;
}