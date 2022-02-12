# Solve a multi-extremal continous model using GOP solver.
#
#           MINIMIZE      x * sin(x * pi)
#           subject to    0 <= x <= 10


import lindo
import numpy as np
import os
#Number of constraints
ncons = 1
#Number of variables
nvars = 2
#Number of objectives
nobjs = 1
#Number of real number constants
nnums = 0
#Lower bounds of variables
lwrbnd = np.array([0.0, -2.0],dtype=np.double)
#Upper bounds of variables
uprbnd = np.array([10.0, 2.0],dtype=np.double)
#Starting point of variables
varval = np.array([0.0, 0.0],dtype=np.double)
numval = np.empty((nvars),dtype=np.double)
#Variable type
vtype = np.array(['C','C'],dtype='|S1')
#Count for instruction code
ikod = 0
#Count for objective row
iobj = 0
#Count for constraint row
icon = 0

#Instruction code of the objective
objsense = np.empty((10),dtype=np.int32)
objs_beg = np.empty((10),dtype=np.int32)
objs_length = np.empty((10),dtype=np.int32)
cons_beg = np.empty((10),dtype=np.int32)
cons_length = np.empty((10),dtype=np.int32)
code = np.empty((200),dtype=np.int32)
#Direction of optimization
objsense[iobj] = lindo.LS_MIN
#Beginning position of objective
objs_beg[iobj] = ikod
#Instruction list code
code[ikod] = lindo.EP_PUSH_VAR
ikod = ikod + 1
code[ikod] = 0
ikod = ikod + 1
code[ikod] = lindo.EP_PUSH_VAR
ikod = ikod + 1
code[ikod] = 0
ikod = ikod + 1
code[ikod] = lindo.EP_PI
ikod = ikod + 1
code[ikod] = lindo.EP_MULTIPLY
ikod = ikod + 1
code[ikod] = lindo.EP_SIN
ikod = ikod + 1
code[ikod] = lindo.EP_MULTIPLY
ikod = ikod + 1

#Length of objective
objs_length[iobj] = ikod - objs_beg[iobj]
iobj = iobj + 1

#Constraint type
ctype = np.array(['E'],dtype='|S1')
#Beginning position of constraint 0
cons_beg[icon] = ikod;
#Instruction list code
code[ikod] = lindo.EP_PUSH_VAR;
ikod = ikod + 1
code[ikod] = 1;
ikod = ikod + 1

#Length of constraint 0
cons_length[icon] = ikod - cons_beg[icon];
icon = icon + 1;

#Total number of items in the instruction list
lsize = ikod

#create LINDO environment and model objects
LicenseKey = np.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = np.array([-1],dtype=np.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
lindo.geterrormessage(pEnv,pnErrorCode[0])

#Set linearization level, before a call to LSloadNLPCode.
#If not specified, the solver will decide
nLinearz = 1;

errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_NLP_LINEARZ,
                                           nLinearz);
lindo.geterrormessage(pEnv,errorcode)

#Select algebraic reformulation level in convex relaxation
nCRAlgReform = 1;
errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_NLP_CR_ALG_REFORM,
                                           nCRAlgReform);
lindo.geterrormessage(pEnv,errorcode)

#Select convex relax level
nConvexRelax = 0;
errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_NLP_CONVEXRELAX,
                                           nConvexRelax);
lindo.geterrormessage(pEnv,errorcode)


#Set up automatic differentiation, before a call to LSloadNLPCode.
#If not specified, the numerical derivative will be applied
nAutoDeriv = 1;
errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_NLP_AUTODERIV,
                                           nAutoDeriv);
lindo.geterrormessage(pEnv,errorcode)

#Load instruction list
print("Loading instruction list...")
varindex =  np.asarray(None)
errorcode = lindo.pyLSloadInstruct(pModel, ncons, nobjs, nvars, nnums,
                                   objsense, ctype,  vtype, code, lsize,
                                   varindex,numval, varval, objs_beg, objs_length,
                                   cons_beg,cons_length, lwrbnd, uprbnd);
lindo.geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_LP_PRINTLEVEL,0);
lindo.geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           lindo.LS_IPARAM_GOP_PRINTLEVEL,1);
lindo.geterrormessage(pEnv,errorcode)

#solve the model
print("Solving the model...")
pnStatus = np.array([-1],dtype=np.int32)
errorcode = lindo.pyLSsolveGOP(pModel, pnStatus);
lindo.geterrormessage(pEnv,errorcode)
print("Solution status: %d" %pnStatus[0])
print("")


#retrieve the objective value
dObj = np.array([-1.0],dtype=np.double)
errorcode = lindo.pyLSgetInfo(pModel,lindo.LS_DINFO_POBJ,dObj)
lindo.geterrormessage(pEnv,errorcode)
print("Objective is: %.5f" %dObj[0])
print("")

#retrieve the primal solution
padPrimal = np.empty((nvars),dtype=np.double)
errorcode = lindo.pyLSgetPrimalSolution(pModel,padPrimal)
lindo.geterrormessage(pEnv,errorcode)
print("Primal solution is: ")
for x in padPrimal: print("%.5f" % x)

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
lindo.geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
lindo.geterrormessage(pEnv,errorcode)

