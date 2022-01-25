
from setuptools import setup, Extension, find_packages
from distutils.sysconfig import get_python_lib

import os
import sys
import platform

MAJOR = "13"
MINOR = "0"


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


API_HOME = os.environ.get('LINDOAPI_HOME')
IncludePath = os.path.join(API_HOME, "include")

platform = platform.system()
is_64bits = sys.maxsize > 2**32

# For Windows
if platform == 'Windows':
    LindoLib = 'lindo64_' + MAJOR + '_' + MINOR
    if is_64bits:
        LibPath = os.path.join(API_HOME, 'lib/win64')
        BinPath = os.path.join(API_HOME, 'lib/win64')
    else:
        LibPath = os.path.join(API_HOME, 'lib/win32')
        BinPath = os.path.join(API_HOME, 'bin/win32')
    funcName = "windows"
    extra_link_args = '-Wl,--enable-stdcall-fixup'

# For Linux
elif platform == 'Linux':
    if is_64bits:
        LindoLib = 'lindo64'
        LibPath = os.path.join(API_HOME, 'lib/linux64')
        BinPath = os.path.join(API_HOME, 'bin/linux64')
    else:
        LindoLib = 'lindo'
        LibPath = os.path.join(API_HOME, 'lib/linux32')
        BinPath = os.path.join(API_HOME, 'bin/linux32')
    funcName = "linux"
    extra_link_args = '-Wl,-rpath-link,' + LibPath + ' -Wl,-rpath,' + LibPath

# For Mac OS X
elif platform == 'Darwin':
    if is_64bits:
        LindoLib = 'lindo64'
        LibPath = os.path.join(API_HOME, 'lib/osx64x86')
        BinPath = os.path.join(API_HOME, 'bin/osx64x86')
        lib = os.path.join('bin/osx64x86', LindoLib + ".dylib")
    else:
        LindoLib = 'lindo'
        LibPath = os.path.join(API_HOME, 'lib/osx32x86')
        BinPath = os.path.join(API_HOME, 'bin/osx32x86')
    funcName = "mac"
    extra_link_args = '-Wl,-rpath,' + LibPath

else:
    print("System not supported!")
    exit(0)


extension = Extension(
                name="lindo.lindo",
                define_macros=[('_LINDO_DLL_', '')],
                sources=["src/lindo/pyLindo.c"],
                library_dirs=[LibPath, BinPath],
                libraries=[LindoLib],
                include_dirs=[IncludePath, numpyinclude],
                extra_link_args=[extra_link_args],
                )

kwargs = {
        "name": "lindo",
        "version": "1.0.0",
        "description": "Python interface to LINDO API",
        "long_description": long_description,
        "long_description_content_type": "text/markdown",
        "author": "Lindo Systems, Inc.",
        "author_email": "support@lindo.com",
        "url": "http://www.lindo.com",
        "classifiers": [
                "Programming Language :: Python :: 3",
                "Programming Language :: Python :: 3.6",
                "Programming Language :: Python :: 3.7",
                "Programming Language :: Python :: 3.8",
                "Programming Language :: Python :: 3.9",
                "Programming Language :: Python :: 3 :: Only",
        ],
        "python_requires": ">=3.6",
        "install_requires": ["numpy >= 1.14.0"],
        "ext_modules": [extension],
        "packages": find_packages(where="src"),
        "package_dir": {"": "src"},
        "package_data": {"lindo": ["*.txt"]},
        "entry_points": {
                'console_scripts': [
                    'link_lindo=lindo_command.command_line:'+funcName,
                ],
            },

}

setup(**kwargs)
