#include <stdio.h>
#define LEFT  -1
#define RIGHT  1

void printPermutation(int perm[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", perm[i]);
    printf("\n");
}

int getMobile(int perm[], int dir[], int n) {
    int mobile = 0, mobile_index = -1;

    for (int i = 0; i < n; i++) {
        if (dir[i] == LEFT && i != 0 && perm[i] > perm[i - 1] && perm[i] > mobile) {
            mobile = perm[i];
            mobile_index = i;
        }
        if (dir[i] == RIGHT && i != n - 1 && perm[i] > perm[i + 1] && perm[i] > mobile) {
            mobile = perm[i];
            mobile_index = i;
        }
    }
    return mobile_index;
}

void generatePermutations(int n) {
    int perm[n], dir[n];

    for (int i = 0; i < n; i++) {
        perm[i] = i + 1;
        dir[i] = LEFT;
    }

    printPermutation(perm, n);

    while (1) {
        int mobile_index = getMobile(perm, dir, n);

        if (mobile_index == -1)
            break;

        int swap_index = mobile_index + dir[mobile_index];

        int temp = perm[mobile_index];
        perm[mobile_index] = perm[swap_index];
        perm[swap_index] = temp;

        temp = dir[mobile_index];
        dir[mobile_index] = dir[swap_index];
        dir[swap_index] = temp;

        int mobile = perm[swap_index];

        for (int i = 0; i < n; i++) {
            if (perm[i] > mobile)
                dir[i] = -dir[i];
        }

        printPermutation(perm, n);
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    generatePermutations(n);

    return 0;
}
