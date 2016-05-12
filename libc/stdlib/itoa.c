#include <stdlib.h>

size_t
itoa(int nb, char* nb_str, unsigned int base) {
  if (nb < 0) {
    *nb_str = '-';
    return 1 + uitoa(nb * -1, nb_str + 1, base);
  }

  return uitoa(nb, nb_str, base);
}
