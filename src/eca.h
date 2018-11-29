#ifndef ECA_H
#define ECA_H

#define ECA_VERSION "0.0"

#include <stdint.h>

// returns 1 if all values are either 0 or 1, and 0 otherwise
int64_t eca_assert_01(const int64_t * const data, const int64_t nsamp, const int64_t len);

// compute nsamp*nsamp vector with precursor/trigger coincidence matrix (in row-major order)
int eca_kpr(const int64_t * const data, const int64_t nsamp, const int64_t len,
    const int64_t delta, int64_t * const outp);
int eca_ktr(const int64_t * const data, const int64_t nsamp, const int64_t len,
    const int64_t delta, int64_t * const outp);

// compute nsamp*nsamp vector with precursor/trigger coincidence rate matrix (in row-major order)
void eca_rpr(const int64_t * const kpr, const int64_t nsamp, double * const outp);
void eca_rtr(const int64_t * const kpr, const int64_t nsamp, double * const outp);

#endif
