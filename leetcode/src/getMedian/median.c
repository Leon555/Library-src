#include <stdio.h>

#define SIZE 5

int getMedian(int* arra, int* arrb, int left, int right)
{
	int size;
	int mid;

	size = right - left + 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid == size - 1)
		{
			if (arra[mid] <= arrb[0])
				return arra[mid];
			else
				return -1 ;
		}
		else if (arra[mid] >= arrb[right - mid - 1])
		{
			if (arra[mid] <= arrb[right - mid])
				return arra[mid];
			else
				right = mid - 1;
		}
		else
			left = mid + 1;
	}

	return -1;
}

int getSecond(int a, int b, int c, int d)
{
    if(a > c)
        return a > d ? d : a;
    else
        return b > c ? c : b;
}

int getMedian2(int* arra, int* arrb, int left, int right)
{
	int mida, midb;
    int lefta, leftb;
    int righta, rightb;
    
    lefta = left; righta = right;
    leftb = left; rightb = right;
    
    int mid = right; // the median's position
    
	while (lefta <= righta && leftb <= rightb)
	{
		mida = (lefta + righta) / 2;
        midb = (leftb + rightb) / 2;
        
        if(arra[mida] == arrb[midb])
            return arra[mida];
        else if(arra[mida] > arrb[midb]) {
            righta = mida - 1;
            leftb =  midb + 1;
            mid -= (midb - leftb + 1);
        }
        else {
            lefta = mida + 1;
            rightb = midb - 1;
            mid -= (mida - lefta + 1);
        }
	}

    printf("%d %d %d %d %d %d\n", lefta, righta, mida, leftb, rightb, midb);
    
    int res = getSecond(arra[(lefta+righta)/2], arra[(int)ceil((lefta+righta)/2.0)], 
        arrb[(leftb+rightb)/2], arrb[(int)ceil((leftb+rightb)/2.0)]);
	return res;
}

int main (void)
{
	int arra[SIZE] = {1, 2, 9, 11, 13};
	int arrb[SIZE] = {3, 4, 8, 10, 14};
	int size = SIZE;
	int value ;
	
	value = getMedian(arra, arrb, 0, size - 1) ;
	if (-1 == value)
		value = getMedian(arrb, arra, 0, size - 1) ;
    
	printf ("%d\n", value);
    
    value = getMedian2(arra, arrb, 0, size - 1) ;
    printf ("%d\n", value);

	return 0 ;
}
