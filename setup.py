from distutils.core import setup, Extension

module = Extension("openf4", sources=["src/openf4.cpp"], libraries=["openf4"])

setup (
  name = 'openf4',
  version = '1.0',
  description = 'libopenf4(http://nauotit.github.io/openf4/) for Python',
  ext_modules = [module])
