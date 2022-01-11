import sys
import os
import platform
from distutils.core import setup, Extension
from distutils.sysconfig import get_python_lib
import fileinput

try:
    import numpy
except Exception:
    print('\nWarning: numpy was not found, installing...\n')
    import subprocess
    subprocess.call([sys.executable, "-m", "pip", "install", "numpy"])

###################################################
# Environment variable LINDOAPI_HOME must be set
API_HOME = os.environ.get('LINDOAPI_HOME')
if API_HOME == None:
    print("Environment variable LINDOAPI_HOME is empty!")
    exit(0)
# Version numbers from API_HOME/include/lsversion.sh
szMajorVer = '13'
szMinorVer = '0'
# Path to API for windows 64
IncludePath = API_HOME + '/include'
LibPath = API_HOME + '/bin/win64'
LindoLib = 'lindo64_' + szMajorVer + '_' + szMinorVer
if not os.path.isfile(LibPath + '/' + LindoLib + '.dll'):
    print("Cannot find 64-bit LINDO API.")
    exit(0)
# include the numpy library
numpyinclude = os.path.join(get_python_lib(
  plat_specific=1), 'numpy/core/include/numpy')
# Description of the module written in C
lindomodule = Extension('pyLindo.lindo',
                        define_macros=[('_LINDO_DLL_', '')],
                        include_dirs=[IncludePath, numpyinclude],
                        library_dirs=[LibPath, LibPath.replace(
                          "bin", "lib"), 'c:/usr/Python38'],
                        libraries=[LindoLib],
                        extra_link_args=['-Wl,--enable-stdcall-fixup'],
                        sources=['src/pyLindo.c'])
# The gateway to the Distutils
setup(name='pyLindo',
      version='13.0.1',
      description='Python interface to LINDO API',
      author='Lindo Systems, Inc.',
      author_email='support@lindo.com',
      url='http://www.lindo.com',
      platforms=['any'],
      ext_modules=[lindomodule],
      packages=['src'],
      package_data={'pyLindo': ['*.txt', 'pyLindo.c']})
