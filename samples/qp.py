# Set up and solve a (quadratic) portfolio model with LINDO API.
#
#                    Portfolio Selection Problem                 
#                       The Markowitz Model.                     
#                                                                
#       MAXIMIZE  r(1)w(1) + ... +r(n)w(n)
#           st.       sum_{ij} Q(i,j)w(i)w(j) <= K
#                         w(1) + ..... + w(n)  = 1
#                         w(1),         ,w(n) >= 0
#           where
#           r(i)  : return on asset i
#           Q(i,j): covariance between the returns of i^th and
#                   j^th assets.
#           K     : a scalar denoting the level of risk of loss.
#           w(i)  : proportion of total budget invested on asset i

#           Covariance Matrix:
#                  w1    w2    w3    w4
#             w1 [ 1.00  0.64  0.27  0.    ]
#             w2 [ 0.64  1.00  0.13  0.    ]
#             w3 [ 0.27  0.13  1.00  0.    ]
#             w4 [ 0.    0.    0.    1.00  ]

#           Returns Vector:
#                    w1    w2    w3    w4
#           r =   [ 0.30  0.20 -0.40  0.20  ]

#           Risk of Loss Factor:
#           K = 0.4     


from pyLindo import *
import os
#LP data
nM = 2
nN = 4
K = 0.20
objsense = LSconst.LS_MAX
objconst = 0
reward = N.array([0.300,0.200,-0.400,0.200],dtype=N.double)
rhs = N.array([K,1.0],dtype=N.double)
contype = N.array(['L','E'],dtype=N.character)
Anz = 4
Abegcol = N.array([0,1,2,3,Anz],dtype=N.int32)
Alencol = N.asarray(None)
A = N.array([1.,1.,1.,1.],dtype=N.double)
Arowndx = N.array([1,1,1,1],dtype=N.int32)
lb = N.asarray(None)
ub = N.asarray(None)

#QP data
Qnz = 7
Qrowndx = N.array([0,0,0,0,0,0,0],dtype=N.int32)
Qcolndx1 = N.array([0,0,0,1,1,2,3],dtype=N.int32)
Qcolndx2 = N.array([0,1,2,1,2,2,3],dtype=N.int32)
Q = N.array([1.0000,0.6400,0.2700,1.0000,0.1300,1.0000,1.0000],dtype=N.double)

#create LINDO environment and model objects
LicenseKey = N.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = N.array([-1],dtype=N.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)

print(getversion(pEnv))

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])

#load LP data into the model
print("Loading LP data...")
errorcode = lindo.pyLSloadLPData(pModel, nM, nN, objsense, objconst,
                                 reward, rhs, contype,
                                 Anz, Abegcol, Alencol, A, Arowndx,
                                 lb, ub)
geterrormessage(pEnv,errorcode)

#load QP data into the model
print("Loading QP data...")
errorcode = lindo.pyLSloadQCData(pModel, Qnz, Qrowndx,
                                 Qcolndx1, Qcolndx2, Q)
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

#retrieve the primal solution
padPrimal = N.empty((nN),dtype=N.double)
errorcode = lindo.pyLSgetPrimalSolution(pModel,padPrimal)
geterrormessage(pEnv,errorcode)
print("Primal solution is: ")
for x in padPrimal: print("%.5f" % x)

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

