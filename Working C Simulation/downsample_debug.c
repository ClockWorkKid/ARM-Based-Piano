#include <stdio.h>
#include<math.h>
#define pi 3.14159265
#define SIZE 17

void generateSig(double *x, double *t);
void downsample(double *x, double *t, double *x_d, double *t_d, int d, int down_SIZE);
void printArray(double *x, double *t, int len);

int main()
{
    int d = 2; //d = downsampling factor
    int down_SIZE = (int)ceil((double)SIZE/d);

	double x[SIZE];
	double t[SIZE];
	double down_x[down_SIZE];
	double down_t[down_SIZE];

	double t_step, fs;
	double fs_d;
	int i;

	generateSig(x, t);
	printf("Original Signal\n\n");
	printArray(x, t, SIZE);

	//upsampling


	//downsampling
	t_step = t[1]-t[0];
	fs = 1/t_step;
	fs_d = fs/d;
	downsample(x, t, down_x, down_t, d, down_SIZE);

	printf("\n\nAfter downsampling: \n\n");
	printArray(down_x, down_t, down_SIZE);

	return 0;
}

void generateSig(double *x, double *t)
{
    int i;
    for(i=0;i<SIZE;i++)
	{
		t[i] = i*( ((double)1) / (SIZE-1));
		x[i] = 2*sin(2*pi*2*t[i]);
		//printf("At time=%f, x=%f, i=%d\n", t[i],x[i], i);
	}
}

void printArray(double *x, double *t, int len)
{
    //size_t n = sizeof(x)/sizeof(x[0]);
    int i;
    for(i=0;i<len;i++)
	{
		printf("At time=%f, x=%f, i=%d\n", t[i],x[i], i);
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







