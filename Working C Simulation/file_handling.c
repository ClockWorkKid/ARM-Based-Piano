#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000

void main()
{
    double first_channel[SIZE];
    char f_channel[20];
    int flag;
    FILE *fp = fopen("A2_choto.txt", "r");
    int i,j;
    int index;
    if(fp != NULL)
    {
        char line[40];
        char currentChar;
        while(fgets(line, sizeof line, fp) != NULL)
        {
            flag = 0;
            for(i=0;i<=strlen(line);i++)
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
            }

            first_channel[j] = (double)atof(f_channel);
            printf("First Channel = %f\n", first_channel[j]);

        }
        fclose(fp);
    }
    else
    {
        perror("A2.txt");
    }
}
