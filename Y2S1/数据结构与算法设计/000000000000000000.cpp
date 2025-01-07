#include <iostream>
using namespace std;
int main()
{
  long long n, q;
  scanf("%lld %lld", &n, &q);
  while (q--){
    long long b;
    scanf("%lld", &b);
    long long u = (b+2)/3;
    if ((b+2) % 3 != 0) u++;
    long long v = b+3-2*u;
    cout << u << " " << v << endl;
  }
  return 0;
}