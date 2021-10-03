//
//  main.c
//  week_1
//
//  Created by 曲耕余 on 2021/10/3.
//

#include <stdio.h>
#include <time.h>
double AlgorithmOne(double x, int n);
double IterationAlgorithm(double x, int n);
double RecursiveAlgorithm(double x, int n);
int Test(int n);
clock_t start, stop;
double duration;
enum parity {odd, even};     //enumerator to better express
int main(void)
{
    int i = 0;
    start = clock();
    for(;i <= 10000;i++)              //do iterations , change upper bounder can change iteration times
    AlgorithmOne(1.0001, 100000);      //change  function can change the tested function
    stop = clock();
    duration = ((double)(stop - start) / CLK_TCK);  //calculate time duration
    printf("%d", duration);          //print result to the monitor
    return 0;
}
double AlgorithmOne(double x, int n)   //x for base and n for exponent
{
    double result = x;
    if(0 == n)  //test for n^0, 0^0 is not considered here.
        return 1.0;
    for(int i = 1; i < n; i++) // iterative method to calculate the multiplication
    {
        result *= x;
    }
    return result;
}
int Test(int n) //test for the number is odd or even
{
    if(n % 2)  // result 1 means odd
        return odd;
    else return even;
}
double IterationAlgorithm(double x, int n) // parameters are the sam e as above
{
        if(0 == n)
            return 1.0;       //test for n^0, 0^0 is not considered here.
    double result;
    if(odd == Test(n))
    {
        int temp = (n - 1) / 2;
        result = 1;
        for(int i = 1; i <= temp; i++) // x^((n-1)/2)
            result *= x;
        result *= result;    // multiply 3 times. x*x^((n-1)/2)*x^((n-1)/2)
        result *= x;
    }
    else
    {
        int temp = n / 2;
        result = 1;
        for(int i = 1; i <= temp; i++)     // x^0.5n
            result *=x;
        result *= result;      //x^n
    }
    return result;
}
double RecursiveAlgorithm(double x, int n) //x for base and n for exponent
{
    if(0 == n)
        return 1.0;       //test for n^0, 0^0 is not considered here.
    if(odd == Test(n))
        return RecursiveAlgorithm(x * x, n / 2) * x; //n is integer so n / 2 == (n - 1) / 2
    else
        return RecursiveAlgorithm(x * x, n / 2);
}

