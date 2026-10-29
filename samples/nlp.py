###################################################################
#                       LINDO-API
#                    Sample Programs
#                  Copyright (c) 2011
#
#         LINDO Systems, Inc.           312.988.7422
#         1415 North Dayton St.         info@lindo.com
#         Chicago, IL 60622             http://www.lindo.com
###################################################################
#
#  File   : Derived from samples/c/ex_nlp1/ex_nlp1.c
#
#  Purpose: Solve a NLP using the black-box style interface.
#  Model  : A nonlinear model with multiple local minimizers.
#
#        minimize  f(x,y) =  3*(1-x)^2*exp(-(x^2) - (y+1)^2)
#                         - 10*(x/5 - x^3 - y^5)*exp(-(x^2)-y^2)
#                         - 1/3*exp(-((x+1)^2) - y^2);
#        subject to
#                         x^2 + y   <=  6;
#                         x   + y^2 <=  6;
#                         x, y unconstrained in sign;
import math
import sys

####
##
def logFunc(pModel,line, udict): 
    print("%s" % (line),end =" ")
    sys.stdout.flush()
####
##
def cbFunc(pModel,iloc, udict): 
    dObj = N.array([-1.0],dtype=N.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,iloc,LSconst.LS_DINFO_CUR_OBJ,dObj)
    dIter = N.array([-1.0],dtype=N.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,iloc,LSconst.LS_DINFO_CUR_ITER,dIter)    
    print("\ncbFunc| LOC:%d Iter:%g, Obj=%g" % (iloc,dIter[0],dObj[0]),end =" ")
    sys.stdout.flush()
####
##
def cbMIPFunc(pModel,udict,dObj,padPrimal):     
    dIter = N.array([-1.0],dtype=N.double)
    errorcode = lindo.pyLSgetProgressInfo(pModel,0,LSconst.LS_DINFO_CUR_ITER,dIter)    
    print("\ncbMIPFunc| Iter:%g, Obj=%g" % (dIter[0],dObj,),end =" ")
    for k,x in enumerate(padPrimal): 
        print("\n%.5f %s" % (padPrimal[k],udict["varType"][k]),end=" ")
    sys.stdout.flush()
  
####
## FDE calculations
# Function evals
def  g1(X,Y): return math.exp( -pow(X  ,2)  - pow(Y+1,2) )  
def  g2(X,Y): return math.exp( -pow(X  ,2)  - pow(Y  ,2) )  
def  g3(X,Y): return math.exp( -pow(X+1,2)  - pow(Y  ,2) )  
def  f1(X,Y): return pow(1-X,2)                        
def  f2(X,Y): return X/5 - pow(X  ,3)  - pow(Y  ,5)   
               
# Partial derivatives of the summands  (only to be used with cbGradcalc)
def dxg1(X,Y): return ( g1(X,Y)*(-2)*X     )
def dyg1(X,Y): return ( g1(X,Y)*(-2)*(Y+1) )
def dxg2(X,Y): return ( g2(X,Y)*(-2)*X     )
def dyg2(X,Y): return ( g2(X,Y)*(-2)*Y     )
def dxg3(X,Y): return ( g3(X,Y)*(-2)*(X+1) )
def dyg3(X,Y): return ( g3(X,Y)*(-2)*Y     )
def dxf1(X,Y): return ( 2*(1-X)            )
def dyf1(X,Y): return ( 0                  )
def dxf2(X,Y): return ( 1/5 - 3*pow(X,2)   )
def dyf2(X,Y): return ( -5*pow(Y,4)        )
               
def cbFuncalc(pModel,udict,nRow,padPrimal,nJDiff,dXJBase,pyFuncVal,pReserved):
  nerr = 0
  # compute objective's functional value*/
  X = padPrimal[0]
  Y = padPrimal[1]
  if (nRow==-1):
    val = 3*f1(X,Y)*g1(X,Y) - 10*f2(X,Y)*g2(X,Y) - g3(X,Y)/3;
  # compute constaint 0's functional value */
  elif (nRow==0):
    val = X*X + Y - 6.0;
  # compute constaint 1's functional value */
  elif (nRow==1):
    val = X + Y*Y - 6.0;
    
  pyFuncVal[0]=val  
  udict["nfunc"] = udict["nfunc"] + 1
  return nerr

def cbGradcalc(pModel,udict,nRow,pdX,lb,ub,NewPnt,NPar,parlist,partial):
  nerr = 0
  # compute objective's gradient values*/  
  X = padPrimal[0]
  Y = padPrimal[1]
  
  for i2 in range(NPar): partial[i2]=0.0;
  
  # partial derivatives of the objective function */
  if (nRow==-1):
     for i2 in range(NPar):
       if (lb[parlist[i2]]!=ub[parlist[i2]]):
           if (parlist[i2]==0):
             partial[i2]= 3*(dxf1(X,Y)*g1(X,Y) + f1(X,Y)*dxg1(X,Y) ) -  10*(dxf2(X,Y)*g2(X,Y) + f2(X,Y)*dxg2(X,Y) ) - 1/3*(dxg3(X,Y));
           elif (parlist[i2]==1):
             partial[i2]= 3*(dyf1(X,Y)*g1(X,Y) + f1(X,Y)*dyg1(X,Y) ) -  10*(dyf2(X,Y)*g2(X,Y) + f2(X,Y)*dyg2(X,Y) ) - 1/3*(dyg3(X,Y));
                       
  # partial derivatives of Constraint 0 */
  elif (nRow==0):
     for i2 in range(NPar):
       if (lb[parlist[i2]]!=ub[parlist[i2]]):
         if (parlist[i2]==0):
           partial[i2]=2.0*X;
         elif (parlist[i2]==1):
           partial[i2]=1;
         
  # partial derivatives of Constraint 1 */
  elif (nRow==1):
     for i2 in range(NPar):
       if (lb[parlist[i2]]!=ub[parlist[i2]]):
         if (parlist[i2]==0):
           partial[i2]=1;
         elif (parlist[i2]==1):
           partial[i2]=2.0*Y;
  udict["ngrad"] = udict["ngrad"] + 1
  return nerr
  
