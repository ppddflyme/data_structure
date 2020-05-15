// test_fb_search.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>  
#include  <iostream>  
using namespace std;

const int max_size = 20;//쳲���������ĳ���  

                        /*����һ��쳲���������*/
void Fibonacci(int * F)
{
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i<max_size; ++i)
        F[i] = F[i - 1] + F[i - 2];
}

/*����쳲��������ҷ�*/
int Fibonacci_Search(int *a, int n, int key)  //aΪҪ���ҵ�����,nΪҪ���ҵ����鳤��,keyΪҪ���ҵĹؼ���  
{
    int low = 0;
    int high = n - 1;

    int F[max_size];
    Fibonacci(F);//����һ��쳲���������F   

    int k = 0;
    while (n>F[k] - 1)//����nλ��쳲��������е�λ��  
        ++k;

    int  * temp;//������a��չ��F[k]-1�ĳ���  
    temp = new int[F[k] - 1];
    memcpy(temp, a, n * sizeof(int));

    for (int i = n; i<F[k] - 1; ++i)
        temp[i] = a[n - 1];

    while (low <= high)
    {
        int mid = low + F[k - 1] - 1;
        cout << "low: " << low << ", high: " << high << ", mid = " << mid << endl;
        if (key<temp[mid])
        {
            high = mid - 1;
            k -= 1;
        }
        else if (key>temp[mid])
        {
            low = mid + 1;
            k -= 2;
        }
        else
        {
            if (mid<n)
                return mid; //�������˵��mid��Ϊ���ҵ���λ��  
            else
                return n - 1; //��mid>=n��˵������չ����ֵ,����n-1  
        }
    }
    delete[] temp;
    return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    //int a[] = { 0,16,24,35,47,59,62,73,88,99 };
    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int key = 6;
    int index = Fibonacci_Search(a, sizeof(a) / sizeof(int), key);
    cout << key << " is located at:" << index << endl;
    system("PAUSE");
    return 0;
}

