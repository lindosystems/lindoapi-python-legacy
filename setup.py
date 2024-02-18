import sys
import os
import platform
from distutils.core import setup, Extension
from distutils.sysconfig import get_python_lib 
import fileinput

try:
  import numpy
except:
  print('\nWarning: numpy was not found, installing...\n')
  import subprocess
  subprocess.call([sys.executable, "-m", "pip", "install", "numpy"])
  

__verbose=True
###################################################
def ls_get_version(filename):
    iLine = 0
    for line in fileinput.input(filename):
        if __verbose:
            print(line.split())
        if line.find("LS_MAJOR")>=0:
            tmp = line.split("=")
            szMajorVer = tmp[1]
        elif line.find("LS_MINOR")>=0:
            tmp = line.split("=")
            szMinorVer = tmp[1]
            
        iLine = iLine + 1
    szMajorVer=szMajorVer[0:-1]
    szMinorVer=szMinorVer[0:-1]
    
    LSVERSION = {'major':szMajorVer, 'minor': szMinorVer}
    print(LSVERSION)
    return LSVERSION, szMajorVer, szMinorVer
    
#Environment variable LINDOAPI_HOME must be set
API_HOME = os.environ.get('LINDOAPI_HOME')

if API_HOME == None:
    print("Environment variable LINDOAPI_HOME is empty!")
    exit(0)

LSVERSION,szMajorVer,szMinorVer = ls_get_version(API_HOME + "/include/lsversion.sh")
#sys.exit(1)
platform = platform.system()
is_64bits = sys.maxsize > 2**32

#For Windows
if platform == 'Windows' or platform == "CYGWIN_NT-6.3":
    IncludePath = API_HOME + '/include'
    if is_64bits:
        LibPath = API_HOME + '/bin/win64'        
        LindoLib = 'lindo64_' + szMajorVer + '_' + szMinorVer
        if not os.path.isfile(LibPath + '/' + LindoLib + '.dll'):
            print("Cannot find 64-bit LINDO API.");
            exit(0);
    else:
        LibPath = API_HOME + '/bin/win32'
        LindoLib = 'lindo' +  szMajorVer + '_' + szMinorVer
        if not os.path.isfile(LibPath + '/' + LindoLib + '.dll'):
            print("Cannot find 32-bit LINDO API.");
            exit(0);
        
#For Linux
elif platform == 'Linux':
    IncludePath = API_HOME + '/include'
    if is_64bits:
        LibPath = API_HOME + '/bin/linux64'
        LindoLib = 'lindo64'
        if not os.path.isfile(LibPath + '/lib' + LindoLib + '.so'):
            print("Cannot find 64-bit LINDO API.");
            exit(0);
    else:
        LibPath = API_HOME + '/bin/linux32'
        LindoLib = 'lindo'
        if not os.path.isfile(LibPath + '/lib' + LindoLib + '.so'):
            print("Cannot find 32-bit LINDO API.");
            exit(0);

#For Mac OS X
elif platform == 'Darwin':
    IncludePath = API_HOME + '/include'
    if is_64bits:
        LibPath = API_HOME + '/bin/osx64x86'
        LindoLib = 'lindo64'
        if not os.path.isfile(LibPath + '/lib' + LindoLib + '.dylib'):
            print(LibPath + '/lib' + LindoLib + '.so');
            print("Cannot find 64-bit LINDO API.");
            exit(0);
    else:
        LibPath = API_HOME + '/bin/osx32x86'
        LindoLib = 'lindo'
        if not os.path.isfile(LibPath + '/lib' + LindoLib + '.dylib'):
            print("Cannot find 32-bit LINDO API.");
            exit(0);

else:
    print("System not supported!")
    
numpyinclude = os.path.join(get_python_lib(plat_specific=1), 'numpy/core/include/numpy')

#For Windows
if platform == 'Windows' or platform == "CYGWIN_NT-6.3":
    lindomodule = Extension('pyLindo.lindo',
                            define_macros = [('_LINDO_DLL_','')],
                            include_dirs = [IncludePath, numpyinclude],
                            library_dirs = [LibPath, LibPath.replace("bin","lib"), 'c:/usr/Python38'],
                            libraries = [LindoLib],
                            extra_link_args=['-Wl,--enable-stdcall-fixup'],
                            sources = ['pyLindo/pyLindo.c'])
#For Linux
elif platform == 'Linux':
    lindomodule = Extension('pyLindo.lindo',
                            include_dirs = [IncludePath, numpyinclude],
                            library_dirs = [LibPath],
                            libraries = [LindoLib],
                            extra_link_args = ['-Wl,-rpath-link,' + LibPath + ' -Wl,-rpath,' + LibPath],
                            sources = ['pyLindo/pyLindo.c'])

#For Mac OS X
elif platform == 'Darwin':
    lindomodule = Extension('pyLindo.lindo',
                            include_dirs = [IncludePath, numpyinclude],
                            library_dirs = [LibPath],
                            libraries = [LindoLib],
                            extra_link_args = ['-Wl,-rpath,' + LibPath],
                            sources = ['pyLindo/pyLindo.c'])

setup(name = 'pyLindo',
      version = '13.0.1',
      description = 'Python interface to LINDO API',
      author = 'Lindo Systems, Inc.',
      author_email = 'support@lindo.com',
      url = 'http://www.lindo.com',
      platforms = ['any'],
      ext_modules = [lindomodule],
      packages = ['pyLindo'],
      package_data = {'pyLindo': ['*.txt', 'pyLindo.c']},
      )

#For Mac OS X, change install name
if platform == 'Darwin' and sys.argv[1] == 'install':
    print("changing the install name of pyLindo package")
    pyLindoPath = os.path.join(get_python_lib(plat_specific=1), 'pyLindo')
    if is_64bits:
        command = 'install_name_tool -change @loader_path/liblindo64.dylib ' + API_HOME + '/bin/osx64x86/liblindo64.'+ szMajorVer + '.' + szMinorVer + '.dylib ' + pyLindoPath + '/lindo.so'
    else:
        command = 'install_name_tool -change @loader_path/liblindo.dylib ' + API_HOME + '/bin/osx32x86/liblindo.'+ szMajorVer + '.' + szMinorVer + '.dylib ' + pyLindoPath + '/lindo.so'
    os.system(command)
    

