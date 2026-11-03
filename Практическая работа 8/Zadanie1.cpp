#include <iostream>

using namespace std;

// Рекурсивная функция быстрого возведения в степень за O(log n)
long long fast_pow(long long a, long long n)
{
    if (n == 0)
    {
        return 1;
    }
    if (n % 2 == 1)
    {
        return a * fast_pow(a, n - 1);
    } else
    {
        long long half = fast_pow(a, n / 2);
        return half * half;
    }
}

int main()
{
    long long a, n;
    cin >> a >> n;
    cout << fast_pow(a, n) << endl;
    return 0;
}
