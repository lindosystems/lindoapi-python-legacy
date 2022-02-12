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

import lindo
import numpy as np
import os
import sys
def logFunc(pModel,line, udict): 
    print("%s %s" % (udict["durr"],line),end =" ")
    sys.stdout.flush()

def cbFunc(pModel,iloc, udict): 
    dObj = np.array([-1.0],dtype=np.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,iloc,lindo.LS_DINFO_CUR_OBJ,dObj)
    dIter = np.array([-1.0],dtype=np.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,iloc,lindo.LS_DINFO_CUR_ITER,dIter)    
    print("\ncbFunc| LOC:%d Iter:%g, Obj=%g" % (iloc,dIter[0],dObj[0]),end =" ")
    sys.stdout.flush()

def cbMIPFunc(pModel,udict,dObj,padPrimal):     
    dIter = np.array([-1.0],dtype=np.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,0,lindo.LS_DINFO_CUR_ITER,dIter)    
    print("\ncbMIPFunc| Iter:%g, Obj=%g" % (dIter[0],dObj,),end =" ")
    for k,x in enumerate(padPrimal): 
        print("\n%.5f %s" % (padPrimal[k],udict["varType"][k]),end=" ")
    sys.stdout.flush()

#model data
nCons = 5
nVars = 6
nDir = 1
dObjConst = 0.0
adC = np.array([1.,1.,1.,1.,1.,1.],dtype=np.double)
adB = np.array([3.0,1.0,1.0,2.0,1.0],dtype=np.double)
acConTypes = np.array(['G','L','L','L','L'],dtype='|S1')
nNZ = 15;
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
lindo.geterrormessage(pEnv,pnErrorCode[0])

verstr = lindo.getversion(pEnv)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
lindo.geterrormessage(pEnv,pnErrorCode[0])

#load data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel,nCons,nVars,nDir,
                                 dObjConst,adC,adB,acConTypes,nNZ,anBegCol,
                                 pnLenCol,adA,anRowX,pdLower,pdUpper)
lindo.geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSloadVarType(pModel,pachVarType)
lindo.geterrormessage(pEnv,errorcode)

udict = {
  "prefix": "APILOG",
  "postfix": "..",
  "version": verstr,
  "varType": pachVarType,
  "durr":"FSDFDS"
}
errorcode = lindo.pyLSsetModelLogfunc(pModel,logFunc, udict)
lindo.geterrormessage(pEnv,errorcode)

#errorcode = lindo.pyLSsetCallback(pModel,cbFunc, udict)
#lindo.geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSsetMIPCallback(pModel,cbMIPFunc, udict)
lindo.geterrormessage(pEnv,errorcode)

#solve the model
print("Solving the model...")
pnStatus = np.array([-1],dtype=np.int32)
errorcode = lindo.pyLSsolveMIP(pModel,pnStatus)
lindo.geterrormessage(pEnv,errorcode)

#retrieve the objective value
dObj = np.array([-1.0],dtype=np.double)
errorcode = lindo.pyLSgetInfo(pModel,lindo.LS_DINFO_MIP_OBJ,dObj)
lindo.geterrormessage(pEnv,errorcode)
print("Objective is: %.5f" %dObj[0])
print("")

#retrieve the primal solution
varType = np.empty((nVars),dtype=np.byte)
errorcode = lindo.pyLSgetVarType(pModel,varType)
lindo.geterrormessage(pEnv,errorcode)

padPrimal = np.empty((nVars),dtype=np.double)
errorcode = lindo.pyLSgetMIPPrimalSolution(pModel,padPrimal)
lindo.geterrormessage(pEnv,errorcode)
print("Primal solution is: ")
for k,x in enumerate(padPrimal): 
    print("%.5f %c" % (padPrimal[k],varType[k]))
    

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
lindo.geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
lindo.geterrormessage(pEnv,errorcode)

