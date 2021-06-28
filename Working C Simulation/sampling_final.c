/*The purpose of this code is to read a fixed number of values from a large text file
part by part and resample them and append to another text file*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define pi 3.14159265
#define full_SIZE 100000
#define SIZE 1000

void getText(double *a, FILE **fp);
void writeText(double *a, FILE **fpw, int len);
void downsample(double *x, double *t, double *x_d, double *t_d, int d, int down_SIZE);
void upsample(double *x, double *t, double *x_u, double *t_u, int u, int up_SIZE);

int main()
{
    FILE *fpr = fopen("A2.txt", "r");
    FILE *fpw = fopen("B2_C.txt", "w");

    double fs = 44100;
    int u = 25;
    int d = 28;
    int up_SIZE = SIZE*u - u + 1;
    int down_SIZE = (int)ceil((double)up_SIZE/d);

    double x[SIZE];
	double t[SIZE];
	double up_x[up_SIZE];
	double up_t[up_SIZE];
	double down_x[down_SIZE];
	double down_t[down_SIZE];

    int num_iter = full_SIZE/SIZE;
    int i;
    int p;

    for(i=0; i<num_iter; i++)
    {
        printf("Running iteration: %d\n", i);

        /*get 1000 values and load into a*/
        getText(x, &fpr);

        /*define t for these 1000 values*/
        for(p=0;p<SIZE;p++)
        {
            t[p] = p*( ((double)1) / fs);
        }

        //upsample
        //printf("Upsampled signal size=%d\n", up_SIZE);
        upsample(x, t, up_x, up_t, u, up_SIZE);

        //downsample
        downsample(up_x, up_t, down_x, down_t, d, down_SIZE);

        //append resampled values to file
        writeText(down_x, &fpw, down_SIZE);
    }

    fclose(fpr);
    fclose(fpw);

    return 0;
}

void writeText(double *a, FILE **fpw, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        fprintf(*fpw,"%f\n", a[i]);
    }
}

void getText(double *a, FILE **fp)
{
    char f_channel[20];
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
        }
        a[j] = (double)atof(f_channel);
        j = j+1;
        if (j==SIZE)
            break;
    }
}

void upsample(double *x, double *t, double *x_u, double *t_u, int u, int up_SIZE)
{
    int k,j;
    double t_step;
    double fs;
    double fs_u;

    t_step = t[1]-t[0];
    fs = 1/t_step;
    fs_u = fs*u;

    double a[SIZE];
    double sum;

    for(k=0; k<up_SIZE; k++)
    {
        t_u[k] = (double)k/fs_u;
        sum = 0;
        for (j=0;j<SIZE;j++)
        {
            a[j] = (t_u[k] - t[j])/t_step;

            if (a[j]!=0)
            {
                a[j] = sin(pi*a[j])/(pi*a[j]);
            }
            else
            {
                a[j] = 1;
            }
            sum = sum + a[j]*x[j];
        }

        x_u[k] = sum;
    }

}

void downsample(double *x, double *t, double *x_d, double *t_d, int d, int down_SIZE)
{
    int k;
    for(k = 0; k<down_SIZE; k++)
    {
        x_d[k] = x[d*k];
        t_d[k] = t[d*k];
    }
}
