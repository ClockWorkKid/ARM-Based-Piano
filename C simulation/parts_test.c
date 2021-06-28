#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void getText(double *a, double *b, FILE **fp);

int main()
{
    FILE *fpr = fopen("sample.txt", "r");
    double a[2];
    double b[2];
    for(int i=0; i<3; i++)
    {
        getText(a,b,&fp);
        printf("%f %f %d\n",a[0],b[0],ftell(fp));
        printf("%f %f %d\n",a[1],b[1],ftell(fp));
    }
    fclose(fp);
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
        if (j==2)
            break;
    }
}
