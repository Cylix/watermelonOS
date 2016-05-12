#include <stdlib.h>

size_t
uitoa(unsigned int nb, char* nb_str, unsigned int base) {
  if (nb == 0) {
    nb_str[0] = '0';
    nb_str[1] = '\0';
    return 1;
  }

  size_t len = 0;

  if (nb >= base) {
    len = uitoa(nb / base, nb_str, base);
    nb %= base;
  }

  nb_str[len] = (nb < 10 ? nb + '0' : nb - 10 + 'A');
  nb_str[len + 1] = '\0';

  return 1 + len;
}
