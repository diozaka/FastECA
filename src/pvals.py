import numpy as _numpy
from scipy.stats import binom as _binom

# data: (nsamp, len) input matrix with event series
# ktrmat: (nsamp, nsamp) input matrix with pairwise numbers of trigger coincidences
# delta: time tolerance
# returns (pvals, nemat, pimat), with
#    pvals: (nsamp, nsamp) output matrix with p-values for the pairwise numbers of trigger coincidences
#    nemat: (nsamp, nsamp) output matrix with maximum numbers of trigger coincidences for every pair
#    pimat: (nsamp, nsamp) output matrix with trigger coincidence probabilities \pi for every pair
def ktr_bernoulli(data, ktrmat, delta):
    nemat = _numpy.repeat(_numpy.diag(ktrmat).reshape(-1,1), ktrmat.shape[0], axis=1)
    pimat = _numpy.repeat(1-_numpy.power(1-data.sum(axis=1)/data.shape[1], delta+1).reshape(1,-1), data.shape[0], axis=0)
    pvals = ((1-_binom.cdf(ktrmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1))).reshape(ktrmat.shape)
                 + _binom.pmf(ktrmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1)).reshape(ktrmat.shape))
    return pvals, nemat, pimat

# data: (nsamp, len) input matrix with event series
# ktrmat: (nsamp, nsamp) input matrix with pairwise numbers of precursor coincidences
# delta: time tolerance
# returns (pvals, nemat, pimat), with
#    pvals: (nsamp, nsamp) output matrix with p-values for the pairwise numbers of precursor coincidences
#    nemat: (nsamp, nsamp) output matrix with maximum numbers of precursor coincidences for every pair
#    pimat: (nsamp, nsamp) output matrix with precursor coincidence probabilities \pi for every pair
def kpr_bernoulli(data, kprmat, delta):
    nemat = _numpy.repeat(_numpy.diag(kprmat).reshape(1,-1), kprmat.shape[0], axis=0)
    pimat = _numpy.repeat(1-_numpy.power(1-data.sum(axis=1)/data.shape[1], delta+1).reshape(-1,1), data.shape[0], axis=1)
    pvals = ((1-_binom.cdf(kprmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1))).reshape(kprmat.shape)
                 + _binom.pmf(kprmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1)).reshape(kprmat.shape))
    return pvals, nemat, pimat

