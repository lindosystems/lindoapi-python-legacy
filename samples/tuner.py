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

from pyLindo import *
import os

#create LINDO environment and model objects
LicenseKey = N.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = N.array([-1],dtype=N.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)
geterrormessage(pEnv,pnErrorCode[0])

print(getversion(pEnv))

dataPath = os.getenv('LINDOAPI_HOME') + "/samples/data"
# Tuner instances */
errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/bm23.mps.gz"); geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/p0033.mps.gz"); geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/p0201.mps.gz"); geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSaddTunerInstance(pEnv, dataPath +"/p0282.mps.gz"); geterrormessage(pEnv,errorcode);

# Tuner options */
errorcode = lindo.pyLSaddTunerOption(pEnv,"max_parsets",6); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"use_gop",0); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"time_limit",10); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"ntrials",2); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"nthreads",1); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"seed",1032); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerOption(pEnv,"criterion",1); geterrormessage(pEnv,errorcode);

# Tuner dynamic parameters */
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,LSconst.LS_IPARAM_LP_SCALE); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,LSconst.LS_IPARAM_MIP_PRELEVEL); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,LSconst.LS_IPARAM_MIP_BRANCHDIR); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,LSconst.LS_IPARAM_MIP_BRANCHRULE); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,LSconst.LS_IPARAM_MIP_FP_MODE); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZDynamic(pEnv,LSconst.LS_DPARAM_SOLVER_FEASTOL); geterrormessage(pEnv,errorcode);

# Tuner static groups and parameters */
errorcode = lindo.pyLSaddTunerZStatic(pEnv,1,LSconst.LS_IPARAM_MIP_NODESELRULE,4); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,1,LSconst.LS_DPARAM_MIP_RELINTTOL,0.0001); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,1,LSconst.LS_DPARAM_SOLVER_OPTTOL,1e-006); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,2,LSconst.LS_IPARAM_MIP_NODESELRULE,1); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,2,LSconst.LS_DPARAM_MIP_RELINTTOL,0.001); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,2,LSconst.LS_DPARAM_SOLVER_OPTTOL,1e-005); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,3,LSconst.LS_IPARAM_MIP_NODESELRULE,3); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,3,LSconst.LS_DPARAM_MIP_RELINTTOL,1e-005); geterrormessage(pEnv,errorcode);
errorcode = lindo.pyLSaddTunerZStatic(pEnv,3,LSconst.LS_DPARAM_SOLVER_OPTTOL,0.0001); geterrormessage(pEnv,errorcode);


if 0>1:
    errorcode = lindo.pyLSprintTuner(pEnv);
    geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSrunTuner(pEnv);
geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSdisplayTunerResults(pEnv);
geterrormessage(pEnv,errorcode);

mCriterion = -1; #selected criterion
jInstance  = -1; #avg instance
errorcode = lindo.pyLSwriteTunerParameters(pEnv,"lindo_tuned.par",jInstance,mCriterion);
geterrormessage(pEnv,errorcode);

errorcode = lindo.pyLSclearTuner(pEnv);

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

