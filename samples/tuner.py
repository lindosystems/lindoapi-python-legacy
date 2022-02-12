###################################################################
#                       LINDO-API
#                    Sample Programs
#                  Copyright (c) 2001-2018
#
#         LINDO Systems, Inc.           312.988.7422
#         1415 North Dayton St.         info@lindo.com
#         Chicago, IL 60622             http://www.lindo.com
###################################################################
#  File   : Derived from samples/c/ex_tuner/ex_tuner.c
#  Purpose: Tuning parameters

import lindo
import numpy as np
import os

#create LINDO environment and model objects
LicenseKey = np.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = np.array([-1],dtype=np.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)
lindo.geterrormessage(pEnv,pnErrorCode[0])

print(lindo.getversion(pEnv))

dataPath = os.getenv('LINDOAPI_HOME') + "/samples/data"
# Tuner instances */
errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/bm23.mps.gz"); lindo.geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/p0033.mps.gz"); lindo.geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/p0201.mps.gz"); lindo.geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/p0282.mps.gz"); lindo.geterrormessage(pEnv,errorcode);

# Tuner options */
errorcode = lindo.pyLSaddTunerOption(pEnv,"max_parsets",6); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"use_gop",0); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"time_limit",10); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"ntrials",2); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"nthreads",1); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"seed",1032); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"criterion",1); lindo.geterrormessage(pEnv,errorcode);

# Tuner dynamic parameters */
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,lindo.LS_IPARAM_LP_SCALE); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,lindo.LS_IPARAM_MIP_PRELEVEL); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,lindo.LS_IPARAM_MIP_BRANCHDIR); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,lindo.LS_IPARAM_MIP_BRANCHRULE); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,lindo.LS_IPARAM_MIP_FP_MODE); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,lindo.LS_DPARAM_SOLVER_FEASTOL); lindo.geterrormessage(pEnv,errorcode);

# Tuner static groups and parameters */
errorcode = lindo.pyLSaddTunerZStatic(pEnv,1,lindo.LS_IPARAM_MIP_NODESELRULE,4); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,1,lindo.LS_DPARAM_MIP_RELINTTOL,0.0001); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,1,lindo.LS_DPARAM_SOLVER_OPTTOL,1e-006); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,2,lindo.LS_IPARAM_MIP_NODESELRULE,1); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,2,lindo.LS_DPARAM_MIP_RELINTTOL,0.001); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,2,lindo.LS_DPARAM_SOLVER_OPTTOL,1e-005); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,3,lindo.LS_IPARAM_MIP_NODESELRULE,3); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,3,lindo.LS_DPARAM_MIP_RELINTTOL,1e-005); lindo.geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,3,lindo.LS_DPARAM_SOLVER_OPTTOL,0.0001); lindo.geterrormessage(pEnv,errorcode);


if 0>1:
    errorcode = lindo.pyLSprintTuner(pEnv);
    lindo.geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSrunTuner(pEnv);
lindo.geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSdisplayTunerResults(pEnv);
lindo.geterrormessage(pEnv,errorcode);

mCriterion = -1; #selected criterion
jInstance  = -1; #avg instance
errorcode = lindo.pyLSwriteTunerParameters(pEnv,"lindo_tuned.par",jInstance,mCriterion);
lindo.geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSclearTuner(pEnv);

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
lindo.geterrormessage(pEnv,errorcode)

