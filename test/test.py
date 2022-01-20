import lindo
import numpy as np
import os

"""
    test_pyLindo_version():

    A simple test method that loads a license key, creates an environment
    then checks the major and minor version of the Lindo API.

"""
def test_pyLindo_version():
    correct_major = 13
    correct_minor = 0
    pnMajor = np.array([-1],dtype=np.int32)
    pnMinor = np.array([-1],dtype=np.int32)
    pnErrorCode = np.array([-1],dtype=np.int32)
    LicenseKey = np.array('',dtype='S1024')
    lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
    pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)
    errorcode = lindo.pyLSgetEnvIntParameter(pEnv,lindo.LS_IPARAM_VER_MAJOR,pnMajor)
    geterrormessage(pEnv,errorcode)
    errorcode = lindo.pyLSgetEnvIntParameter(pEnv,lindo.LS_IPARAM_VER_MINOR,pnMinor)
    geterrormessage(pEnv,errorcode)

    if pnMajor[0] != correct_major or pnMinor[0] != correct_minor:
        print("Test Failed")
    else:
        print("Passed")

    #delete LINDO model pointer
    errorcode = lindo.pyLSdeleteModel(pModel)
    geterrormessage(pEnv,errorcode)

    #delete LINDO environment pointer
    errorcode = lindo.pyLSdeleteEnv(pEnv)
    geterrormessage(pEnv,errorcode)





if __name__ == '__main__':
    test_pyLindo_version()
