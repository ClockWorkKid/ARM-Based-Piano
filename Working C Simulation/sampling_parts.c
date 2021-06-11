/*The purpose of this code is to read a fixed number of values from a large text file
part by part and write to another text file*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define full_SIZE 100000
#define SIZE 1000

void getText(double *a, double *b, FILE **fp);
void writeText(double *a, double *b, FILE **fpw);

int main()
{
    FILE *fpr = fopen("A2.txt", "r");
    FILE *fpw = fopen("resampled_A2.txt", "a");
    double a[SIZE];
    double b[SIZE];
    int num_iter = full_SIZE/SIZE;

    for(int i=0; i<num_iter; i++)
    {
        getText(a,b,&fpr);
        writeText(a, b, &fpw);
    }
    fclose(fpr);
    fclose(fpw);

    return 0;
}

void writeText(double *a, double *b, FILE **fpw)
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        fprintf(*fpw,"%f,%f\n", a[i], b[i]);
    }
}

void getText(double *a, double *b, FILE **fp)
{
    char f_channel[20];
    char s_channel[20];
    char line[40];
    char currentChar;
    int flag;
    int i,j;
    j=0;
    int index;

    while(fgets(line, sizeof line, *fp) != NULL)
    {
        flag = 0;
        for(i=0; i<=strlen(line); i++)
        {
            currentChar = line[i];
            if (currentChar==',')
            {
                index = i;
                f_channel[i] = '\0';
                flag = 1;
            }
            if (flag==0)
            {
                f_channel[i] = currentChar;
            }
            else
            {
                s_channel[i-index] = currentChar;
            }
        }
        s_channel[i-index] = '\0';
        for(i=0; i<strlen(s_channel)-1; i++)
        {
            s_channel[i] = s_channel[i+1];
        }
        s_channel[i] = '\0';

        a[j] = (double)atof(f_channel);
        b[j] = (double)atof(s_channel);
        j = j+1;
        if (j==SIZE)
            break;
    }
}
