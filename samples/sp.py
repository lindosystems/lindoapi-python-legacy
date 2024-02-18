#  Stochastic Programming Version of an American Put Option as a
#  six period model.
#
#  The holder of the option has the right to sell a specified stock
#  at any time(the American feature) between now and a specified
#  expiration date at a specified strike price.
#  The holder makes a profit in the period of exercise if the
#  strike price exceeds the market price of the stock at the
#  time of sale.  Wealth is invested at the risk free rate.
#
#  Initial Price  = $100
#  Strike price   =  $99
#  Risk free rate = 0.04%
#
#
#   MODEL:
#   [OBJ] MAX= W5 ;
#
#   [INITIAL]        P0 = 100 ;    !price at t=0;
#   [R0000001] RV0 * P0 = P1  ;    !price at t=1;
#   [R0000003] RV1 * P1 = P2  ;    !price at t=2;
#   [R0000005] RV2 * P2 = P3  ;    !price at t=3;
#   [R0000007] RV3 * P3 = P4  ;    !price at t=4;
#   [R0000009] RV4 * P4 = P5  ;    !price at t=5;
#
#   [R0000000]           + Y0 * ( 99 - P0) = W0  ;  !wealth at t=0;
#   [R0000002] 1.04 * W0 + Y1 * ( 99 - P1) = W1  ;  !wealth at t=1;
#   [R0000004] 1.04 * W1 + Y2 * ( 99 - P2) = W2  ;  !wealth at t=2;
#   [R0000006] 1.04 * W2 + Y3 * ( 99 - P3) = W3  ;  !wealth at t=3;
#   [R0000008] 1.04 * W3 + Y4 * ( 99 - P4) = W4  ;  !wealth at t=4;
#   [R0000010] 1.04 * W4 + Y5 * ( 99 - P5) = W5  ;  !wealth at t=5;
#
#   [R0000011] Y0 + Y1+ Y2+ Y3 + Y4 +  Y5 <= 1 ; ! sell only once;
#
#   @FREE(Wt); t=0..5;
#   @FREE(Pt); t=0..5;
#   @BIN(Yt); t=0..5;
#
#  Stochastic Parameters:
#  RVt : random return in the end of period t, for t=0..4
#
#  Decision Variables:
#  Pt: Price of option in the beginning of period t, for t=0..5
#  Wt: Wealth int the beginning of period t, for t=0..5
#  Yt: 1 if sold in the beginning of period t, 0 otherwise, for t=0..5
#
#  Objective: maximize the wealth at the beginning of period 5 (i.e.
#             end of planning horizon).   

from pyLindo import *
import os
#create LINDO environment and model objects
LicenseKey = N.array('',dtype='S1024')
lindo.pyLSloadLicenseString(os.getenv('LINDOAPI_HOME')+'/license/lndapi130.lic',LicenseKey)
pnErrorCode = N.array([-1],dtype=N.int32)
pEnv = lindo.pyLScreateEnv(pnErrorCode,LicenseKey)

pModel = lindo.pyLScreateModel(pEnv,pnErrorCode)
geterrormessage(pEnv,pnErrorCode[0])

errorcode = lindo.pyLSsetModelIntParameter(pModel,
                                           LSconst.LS_IPARAM_NLP_LINEARZ,1);
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSreadMPIFile(pModel,"smpi/putoption.mpi");
geterrormessage(pEnv,errorcode)

#Load stage/time structure for rows,columns and stochastic params
numStages = 6
colStages = N.array([5,0,1,2,3,4,5,0,0,1,1,2,2,3,3,4,4,5,-1],dtype=N.int32)
rowStages = N.array([0,1,3,5,2,4,0,2,4,1,3,5,5,-1],dtype=N.int32)
panSparStage = N.array([1,2,3,4,5,-1],dtype=N.int32)
padSparValue = N.array([0,0,0,0,0,-1],dtype=N.double)
errorcode = lindo.pyLSloadStageData(pModel,numStages,
                                    rowStages,colStages)
