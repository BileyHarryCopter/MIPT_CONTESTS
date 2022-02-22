#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                       // берет остаток от произведения
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
unsigned long long mul_mod (unsigned long long x,
                            unsigned long long y,
                            unsigned long long r) {
    return ((x % r) * y) % r;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                    // берем остаток от возведения в степень
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
unsigned long long pow_mod (unsigned long long n,
                            unsigned long long k,
                            unsigned long long m) {
  unsigned long long mult, prod;
  //assert(m > 1);
  if (k == 0)
      return 1;
  mult = n % m;
  prod = mult;
  // заменить этот цикл из остатков произведения
  while (k > 1) {
    prod = (prod * mult) % m;
    k -= 1;
  }
  return prod;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                // нахождение остатка при делении 2х чисел
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
unsigned long long gcd (unsigned long long a, unsigned long long b) {
    long long unsigned r;
    r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                               // Тест Ферма
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Prime_Test (unsigned long long p) {
    // создание массива из значений случайных а
    srand (time(NULL));
    int status = 20;
    int witness = 0;
    unsigned long long a = 0;
    while (status > 0) {
        a = rand () % 100;
        if ( gcd (p, a) == 1) {
            if (pow_mod (a, p - 1, a) != 1) {
                witness++;
            }
        }
        status--;
    }

    if (witness == 0) {
        return 1;
    }
    return 0;

}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main () {

    unsigned long long N = 0;
    scanf ("%llu", &N);

    printf("%d\n", Prime_Test (N));

    return 0;
}
