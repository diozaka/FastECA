#ifndef ECA_H
#define ECA_H

#define ECA_VERSION "0.0"

#include <stdint.h>

// data: (nsamp, len) matrix in row-major order
// nsamp: number of samples
// len: length of the event series
// returns 1 if all values are either 0 or 1, and 0 otherwise
int64_t eca_assert_01(const int64_t * const data, const int64_t nsamp, const int64_t len);

// data: (nsamp, len) input matrix in row-major order
// nsamp: number of samples
// len: length of the event series
// delta: time tolerance
// outp: preallocated (nsamp, nsamp) output matrix for the pairwise numbers of
//       precursor/trigger coincidences (stored in row-major order)
// returns 1 if successful, and 0 otherwise
int eca_kpr(const int64_t * const data, const int64_t nsamp, const int64_t len,
    const int64_t delta, int64_t * const outp);
int eca_ktr(const int64_t * const data, const int64_t nsamp, const int64_t len,
    const int64_t delta, int64_t * const outp);

// kpr/ktr: (nsamp, nsamp) input matrix with pairwise numbers of precursor/trigger
//          coincidences (in row-major order)
// nsamp: number of samples
// outp: preallocated (nsamp, nsamp) output matrix for the pairwise precursor/trigger
//       coincidence rates (stored in row-major order)
void eca_rpr(const int64_t * const kpr, const int64_t nsamp, double * const outp);
void eca_rtr(const int64_t * const ktr, const int64_t nsamp, double * const outp);

#endif