geterrormessage(pEnv,errorcode)

errorcode = lindo.pyLSloadStocParData(pModel,panSparStage,padSparValue)
geterrormessage(pEnv,errorcode)

#Load stochastic data
iStage = 1
nBlockEvents = 4
iModifyRule = LSconst.LS_REPLACE
padProb = N.array([0.25,0.25,0.25,0.25,-1],dtype=N.double)
pakStart = N.array([0,1,2,3,4,-1],dtype=N.int32)
paiRows = N.asarray(None)
paiCols = N.asarray(None)
paiStvs = N.array([0,0,0,0,-1],dtype=N.int32)
padVals = N.array([-0.08,0.01,0.07,0.11,-1],dtype=N.double)
errorcode = lindo.pyLSaddDiscreteBlocks(pModel,iStage,
                                        nBlockEvents,padProb,
                                        pakStart,paiRows,
                                        paiCols,paiStvs,
                                        padVals,iModifyRule)
geterrormessage(pEnv,errorcode)

iStage = 2
nBlockEvents = 2
iModifyRule = LSconst.LS_REPLACE
padProb = N.array([0.5,0.5,-1],dtype=N.double)
pakStart = N.array([0,1,2,-1],dtype=N.int32)
paiRows = N.asarray(None)
paiCols = N.asarray(None)
paiStvs = N.array([1,1,-1],dtype=N.int32)
padVals = N.array([-0.08,0.01,-1],dtype=N.double)
errorcode = lindo.pyLSaddDiscreteBlocks(pModel,iStage,
                                        nBlockEvents,padProb,
                                        pakStart,paiRows,
                                        paiCols,paiStvs,
                                        padVals,iModifyRule)
geterrormessage(pEnv,errorcode)

iStage = 3
nBlockEvents = 2
iModifyRule = LSconst.LS_REPLACE
padProb = N.array([0.5,0.5,-1],dtype=N.double)
pakStart = N.array([0,1,2,-1],dtype=N.int32)
paiRows = N.asarray(None)
paiCols = N.asarray(None)
paiStvs = N.array([2,2,-1],dtype=N.int32)
padVals = N.array([0.07,0.11,-1],dtype=N.double)
errorcode = lindo.pyLSaddDiscreteBlocks(pModel,iStage,
                                        nBlockEvents,padProb,
                                        pakStart,paiRows,
                                        paiCols,paiStvs,
                                        padVals,iModifyRule)
geterrormessage(pEnv,errorcode)

iStage = 4
nBlockEvents = 2
iModifyRule = LSconst.LS_REPLACE
padProb = N.array([0.5,0.5,-1],dtype=N.double)
pakStart = N.array([0,1,2,-1],dtype=N.int32)
paiRows = N.asarray(None)
paiCols = N.asarray(None)
paiStvs = N.array([3,3,-1],dtype=N.int32)
padVals = N.array([0.01,0.11,-1],dtype=N.double)
errorcode = lindo.pyLSaddDiscreteBlocks(pModel,iStage,
                                        nBlockEvents,padProb,
                                        pakStart,paiRows,
                                        paiCols,paiStvs,
                                        padVals,iModifyRule)
geterrormessage(pEnv,errorcode)

iStage = 5
nBlockEvents = 2
iModifyRule = LSconst.LS_REPLACE
padProb = N.array([0.5,0.5,-1],dtype=N.double)
pakStart = N.array([0,1,2,-1],dtype=N.int32)
paiRows = N.asarray(None)
paiCols = N.asarray(None)
paiStvs = N.array([4,4,-1],dtype=N.int32)
padVals = N.array([-0.08,0.07,-1],dtype=N.double)
errorcode = lindo.pyLSaddDiscreteBlocks(pModel,iStage,
                                        nBlockEvents,padProb,
                                        pakStart,paiRows,
                                        paiCols,paiStvs,
                                        padVals,iModifyRule)
geterrormessage(pEnv,errorcode)

