
from setuptools import setup, Extension, find_packages
from distutils.sysconfig import get_python_lib
import os
import sys
import sysconfig

try:
    import numpy
except Exception:
    print('\nWarning: numpy was not found, installing...\n')
    import subprocess
    subprocess.call([sys.executable, "-m", "pip", "install", "numpy"])

# include the numpy library
numpyinclude = os.path.join(get_python_lib(
      plat_specific=True), 'numpy/core/include/numpy')

setupDir = os.path.dirname(__file__)
# Gets the long description from README FILE
readmeFn =  os.path.join(setupDir, "README.md")
with open(readmeFn, encoding="utf-8") as f:
        long_description = f.read()
        f.close()

extension = Extension(
                name="lindo.lindo",
                define_macros = [('_LINDO_DLL_','')],
                sources = ["src/lindo/pyLindo.c"],
                library_dirs  = ['C:/Lindoapi/lib/win64', 'C:/Lindoapi/bin/win64'],
                libraries     = ["Lindo64_13_0"],
                include_dirs  = ['C:/Lindoapi/include', numpyinclude],
                )

kwargs = {
        "name" : "lindo",
        "version" : "1.0.0",
        "description" : "Python interface to LINDO API",
        "long_description" : long_description,
        "long_description_content_type" : "text/markdown",
        "author" : "Lindo Systems, Inc.",
        "author_email" : "support@lindo.com",
        "url" : "http://www.lindo.com",
        "classifiers" : [
                "Programming Language :: Python :: 3",
                "Programming Language :: Python :: 3.6",
                "Programming Language :: Python :: 3.7",
                "Programming Language :: Python :: 3.8",
                "Programming Language :: Python :: 3.9",
                "Programming Language :: Python :: 3 :: Only",
        ],
        "python_requires" :">=3.6",
        "install_requires" : ["numpy"],
        "ext_modules" : [extension],
        "packages" : find_packages(where="src"),
        "package_dir" : {"": "src"},
        "package_data": {"lindo" : ["*.txt"]},
}

setup(**kwargs)
