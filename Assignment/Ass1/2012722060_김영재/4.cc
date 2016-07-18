#include <stdio.h>		//Include Headere FIle
#include "4.h"

/*int main()
{
	int arr[5] = { 0, };
	int i=0;

	//Read array value
	//and print current minimun and maximum every read time
	for (i = 0; i < 5; i++)
	{
		printf("숫자 입력 : ");
		scanf("%d", &arr[i]);
		Min(arr, i+1);		//Call Min function(size+1,beacuse i is size -1);
		Max(arr, i + 1);	//CallMax function
	}
	Average(arr);			//Call Average function
	Variance(arr);			//Call variance function

	return 0;
}*/
int Min(int arr[], int num)
{
	int min = arr[0];		//set Min varicable to array's first value
	int i=0;

	//If current value < min, min is current value
	for (i = 0; i < num; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	//Print minimum;
	printf("> Min : %d\n", min);

	return min;		//return minimum
}

int Max(int arr[], int num)
{
	int max = arr[0];		//set Max varicable to array's first value
	int i = 0;

	//If current value > min, min is current value
	for (i = 0; i < num; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	//Print maximum;
	printf("> Max : %d\n\n", max);

	return max;		//return maximum
}

double Average(int arr[])
{
	int sum = 0;
	double AVG = 0;
	int i = 0;

	//Get array's sum
	for (i = 0; i < 5; i++)
	{
		sum += arr[i];
	}
	//Assign AVG(average)
	AVG = (double)sum / 5;
	//Print average
	printf(">> AVG : %lf\n",AVG);

	return AVG;		//return average
}

double Variance(int arr[])
{
	int sum = 0, s_sum = 0;		//Sum and square Sum
	double AVG = 0, S_AVG;		//Sum average and square sum average
	double VAR = 0;				//Variamce
	int i = 0;

	//Get sum and square sum
	for (i = 0; i < 5; i++)
	{
		s_sum += (arr[i] * arr[i]);
		sum += arr[i];
	}

	//Assign square's average
	S_AVG = (double)s_sum / 5;
	//Assign average
	AVG = ((double)sum / 5)*((double)sum / 5);
	//Assign vaiance(square's average - average's square
	VAR = S_AVG - AVG;
	//Print variance
	printf(">> Var : %lf\n", VAR);

	return VAR;		//return variance
}