#Get and display SP statistics
numVars = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetInfo(pModel,
                              LSconst.LS_IINFO_NUM_VARS,
                              numVars)
geterrormessage(pEnv,errorcode)

numCons = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetInfo(pModel,
                              LSconst.LS_IINFO_NUM_CONS,
                              numCons)
geterrormessage(pEnv,errorcode)

numCont = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetInfo(pModel,
                              LSconst.LS_IINFO_NUM_CONT,
                              numCont)
geterrormessage(pEnv,errorcode)

numStocPars = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetInfo(pModel,
                              LSconst.LS_IINFO_NUM_SPARS,
                              numStocPars)
geterrormessage(pEnv,errorcode)

numStages = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_STAGES,
                                  0,
                                  numStages)
geterrormessage(pEnv,errorcode)

numNodes = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_NODES,
                                  0,
                                  numNodes)
geterrormessage(pEnv,errorcode)

numScens = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_SCENARIOS,
                                  0,
                                  numScens)
geterrormessage(pEnv,errorcode)

numDeqRows = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_ROWS_DETEQI,
                                  0,
                                  numDeqRows)
geterrormessage(pEnv,errorcode)

numDeqCols = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_COLS_DETEQI,
                                  0,
                                  numDeqCols)
geterrormessage(pEnv,errorcode)

numCoreRows = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_ROWS_CORE,
                                  0,
                                  numCoreRows)
geterrormessage(pEnv,errorcode)

numCoreCols = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSgetStocInfo(pModel,
                                  LSconst.LS_IINFO_STOC_NUM_COLS_CORE,
                                  0,
                                  numCoreCols)
geterrormessage(pEnv,errorcode)

print("\nStochastic Model Stats:");
print("Number of stages = %d" %numStages[0])
print("Number of nodes = %d" %numNodes[0])
print("Number of scenarios = %d" %numScens[0])
print("Core model (rows,cols) = (%d,%d)" %(numCoreRows[0],numCoreCols[0]))
print("")

numStageRows = N.array([-1],dtype=N.int32)
numStageCols = N.array([-1],dtype=N.int32)
for i in range(0,numStages[0]):
    lindo.pyLSgetStocInfo(pModel,
                          LSconst.LS_IINFO_STOC_NUM_ROWS_STAGE,
                          i,
                          numStageRows)
    lindo.pyLSgetStocInfo(pModel,
                          LSconst.LS_IINFO_STOC_NUM_COLS_STAGE,
                          i,
                          numStageCols)
    print("Core model (rows,col) in stage %d: (%d,%d)" 
          %(i,numStageRows,numStageCols))

print("Deterministic eq. (rows,col) = (%d,%d)\n"
      %(numDeqRows[0],numDeqCols[0]))

#Solve the SP
nStatus = N.array([-1],dtype=N.int32)
errorcode = lindo.pyLSsolveSP(pModel,nStatus);
geterrormessage(pEnv,errorcode)

#Access the final solution if optimal or feasible
if (nStatus[0] == LSconst.LS_STATUS_OPTIMAL or
   nStatus[0] == LSconst.LS_STATUS_BASIC_OPTIMAL or
   nStatus[0] == LSconst.LS_STATUS_LOCAL_OPTIMAL or
   nStatus[0] == LSconst.LS_STATUS_FEASIBLE):
       dObj = N.array([-1.0],dtype=N.double)
       errorcode = lindo.pyLSgetStocInfo(pModel,
                                          LSconst.LS_DINFO_STOC_EVOBJ,
                                          0,
                                          dObj)
       print("Objective  = %f" %dObj[0])
else:
    print("Optimization failed. nStatus = %d" %nStatus[0])

#delete LINDO model pointer
errorcode = lindo.pyLSdeleteModel(pModel)
geterrormessage(pEnv,errorcode)

#delete LINDO environment pointer
errorcode = lindo.pyLSdeleteEnv(pEnv)
geterrormessage(pEnv,errorcode)

