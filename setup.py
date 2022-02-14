"""
    setup.py

    This script is for building the lindo python package.
"""
from setuptools import setup, Extension, find_packages
from distutils.sysconfig import get_python_lib

import os
import sys
import platform

VERSION = "13.0.0"

class BuildData():
    """
    BuildData()

    A class for holding data about Operating system
    and Lindo location/ version

    """
    def __init__(self):
        self.MAJOR = "13"
        self.MINOR = "0"
        self.API_HOME = os.environ.get('LINDOAPI_HOME')
        self.IncludePath = os.path.join(self.API_HOME , "include")
        self.platform = platform.system()
        self.is_64bits = sys.maxsize > 2**32


bd = BuildData()

try:
    import numpy
except Exception:
    print('\nWarning: numpy was not found, installing...\n')
    import subprocess
    subprocess.call([sys.executable, "-m", "pip", "install", "numpy"])

# include the numpy library
numpyinclude = os.path.join(get_python_lib(
      plat_specific=True), 'numpy/core/include/numpy')

# Gets the long description from README FILE
setupDir = os.path.dirname(__file__)
readmeFn = os.path.join(setupDir, "README.md")
with open(readmeFn, encoding="utf-8") as f:
    long_description = f.read()
    f.close()


# For Windows
if bd.platform == 'Windows':
    LindoLib = 'lindo64_' + bd.MAJOR + '_' + bd.MINOR
    if bd.is_64bits:
        LibPath = os.path.join(bd.API_HOME, 'lib/win64')
        BinPath = os.path.join(bd.API_HOME, 'lib/win64')
    else:
        LibPath = os.path.join(bd.API_HOME, 'lib/win32')
        BinPath = os.path.join(bd.API_HOME, 'bin/win32')
    extra_link_args = '-Wl,--enable-stdcall-fixup'
    macros = [('_LINDO_DLL_', '')]

# For Linux
elif bd.platform == 'Linux':
    if bd.is_64bits:
        LindoLib = 'lindo64'
        LibPath = os.path.join(bd.API_HOME, 'lib/linux64')
        BinPath = os.path.join(bd.API_HOME, 'bin/linux64')
    else:
        LindoLib = 'lindo'
        LibPath = os.path.join(bd.API_HOME, 'lib/linux32')
        BinPath = os.path.join(bd.API_HOME, 'bin/linux32')
    extra_link_args = '-Wl,-rpath='+BinPath
    macros = []

# For Mac OS X
elif bd.platform == 'Darwin':
    if bd.is_64bits:
        LindoLib = 'lindo64'
        LibPath = os.path.join(bd.API_HOME, 'lib/osx64x86')
        BinPath = os.path.join(bd.API_HOME, 'bin/osx64x86')
        lib = os.path.join('bin/osx64x86', LindoLib + ".dylib")
    else:
        LindoLib = 'lindo'
        LibPath = os.path.join(bd.API_HOME, 'lib/osx32x86')
        BinPath = os.path.join(bd.API_HOME, 'bin/osx32x86')
        lib = os.path.join('bin/osx32x86', LindoLib + ".dylib")
    extra_link_args = '-Wl,-rpath,' + LibPath
    macros = [('_LINDO_DLL_', '')]
else:
    print("System not supported!")
    exit(0)


extension = Extension(
                name="lindo.lindo",
                sources=["src/lindo/pyLindo.c"],
                define_macros=macros,
                library_dirs=[LibPath, BinPath],
                depends=[BinPath],
                libraries=[LindoLib],
                include_dirs=[bd.IncludePath, numpyinclude],
                extra_link_args=[extra_link_args],
                )

kwargs = {
        "name": "lindo",
        "version": VERSION,
        "description": "Python interface to LINDO API",
        "long_description": long_description,
        "long_description_content_type": "text/markdown",
        "author": "Lindo Systems, Inc.",
        "author_email": "support@lindo.com",
        "url": "http://www.lindo.com",
        "classifiers": [
                "Programming Language :: Python :: 3",
                "Programming Language :: Python :: 3.7",
                "Programming Language :: Python :: 3.8",
                "Programming Language :: Python :: 3.9",
                "Programming Language :: Python :: 3.10",
                "Programming Language :: Python :: 3 :: Only",
        ],
        "python_requires": ">=3.7",
        "install_requires": ["numpy>=1.19"],
        "ext_modules": [extension],
        "packages": ["lindo", "lindo_test"],
        "package_dir": {"": "src"},
        "package_data": {"lindo": ["*.txt"]},
}

setup(**kwargs)
