#  Solve an MIP model.
#
#  The problem:
#
#      Minimize x1 + x2 + x3 + x4 + x5 + x6
#      s.t.
#               [r1]x1 + x2 + x3 + x4 + x5 + x6  >=3;
#               [r2]x1 + x2                      <=1;
#               [r3]     x2 + x3                 <=1;
#               [r4]               x4 + x5 + x6  <=2;
#               [r5]               x4 +      x6  <=1;
#
#               x1,x2,x3,x4,x5,x6 are binary variables

import sys
def logFunc(pModel,line, udict): 
    print("%s" % (line),end =" ")
    sys.stdout.flush()

def cbFunc(pModel,iloc, udict): 
    dObj = N.array([-1.0],dtype=N.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,iloc,LSconst.LS_DINFO_CUR_OBJ,dObj)
    dIter = N.array([-1.0],dtype=N.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,iloc,LSconst.LS_DINFO_CUR_ITER,dIter)    
    print("\ncbFunc| LOC:%d Iter:%g, Obj=%g" % (iloc,dIter[0],dObj[0]),end =" ")
    sys.stdout.flush()

def cbMIPFunc(pModel,udict,dObj,padPrimal):     
    dIter = N.array([-1.0],dtype=N.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,0,LSconst.LS_DINFO_CUR_ITER,dIter)    
    print("\ncbMIPFunc| Iter:%g, Obj=%g" % (dIter[0],dObj,),end =" ")
    for k,x in enumerate(padPrimal): 
        print("\n%.5f %s" % (padPrimal[k],udict["varType"][k]),end=" ")
    sys.stdout.flush()
    
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
geterrormessage(pEnv,pnErrorCode[0])

verstr = getversion(pEnv)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])

#load data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel,nCons,nVars,nDir,
                                 dObjConst,adC,adB,acConTypes,nNZ,anBegCol,
                                 pnLenCol,adA,anRowX,pdLower,pdUpper)
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSloadVarType(pModel,pachVarType)
geterrormessage(pEnv,errorcode)

udict = {
  "prefix": "APILOG",
  "postfix": "..",
  "version": verstr,
  "varType": pachVarType
}
errorcode = lindo.pyLSsetModelLogfunc(pModel,logFunc, udict)
geterrormessage(pEnv,errorcode)

#errorcode = lindo.pyLSsetCallback(pModel,cbFunc, udict)
#geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSsetMIPCallback(pModel,cbMIPFunc, udict)
geterrormessage(pEnv,errorcode)

#solve the model
print("Solving the model...")
pnStatus = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSsolveMIP(pModel,pnStatus)
geterrormessage(pEnv,errorcode)

#retrieve the objective value
dObj = N.array([-1.0],dtype=N.double)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_DINFO_MIP_OBJ,dObj)
geterrormessage(pEnv,errorcode)
print("Objective is: %.5f" %dObj[0])
print("")

#retrieve the primal solution
varType = N.empty((nVars),dtype=N.byte)
errorcode = lindo.pyLSgetVarType(pModel,varType)
geterrormessage(pEnv,errorcode)

padPrimal = N.empty((nVars),dtype=N.double)
errorcode = lindo.pyLSgetMIPPrimalSolution(pModel,padPrimal)
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

