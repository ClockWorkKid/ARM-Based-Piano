#include <stdio.h>
#include<math.h>
#include<string.h>
#define pi 3.14159265
#define SIZE 100000
#define SIZE 1000

void getSig(double *first_channel, double *second_channel, FILE **fp);
void downsample(double *x, double *t, double *x_d, double *t_d, int d, int down_SIZE);
void upsample(double *x, double *t, double *x_u, double *t_u, int u, int up_SIZE);
void printArray(double *x, double *t, int len);
void writeSig(double *f_channel, double *s_channel, int n);

int main()
{
    FILE *fpr = fopen("A2.txt", "r");

    int u = 3; //u = upsampling factor
    int d = 2; //d = downsampling factor
    int up_SIZE = SIZE*u - u + 1;
    int down_SIZE = (int)ceil((double)up_SIZE/d);

	double first_channel[SIZE];
	double second_channel[SIZE];
	double t[SIZE];
	double up_first[up_SIZE];
	double up_second[up_SIZE];
	double up_t[up_SIZE];
	double down_first[down_SIZE];
	double down_second[down_SIZE];
	double down_t[down_SIZE];

	double fs = 44100;
	double t_step = 1/fs;
	double fs_u, fs_d;
	int i;

	getSig(first_channel, second_channel, &fpr);

	//getSig(first_channel, second_channel);
	for(i=0;i<SIZE;i++)
    {
        t[i] = (double)i/fs;
    }

    printf("Original Signal:\n\n");
    printf("First Channel:\n");
	printArray(first_channel, t, SIZE);
	//printf("\nSecond Channel:\n");
	//printArray(second_channel, t, SIZE);

	//upsampling
/*
	t_step = t[1]-t[0];
	fs = 1/t_step;
	fs_u = fs*u;
	upsample(first_channel, t, up_first, up_t, u, up_SIZE);
	upsample(second_channel, t, up_second, up_t, u, up_SIZE);

    //printf("\n\nAfter upsampling: \n\n");
	//printArray(up_first, up_t, up_SIZE);

	//downsampling
	fs_d = fs/d;
	downsample(up_first, up_t, down_first, down_t, d, down_SIZE);
	downsample(up_second, up_t, down_second, down_t, d, down_SIZE);

	//printf("\n\nAfter downsampling: \n\n");
	//printArray(down_first, down_t, down_SIZE);

	writeSig(down_first, down_second, down_SIZE);
*/
	return 0;
}

void getSig(double *first_channel, double *second_channel, FILE **fp)
{
    char f_channel[20];
    char s_channel[20];
    int flag;

    //FILE *fp = fopen("A2.txt", "r");

    int i,j;
    j=0;
    int index;
    if(*fp != NULL)
    {
        char line[40];
        char currentChar;
        while(fgets(line, sizeof line, *fp) != NULL)
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

            first_channel[j] = (double)atof(f_channel);
            second_channel[j] = (double)atof(s_channel);
            j = j+1;
            if (j==1000)
                break;

            //printf("First Channel = %f, Second Channel=%f\n", first_channel[j], second_channel[j]);

        }
        //fclose(fp);
    }
    else
    {
        perror("A2.txt");
    }
}

void writeSig(double *f_channel, double *s_channel, int n)
{
    int i;
    //open in write mode
    FILE *fptr = fopen("A2_resampled.txt", "w");
    if (fptr == NULL)
    {
        printf("Could not open file");
    }

    for (i = 0; i < n; i++)
    {
        fprintf(fptr,"%f,%f\n", f_channel[i], s_channel[i]);
    }
    fclose(fptr);
}

void printArray(double *x, double *t, int len)
{
    //size_t n = sizeof(x)/sizeof(x[0]);
    int i;
    for(i=500;i<len;i++)
	{
		printf("At time=%f, x=%f, i=%d\n", t[i],x[i], i);
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

    //printf("Upsampled signal frequency: %.2f\n", fs_u);
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
        //printf("At time=%f, x_d=%f, k=%d\n", t_d[k], x_d[k], k);
    }
}





