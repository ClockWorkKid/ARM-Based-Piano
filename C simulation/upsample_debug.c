#include <stdio.h>
#include<math.h>
#define pi 3.14159265
#define SIZE 17

void generateSig(double *x, double *t);
void upsample(double *x, double *t, double *x_u, double *t_u, int u, int up_SIZE);
void printArray(double *x, double *t, int len);

int main()
{
    int u = 3; //u = upsampling factor
    int up_SIZE = SIZE*u - u + 1;
    double *p;

	double x[SIZE];
	double t[SIZE];
	double up_x[up_SIZE];
	double up_t[up_SIZE];

	double t_step, fs;
	double fs_u;
	int i;

	generateSig(x, t);
	printf("Original Signal\n\n");
	printArray(x, t, SIZE);

	//upsampling
	t_step = t[1]-t[0];
	fs = 1/t_step;
	fs_u = fs*u;
	upsample(x, t, up_x, up_t, u, up_SIZE);

	printf("\n\nAfter upsampling: \n\n");
	printArray(up_x, up_t, up_SIZE);

	return 0;
}

void generateSig(double *x, double *t)
{
    int i;
    for(i=0;i<SIZE;i++)
	{
		t[i] = i*( ((double)1) / (SIZE-1));
		x[i] = 2*sin(2*pi*2*t[i]);
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





