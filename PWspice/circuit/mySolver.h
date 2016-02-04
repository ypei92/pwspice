#ifndef MYSOLVER_H_INCLUDED
#define MYSOLVER_H_INCLUDED

#include <iostream>

/*using namespace std;*/

/*===============================================================================
1:This solver implement LU Decomposition to solve the equation
2:Return value is 0 when the matrix is singular, vice versa.
3:Sort according to the # of zeros at the beginning to keep matrix sparse.
4:Put the largest valve at diagonal to maximize precision.
5:Using index[n] to reflect the # of column.
6:A small enough number can be regarded as zero, it is difined as MYZERO.
===============================================================================*/



int count_zero_number(complex<double> *x, int n)
{
    int num=0;
    for (int i=0; i<n; i++)
    {
        if (abs(x[i])==0) num+=1;
    }
    return num;
}

bool mySolve(int n, complex<double> **AA, complex<double> *bb, complex<double> *xx)
{
    const complex<double> MYZERO = 1e-10;
    //const complex<double> MYZERO = 0;
    /* build A,b,x */
    complex<double> **A = new complex<double>*[n];
    for (int i=0; i<n; i++)
    {
        A[i] = new complex<double>[n];
    }
    complex<double> *x = new complex<double>[n];
    complex<double> *b = new complex<double>[n];
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++) A[i][j]=AA[i][j];
        b[i]=bb[i];
    }

    /* make initial index sorting by # of zeros */
    int *zero_number = new int[n];
    int *index = new int[n];
    for (int i=0; i<n; i++)
    {
        index[i]=i;
    }
    for (int i=0; i<n; i++)
    {
        zero_number[i]=count_zero_number(A[i],n);
    }
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (zero_number[i]<zero_number[j])
            {
                int tmp;
                tmp=zero_number[i];
                zero_number[i]=zero_number[j];
                zero_number[j]=tmp;
                tmp=index[i];
                index[i]=index[j];
                index[j]=tmp;
            }
        }
    }
    /* check for index */
    /*cout<<"Check for index:"<<endl;
    for (int i=0; i<n; i++) cout<<index[i]<<' ';
    cout<<endl;*/

    /* LU */
    for (int i=0; i<n; i++)
    {
        /*cout<<"LU:"<<i<<"======================================================="<<endl;*/

        /* find the max num below element A["i"][i] */
        complex<double> max_value=0;
        int max_index=i;
        for (int j=i; j<n; j++)
        {
            if ( abs(A[index[j]][i]*A[index[j]][i]) > abs(max_value) )
            {
                max_value=A[index[j]][i]*A[index[j]][i];
                max_index=j;
            }
        }
        /* if all element is 0, the matrix is singular, return 0 */
        if (abs(max_value)<=abs(MYZERO*MYZERO)) return 0;
        /* re-index the A[i:n,i:n] */
        int tmp = index[max_index];
        for (int j=max_index; j>i; j--) index[j]=index[j-1];
        index[i]=tmp;
        /*cout<<"Check for index:"<<endl;
        for (int j=0; j<n; j++) cout<<index[j]<<' ';
        cout<<endl;*/

        /* column elimination */
        for (int j=i+1; j<n; j++)
        {
            complex<double> div = A[index[j]][i] / A[index[i]][i];
            A[index[j]][i] = div;
            for (int k=i+1; k<n; k++)
            {
                A[index[j]][k] -= A[index[i]][k] * div;
            }
            b[index[j]] -= b[index[i]] * div;
        }
    }

    /* solve L*y=b */
    complex<double> *y = new complex<double>[n];
    for (int i=0; i<n; i++)
    {
        y[index[i]]=b[index[i]];
//        for (int j=0; j<i; j++)
//        {
//            y[index[i]] -= A[index[i]][j];
//        }
//        for (int j=i+1; j<n; j++)
//        {
//            A[index[j]][i] *= y[index[i]];
//        }
    }
    /*cout<<"Display y:"<<endl;
    for (int i=0; i<n; i++) cout<<y[i]<<' ';
    cout<<endl;*/

    /* solve U*x=y */
    for (int i=n-1; i>=0; i--)
    {
        x[index[i]]=y[index[i]];
        for (int j=n-1; j>i; j--)
        {
            x[index[i]] -= A[index[i]][j];
        }
        x[index[i]] /= A[index[i]][i];
        for (int j=i-1; j>=0; j--)
        {
            A[index[j]][i] *= x[index[i]];
        }
    }
    /*cout<<"Display x:"<<endl;
    for (int i=0; i<n; i++) cout<<x[i]<<' ';
    cout<<endl;*/

    /* reflect xx */
    for (int i=0; i<n; i++) xx[i]=x[index[i]];
    return 1;
}

#endif // MYSOLVER_H_INCLUDED
