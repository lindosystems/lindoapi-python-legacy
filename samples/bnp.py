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

import lindo
import numpy as np 
import os
#model data
nCons = 5
nVars = 6
nDir = 1
dObjConst = 0.0
adC = np.array([1.,1.,1.,1.,1.,1.],dtype=np.double)
adB = np.array([3.0,1.0,1.0,2.0,1.0],dtype=np.double)
acConTypes = np.array(['G','L','L','L','L'],dtype='|S1')
nNZ = 15
anBegCol = np.array([0,2,5,7,10,12,15],dtype=np.int32)
pnLenCol = np.asarray(None)
adA = np.array([1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0],dtype=np.double)
anRowX = np.array([0,1,0,1,2,0,2,0,3,4,0,3,0,3,4],dtype=np.int32)
pdLower = np.array([0,0,0,0,0,0],dtype=np.double)
pdUpper = np.array([1.,1.,1.,1.,1.,1.],dtype=np.double)
pachVarType = np.array(['B','B','B','B','B','B'],dtype='|S1')

#create LINDO environment and model objects
LicenseKey = np.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = np.array([-1],dtype=np.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
lindo.geterrormessage(pEnv,pnErrorCode[0])

#load data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel,nCons,nVars,nDir,
                                 dObjConst,adC,adB,acConTypes,nNZ,anBegCol,
                                 pnLenCol,adA,anRowX,pdLower,pdUpper)
lindo.geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSloadVarType(pModel,pachVarType)

#load block structure
panRblock = np.array([0,1,1,2,2],dtype=np.int32)
panCblock = np.array([1,1,1,2,2,2],dtype=np.int32)
nBlock = 2
nType = lindo.LS_LINK_BLOCKS_FREE
errorcode = lindo.pyLSloadBlockStructure(pModel,
                                         nBlock + 1,
                                         panRblock,
                                         panCblock,
                                         nType)
lindo.geterrormessage(pEnv,errorcode)

#set the method for finding block
nMethod = 5
errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_BNP_FIND_BLK,
                                           nMethod)
lindo.geterrormessage(pEnv,errorcode)

#solve the model using BNP
print("\nSolving the model...")
pnStatus = np.array([-1],dtype=np.int32)
errorcode = lindo.pyLSsolveMipBnp(pModel,nBlock,"ddd",pnStatus)
lindo.geterrormessage(pEnv,errorcode)

#retrieve the objective value
dObj = np.array([-1.0],dtype=np.double)
errorcode = lindo.pyLSgetInfo(pModel,lindo.LS_DINFO_MIP_OBJ,dObj)
lindo.geterrormessage(pEnv,errorcode)
print("Objective is: %.5f" %dObj[0])
print("")

#retrieve the primal solution
padPrimal = np.empty((nVars),dtype=np.double)
errorcode = lindo.pyLSgetMIPPrimalSolution(pModel,padPrimal)
lindo.geterrormessage(pEnv,errorcode)
print("Primal solution is: ")
for x in padPrimal: print("%.5f" % x)

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
lindo.geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
lindo.geterrormessage(pEnv,errorcode)

