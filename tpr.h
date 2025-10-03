#pragma once

#ifndef TPR_H
#define TPR_H

#include <inttypes.h>
#include <time.h>

#include <openssl/rand.h>

#include <arpa/inet.h>

typedef struct __attribute__((packed)) tpr_clg {
  uint32_t _ts;
  uint32_t _rand;
} tpr_clg_t;

static inline tpr_clg_t tpr_mk_clg() {
  time_t ts = 0;
  tpr_clg_t clg = {0};

  RAND_bytes((uint8_t *)&clg._rand, sizeof(clg._rand));

  clg._rand = htonl(clg._rand);

  ts = time(NULL);

  clg._ts = ntohl(ts);

  return clg;
}

// Str save in internal static str
static inline const char *tpr_str_clg(const tpr_clg_t clg) {
  static char buffer[9] = {0};

  snprintf(buffer, 9, "%04X%04x", ntohl(clg._rand) & 0xFFFF,
           ntohl(clg._ts) & 0xFFFF);
  return buffer;
}

#endif
