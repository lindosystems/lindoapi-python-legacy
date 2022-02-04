from .LSconst import *
from .lindo import *
import numpy as N

def geterrormessage(pEnv, errorcode):
    if errorcode != LSERR_NO_ERROR:
        errormessage = N.array('', dtype='S256')
        pyLSgetErrorMessage(pEnv, errorcode, errormessage)
        print("Error:", errorcode, errormessage)
        pyLSdeleteEnv(pEnv)
        exit(1)


def getversion(pEnv):
    pnMajor = N.array([-1], dtype=N.int32)
    pnMinor = N.array([-1], dtype=N.int32)
    pnRevis = N.array([-1], dtype=N.int32)
    pnArchId = N.array([-1], dtype=N.int32)

    errorcode = pyLSgetEnvIntParameter(
        pEnv, LS_IPARAM_VER_MAJOR, pnMajor)
    # geterrormessage(pEnv,errorcode)
    errorcode = pyLSgetEnvIntParameter(
        pEnv, LS_IPARAM_VER_MINOR, pnMinor)
    # geterrormessage(pEnv,errorcode)
    errorcode = pyLSgetEnvIntParameter(
        pEnv, LS_IPARAM_VER_REVISION, pnRevis)
    # geterrormessage(pEnv,errorcode)
    errorcode = pyLSgetInfo(None, LS_IINFO_ARCH_ID, pnArchId)
    if True:
        version = N.array('', dtype='S256')
        builton = N.array('', dtype='S256')
        pyLSgetVersionInfo(version, builton)
        version = version.astype('U')
        builton = builton.astype('U')
        print("LINDO API Version ", version, builton)
    verstr = "LINDO API Version %d.%d.%d, Arch %d" % (
        pnMajor[0], pnMinor[0], pnRevis[0], pnArchId[0])
    return verstr