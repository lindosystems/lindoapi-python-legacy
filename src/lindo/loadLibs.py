from distutils.sysconfig import get_python_lib
import os
import sys
import subprocess
import platform
import glob

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

def setSymLink(src, dest):
     try:
         os.symlink(src,  dest)
     except Exception:
         pass
#
# mac(bd:BuildData)
# This function adds the Lindo API bin path to the 
# environment variable DYLD_LIBRARY_PATH if it is
# not already included.
#
def mac(bd:BuildData):
    if bd.is_64bits:
        binPath= os.path.join(bd.API_HOME,"bin/osx64x86")
    else:
        binPath= os.path.join(bd.API_HOME,"bin/osx32x86")

    dylibList = glob.glob(os.path.join(binPath, "*.dylib"))
    for dylibPath in dylibList:
        dylibName = str.split(dylibPath, sep="/")[-1]
        linkPath = os.path.join(bd.pylindoPath, dylibName)
        setSymLink(dylibPath, linkPath)
        
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
        pass
    else:
        mac(bd)
main()