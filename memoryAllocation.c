#include<stdio.h>
#include<conio.h>
#define max 25

void worstFit(int b[], int nb, int f[], int nf) {
    int frag[max], ff[max], bf[max], i, j, temp, highest = 0;
    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && highest < temp) {
                    ff[i] = j;
                    highest = temp;
                }
            }
        }
        frag[i] = highest;
        bf[ff[i]] = 1;
        highest = 0;
    }
    printf("\nFile No\tFile Size \tBlock No\tBlock Size\tFragment");
    for (i = 1; i <= nf; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
   // getch();
}

void firstFit(int b[], int nb, int f[], int nf) {
    int frag[max], ff[max], bf[max], i, j, temp;
    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0) {
                    ff[i] = j;
                    bf[j] = 1;
                    frag[i] = temp;
                    break;
                }
            }
        }
    }
    printf("\nFile No\tFile Size \tBlock No\tBlock Size\tFragment");
    for (i = 1; i <= nf && ff[i] != 0; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
  //  getch();
}

void bestFit(int b[], int nb, int f[], int nf) {
    int frag[max], ff[max], bf[max], i, j, temp, lowest = 10000;
    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && lowest > temp) {
                    ff[i] = j;
                    lowest = temp;
                }
            }
        }
        frag[i] = lowest;
        bf[ff[i]] = 1;
        lowest = 10000;
    }
    printf("\nFile No\tFile Size \tBlock No\tBlock Size\tFragment");
    for (i = 1; i <= nf && ff[i] != 0; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
   // getch();
}

int main() 
{
    int b[max], f[max], nb, nf, choice;
    printf("Menu Driven Memory Management Scheme\n");
    printf("1. Worst Fit\n");
    printf("2. First Fit\n");
    printf("3. Best Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("Enter the size of the blocks:\n");
    for (int i = 1; i <= nb; i++) {
        printf("Block %d: ", i);
        scanf("%d", &b[i]);
    }

    printf("Enter the size of the files:\n");
    for (int i = 1; i <= nf; i++) {
        printf("File %d: ", i);
        scanf("%d", &f[i]);
    }

    switch (choice) {
        case 1:
            printf("\nMemory Management Scheme - Worst Fit\n");
            worstFit(b, nb, f, nf);
            break;
        case 2:
            printf("\nMemory Management Scheme - First Fit\n");
            firstFit(b, nb, f, nf);
            break;
        case 3:
            printf("\nMemory Management Scheme - Best Fit\n");
            bestFit(b, nb, f, nf);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}