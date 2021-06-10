#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000

void main()
{
    double first_channel[SIZE];
    double second_channel[SIZE];
    char f_channel[20];
    char s_channel[20];
    int flag;

    FILE *fp = fopen("A2.txt", "r");
    const char s = ",";
    char *token;
    int i,j;
    int index;
    if(fp != NULL)
    {
        char line[40];
        char currentChar;
        while(fgets(line, sizeof line, fp) != NULL)
        {
            //printf("%s\n",line);
            flag = 0;
            for(i=0;i<=strlen(line);i++)
            {
                currentChar = line[i];
                if (currentChar==',')
                {
                    index = i;
                    f_channel[i] = '\0';
                    flag = 1;
                    //printf("Found , at %d index\n", index);
                    //break;
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

            //printf("Length of second channel = %d\n", strlen(s_channel));

            //printf("First Channel = %s, Second Channel=%s\n", f_channel, s_channel);

            first_channel[j] = (double)atof(f_channel)/10;
            second_channel[j] = (double)atof(s_channel)/10;

            printf("First Channel = %f, Second Channel=%f\n", first_channel[j], second_channel[j]);

        }
        fclose(fp);
    }
    else
    {
        perror("A2.txt");
    }
}
