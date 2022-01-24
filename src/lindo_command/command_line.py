from distutils.sysconfig import get_python_lib
import platform
import os
import sys


class BuildData():

    def __init__(self):
        self.MAJOR = "13"
        self.MINOR = "0"
        self.API_HOME = os.environ.get('LINDOAPI_HOME')
        self.platform = platform.system()
        self.is_64bits = sys.maxsize > 2**32
        self.lindoPath = os.path.join(get_python_lib(
            plat_specific=1), 'lindo')


def main():
    bd = BuildData()
    if bd.platform == "Darwin":
        libname = "liblindo64." + bd.MAJOR + "." + bd.MINOR + ".dylib"
        binpath = os.path.join("bin/osx64x86/", libname)
    else:
        libname = "lindo64_" + bd.MAJOR + "_" + bd.MINOR + ".dll"
        binpath = os.path.join("bin/win64/", libname)

    lindoPath = os.path.join(bd.API_HOME, binpath)
    linkPath = os.path.join(bd.lindoPath, libname)
    print(os.path.islink(linkPath))
    try:
        os.symlink(lindoPath, linkPath)
        print("symbolic link created")
    except Exception:
        if os.path.exists(linkPath):
            print("Symbolic link already exists")
        else:
            print("Faild to create symbolic link")
