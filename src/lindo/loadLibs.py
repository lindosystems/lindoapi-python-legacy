from distutils.sysconfig import get_python_lib
import os
import sys
import platform

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
        self.pylindoPath = os.path.join(get_python_lib(
             plat_specific=1), 'lindo')

#
# mac(bd:BuildData)
# This function adds the Lindo API bin path to the 
# environment variable DYLD_LIBRARY_PATH if it is
# not already included.
#
def mac(bd:BuildData):
    if bd.is_64bits:
        lindoapi_dyld= os.path.join(bd.API_HOME,"bin/osx64x86")
    else:
        lindoapi_dyld= os.path.join(bd.API_HOME,"bin/osx32x86")
        
    DYLD_LIBRARY_PATH = os.environ["DYLD_LIBRARY_PATH"]
    if lindoapi_dyld not in DYLD_LIBRARY_PATH:
        DYLD_LIBRARY_PATH += ";"+lindoapi_dyld
        os.environ["DYLD_LIBRARY_PATH"] = DYLD_LIBRARY_PATH

#
# linux(bd:BuildData)
# This function adds the Lindo API bin path to the 
# environment variable LD_LIBRARY_PATH if it is
# not already included.
#
def linux(bd:BuildData):
    if bd.is_64bits:
        lindoapi_ld = os.path.join(bd.API_HOME,"bin/linux64/")
    else:
        lindoapi_ld = os.path.join(bd.API_HOME,"bin/linux/")

    LD_LIBRARY_PATH = os.environ["DYLD_LIBRARY_PATH"]
    if lindoapi_ld not in LD_LIBRARY_PATH:
        LD_LIBRARY_PATH += ";"+lindoapi_ld
        os.environ["LD_LIBRARY_PATH"] = LD_LIBRARY_PATH
#
# windows()
# This function adds the dll directory at 
# runtime
def windows(bd:BuildData):
    if bd.is_64bits:
        LibPath = bd.API_HOME + '/bin/win64'        
    else:
        LibPath = bd.API_HOME + '/bin/win32'
    os.add_dll_directory(LibPath)


def main():
    bd = BuildData()
    #Environment variable LINDOAPI_HOME must be set
    if bd.API_HOME == None:
        print("Environment variable LINDOAPI_HOME should be set!")
        exit(0)
    if bd.platform == 'Windows' or bd.platform == "CYGWIN_NT-6.3":
        windows(bd)
    elif bd.platform == 'Linux':
        linux(bd)
    else:
        mac(bd)
main()