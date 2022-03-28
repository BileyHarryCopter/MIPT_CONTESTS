#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashmap_ctor(hashmap *hshmp, unsigned len_buff) {
  char symb = 0;
  char *str = 0;
  unsigned ip = 0;
  unsigned key = 0;

  hshmp->size = SIZE;
  hshmp->array = (node_t **)calloc(SIZE, sizeof(node_t *));

  for (ip = 0; ip < SIZE; ip++) {
    hshmp->array[ip] = (node_t *)calloc(1, sizeof(node_t));
  }

  symb = getchar();

  for (ip = 1; ip < len_buff; ip++) {
    symb = getchar();
    if (isalpha(symb) != 0) {
      str = str_ctor(symb);
      ip += strlen(str);
      key = hash_calc(str);
      hashmap_insrt(hshmp, key, str);
      free(str);
    }
  }
}

int main(void) {
  float roof, cell = 0.0;
  float frac, frac_up, frac_down = 0.0;
  float pos_infty = 1 / 0;
  float neg_infty = -1 / 0;
  unsigned u_eps = 0;
  unsigned u_frac = 0;
  unsigned u_up = 0;
  unsigned u_down = 0;
  scanf("%f %f", &roof, &cell);

  frac = (float)roof / cell;

  fesetround(FE_DOWNWARD);

  frac_up = nextafterf(frac, pos_infty);
  frac_down = nextafterf(frac, neg_infty);

  memcpy(&u_frac, &frac, sizeof(float));
  memcpy(&u_up, &frac_up, sizeof(float));
  memcpy(&u_down, &frac_down, sizeof(float));

  /*
  printf ("%.20f\t%x\n", frac, u_frac);
  printf ("%.20f\t%x\n", frac_up, u_up);
  printf ("%.20f\t%x\n", frac_down, u_down);
  */

  return 0;
}
