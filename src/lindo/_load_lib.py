import ctypes
import os
import sys
import platform

class Loader():
        """
        A class for loading the Lindo API DLL

        ...
        Attributes
        ----------
        apiHome: str
                Initilized from the LINDOAPI_HOME enviroment variable
        libpath: str
                path LindoAPI's to dynamic libraries
        major: str
                Major version number loaded from const.txt
        minor: str
                Minor version number loaded from const.txt
        lib: WinDLL
                A loaded DLL

        Methods
        -------
        getMajorMinor(self):
                Reads const.txt

        """
        def __init__(self):
                self.apiHome = os.environ.get('LINDOAPI_HOME')
                self.libPath = os.path.join(self.apiHome, "bin//win64")
                self.major, self.minor = self.getMajorMinor()
                self.lib = ctypes.WinDLL(os.path.join(self.libPath,
                 "lindo64" + "_" + self.major + "_" + self.minor + ".dll"))

        def getMajorMinor(self):
                constFn = os.path.join(os.path.dirname(__file__), "const.txt")
                fo = open(constFn, "r")
                majorLine = fo.readline()
                minorLine = fo.readline()
                fo.close()
                major = str.split(majorLine)[1]
                minor = str.split(minorLine)[1]
                return major, minor

loader = Loader()
