#  A Python programming example of interfacing with LINDO API.
#
#  The problem:
#

from pyLindo import *
import os
#model data
numVars = N.array([0],dtype=N.int32)
numCons = N.array([0],dtype=N.int32)
numNlpVars = N.array([0],dtype=N.int32)
numLpVars = N.array([0],dtype=N.int32)
numCodes = N.array([0],dtype=N.int32)
numVals = N.array([0],dtype=N.int32)
nObjSense = N.array([0],dtype=N.int32)

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
errorcode = lindo.pyLSreadMPIFile(pModel,'c:/tmp/prob/Model_14DF.mpi')
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_IINFO_NUM_VARS,numVars)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_IINFO_NUM_CONS,numCons)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_IINFO_NUM_NLP_VARS,numNlpVars)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_IINFO_NUM_INST_CODES,numCodes)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(pModel,LSconst.LS_IINFO_NUM_INST_REAL_NUM,numVals)
geterrormessage(pEnv,errorcode)
numLpVars[0]=numVars[0]-numNlpVars[0]
print("numVars   : %d" %numVars[0])
print("numCons   : %d" %numCons[0])
print("numNlpVars: %d" %numNlpVars[0])
print("numLpVars : %d" %numLpVars[0])
print("numCodes  : %d" %numCodes[0])
print("numVals   : %d" %numVals[0])

pachVarType = N.empty((numVars[0]),dtype=N.byte)
pachConType = N.empty((numCons[0]),dtype=N.byte)
panCode     = N.empty((numCodes[0]),dtype=N.int32)
padNumVal   = N.empty((numVals[0]),dtype=N.double)
padVarVal   = N.asarray(None)
panObjBeg   = N.empty((1+1),dtype=N.int32)
panObjLength = N.empty((1),dtype=N.int32)
panBuf        = N.empty((100),dtype=N.int32)
padBuf        = N.empty((100),dtype=N.int32)
panConBeg   = N.empty((numCons[0]+1),dtype=N.int32)
panConLength = N.empty((numCons[0]),dtype=N.int32)
padLB = N.empty((numVars[0]),dtype=N.double)
padUB = N.empty((numVars[0]),dtype=N.double)
paiVarBuf = N.empty((numVars[0]),dtype=N.int32)
paiConBuf = N.empty((numCons[0]),dtype=N.int32)
padVarBuf = N.empty((numVars[0]),dtype=N.double)
padConBuf = N.empty((numCons[0]),dtype=N.double)
paiTypeMap = N.empty((numVars[0]),dtype=N.int32)
NULL = N.asarray(None)
errorcode = lindo.pyLSgetInstruct(pModel,nObjSense,pachConType,pachVarType,panCode,padNumVal,padVarVal,panObjBeg,panObjLength,panConBeg,panConLength,padLB,padUB)
print(panConBeg)
print(padLB)
print(padUB)
padNumVal = N.append(padNumVal,[1.234])
#print(padNumVal)
for j,x in enumerate(padLB):
    errorcode = lindo.pyLSgetNLPVariableDataj(pModel,j,panBuf, NULL, NULL)
    geterrormessage(pEnv,errorcode)
    if panBuf[0]>0:
        paiTypeMap[j]=panBuf[0] #NL var
        #paiVarBuf[0]=j
        #padVarBuf[0]=0
        #lindo.pyLSmodifyLowerBounds(pModel,1,paiVarBuf,padVarBuf)
        #lindo.pyLSmodifyUpperBounds(pModel,1,paiVarBuf,padVarBuf)
    else:
        paiTypeMap[j]=0
        


##
xModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])
paiVars = N.asarray(None)
for k,x in enumerate(panCode):    
    if panCode[k]==LSconst.EP_PUSH_VAR:
        j = panCode[k+1]
        if paiTypeMap[j]>0:
            panCode[k] = LSconst.EP_PUSH_NUM
            panCode[k+1]=padNumVal.size-1

#lindo.pyLSsetModelIntParameter(xModel,LSconst.LS_IPARAM_INSTRUCT_SUBOUT,1)
errorcode = lindo.pyLSloadInstruct(xModel,numCons[0],1,numVars[0],padNumVal.size,nObjSense,pachConType,pachVarType,panCode,panCode.size,paiVars,padNumVal,padVarVal,panObjBeg,panObjLength,panConBeg,panConLength,padLB,padUB)
geterrormessage(pEnv,pnErrorCode[0])

errorcode = lindo.pyLSgetInfo(xModel,LSconst.LS_IINFO_NUM_VARS,numVars)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(xModel,LSconst.LS_IINFO_NUM_CONS,numCons)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(xModel,LSconst.LS_IINFO_NUM_NLP_VARS,numNlpVars)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(xModel,LSconst.LS_IINFO_NUM_INST_CODES,numCodes)
geterrormessage(pEnv,errorcode)
errorcode = lindo.pyLSgetInfo(xModel,LSconst.LS_IINFO_NUM_INST_REAL_NUM,numVals)
geterrormessage(pEnv,errorcode)
numLpVars[0]=numVars[0]-numNlpVars[0]
print("numVars   : %d" %numVars[0])
print("numCons   : %d" %numCons[0])
print("numNlpVars: %d" %numNlpVars[0])
print("numLpVars : %d" %numLpVars[0])
print("numCodes  : %d" %numCodes[0])
print("numVals   : %d (%d)" % (numVals[0],padNumVal.size))
errorcode = lindo.pyLSwriteMPIFile(xModel,"b.mpi")
geterrormessage(pEnv,errorcode)


print("Solving the model...")
errorcode = lindo.pyLSsetModelIntParameter(xModel,LSconst.LS_IPARAM_SOLVER_IUSOL,1)
pnStatus = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSoptimize(xModel,0,pnStatus)
geterrormessage(pEnv,errorcode)

padPrimal = N.empty((numVars[0]),dtype=N.double)
errorcode = lindo.pyLSgetPrimalSolution(xModel,padPrimal)
geterrormessage(pEnv,errorcode)
if 0>1:
    print("Primal solution is: ")
    for k,x in enumerate(padPrimal): 
        if paiTypeMap[k]>0:
            print("-%.6f %8d" % (padPrimal[k],paiTypeMap[k]))
    print("Primal solution is: ")        
    for k,x in enumerate(padPrimal): 
        if paiTypeMap[k]==0:
            print("-%.6f %8d" % (padPrimal[k],paiTypeMap[k]))    
if 0>1:
    errorcode = lindo.pyLSsetModelIntParameter(xModel,LSconst.LS_IPARAM_IIS_METHOD,3)
    geterrormessage(pEnv,errorcode)
    errorcode = lindo.pyLSfindIIS(xModel,3)
    geterrormessage(pEnv,errorcode)

    errorcode = lindo.pyLSwriteIIS(xModel,"iis.ltx")
    geterrormessage(pEnv,errorcode)

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
errorcode = lindo.pyLSdeleteModel(xModel)
geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

