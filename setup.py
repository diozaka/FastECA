from setuptools import setup, Extension
import numpy, os

def read(fname):
  return open(os.path.join(os.path.dirname(__file__), fname)).read()

mod = Extension('FastECA._eca',
  include_dirs = [numpy.get_include()],
  sources = ['src/eca.c', 'src/pyeca.c'],
  extra_compile_args=['-fopenmp','-O3', '-march=native', '-mavx'],
  extra_link_args=['-fopenmp']
)

setup(
  name = 'FastECA',
  version = '0.1',
  author = 'Erik Scharwaechter',
  author_email = 'scharwaechter@bit.uni-bonn.de',
  license = 'MIT',
  description='Fast Event Coincidence Analysis',
  long_description=read('README.md'),

  ext_modules = [mod],
  packages = {'FastECA'},
  package_dir = {'FastECA' : 'src'},

  install_requires = ['numpy', 'scipy']
)
