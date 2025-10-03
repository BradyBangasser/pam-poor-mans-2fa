#include <openssl/pem.h>

#include <arpa/inet.h>
#include <stdlib.h>

#include "tpr.h"

int main(int argc, char *argv[]) {
  char buffer[5] = {0};
  uint16_t cts = 0;
  uint16_t crand = 0;

  memcpy(buffer, argv[1], 4);
  crand = strtol(buffer, NULL, 16);

  memcpy(buffer, argv[1] + 4, 4);
  cts = strtol(buffer, NULL, 16);

  return 0;
}
