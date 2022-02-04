import numpy as N
import os, platform,sys

#Environment variable LINDOAPI_HOME must be set
API_HOME = os.environ.get('LINDOAPI_HOME')

if API_HOME == None:
    print("Environment variable LINDOAPI_HOME should be set!")
    exit(0)
    
platform = platform.system()
is_64bits = sys.maxsize > 2**32

#For Windows
if platform == 'Windows' or platform == "CYGWIN_NT-6.3":
    if is_64bits:
        LibPath = API_HOME + '/bin/win64'        
    else:
        LibPath = API_HOME + '/bin/win32'
    os.add_dll_directory(LibPath)
        
#For Linux
elif platform == 'Linux':
    if is_64bits:
        LibPath = API_HOME + '/bin/linux64'
    else:
        LibPath = API_HOME + '/bin/linux32'

#For Mac OS X
elif platform == 'Darwin':
    if is_64bits:
        LibPath = API_HOME + '/bin/osx64x86'
    else:
        LibPath = API_HOME + '/bin/osx32x86'
else:
    print("System not supported!")
    exit(0)
print("LINDOAPI for '%s' will load from '%s'" % (platform,LibPath))


from pyLindo import LSconst
from pyLindo import lindo

def geterrormessage(pEnv,errorcode):
    if errorcode != LSconst.LSERR_NO_ERROR:
        errormessage = N.array('',dtype='S256')
        lindo.pyLSgetErrorMessage(pEnv,errorcode,errormessage)
        print("Error:",errorcode,errormessage)
        lindo.pyLSdeleteEnv(pEnv)
        exit(1)

def getversion(pEnv):
    pnMajor = N.array([-1],dtype=N.int32)
    pnMinor = N.array([-1],dtype=N.int32)
    pnRevis = N.array([-1],dtype=N.int32)
    pnArchId = N.array([-1],dtype=N.int32)

    errorcode = lindo.pyLSgetEnvIntParameter(pEnv,LSconst.LS_IPARAM_VER_MAJOR,pnMajor)
    #geterrormessage(pEnv,errorcode)
    errorcode = lindo.pyLSgetEnvIntParameter(pEnv,LSconst.LS_IPARAM_VER_MINOR,pnMinor)
    #geterrormessage(pEnv,errorcode)
    errorcode = lindo.pyLSgetEnvIntParameter(pEnv,LSconst.LS_IPARAM_VER_REVISION,pnRevis)
    #geterrormessage(pEnv,errorcode)
    errorcode = lindo.pyLSgetInfo(None,LSconst.LS_IINFO_ARCH_ID,pnArchId)
    if True:
        version = N.array('',dtype='S256')
        builton = N.array('',dtype='S256')
        lindo.pyLSgetVersionInfo(version,builton)        
        version = version.astype('U')
        builton = builton.astype('U')
        print("LINDO API Version ",version,builton)
    verstr = "LINDO API Version %d.%d.%d, Arch %d" % (pnMajor[0],pnMinor[0],pnRevis[0],pnArchId[0])    
    return verstr