####################################
## MAIN    
####################################
from pyLindo import *
import os
#model LP data
nCons = 2
nVars = 2
nDir = 1
dObjConst = 0.0
adC = N.array([0.0,0.0],dtype=N.double)
adB = N.array([0.0,0.0],dtype=N.double)
acConTypes = N.array(['L','L'],dtype=N.character)
nNZ = 4;
Abegcol = N.array([0,2,4],dtype=N.int32)
Alencol = N.array([2,2],dtype=N.int32)
Acoef = N.array([0.,1.,1.,0.],dtype=N.double)
Arowndx = N.array([0,1,0,1],dtype=N.int32)
lb = N.array([-3.,-3.],dtype=N.double)
ub = N.array([3.,3.],dtype=N.double)
pachVarType = N.array(['C','C'],dtype=N.character)
# NLP data
Nobjndx = N.array([0,1],dtype=N.int32)
Nnlobj = 2

#create LINDO environment and model objects
LicenseKey = N.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)

pnErrorCode = N.array([-1],dtype=N.int32)

pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)
geterrormessage(pEnv,pnErrorCode[0])

verstr = getversion(pEnv)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])

#load LP data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel,nCons,nVars,nDir,
                                 dObjConst,adC,adB,acConTypes,nNZ,Abegcol,
                                 Alencol,Acoef,Arowndx,lb,ub)
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSloadVarType(pModel,pachVarType)
geterrormessage(pEnv,errorcode)

#load NLP data
# The number of nonlinear variables in each column 
Alencol[0]=1; Alencol[1]=1;

# The indices of the first nonlinear variable in each column 
Abegcol[0]=0; Abegcol[1]=1; Abegcol[2]=2;

# The indices of nonlinear constraints 
Arowndx[0]=0;
Arowndx[1]=1;

errorcode=lindo.pyLSloadNLPData(pModel,Abegcol,Alencol,
        N.asarray(None),Arowndx,Nnlobj,Nobjndx,N.asarray(None));
 
###############################
## Set callbacks 
udict = {
  "prefix": "APILOG",
  "postfix": "..",
  "version": verstr,
  "varType": pachVarType,
  "ngrad": 0,
  "nfunc": 0
}
errorcode = lindo.pyLSsetModelLogfunc(pModel,logFunc, udict)
geterrormessage(pEnv,errorcode)

#errorcode = lindo.pyLSsetCallback(pModel,cbFunc, udict)
#geterrormessage(pEnv,errorcode)

#errorcode = lindo.pyLSsetMIPCallback(pModel,cbMIPFunc, udict)
#geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSsetFuncalc(pModel,cbFuncalc, udict)
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSsetGradcalc(pModel,cbGradcalc, udict)
geterrormessage(pEnv,errorcode)

###############################
## Set misc parameters

# Turn multi-start search on */
#errorcode = lindo.pyLSsetModelIntParameter(pModel,LSconst.LS_IPARAM_NLP_SOLVER,LSconst.LS_NMETHOD_MSW_GRG);
geterrormessage(pEnv,errorcode)

# Set maximum number of local optimizations */
errorcode = lindo.pyLSsetModelIntParameter(pModel,LSconst.LS_IPARAM_NLP_MAXLOCALSEARCH,5);
geterrormessage(pEnv,errorcode)
  
###############################
# Get model stats  
ibuf = N.array([1],dtype=N.int32)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_IINFO_NUM_CONT,ibuf) # number of continuous variables
geterrormessage(pEnv,errorcode)
nCont = ibuf[0] 

#####################################
## Load initial solution
padPrimal = N.empty((nVars),dtype=N.double)
padPrimal[0] = 0.25;  padPrimal[1] = -1.65;
errorcode=lindo.pyLSloadVarStartPoint(pModel,padPrimal);
geterrormessage(pEnv,errorcode)

#####################################
## Solve the model
print("Solving the model...")
pnStatus = N.array([-1],dtype=N.int32)
if nCont<nVars:
    errorcode = lindo.pyLSsolveMIP(pModel,pnStatus)
else:
    errorcode = lindo.pyLSoptimize(pModel,LSconst.LS_METHOD_FREE, pnStatus)    
geterrormessage(pEnv,errorcode)

#####################################
## Retrieve the objective value
dObj = N.array([-1.0],dtype=N.double)
if nCont<nVars:
    errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_DINFO_MIP_OBJ,dObj)
else:
    errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_DINFO_POBJ,dObj)    
geterrormessage(pEnv,errorcode)
print("")

#####################################
## Retrieve the primal solution
if nCont<nVars:
    errorcode = lindo.pyLSgetMIPPrimalSolution(pModel,padPrimal)
else:
    errorcode = lindo.pyLSgetPrimalSolution(pModel,padPrimal)    
geterrormessage(pEnv,errorcode)

varType = N.empty((nVars),dtype=N.byte)
errorcode = lindo.pyLSgetVarType(pModel,varType)
geterrormessage(pEnv,errorcode)

print("Primal solution is: ")
for k,x in enumerate(padPrimal): 
    print("x[%d] =%10.5f %c" % (k,padPrimal[k],varType[k]))

print("Objective is: %.5f (nfunc:%d, ngrad:%d)" % (dObj[0],udict["nfunc"],udict["ngrad"]))
################################    
# Delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
geterrormessage(pEnv,errorcode)

################################
# Delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

