import numpy as _numpy
from scipy.stats import binom as _binom

def ktr_bernoulli(data, ktrmat, delta):
    nemat = _numpy.repeat(_numpy.diag(ktrmat).reshape(-1,1), ktrmat.shape[0], axis=1)
    pimat = _numpy.repeat(1-_numpy.power(1-data.sum(axis=1)/data.shape[1], delta+1).reshape(1,-1), data.shape[0], axis=0)
    pvals = ((1-_binom.cdf(ktrmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1))).reshape(ktrmat.shape)
                 + _binom.pmf(ktrmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1)).reshape(ktrmat.shape))
    return pvals, nemat, pimat

def kpr_bernoulli(data, kprmat, delta):
    nemat = _numpy.repeat(_numpy.diag(kprmat).reshape(1,-1), kprmat.shape[0], axis=0)
    pimat = _numpy.repeat(1-_numpy.power(1-data.sum(axis=1)/data.shape[1], delta+1).reshape(-1,1), data.shape[0], axis=1)
    pvals = ((1-_binom.cdf(kprmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1))).reshape(kprmat.shape)
                 + _binom.pmf(kprmat.reshape(-1), nemat.reshape(-1), pimat.reshape(-1)).reshape(kprmat.shape))
    return pvals, nemat, pimat

