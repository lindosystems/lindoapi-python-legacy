#  A Python programming example of interfacing with LINDO API.
#
#  The problem:
#
#      Minimize x1 + x2 + x3 + x4
#      s.t.
#              3x1              + 2x4   = 20
#                    6x2        + 9x4  >= 20
#              4x1 + 5x2 + 8x3          = 40
#                    7x2 + 1x3         >= 10
#
#               2 <= x1 <= 5
#               1 <= x2 <= +inf
#            -inf <= x3 <= 10
#            -inf <= x4 <= +inf

from pyLindo import *
import os
#model data
nCons = 4
nVars = 4
nDir = 1
dObjConst = 0.0
adC = N.array([1.,1.,1.,1.],dtype=N.double)
adB = N.array([20.0,20.0,40.0,10.0],dtype=N.double)
acConTypes = N.array(['E','G','E','G'],dtype=N.character)
nNZ = 9;
anBegCol = N.array([0,2,5,7,9],dtype=N.int32)
pnLenCol = N.asarray(None)
adA = N.array([3.0,4.0,6.0,5.0,7.0,8.0,1.0,2.0,9.0],dtype=N.double)
anRowX = N.array([0,2,1,2,3,2,3,0,1],dtype=N.int32)
pdLower = N.array([2,1,-LSconst.LS_INFINITY,-LSconst.LS_INFINITY],dtype=N.double)
pdUpper = N.array([5,LSconst.LS_INFINITY,10,LSconst.LS_INFINITY],dtype=N.double)

#create LINDO environment and model objects
LicenseKey = N.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = N.array([-1],dtype=N.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)

print(getversion(pEnv))


pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])

#load data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel,nCons,nVars,nDir,
                                 dObjConst,adC,adB,acConTypes,nNZ,anBegCol,
                                 pnLenCol,adA,anRowX,pdLower,pdUpper)
geterrormessage(pEnv,errorcode)

#solve the model
print("Solving the model...")
pnStatus = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSoptimize(pModel,LSconst.LS_METHOD_FREE,pnStatus)
geterrormessage(pEnv,errorcode)

#retrieve the objective value
dObj = N.array([-1.0],dtype=N.double)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_DINFO_POBJ,dObj)
geterrormessage(pEnv,errorcode)
print("Objective is: %.5f" %dObj[0])
print("")

#retrieve the primal solution and variable types
varType = N.empty((nVars),dtype=N.byte)
errorcode = lindo.pyLSgetVarType(pModel,varType)
geterrormessage(pEnv,errorcode)

padPrimal = N.empty((nVars),dtype=N.double)
errorcode = lindo.pyLSgetPrimalSolution(pModel,padPrimal)
geterrormessage(pEnv,errorcode)
print("Primal solution is: ")
for k,x in enumerate(padPrimal): 
    print("%.5f %c" % (padPrimal[k],varType[k]))
    
#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

