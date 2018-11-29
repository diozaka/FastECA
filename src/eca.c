#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "eca.h"

int64_t eca_assert_01(const int64_t * const data, const int64_t nsamp, const int64_t len) {
  int64_t any = 0;
#pragma omp simd reduction(|:any)
  for (int64_t i=0; i<nsamp*len; i++) {
    any |= data[i];
  }
  return ((any & ~1) == 0);
}


// data must contain 0/1 only
// outp must have size nsamp*nsamp
int eca_ktr(const int64_t * const data, const int64_t nsamp, const int64_t len,
    const int64_t delta, int64_t * const outp) {
  int64_t *zind;

  // fill indicator series zind[i,t]: is there an event in series i between t,...,t+delta?
  zind = (int64_t *) calloc(nsamp*len, sizeof (int64_t)); // excess of delta elements for simpler code
  if (!zind) {
    return 0;
  }
  for (int64_t i=0; i<nsamp; i++) {
    int64_t idx = i*len;
    for (int64_t t=0; t<len-delta; t++) {
      int64_t any = 0;
      for (int64_t d=0; d<=delta; d++) {
        any |= data[idx+t+d];
      }
      zind[idx+t] = (any > 0);
    }
  }

  // fill output matrix
#pragma omp parallel for collapse(2)
  for (int64_t i=0; i<nsamp; i++) {
    for (int64_t j=0; j<nsamp; j++) {
      int64_t sum = 0;
      int64_t idxi = i*len;
      int64_t idxj = j*len;
#pragma omp simd reduction(+:sum)
      for (int64_t t=0; t<len-delta; t++) {
        sum += ((data[idxi+t]) & (zind[idxj+t]));
      }
      outp[i*nsamp+j] = sum;
    }
  }

  free(zind);
  return 1;
}

// data must contain 0/1 only
// outp must have size nsamp*nsamp
int eca_kpr(const int64_t * const data, const int64_t nsamp, const int64_t len,
    const int64_t delta, int64_t * const outp) {
  int64_t *zind;

  // fill indicator series zind[i,t]: is there an event in series i between t-delta,...,t?
  zind = (int64_t *) calloc(nsamp*len, sizeof (int64_t)); // excess of delta elements for simpler code
  if (!zind) {
    return 0;
  }
#pragma omp parallel for
  for (int64_t i=0; i<nsamp; i++) {
    int64_t idx = i*len;
    for (int64_t t=delta; t<len; t++) {
      zind[idx+t] = 0;
      for (int64_t d=0; d<=delta; d++) {
        zind[idx+t] += data[idx+t-d];
      }
      if (zind[idx+t] > 1) zind[idx+t] = 1;
    }
  }

  // fill output matrix
#pragma omp parallel for collapse(2)
  for (int64_t i=0; i<nsamp; i++) {
    for (int64_t j=0; j<nsamp; j++) {
      int64_t sum = 0;
      int64_t idxi = i*len;
      int64_t idxj = j*len;
#pragma omp simd reduction(+:sum)
      for (int64_t t=delta; t<len; t++) {
        sum += ((data[idxj+t]) & (zind[idxi+t]));
      }
      outp[i*nsamp+j] = sum;
    }
  }

  free(zind);
  return 1;
}

void eca_rtr(const int64_t * const ktr, const int64_t nsamp, double * const outp) {
#pragma omp parallel for collapse(2)
  for (int64_t i=0; i<nsamp; i++) {
    for (int64_t j=0; j<nsamp; j++) {
      outp[i*nsamp+j] = ((double) ktr[i*nsamp+j])/ktr[i*nsamp+i];
    }
  }
}

void eca_rpr(const int64_t * const kpr, const int64_t nsamp, double * const outp) {
#pragma omp parallel for collapse(2)
  for (int64_t i=0; i<nsamp; i++) {
    for (int64_t j=0; j<nsamp; j++) {
      outp[i*nsamp+j] = ((double) kpr[i*nsamp+j])/kpr[j*nsamp+j];
    }
  }
}
