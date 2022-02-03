"""
    link.py
    This module is used to build the entry_points from setup.py
    The command link_lindo creates a symbolic link between the
    Lindo binaries to the python library.
"""


from distutils.sysconfig import get_python_lib
import platform
import os
import sys
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
        self.platform = platform.system()
        self.is_64bits = sys.maxsize > 2**32
        self.pylindoPath = os.path.join(get_python_lib(
             plat_specific=1), 'lindo')

def setSymLink(src, dest):
    print(src," -> ", dest)
    try:
        os.symlink(src,  dest)
        print("Symbolic link created")
    except Exception:
        if os.path.exists(dest) and os.path.islink(dest):
            print("Symbolic link already exists")
        elif os.path.islink(dest):
            print("Broken link")
        else:
            print("Faild to create link")

"""
    linux is going to temporarily add lindo to LD_LIBRARY_PATH
    
"""
def linux(bd:BuildData):
    binPath = "bin/linux64/"
    lindoPath = os.path.join(bd.API_HOME, binPath)
    LD_LIBRARY_PATH = "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"+lindoPath
    exportCMD = "export LD_LIBRARY_PATH"
    print("Temporarily adding Lindo API to the dynamic library path environment variable")
    os.system(LD_LIBRARY_PATH )
    os.system(exportCMD)
    print("=============================================================")
    print("#Copy below to .bashrc")
    print("#Adds the Lindo API to the dynamic library path environment variable")
    print(LD_LIBRARY_PATH)
    print(exportCMD)
    print("=============================================================")
    
"""
    Mac OS command
    Links the liblindo dylib to the lindo python library
"""
def mac(bd:BuildData):
    binPath = os.path.join(bd.API_HOME, "bin/osx64x86")
    dylibList = glob.glob(os.path.join(binPath, "*.dylib"))
    for dylibPath in dylibList:
        dylibName = str.split(dylibPath, sep="/")[-1]
        linkPath = os.path.join(bd.pylindoPath, dylibName)
        setSymLink(dylibPath, linkPath)
"""
    Windows command
    Links every Lindo .dll to the python library
"""
def windows(bd:BuildData):
    binPath = os.path.join(bd.API_HOME,"bin/win64/")
    dllList = glob.glob(os.path.join(binPath, "*.dll"))
    for dllPath in dllList:
        dllName = str.split(dllPath, sep="\\")[-1]
        linkPath = os.path.join(bd.pylindoPath, dllName)
        setSymLink(dllPath, linkPath)