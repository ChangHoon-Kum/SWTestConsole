#include "CFibo.h"

long CFibo::recursiveFibo(long n)
{
    if (n < 2)
    {
        return n;
    }
    else
    {
        return recursiveFibo(n - 1) + recursiveFibo(n - 2);
    }
}
