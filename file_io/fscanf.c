#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    FILE *fp, *fp_out;
    int count = 0;
    int id, g1, g2, g3;
    char name[50];

    fp = fopen("student.txt", "r");
    fp_out = fopen("student_avg.txt", "w");

    fscanf(fp, "%d", &count);

    for (int i = 0; i < count; i++) {
        fscanf(fp, "%d", &id);
        fscanf(fp, "%s", name);
        fscanf(fp, "%d%d%d", &g1, &g2, &g3);
        double avg = (g1 + g2 + g3) / 3;
        printf("%d %s avg: %0.2f\n", id, name, avg);
        fprintf(fp_out, "%d %s avg: %0.2f\n", id, name, avg);
    }

    fclose(fp);
    fclose(fp_out);
    return 0;
}