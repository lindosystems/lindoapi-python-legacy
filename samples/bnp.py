#  Solve an MIP with block structure using the BNP solver.
#
#  The problem:
#
#      Minimize x1 + x2 + x3 + x4 + x5 + x6
#      s.t.
#               [r1]x1 + x2 + x3 + x4 + x5 + x6  >=3; !block 0 - linking constraint;
#               [r2]x1 + x2                      <=1; !block 1;
#               [r3]     x2 + x3                 <=1; !block 1;
#               [r4]               x4 + x5 + x6  <=2; !block 2;
#               [r5]               x4 +      x6  <=1; !block 2;
#
#               x1,x2,x3,x4,x5,x6 are binary variables

from pyLindo import *
import os
#model data
nCons = 5
nVars = 6
nDir = 1
dObjConst = 0.0
adC = N.array([1.,1.,1.,1.,1.,1.],dtype=N.double)
adB = N.array([3.0,1.0,1.0,2.0,1.0],dtype=N.double)
acConTypes = N.array(['G','L','L','L','L'],dtype=N.character)
nNZ = 15;
anBegCol = N.array([0,2,5,7,10,12,15],dtype=N.int32)
pnLenCol = N.asarray(None)
adA = N.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0],dtype=N.double)
anRowX = N.array([0,1,0,1,2,0,2,0,3,4,0,3,0,3,4],dtype=N.int32)
pdLower = N.array([0,0,0,0,0,0],dtype=N.double)
pdUpper = N.array([1.,1.,1.,1.,1.,1.],dtype=N.double)
pachVarType = N.array(['B','B','B','B','B','B'],dtype=N.character)

#create LINDO environment and model objects
LicenseKey = N.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = N.array([-1],dtype=N.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])

#load data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel,nCons,nVars,nDir,
                                 dObjConst,adC,adB,acConTypes,nNZ,anBegCol,
                                 pnLenCol,adA,anRowX,pdLower,pdUpper)
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSloadVarType(pModel,pachVarType)

#load block structure
panRblock = N.array([0,1,1,2,2],dtype=N.int32)
panCblock = N.array([1,1,1,2,2,2],dtype=N.int32)
nBlock = 2
nType = LSconst.LS_LINK_BLOCKS_FREE
errorcode = lindo.pyLSloadBlockStructure(pModel,
                                         nBlock + 1,
                                         panRblock,
                                         panCblock,
                                         nType)
geterrormessage(pEnv,errorcode)

#set the method for finding block
nMethod = 5
errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           LSconst.LS_IPARAM_BNP_FIND_BLK,
                                           nMethod)
geterrormessage(pEnv,errorcode)

#solve the model using BNP
print("\nSolving the model...")
pnStatus = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSsolveMipBnp(pModel,nBlock,"ddd",pnStatus)
geterrormessage(pEnv,errorcode)

#retrieve the objective value
dObj = N.array([-1.0],dtype=N.double)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_DINFO_MIP_OBJ,dObj)
geterrormessage(pEnv,errorcode)
print("Objective is: %.5f" %dObj[0])
print("")

#retrieve the primal solution
padPrimal = N.empty((nVars),dtype=N.double)
errorcode = lindo.pyLSgetMIPPrimalSolution(pModel,padPrimal)
geterrormessage(pEnv,errorcode)
print("Primal solution is: ")
for x in padPrimal: print("%.5f" % x)

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

