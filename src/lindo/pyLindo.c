#include "Python.h"
#include "arrayobject.h"
#include "lindo.h"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define LSASSERT(a) {if ((errorcode = (a)) != 0) goto ErrorReturn;}

#define DCL_BUF(Nx) \
    int errorcode = 0;\
    int    m, n;\
    size_t buflen;\
    char  *sbuf[Nx];\
    int    ibuf[Nx];\
    double dbuf[Nx];\
    double *dvecptr[Nx];\
    int    *ivecptr[Nx];\
    char   *svecptr[Nx];\
    PyArrayObject *pyArr[Nx];


#define ZERO_BUF(Nx) {\
    memset(dvecptr, 0, Nx * sizeof(double*));\
    memset(ivecptr, 0, Nx * sizeof(int*));\
    memset(svecptr, 0, Nx * sizeof(char*));\
    memset(sbuf, 0, Nx * sizeof(char*));\
    memset(ibuf, 0, Nx * sizeof(int));\
    memset(dbuf, 0, Nx * sizeof(double));\
    memset(pyArr, 0, Nx * sizeof(PyArrayObject*));\
    errorcode = m = n = 0;\
    buflen = 0; buflen++;\
    index[0] = 0; buflen = (size_t) index[0];\
}

#define D_GET_VECPTR(k) {\
    if (pyArr[k])\
        dvecptr[k] = (double *)PyArray_GetPtr(pyArr[k], index);\
}

#define I_GET_VECPTR(k) {\
    if (pyArr[k])\
        ivecptr[k] = (int *)PyArray_GetPtr(pyArr[k], index);\
}

#define S_GET_VECPTR(k) {\
    if (pyArr[k])\
        svecptr[k] = (char *)PyArray_GetPtr(pyArr[k], index);\
}

#define I_VECDATA(k) {\
    if (pyArr[k] && pyArr[2]->dimensions > 0)\
        ivecptr[k] = (int*)pyArr[k]->data;\
}

#define D_VECDATA(k) {\
    if (pyArr[k] && pyArr[2]->dimensions > 0)\
        dvecptr[k] = (double*)pyArr[k]->data;\
}

#define S_VECDATA(k) {\
    if (pyArr[k] && pyArr[2]->dimensions > 0)\
        svecptr[k] = (char*)pyArr[k]->data;\
}

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif



static PyObject * error_out(PyObject *m)
{
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

/*********************************************************************
 * Structure Creation and Deletion Routines (5)                      *
 *********************************************************************/
PyObject *pyLScreateEnv(PyObject *self, PyObject *args);
PyObject *pyLScreateModel(PyObject *self, PyObject *args);
PyObject *pyLSdeleteEnv(PyObject *self, PyObject *args);
PyObject *pyLSdeleteModel(PyObject *self, PyObject *args);
PyObject *pyLScopyParam(PyObject *self, PyObject *args);
PyObject *pyLSloadLicenseString(PyObject *self, PyObject *args);
PyObject *pyLSgetVersionInfo(PyObject *self, PyObject *args);

/********************************************************
 * Model I-O Routines (18)                              *
 ********************************************************/
PyObject *pyLSreadMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSreadLINDOFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteLINDOFile(PyObject *self, PyObject *args);
PyObject *pyLSreadLINDOStream(PyObject *self, PyObject *args);
PyObject *pyLSwriteLINGOFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteDualMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteSolution(PyObject *self, PyObject *args);
PyObject *pyLSwriteSolutionOfType(PyObject *self, PyObject *args);
PyObject *pyLSwriteIIS(PyObject *self, PyObject *args);
PyObject *pyLSwriteIUS(PyObject *self, PyObject *args);
PyObject *pyLSreadMPIFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteMPIFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteWithSetsAndSC(PyObject *self, PyObject *args);
PyObject *pyLSreadBasis(PyObject *self, PyObject *args);
PyObject *pyLSwriteBasis(PyObject *self, PyObject *args);
PyObject *pyLSreadLPFile(PyObject *self, PyObject *args);
PyObject *pyLSreadLPStream(PyObject *self, PyObject *args);

/********************************************************
 * Error Handling Routines (3)                          *
 ********************************************************/
PyObject *pyLSgetErrorMessage(PyObject *self, PyObject *args);
PyObject *pyLSgetFileError(PyObject *self, PyObject *args);
PyObject *pyLSgetErrorRowIndex(PyObject *self, PyObject *args);

/***********************************************************
 * Routines for Setting and Retrieving Parameter Values(21)*
 ***********************************************************/
PyObject *pyLSsetModelParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetModelParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetEnvParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetEnvParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetModelDouParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetModelDouParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetModelIntParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetModelIntParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetEnvDouParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetEnvDouParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetEnvIntParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetEnvIntParameter(PyObject *self, PyObject *args);
PyObject *pyLSreadModelParameter(PyObject *self, PyObject *args);
PyObject *pyLSreadEnvParameter(PyObject *self, PyObject *args);
PyObject *pyLSwriteModelParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetIntParameterRange(PyObject *self, PyObject *args);
PyObject *pyLSgetDouParameterRange(PyObject *self, PyObject *args);
PyObject *pyLSgetParamShortDesc(PyObject *self, PyObject *args);
PyObject *pyLSgetParamLongDesc(PyObject *self, PyObject *args);
PyObject *pyLSgetParamMacroName(PyObject *self, PyObject *args);
PyObject *pyLSgetParamMacroID(PyObject *self, PyObject *args);

/********************************************************
* Model Loading Routines (10)                           *
*********************************************************/
PyObject *pyLSloadLPData(PyObject *self, PyObject *args);
PyObject *pyLSloadQCData(PyObject *self, PyObject *args);
PyObject *pyLSloadConeData(PyObject *self, PyObject *args);
PyObject *pyLSloadSETSData(PyObject *self, PyObject *args);
PyObject *pyLSloadSemiContData(PyObject *self, PyObject *args);
PyObject *pyLSloadVarType(PyObject *self, PyObject *args);
PyObject *pyLSloadNLPData(PyObject *self, PyObject *args);
PyObject *pyLSloadInstruct(PyObject *self, PyObject *args);
PyObject *pyLSaddInstruct(PyObject *self, PyObject *args);
PyObject *pyLSgetDualModel(PyObject *self, PyObject *args);

/**********************************************************************
 * Solver Initialization Routines (9)                                 *
 **********************************************************************/
PyObject *pyLSloadBasis(PyObject *self, PyObject *args);
PyObject *pyLSloadVarPriorities(PyObject *self, PyObject *args);
PyObject *pyLSreadVarPriorities(PyObject *self, PyObject *args);
PyObject *pyLSloadVarStartPoint(PyObject *self, PyObject *args);
PyObject *pyLSloadVarStartPointPartial(PyObject *self, PyObject *args);
PyObject *pyLSloadMIPVarStartPoint(PyObject *self, PyObject *args);
PyObject *pyLSloadMIPVarStartPointPartial(PyObject *self, PyObject *args);
PyObject *pyLSreadVarStartPoint(PyObject *self, PyObject *args);
PyObject *pyLSloadBlockStructure(PyObject *self, PyObject *args);
PyObject *pyLSfindBlockStructure(PyObject *self, PyObject *args);

/**********************************************************************
 * Optimization Routines (6)                                          *
 **********************************************************************/
PyObject *pyLSoptimize(PyObject *self, PyObject *args);
PyObject *pyLSsolveMIP(PyObject *self, PyObject *args);
PyObject *pyLSsolveGOP(PyObject *self, PyObject *args);
PyObject *pyLSoptimizeQP(PyObject *self, PyObject *args);
PyObject *pyLScheckConvexity(PyObject *self, PyObject *args);
PyObject *pyLSsolveSBD(PyObject *self, PyObject *args);

/**********************************************************************
 * Solution Query Routines (14)                                       *
**********************************************************************/
PyObject *pyLSgetInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetPrimalSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetDualSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetReducedCosts(PyObject *self, PyObject *args);
PyObject *pyLSgetReducedCostsCone(PyObject *self, PyObject *args);
PyObject *pyLSgetSlacks(PyObject *self, PyObject *args);
PyObject *pyLSgetBasis(PyObject *self, PyObject *args);
PyObject *pyLSgetSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPPrimalSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPDualSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPReducedCosts(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPSlacks(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPBasis(PyObject *self, PyObject *args);
PyObject *pyLSgetNextBestMIPSol(PyObject *self, PyObject *args);

/*********************************************************************
 *  Model Query Routines (30)                                        *
 *********************************************************************/
PyObject *pyLSgetLPData(PyObject *self, PyObject *args);
PyObject *pyLSgetQCData(PyObject *self, PyObject *args);
PyObject *pyLSgetQCDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetVarType(PyObject *self, PyObject *args);
PyObject *pyLSgetVarStartPoint(PyObject *self, PyObject *args);
PyObject *pyLSgetVarStartPointPartial(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPVarStartPointPartial(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPVarStartPoint(PyObject *self, PyObject *args);
PyObject *pyLSgetSETSData(PyObject *self, PyObject *args);
PyObject *pyLSgetSETSDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetSemiContData(PyObject *self, PyObject *args);
PyObject *pyLSgetLPVariableDataj(PyObject *self, PyObject *args);
PyObject *pyLSgetVariableNamej(PyObject *self, PyObject *args);
PyObject *pyLSgetVariableIndex(PyObject *self, PyObject *args);
PyObject *pyLSgetConstraintNamei(PyObject *self, PyObject *args);
PyObject *pyLSgetConstraintIndex(PyObject *self, PyObject *args);
PyObject *pyLSgetConstraintDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetLPConstraintDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetConeNamei(PyObject *self, PyObject *args);
PyObject *pyLSgetConeIndex(PyObject *self, PyObject *args);
PyObject *pyLSgetConeDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetNLPData(PyObject *self, PyObject *args);
PyObject *pyLSgetNLPConstraintDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetNLPVariableDataj(PyObject *self, PyObject *args);
PyObject *pyLSgetNLPObjectiveData(PyObject *self, PyObject *args);
PyObject *pyLSgetInstruct(PyObject *self, PyObject *args);
PyObject *pyLScalinfeasMIPsolution(PyObject *self, PyObject *args);
PyObject *pyLSgetRoundMIPsolution(PyObject *self, PyObject *args);
PyObject *pyLSgetDuplicateColumns(PyObject *self, PyObject *args);
PyObject *pyLSgetRangeData(PyObject *self, PyObject *args);

/**********************************************************************
 *  Model Modification Routines (26)                                  *
 **********************************************************************/
PyObject *pyLSaddConstraints(PyObject *self, PyObject *args);
PyObject *pyLSaddVariables(PyObject *self, PyObject *args);
PyObject *pyLSaddCones(PyObject *self, PyObject *args);
PyObject *pyLSaddSETS(PyObject *self, PyObject *args);
PyObject *pyLSaddQCterms(PyObject *self, PyObject *args);
PyObject *pyLSdeleteConstraints(PyObject *self, PyObject *args);
PyObject *pyLSdeleteCones(PyObject *self, PyObject *args);
PyObject *pyLSdeleteSETS(PyObject *self, PyObject *args);
PyObject *pyLSdeleteSemiContVars(PyObject *self, PyObject *args);
PyObject *pyLSdeleteVariables(PyObject *self, PyObject *args);
PyObject *pyLSdeleteQCterms(PyObject *self, PyObject *args);
PyObject *pyLSdeleteAj(PyObject *self, PyObject *args);
PyObject *pyLSmodifyLowerBounds(PyObject *self, PyObject *args);
PyObject *pyLSmodifyUpperBounds(PyObject *self, PyObject *args);
PyObject *pyLSmodifyRHS(PyObject *self, PyObject *args);
PyObject *pyLSmodifyObjective(PyObject *self, PyObject *args);
PyObject *pyLSmodifyObjConstant(PyObject *self, PyObject *args);
PyObject *pyLSmodifyAj(PyObject *self, PyObject *args);
PyObject *pyLSmodifyCone(PyObject *self, PyObject *args);
PyObject *pyLSmodifySET(PyObject *self, PyObject *args);
PyObject *pyLSmodifySemiContVars(PyObject *self, PyObject *args);
PyObject *pyLSmodifyConstraintType(PyObject *self, PyObject *args);
PyObject *pyLSmodifyVariableType(PyObject *self, PyObject *args);
PyObject *pyLSaddNLPAj(PyObject *self, PyObject *args);
PyObject *pyLSaddNLPobj(PyObject *self, PyObject *args);
PyObject *pyLSdeleteNLPobj(PyObject *self, PyObject *args);

/*********************************************************************
 *   Model & Solution Analysis Routines (8)                         *
 *********************************************************************/
PyObject *pyLSgetConstraintRanges(PyObject *self, PyObject *args);
PyObject *pyLSgetObjectiveRanges(PyObject *self, PyObject *args);
PyObject *pyLSgetBoundRanges(PyObject *self, PyObject *args);
PyObject *pyLSgetBestBounds(PyObject *self, PyObject *args);
PyObject *pyLSfindIIS(PyObject *self, PyObject *args);
PyObject *pyLSfindIUS(PyObject *self, PyObject *args);
PyObject *pyLSgetIIS(PyObject *self, PyObject *args);
PyObject *pyLSgetBlockStructure(PyObject *self, PyObject *args);
PyObject *pyLSgetIUS(PyObject *self, PyObject *args);

/*********************************************************************
 *    Stochastic Programming Interface (73)                          *
 *********************************************************************/
PyObject *pyLSwriteDeteqMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteDeteqLINDOFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteSMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSreadSMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteSMPIFile(PyObject *self, PyObject *args);
PyObject *pyLSreadSMPIFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteScenarioSolutionFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteNodeSolutionFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteScenarioMPIFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteScenarioMPSFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteScenarioLINDOFile(PyObject *self, PyObject *args);
PyObject *pyLSgetModelStocDouParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetModelStocIntParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetModelStocIntParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioIndex(PyObject *self, PyObject *args);
PyObject *pyLSgetStageIndex(PyObject *self, PyObject *args);
PyObject *pyLSgetStocParIndex(PyObject *self, PyObject *args);
PyObject *pyLSgetStocParName(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioName(PyObject *self, PyObject *args);
PyObject *pyLSgetStageName(PyObject *self, PyObject *args);
PyObject *pyLSgetStocInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetStocCCPInfo(PyObject *self, PyObject *args);
PyObject *pyLSloadSampleSizes(PyObject *self, PyObject *args);
PyObject *pyLSloadConstraintStages(PyObject *self, PyObject *args);
PyObject *pyLSloadVariableStages(PyObject *self, PyObject *args);
PyObject *pyLSloadStageData(PyObject *self, PyObject *args);
PyObject *pyLSloadStocParData(PyObject *self, PyObject *args);
PyObject *pyLSgetDeteqModel(PyObject *self, PyObject *args);
PyObject *pyLSaggregateStages(PyObject *self, PyObject *args);
PyObject *pyLSgetStageAggScheme(PyObject *self, PyObject *args);
PyObject *pyLSsolveSP(PyObject *self, PyObject *args);
PyObject *pyLSsolveHS(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioObjective(PyObject *self, PyObject *args);
PyObject *pyLSgetNodePrimalSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetNodeDualSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetNodeReducedCost(PyObject *self, PyObject *args);
PyObject *pyLSgetNodeSlacks(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioPrimalSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioReducedCost(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioDualSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioSlacks(PyObject *self, PyObject *args);
PyObject *pyLSgetNodeListByScenario(PyObject *self, PyObject *args);
PyObject *pyLSgetProbabilityByScenario(PyObject *self, PyObject *args);
PyObject *pyLSgetProbabilityByNode(PyObject *self, PyObject *args);
PyObject *pyLSgetStocParData(PyObject *self, PyObject *args);
PyObject *pyLSaddDiscreteBlocks(PyObject *self, PyObject *args);
PyObject *pyLSaddScenario(PyObject *self, PyObject *args);
PyObject *pyLSaddDiscreteIndep(PyObject *self, PyObject *args);
PyObject *pyLSaddParamDistIndep(PyObject *self, PyObject *args);
PyObject *pyLSaddChanceConstraint(PyObject *self, PyObject *args);
PyObject *pyLSsetNumStages(PyObject *self, PyObject *args);
PyObject *pyLSgetStocParOutcomes(PyObject *self, PyObject *args);
PyObject *pyLSloadCorrelationMatrix(PyObject *self, PyObject *args);
PyObject *pyLSgetCorrelationMatrix(PyObject *self, PyObject *args);
PyObject *pyLSgetStocParSample(PyObject *self, PyObject *args);
PyObject *pyLSgetDiscreteBlocks(PyObject *self, PyObject *args);
PyObject *pyLSgetDiscreteBlockOutcomes(PyObject *self, PyObject *args);
PyObject *pyLSgetDiscreteIndep(PyObject *self, PyObject *args);
PyObject *pyLSgetParamDistIndep(PyObject *self, PyObject *args);
PyObject *pyLSgetScenario(PyObject *self, PyObject *args);
PyObject *pyLSgetChanceConstraint(PyObject *self, PyObject *args);
PyObject *pyLSgetSampleSizes(PyObject *self, PyObject *args);
PyObject *pyLSgetConstraintStages(PyObject *self, PyObject *args);
PyObject *pyLSgetVariableStages(PyObject *self, PyObject *args);
PyObject *pyLSgetStocRowIndices(PyObject *self, PyObject *args);
PyObject *pyLSsetStocParRG(PyObject *self, PyObject *args);
PyObject *pyLSgetScenarioModel(PyObject *self, PyObject *args);
PyObject *pyLSfreeStocMemory(PyObject *self, PyObject *args);
PyObject *pyLSfreeStocHashMemory(PyObject *self, PyObject *args);
PyObject *pyLSgetModelStocParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetModelStocParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetEnvStocParameter(PyObject *self, PyObject *args);
PyObject *pyLSgetEnvStocParameter(PyObject *self, PyObject *args);
PyObject *pyLSsetModelStocDouParameter(PyObject *self, PyObject *args);

/*********************************************************************
 *    Statistical Calculations Interface (16)                        *
 *********************************************************************/
PyObject *pyLSsampCreate(PyObject *self, PyObject *args);
PyObject *pyLSsampDelete(PyObject *self, PyObject *args);
PyObject *pyLSsampSetDistrParam(PyObject *self, PyObject *args);
PyObject *pyLSsampGetDistrParam(PyObject *self, PyObject *args);
PyObject *pyLSsampEvalDistr(PyObject *self, PyObject *args);
PyObject *pyLSsampEvalDistrLI(PyObject *self, PyObject *args);
PyObject *pyLSsampEvalUserDistr(PyObject *self, PyObject *args);
PyObject *pyLSsampSetRG(PyObject *self, PyObject *args);
PyObject *pyLSsampGenerate(PyObject *self, PyObject *args);
PyObject *pyLSsampGetPoints(PyObject *self, PyObject *args);
PyObject *pyLSsampLoadPoints(PyObject *self, PyObject *args);
PyObject *pyLSsampGetCIPoints(PyObject *self, PyObject *args);
PyObject *pyLSsampLoadDiscretePdfTable(PyObject *self, PyObject *args);
PyObject *pyLSsampGetDiscretePdfTable(PyObject *self, PyObject *args);
PyObject *pyLSsampGetInfo(PyObject *self, PyObject *args);
PyObject *pyLSsampAddUserFuncArg(PyObject *self, PyObject *args);

/*********************************************************************
 *      Random Number Generation Interface()                         *
 *********************************************************************/
PyObject *pyLScreateRG(PyObject *self, PyObject *args);
PyObject *pyLScreateRGMT(PyObject *self, PyObject *args);
PyObject *pyLSgetDoubleRV(PyObject *self, PyObject *args);
PyObject *pyLSgetInt32RV(PyObject *self, PyObject *args);
PyObject *pyLSsetRGSeed(PyObject *self, PyObject *args);
PyObject *pyLSdisposeRG(PyObject *self, PyObject *args);
PyObject *pyLSsetDistrParamRG(PyObject *self, PyObject *args);
PyObject *pyLSsetDistrRG(PyObject *self, PyObject *args);
PyObject *pyLSgetDistrRV(PyObject *self, PyObject *args);
PyObject *pyLSgetInitSeed(PyObject *self, PyObject *args);
PyObject *pyLSgetRGNumThreads(PyObject *self, PyObject *args);
PyObject *pyLSfillRGBuffer(PyObject *self, PyObject *args);
PyObject *pyLSgetHistogram(PyObject *self, PyObject *args);
PyObject *pyLSsolveMipBnp(PyObject *self, PyObject *args);
// lsmakepy.lua 2020-02-22
PyObject *pyLSwriteMPXFile(PyObject *self, PyObject *args);
PyObject *pyLSreadMPXFile(PyObject *self, PyObject *args);
PyObject *pyLSwriteVarPriorities(PyObject *self, PyObject *args);
PyObject *pyLSwriteNLSolution(PyObject *self, PyObject *args);
PyObject *pyLSaddTunerInstance(PyObject *self, PyObject *args);
PyObject *pyLSaddTunerOption(PyObject *self, PyObject *args);
PyObject *pyLSaddTunerZDynamic(PyObject *self, PyObject *args);
PyObject *pyLSaddTunerZStatic(PyObject *self, PyObject *args);
PyObject *pyLSclearTuner(PyObject *self, PyObject *args);
PyObject *pyLSdisplayTunerResults(PyObject *self, PyObject *args);
PyObject *pyLSgetTunerConfigString(PyObject *self, PyObject *args);
PyObject *pyLSgetTunerOption(PyObject *self, PyObject *args);
PyObject *pyLSgetTunerResult(PyObject *self, PyObject *args);
PyObject *pyLSgetTunerSpace(PyObject *self, PyObject *args);
PyObject *pyLSgetTunerStrOption(PyObject *self, PyObject *args);
PyObject *pyLSloadTunerConfigFile(PyObject *self, PyObject *args);
PyObject *pyLSloadTunerConfigString(PyObject *self, PyObject *args);
PyObject *pyLSprintTuner(PyObject *self, PyObject *args);
PyObject *pyLSresetTuner(PyObject *self, PyObject *args);
PyObject *pyLSrunTuner(PyObject *self, PyObject *args);
PyObject *pyLSrunTunerFile(PyObject *self, PyObject *args);
PyObject *pyLSrunTunerString(PyObject *self, PyObject *args);
PyObject *pyLSsetTunerOption(PyObject *self, PyObject *args);
PyObject *pyLSsetTunerStrOption(PyObject *self, PyObject *args);
PyObject *pyLSaddQCShift(PyObject *self, PyObject *args);
PyObject *pyLSgetQCShift(PyObject *self, PyObject *args);
PyObject *pyLSresetQCShift(PyObject *self, PyObject *args);

PyObject *pyLSreadCBFFile(PyObject *self, PyObject *args);
PyObject *pyLSreadNLFile(PyObject *self, PyObject *args);
PyObject *pyLSreadSDPAFile(PyObject *self, PyObject *args);
PyObject *pyLSsolveFileLP(PyObject *self, PyObject *args);
PyObject *pyLSgetProfilerContext(PyObject *self, PyObject *args);
PyObject *pyLSgetProfilerInfo(PyObject *self, PyObject *args);
PyObject *pyLSaddEmptySpacesAcolumns(PyObject *self, PyObject *args);
PyObject *pyLSaddEmptySpacesNLPAcolumns(PyObject *self, PyObject *args);
PyObject *pyLSaddObjPool(PyObject *self, PyObject *args);
PyObject *pyLSapplyLtf(PyObject *self, PyObject *args);
PyObject *pyLSbnbSolve(PyObject *self, PyObject *args);
PyObject *pyLSbuildStringData(PyObject *self, PyObject *args);
PyObject *pyLScalcConFunc(PyObject *self, PyObject *args);
PyObject *pyLScalcConGrad(PyObject *self, PyObject *args);
PyObject *pyLScalcObjFunc(PyObject *self, PyObject *args);
PyObject *pyLScalcObjGrad(PyObject *self, PyObject *args);
PyObject *pyLScheckQterms(PyObject *self, PyObject *args);
PyObject *pyLSdeduceStages(PyObject *self, PyObject *args);
PyObject *pyLSdeleteString(PyObject *self, PyObject *args);
PyObject *pyLSdeleteStringData(PyObject *self, PyObject *args);
PyObject *pyLSdisplayBlockStructure(PyObject *self, PyObject *args);
PyObject *pyLSdoBTRAN(PyObject *self, PyObject *args);
PyObject *pyLSdoFTRAN(PyObject *self, PyObject *args);
PyObject *pyLSfindLtf(PyObject *self, PyObject *args);
PyObject *pyLSfindSymmetry(PyObject *self, PyObject *args);
PyObject *pyLSfreeGOPSolutionMemory(PyObject *self, PyObject *args);
PyObject *pyLSfreeHashMemory(PyObject *self, PyObject *args);
PyObject *pyLSfreeMIPSolutionMemory(PyObject *self, PyObject *args);
PyObject *pyLSfreeObjPool(PyObject *self, PyObject *args);
PyObject *pyLSfreeSolutionMemory(PyObject *self, PyObject *args);
PyObject *pyLSfreeSolverMemory(PyObject *self, PyObject *args);
PyObject *pyLSgetALLDIFFData(PyObject *self, PyObject *args);
PyObject *pyLSgetALLDIFFDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetDimensions(PyObject *self, PyObject *args);
PyObject *pyLSgetDualMIPsolution(PyObject *self, PyObject *args);
PyObject *pyLSgetGOPVariablePriority(PyObject *self, PyObject *args);
PyObject *pyLSgetHess(PyObject *self, PyObject *args);
PyObject *pyLSgetIISInts(PyObject *self, PyObject *args);
PyObject *pyLSgetIISSETs(PyObject *self, PyObject *args);
PyObject *pyLSgetJac(PyObject *self, PyObject *args);
PyObject *pyLSgetKBestMIPSols(PyObject *self, PyObject *args);
PyObject *pyLSgetLicenseInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetMasterModel(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPCallbackInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPSolutionStatus(PyObject *self, PyObject *args);
PyObject *pyLSgetNextBestSol(PyObject *self, PyObject *args);
PyObject *pyLSgetNnzData(PyObject *self, PyObject *args);
PyObject *pyLSgetObjectiveRanges(PyObject *self, PyObject *args);
PyObject *pyLSgetObjPoolNumSol(PyObject *self, PyObject *args);
PyObject *pyLSgetOrbitInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetPOSDData(PyObject *self, PyObject *args);
PyObject *pyLSgetPOSDDatai(PyObject *self, PyObject *args);
PyObject *pyLSgetProgressInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetSolutionInfo(PyObject *self, PyObject *args);
PyObject *pyLSgetSolutionStatus(PyObject *self, PyObject *args);
PyObject *pyLSgetXSolverLibrary(PyObject *self, PyObject *args);
PyObject *pyLSloadALLDIFFData(PyObject *self, PyObject *args);
PyObject *pyLSloadGASolution(PyObject *self, PyObject *args);
PyObject *pyLSloadIISPriorities(PyObject *self, PyObject *args);
PyObject *pyLSloadMultiStartSolution(PyObject *self, PyObject *args);
PyObject *pyLSloadNLPDense(PyObject *self, PyObject *args);
PyObject *pyLSloadPOSDData(PyObject *self, PyObject *args);
PyObject *pyLSloadSolutionAt(PyObject *self, PyObject *args);
PyObject *pyLSloadStringData(PyObject *self, PyObject *args);
PyObject *pyLSloadStringData(PyObject *self, PyObject *args);
PyObject *pyLSreadMPXStream(PyObject *self, PyObject *args);
PyObject *pyLSsetObjPoolParam(PyObject *self, PyObject *args);
PyObject *pyLSgetObjPoolParam(PyObject *self, PyObject *args);
PyObject *pyLSsetProbAllocSizes(PyObject *self, PyObject *args);
PyObject *pyLSsetProbNameAllocSizes(PyObject *self, PyObject *args);
PyObject *pyLSsetSETSStatei(PyObject *self, PyObject *args);
PyObject *pyLSsetXSolverLibrary(PyObject *self, PyObject *args);
PyObject *pyLSsetConstraintProperty(PyObject *self, PyObject *args);
PyObject *pyLSregress(PyObject *self, PyObject *args);
PyObject *pyLSremObjPool(PyObject *self, PyObject *args);
PyObject *pyLSgetMIPSolution(PyObject *self, PyObject *args);
PyObject *pyLSgetObjective(PyObject *self, PyObject *args);
PyObject *pyLSsetGOPVariablePriority(PyObject *self, PyObject *args);
PyObject *pyLSgetStringValue(PyObject *self, PyObject *args);
PyObject *pyLSrepairQterms(PyObject *self, PyObject *args);
PyObject *pyLSsetMIPCCStrategy(PyObject *self, PyObject *args);

PyObject *pyLSsetModelLogfunc(PyObject *self, PyObject *args);
PyObject *pyLSsetEnvLogfunc(PyObject *self, PyObject *args);
PyObject *pyLSsetCallback(PyObject *self, PyObject *args);
PyObject *pyLSsetMIPCallback(PyObject *self, PyObject *args);
PyObject *pyLSsetFuncalc(PyObject *self, PyObject *args);
PyObject *pyLSsetGradcalc(PyObject *self, PyObject *args);
PyObject *pyLSwriteTunerParameters(PyObject *self, PyObject *args);
#ifdef _DEBUG
#include "pyLindo_decl.h"
#endif
static PyMethodDef lindo_methods[] =
{
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"pyLScreateEnv", pyLScreateEnv, METH_VARARGS},
    {"pyLScreateModel", pyLScreateModel, METH_VARARGS},
    {"pyLSdeleteEnv", pyLSdeleteEnv, METH_VARARGS},
    {"pyLSdeleteModel", pyLSdeleteModel, METH_VARARGS},
    {"pyLScopyParam", pyLScopyParam, METH_VARARGS},
    {"pyLSloadLicenseString", pyLSloadLicenseString, METH_VARARGS},
    {"pyLSgetVersionInfo", pyLSgetVersionInfo, METH_VARARGS},
    {"pyLSreadMPSFile", pyLSreadMPSFile, METH_VARARGS},
    {"pyLSwriteMPSFile", pyLSwriteMPSFile, METH_VARARGS},
    {"pyLSreadLINDOFile", pyLSreadLINDOFile, METH_VARARGS},
    {"pyLSwriteLINDOFile", pyLSwriteLINDOFile, METH_VARARGS},
    {"pyLSreadLINDOStream", pyLSreadLINDOStream, METH_VARARGS},
    {"pyLSwriteLINGOFile", pyLSwriteLINGOFile, METH_VARARGS},
    {"pyLSwriteDualMPSFile", pyLSwriteDualMPSFile, METH_VARARGS},
    {"pyLSwriteSolution", pyLSwriteSolution, METH_VARARGS},
    {"pyLSwriteSolutionOfType", pyLSwriteSolutionOfType, METH_VARARGS},
    {"pyLSwriteIIS", pyLSwriteIIS, METH_VARARGS},
    {"pyLSwriteIUS", pyLSwriteIUS, METH_VARARGS},
    {"pyLSreadMPIFile", pyLSreadMPIFile, METH_VARARGS},
    {"pyLSwriteMPIFile", pyLSwriteMPIFile, METH_VARARGS},
    {"pyLSwriteWithSetsAndSC", pyLSwriteWithSetsAndSC, METH_VARARGS},
    {"pyLSreadBasis", pyLSreadBasis, METH_VARARGS},
    {"pyLSwriteBasis", pyLSwriteBasis, METH_VARARGS},
    {"pyLSreadLPFile", pyLSreadLPFile, METH_VARARGS},
    {"pyLSreadLPStream", pyLSreadLPStream, METH_VARARGS},
    {"pyLSgetErrorMessage", pyLSgetErrorMessage, METH_VARARGS},
    {"pyLSgetFileError", pyLSgetFileError, METH_VARARGS},
    {"pyLSgetErrorRowIndex", pyLSgetErrorRowIndex, METH_VARARGS},
    {"pyLSsetModelParameter", pyLSsetModelParameter, METH_VARARGS},
    {"pyLSgetModelParameterr", pyLSgetModelParameter, METH_VARARGS},
    {"pyLSsetEnvParameter", pyLSsetEnvParameter, METH_VARARGS},
    {"pyLSgetEnvParameter", pyLSgetEnvParameter, METH_VARARGS},
    {"pyLSsetModelDouParameter", pyLSsetModelDouParameter, METH_VARARGS},
    {"pyLSgetModelDouParameter", pyLSgetModelDouParameter, METH_VARARGS},
    {"pyLSsetModelIntParameter", pyLSsetModelIntParameter, METH_VARARGS},
    {"pyLSgetModelIntParameter", pyLSgetModelIntParameter, METH_VARARGS},
    {"pyLSsetEnvDouParameter", pyLSsetEnvDouParameter, METH_VARARGS},
    {"pyLSgetEnvDouParameter", pyLSgetEnvDouParameter, METH_VARARGS},
    {"pyLSsetEnvIntParameter", pyLSsetEnvIntParameter, METH_VARARGS},
    {"pyLSgetEnvIntParameter", pyLSgetEnvIntParameter, METH_VARARGS},
    {"pyLSreadModelParameter", pyLSreadModelParameter, METH_VARARGS},
    {"pyLSreadEnvParameter", pyLSreadEnvParameter, METH_VARARGS},
    {"pyLSwriteModelParameter", pyLSwriteModelParameter, METH_VARARGS},
    {"pyLSgetIntParameterRange", pyLSgetIntParameterRange, METH_VARARGS},
    {"pyLSgetDouParameterRange", pyLSgetDouParameterRange, METH_VARARGS},
    {"pyLSgetParamShortDesc", pyLSgetParamShortDesc, METH_VARARGS},
    {"pyLSgetParamLongDesc", pyLSgetParamLongDesc, METH_VARARGS},
    {"pyLSgetParamMacroName", pyLSgetParamMacroName, METH_VARARGS},
    {"pyLSgetParamMacroID", pyLSgetParamMacroID, METH_VARARGS},
    {"pyLSloadLPData", pyLSloadLPData, METH_VARARGS},
    {"pyLSloadQCData", pyLSloadQCData, METH_VARARGS},
    {"pyLSloadConeData", pyLSloadConeData, METH_VARARGS},
    {"pyLSloadSETSData", pyLSloadSETSData, METH_VARARGS},
    {"pyLSloadSemiContData", pyLSloadSemiContData, METH_VARARGS},
    {"pyLSloadVarType", pyLSloadVarType, METH_VARARGS},
    {"pyLSloadNLPData", pyLSloadNLPData, METH_VARARGS},
    {"pyLSloadInstruct", pyLSloadInstruct, METH_VARARGS},
    {"pyLSaddInstruct", pyLSaddInstruct, METH_VARARGS},
    {"pyLSloadBasis", pyLSloadBasis, METH_VARARGS},
    {"pyLSloadVarPriorities", pyLSloadVarPriorities, METH_VARARGS},
    {"pyLSreadVarPriorities", pyLSreadVarPriorities, METH_VARARGS},
    {"pyLSloadVarStartPoint", pyLSloadVarStartPoint, METH_VARARGS},
    {"pyLSloadVarStartPointPartial", pyLSloadVarStartPointPartial, METH_VARARGS},
    {"pyLSloadMIPVarStartPoint", pyLSloadMIPVarStartPoint, METH_VARARGS},
    {"pyLSloadMIPVarStartPointPartial", pyLSloadMIPVarStartPointPartial, METH_VARARGS},
    {"pyLSreadVarStartPoint", pyLSreadVarStartPoint, METH_VARARGS},
    {"pyLSloadBlockStructure", pyLSloadBlockStructure, METH_VARARGS},
    {"pyLSoptimize", pyLSoptimize, METH_VARARGS},
    {"pyLSsolveMIP", pyLSsolveMIP, METH_VARARGS},
    {"pyLSsolveGOP", pyLSsolveGOP, METH_VARARGS},
    {"pyLSoptimizeQP", pyLSoptimizeQP, METH_VARARGS},
    {"pyLScheckConvexity", pyLScheckConvexity, METH_VARARGS},
    {"pyLSsolveSBD", pyLSsolveSBD, METH_VARARGS},
    {"pyLSgetInfo", pyLSgetInfo, METH_VARARGS},
    {"pyLSgetPrimalSolution", pyLSgetPrimalSolution, METH_VARARGS},
    {"pyLSgetDualSolution", pyLSgetDualSolution, METH_VARARGS},
    {"pyLSgetReducedCosts", pyLSgetReducedCosts, METH_VARARGS},
    {"pyLSgetReducedCostsCone", pyLSgetReducedCostsCone, METH_VARARGS},
    {"pyLSgetSlacks", pyLSgetSlacks, METH_VARARGS},
    {"pyLSgetBasis", pyLSgetBasis, METH_VARARGS},
    {"pyLSgetSolution", pyLSgetSolution, METH_VARARGS},
    {"pyLSgetMIPPrimalSolution", pyLSgetMIPPrimalSolution, METH_VARARGS},
    {"pyLSgetMIPDualSolution", pyLSgetMIPDualSolution, METH_VARARGS},
    {"pyLSgetMIPReducedCosts", pyLSgetMIPReducedCosts, METH_VARARGS},
    {"pyLSgetMIPSlacks", pyLSgetMIPSlacks, METH_VARARGS},
    {"pyLSgetMIPBasis", pyLSgetMIPBasis, METH_VARARGS},
    {"pyLSgetNextBestMIPSol", pyLSgetNextBestMIPSol, METH_VARARGS},
    {"pyLSgetLPData", pyLSgetLPData, METH_VARARGS},
    {"pyLSgetQCData", pyLSgetQCData, METH_VARARGS},
    {"pyLSgetQCDatai", pyLSgetQCDatai, METH_VARARGS},
    {"pyLSgetVarType", pyLSgetVarType, METH_VARARGS},
    {"pyLSgetVarStartPoint", pyLSgetVarStartPoint, METH_VARARGS},
    {"pyLSgetVarStartPointPartial", pyLSgetVarStartPointPartial, METH_VARARGS},
    {"pyLSgetMIPVarStartPointPartial", pyLSgetMIPVarStartPointPartial, METH_VARARGS},
    {"pyLSgetMIPVarStartPoint", pyLSgetMIPVarStartPoint, METH_VARARGS},
    {"pyLSgetSETSData", pyLSgetSETSData, METH_VARARGS},
    {"pyLSgetSETSDatai", pyLSgetSETSDatai, METH_VARARGS},
    {"pyLSgetSemiContData", pyLSgetSemiContData, METH_VARARGS},
    {"pyLSgetLPVariableDataj", pyLSgetLPVariableDataj, METH_VARARGS},
    {"pyLSgetVariableNamej", pyLSgetVariableNamej, METH_VARARGS},
    {"pyLSgetVariableIndex", pyLSgetVariableIndex, METH_VARARGS},
    {"pyLSgetConstraintNamei", pyLSgetConstraintNamei, METH_VARARGS},
    {"pyLSgetConstraintIndex", pyLSgetConstraintIndex, METH_VARARGS},
    {"pyLSgetConstraintDatai", pyLSgetConstraintDatai, METH_VARARGS},
    {"pyLSgetLPConstraintDatai", pyLSgetLPConstraintDatai, METH_VARARGS},
    {"pyLSgetConeNamei", pyLSgetConeNamei, METH_VARARGS},
    {"pyLSgetConeIndex", pyLSgetConeIndex, METH_VARARGS},
    {"pyLSgetConeDatai", pyLSgetConeDatai, METH_VARARGS},
    {"pyLSgetNLPData", pyLSgetNLPData, METH_VARARGS},
    {"pyLSgetNLPConstraintDatai", pyLSgetNLPConstraintDatai, METH_VARARGS},
    {"pyLSgetNLPVariableDataj", pyLSgetNLPVariableDataj, METH_VARARGS},
    {"pyLSgetNLPObjectiveData", pyLSgetNLPObjectiveData, METH_VARARGS},
    {"pyLSgetInstruct", pyLSgetInstruct, METH_VARARGS},
    {"pyLScalinfeasMIPsolution", pyLScalinfeasMIPsolution, METH_VARARGS},
    {"pyLSgetRoundMIPsolution", pyLSgetRoundMIPsolution, METH_VARARGS},
    {"pyLSgetDuplicateColumns", pyLSgetDuplicateColumns, METH_VARARGS},
    {"pyLSgetRangeData", pyLSgetRangeData, METH_VARARGS},
    {"pyLSaddConstraints", pyLSaddConstraints, METH_VARARGS},
    {"pyLSaddVariables", pyLSaddVariables, METH_VARARGS},
    {"pyLSaddCones", pyLSaddCones, METH_VARARGS},
    {"pyLSaddSETS", pyLSaddSETS, METH_VARARGS},
    {"pyLSaddQCterms", pyLSaddQCterms, METH_VARARGS},
    {"pyLSdeleteConstraints", pyLSdeleteConstraints, METH_VARARGS},
    {"pyLSdeleteCones", pyLSdeleteCones, METH_VARARGS},
    {"pyLSdeleteSETS", pyLSdeleteSETS, METH_VARARGS},
    {"pyLSdeleteSemiContVars", pyLSdeleteSemiContVars, METH_VARARGS},
    {"pyLSdeleteVariables", pyLSdeleteVariables, METH_VARARGS},
    {"pyLSdeleteQCterms", pyLSdeleteQCterms, METH_VARARGS},
    {"pyLSdeleteAj", pyLSdeleteAj, METH_VARARGS},
    {"pyLSmodifyLowerBounds", pyLSmodifyLowerBounds, METH_VARARGS},
    {"pyLSmodifyUpperBounds", pyLSmodifyUpperBounds, METH_VARARGS},
    {"pyLSmodifyRHS", pyLSmodifyRHS, METH_VARARGS},
    {"pyLSmodifyObjective", pyLSmodifyObjective, METH_VARARGS},
    {"pyLSmodifyObjConstant", pyLSmodifyObjConstant, METH_VARARGS},
    {"pyLSmodifyAj", pyLSmodifyAj, METH_VARARGS},
    {"pyLSmodifyCone", pyLSmodifyCone, METH_VARARGS},
    {"pyLSmodifySET", pyLSmodifySET, METH_VARARGS},
    {"pyLSmodifySemiContVars", pyLSmodifySemiContVars, METH_VARARGS},
    {"pyLSmodifyConstraintType", pyLSmodifyConstraintType, METH_VARARGS},
    {"pyLSmodifyVariableType", pyLSmodifyVariableType, METH_VARARGS},
    {"pyLSaddNLPAj", pyLSaddNLPAj, METH_VARARGS},
    {"pyLSaddNLPobj", pyLSaddNLPobj, METH_VARARGS},
    {"pyLSdeleteNLPobj", pyLSdeleteNLPobj, METH_VARARGS},
    {"pyLSgetConstraintRanges", pyLSgetConstraintRanges, METH_VARARGS},
    {"pyLSdeleteNLPobj", pyLSdeleteNLPobj, METH_VARARGS},
    {"pyLSgetBoundRanges", pyLSgetBoundRanges, METH_VARARGS},
    {"pyLSgetBestBounds", pyLSgetBoundRanges, METH_VARARGS},
    {"pyLSfindIIS", pyLSfindIIS, METH_VARARGS},
    {"pyLSfindIUS", pyLSfindIUS, METH_VARARGS},
    {"pyLSgetIIS", pyLSgetIIS, METH_VARARGS},
    {"pyLSgetBlockStructure", pyLSgetBlockStructure, METH_VARARGS},
    {"pyLSwriteDeteqMPSFile", pyLSwriteDeteqMPSFile, METH_VARARGS},
    {"pyLSwriteDeteqLINDOFile", pyLSwriteDeteqLINDOFile, METH_VARARGS},
    {"pyLSwriteSMPSFile", pyLSwriteSMPSFile, METH_VARARGS},
    {"pyLSreadSMPSFile", pyLSreadSMPSFile, METH_VARARGS},
    {"pyLSwriteSMPIFile", pyLSwriteSMPIFile, METH_VARARGS},
    {"pyLSreadSMPIFile", pyLSreadSMPIFile, METH_VARARGS},
    {"pyLSwriteScenarioSolutionFile", pyLSwriteScenarioSolutionFile, METH_VARARGS},
    {"pyLSwriteNodeSolutionFile", pyLSwriteNodeSolutionFile, METH_VARARGS},
    {"pyLSwriteScenarioMPIFile", pyLSwriteScenarioMPIFile, METH_VARARGS},
    {"pyLSwriteScenarioMPSFile", pyLSwriteScenarioMPSFile, METH_VARARGS},
    {"pyLSwriteScenarioLINDOFile", pyLSwriteScenarioLINDOFile, METH_VARARGS},
    {"pyLSgetModelStocDouParameter", pyLSgetModelStocDouParameter, METH_VARARGS},
    {"pyLSsetModelStocIntParameter", pyLSsetModelStocIntParameter, METH_VARARGS},
    {"pyLSgetModelStocIntParameter", pyLSgetModelStocIntParameter, METH_VARARGS},
    {"pyLSgetScenarioIndex", pyLSgetScenarioIndex, METH_VARARGS},
    {"pyLSgetStageIndex", pyLSgetStageIndex, METH_VARARGS},
    {"pyLSgetStocParIndex", pyLSgetStocParIndex, METH_VARARGS},
    {"pyLSgetStocParName", pyLSgetStocParName, METH_VARARGS},
    {"pyLSgetScenarioName", pyLSgetScenarioName, METH_VARARGS},
    {"pyLSgetStageName", pyLSgetStageName, METH_VARARGS},
    {"pyLSgetStocInfo", pyLSgetStocInfo, METH_VARARGS},
    {"pyLSgetStocCCPInfo", pyLSgetStocCCPInfo, METH_VARARGS},
    {"pyLSloadSampleSizes", pyLSloadSampleSizes, METH_VARARGS},
    {"pyLSloadConstraintStages", pyLSloadConstraintStages, METH_VARARGS},
    {"pyLSloadVariableStages", pyLSloadVariableStages, METH_VARARGS},
    {"pyLSloadStageData", pyLSloadStageData, METH_VARARGS},
    {"pyLSloadStocParData", pyLSloadStocParData, METH_VARARGS},
    {"pyLSgetDeteqModel", pyLSgetDeteqModel, METH_VARARGS},
    {"pyLSaggregateStages", pyLSaggregateStages, METH_VARARGS},
    {"pyLSgetStageAggScheme", pyLSgetStageAggScheme, METH_VARARGS},
    {"pyLSsolveSP", pyLSsolveSP, METH_VARARGS},
    {"pyLSsolveHS", pyLSsolveHS, METH_VARARGS},
    {"pyLSgetScenarioObjective", pyLSgetScenarioObjective, METH_VARARGS},
    {"pyLSgetNodePrimalSolution", pyLSgetNodePrimalSolution, METH_VARARGS},
    {"pyLSgetNodeDualSolution", pyLSgetNodeDualSolution, METH_VARARGS},
    {"pyLSgetNodeReducedCost", pyLSgetNodeReducedCost, METH_VARARGS},
    {"pyLSgetNodeSlacks", pyLSgetNodeSlacks, METH_VARARGS},
    {"pyLSgetScenarioPrimalSolution", pyLSgetScenarioPrimalSolution, METH_VARARGS},
    {"pyLSgetScenarioReducedCost", pyLSgetScenarioReducedCost, METH_VARARGS},
    {"pyLSgetScenarioDualSolution", pyLSgetScenarioDualSolution, METH_VARARGS},
    {"pyLSgetScenarioSlacks", pyLSgetScenarioSlacks, METH_VARARGS},
    {"pyLSgetNodeListByScenario", pyLSgetNodeListByScenario, METH_VARARGS},
    {"pyLSgetProbabilityByScenario", pyLSgetProbabilityByScenario, METH_VARARGS},
    {"pyLSgetProbabilityByNode", pyLSgetProbabilityByNode, METH_VARARGS},
    {"pyLSgetStocParData", pyLSgetStocParData, METH_VARARGS},
    {"pyLSaddDiscreteBlocks", pyLSaddDiscreteBlocks, METH_VARARGS},
    {"pyLSaddScenario", pyLSaddScenario, METH_VARARGS},
    {"pyLSaddDiscreteIndep", pyLSaddDiscreteIndep, METH_VARARGS},
    {"pyLSaddParamDistIndep", pyLSaddParamDistIndep, METH_VARARGS},
    {"pyLSaddChanceConstraint", pyLSaddChanceConstraint, METH_VARARGS},
    {"pyLSsetNumStages", pyLSsetNumStages, METH_VARARGS},
    {"pyLSgetStocParOutcomes", pyLSgetStocParOutcomes, METH_VARARGS},
    {"pyLSloadCorrelationMatrix", pyLSloadCorrelationMatrix, METH_VARARGS},
    {"pyLSgetCorrelationMatrix", pyLSgetCorrelationMatrix, METH_VARARGS},
    {"pyLSgetStocParSample", pyLSgetStocParSample, METH_VARARGS},
    {"pyLSgetDiscreteBlocks", pyLSgetDiscreteBlocks, METH_VARARGS},
    {"pyLSgetDiscreteBlockOutcomes", pyLSgetDiscreteBlockOutcomes, METH_VARARGS},
    {"pyLSgetDiscreteIndep", pyLSgetDiscreteIndep, METH_VARARGS},
    {"pyLSgetParamDistIndep", pyLSgetParamDistIndep, METH_VARARGS},
    {"pyLSgetScenario", pyLSgetScenario, METH_VARARGS},
    {"pyLSgetChanceConstraint", pyLSgetChanceConstraint, METH_VARARGS},
    {"pyLSgetSampleSizes", pyLSgetSampleSizes, METH_VARARGS},
    {"pyLSgetConstraintStages", pyLSgetConstraintStages, METH_VARARGS},
    {"pyLSgetVariableStages", pyLSgetVariableStages, METH_VARARGS},
    {"pyLSgetStocRowIndices", pyLSgetStocRowIndices, METH_VARARGS},
    {"pyLSsetStocParRG", pyLSsetStocParRG, METH_VARARGS},
    {"pyLSgetScenarioModel", pyLSgetScenarioModel, METH_VARARGS},
    {"pyLSfreeStocMemory", pyLSfreeStocMemory, METH_VARARGS},
    {"pyLSfreeStocHashMemory", pyLSfreeStocHashMemory, METH_VARARGS},
    {"pyLSgetModelStocParameter", pyLSgetModelStocParameter, METH_VARARGS},
    {"pyLSsetModelStocParameter", pyLSsetModelStocParameter, METH_VARARGS},
    {"pyLSsetEnvStocParameter", pyLSsetEnvStocParameter, METH_VARARGS},
    {"pyLSgetEnvStocParameter", pyLSgetEnvStocParameter, METH_VARARGS},
    {"pyLSsampCreate", pyLSsampCreate, METH_VARARGS},
    {"pyLSsampDelete", pyLSsampDelete, METH_VARARGS},
    {"pyLSsampSetDistrParam", pyLSsampSetDistrParam, METH_VARARGS},
    {"pyLSsampGetDistrParam", pyLSsampGetDistrParam, METH_VARARGS},
    {"pyLSsampEvalDistr", pyLSsampEvalDistr, METH_VARARGS},
    {"pyLSsampEvalDistrLI", pyLSsampEvalDistrLI, METH_VARARGS},
    {"pyLSsampEvalUserDistr", pyLSsampEvalUserDistr, METH_VARARGS},
    {"pyLSsampSetRG", pyLSsampSetRG, METH_VARARGS},
    {"pyLSsampGenerate", pyLSsampGenerate, METH_VARARGS},
    {"pyLSsampGetPoints", pyLSsampGetPoints, METH_VARARGS},
    {"pyLSsampLoadPoints", pyLSsampLoadPoints, METH_VARARGS},
    {"pyLSsampGetCIPoints", pyLSsampGetCIPoints, METH_VARARGS},
    {"pyLSsampLoadDiscretePdfTable", pyLSsampLoadDiscretePdfTable, METH_VARARGS},
    {"pyLSsampGetDiscretePdfTable", pyLSsampGetDiscretePdfTable, METH_VARARGS},
    {"pyLSsampGetInfo", pyLSsampGetInfo, METH_VARARGS},
    {"pyLSsampAddUserFuncArg", pyLSsampAddUserFuncArg, METH_VARARGS},
    {"pyLScreateRG", pyLScreateRG, METH_VARARGS},
    {"pyLScreateRGMT", pyLScreateRGMT, METH_VARARGS},
    {"pyLSgetDoubleRV", pyLSgetDoubleRV, METH_VARARGS},
    {"pyLSgetInt32RV", pyLSgetInt32RV, METH_VARARGS},
    {"pyLSsetRGSeed", pyLSsetRGSeed, METH_VARARGS},
    {"pyLSdisposeRG", pyLSdisposeRG, METH_VARARGS},
    {"pyLSsetDistrParamRG", pyLSsetDistrParamRG, METH_VARARGS},
    {"pyLSsetDistrRG", pyLSsetDistrRG, METH_VARARGS},
    {"pyLSgetDistrRV", pyLSgetDistrRV, METH_VARARGS},
    {"pyLSgetInitSeed", pyLSgetInitSeed, METH_VARARGS},
    {"pyLSgetRGNumThreads", pyLSgetRGNumThreads, METH_VARARGS},
    {"pyLSfillRGBuffer", pyLSfillRGBuffer, METH_VARARGS},
    {"pyLSgetHistogram", pyLSgetHistogram, METH_VARARGS},
    {"pyLSsolveMipBnp", pyLSsolveMipBnp, METH_VARARGS},

    { "pyLSwriteMPXFile", pyLSwriteMPXFile, METH_VARARGS },
    { "pyLSreadMPXFile", pyLSreadMPXFile, METH_VARARGS },
    { "pyLSwriteVarPriorities", pyLSwriteVarPriorities, METH_VARARGS },
    { "pyLSwriteNLSolution", pyLSwriteNLSolution, METH_VARARGS },
    { "pyLSaddTunerInstance", pyLSaddTunerInstance, METH_VARARGS },
    { "pyLSaddTunerOption", pyLSaddTunerOption, METH_VARARGS },
    { "pyLSaddTunerZDynamic", pyLSaddTunerZDynamic, METH_VARARGS },
    { "pyLSaddTunerZStatic", pyLSaddTunerZStatic, METH_VARARGS },
    { "pyLSclearTuner", pyLSclearTuner, METH_VARARGS },
    { "pyLSdisplayTunerResults", pyLSdisplayTunerResults, METH_VARARGS },
    { "pyLSgetTunerConfigString", pyLSgetTunerConfigString, METH_VARARGS },
    { "pyLSgetTunerOption", pyLSgetTunerOption, METH_VARARGS },
    { "pyLSgetTunerResult", pyLSgetTunerResult, METH_VARARGS },
    { "pyLSgetTunerSpace", pyLSgetTunerSpace, METH_VARARGS },
    { "pyLSgetTunerStrOption", pyLSgetTunerStrOption, METH_VARARGS },
    { "pyLSloadTunerConfigFile", pyLSloadTunerConfigFile, METH_VARARGS },
    { "pyLSloadTunerConfigString", pyLSloadTunerConfigString, METH_VARARGS },
    { "pyLSprintTuner", pyLSprintTuner, METH_VARARGS },
    { "pyLSresetTuner", pyLSresetTuner, METH_VARARGS },
    { "pyLSrunTuner", pyLSrunTuner, METH_VARARGS },
    { "pyLSrunTunerFile", pyLSrunTunerFile, METH_VARARGS },
    { "pyLSrunTunerString", pyLSrunTunerString, METH_VARARGS },
    { "pyLSsetTunerOption", pyLSsetTunerOption, METH_VARARGS },
    { "pyLSsetTunerStrOption", pyLSsetTunerStrOption, METH_VARARGS },
    { "pyLSaddQCShift", pyLSaddQCShift, METH_VARARGS },
    { "pyLSgetQCShift", pyLSgetQCShift, METH_VARARGS },
    { "pyLSresetQCShift", pyLSresetQCShift, METH_VARARGS },
    { "pyLSreadCBFFile", pyLSreadCBFFile, METH_VARARGS },
    { "pyLSreadNLFile", pyLSreadNLFile, METH_VARARGS },
    { "pyLSreadSDPAFile", pyLSreadSDPAFile, METH_VARARGS },
    { "pyLSsolveFileLP", pyLSsolveFileLP, METH_VARARGS },
    { "pyLSgetProfilerContext", pyLSgetProfilerContext, METH_VARARGS },
    { "pyLSgetProfilerInfo", pyLSgetProfilerInfo, METH_VARARGS },
    { "pyLSaddEmptySpacesAcolumns", pyLSaddEmptySpacesAcolumns, METH_VARARGS },
    { "pyLSaddEmptySpacesNLPAcolumns", pyLSaddEmptySpacesNLPAcolumns, METH_VARARGS },
    { "pyLSaddObjPool", pyLSaddObjPool, METH_VARARGS },
    { "pyLSapplyLtf", pyLSapplyLtf, METH_VARARGS },
    { "pyLSbnbSolve", pyLSbnbSolve, METH_VARARGS },
    { "pyLSbuildStringData", pyLSbuildStringData, METH_VARARGS },
    { "pyLScalcConFunc", pyLScalcConFunc, METH_VARARGS },
    { "pyLScalcConGrad", pyLScalcConGrad, METH_VARARGS },
    { "pyLScalcObjFunc", pyLScalcObjFunc, METH_VARARGS },
    { "pyLScalcObjGrad", pyLScalcObjGrad, METH_VARARGS },
    { "pyLScheckQterms", pyLScheckQterms, METH_VARARGS },
    { "pyLSdeduceStages", pyLSdeduceStages, METH_VARARGS },
    { "pyLSdeleteString", pyLSdeleteString, METH_VARARGS },
    { "pyLSdeleteStringData", pyLSdeleteStringData, METH_VARARGS },
    { "pyLSdisplayBlockStructure", pyLSdisplayBlockStructure, METH_VARARGS },
    { "pyLSdoBTRAN", pyLSdoBTRAN, METH_VARARGS },
    { "pyLSdoFTRAN", pyLSdoFTRAN, METH_VARARGS },
    { "pyLSfindLtf", pyLSfindLtf, METH_VARARGS },
    { "pyLSfindSymmetry", pyLSfindSymmetry, METH_VARARGS },
    { "pyLSfreeGOPSolutionMemory", pyLSfreeGOPSolutionMemory, METH_VARARGS },
    { "pyLSfreeHashMemory", pyLSfreeHashMemory, METH_VARARGS },
    { "pyLSfreeMIPSolutionMemory", pyLSfreeMIPSolutionMemory, METH_VARARGS },
    { "pyLSfreeObjPool", pyLSfreeObjPool, METH_VARARGS },
    { "pyLSfreeSolutionMemory", pyLSfreeSolutionMemory, METH_VARARGS },
    { "pyLSfreeSolverMemory", pyLSfreeSolverMemory, METH_VARARGS },
    { "pyLSgetALLDIFFData", pyLSgetALLDIFFData, METH_VARARGS },
    { "pyLSgetALLDIFFDatai", pyLSgetALLDIFFDatai, METH_VARARGS },
    { "pyLSgetDimensions", pyLSgetDimensions, METH_VARARGS },
    { "pyLSgetDualMIPsolution", pyLSgetDualMIPsolution, METH_VARARGS },
    { "pyLSgetGOPVariablePriority", pyLSgetGOPVariablePriority, METH_VARARGS },
    { "pyLSgetHess", pyLSgetHess, METH_VARARGS },
    { "pyLSgetIISInts", pyLSgetIISInts, METH_VARARGS },
    { "pyLSgetIISSETs", pyLSgetIISSETs, METH_VARARGS },
    { "pyLSgetJac", pyLSgetJac, METH_VARARGS },
    { "pyLSgetKBestMIPSols", pyLSgetKBestMIPSols, METH_VARARGS },
    { "pyLSgetLicenseInfo", pyLSgetLicenseInfo, METH_VARARGS },
    { "pyLSgetMasterModel", pyLSgetMasterModel, METH_VARARGS },
    { "pyLSgetMIPCallbackInfo", pyLSgetMIPCallbackInfo, METH_VARARGS },
    { "pyLSgetMIPSolutionStatus", pyLSgetMIPSolutionStatus, METH_VARARGS },
    { "pyLSgetMIPSolutionStatus", pyLSgetMIPSolutionStatus, METH_VARARGS },
    { "pyLSgetNextBestSol", pyLSgetNextBestSol, METH_VARARGS },
    { "pyLSgetNnzData", pyLSgetNnzData, METH_VARARGS },
    { "pyLSgetObjectiveRanges", pyLSgetObjectiveRanges, METH_VARARGS },
    { "pyLSgetObjPoolNumSol", pyLSgetObjPoolNumSol, METH_VARARGS },
    { "pyLSgetOrbitInfo", pyLSgetOrbitInfo, METH_VARARGS },
    { "pyLSgetPOSDData", pyLSgetPOSDData, METH_VARARGS },
    { "pyLSgetPOSDDatai", pyLSgetPOSDDatai, METH_VARARGS },
    { "pyLSgetMIPSolutionStatus", pyLSgetMIPSolutionStatus, METH_VARARGS },
    { "pyLSgetObjectiveRanges", pyLSgetObjectiveRanges, METH_VARARGS },
    { "pyLSgetProgressInfo", pyLSgetProgressInfo, METH_VARARGS },
    { "pyLSgetSolutionInfo", pyLSgetSolutionInfo, METH_VARARGS },
    { "pyLSgetSolutionStatus", pyLSgetSolutionStatus, METH_VARARGS },
    { "pyLSgetXSolverLibrary", pyLSgetXSolverLibrary, METH_VARARGS },
    { "pyLSloadALLDIFFData", pyLSloadALLDIFFData, METH_VARARGS },
    { "pyLSloadGASolution", pyLSloadGASolution, METH_VARARGS },
    { "pyLSloadIISPriorities", pyLSloadIISPriorities, METH_VARARGS },
    { "pyLSloadMultiStartSolution", pyLSloadMultiStartSolution, METH_VARARGS },
    { "pyLSloadNLPDense", pyLSloadNLPDense, METH_VARARGS },
    { "pyLSloadPOSDData", pyLSloadPOSDData, METH_VARARGS },
    { "pyLSloadSolutionAt", pyLSloadSolutionAt, METH_VARARGS },
    { "pyLSloadStringData", pyLSloadStringData, METH_VARARGS },
    { "pyLSloadStringData", pyLSloadStringData, METH_VARARGS },
    { "pyLSreadMPXStream", pyLSreadMPXStream, METH_VARARGS },
    { "pyLSsetObjPoolParam", pyLSsetObjPoolParam, METH_VARARGS },
    { "pyLSsetProbAllocSizes", pyLSsetProbAllocSizes, METH_VARARGS },
    { "pyLSsetProbNameAllocSizes", pyLSsetProbNameAllocSizes, METH_VARARGS },
    { "pyLSsetSETSStatei", pyLSsetSETSStatei, METH_VARARGS },
    { "pyLSsetXSolverLibrary", pyLSsetXSolverLibrary, METH_VARARGS },
    { "pyLSsetConstraintProperty", pyLSsetConstraintProperty, METH_VARARGS },
    { "pyLSregress", pyLSregress, METH_VARARGS },
    { "pyLSremObjPool", pyLSremObjPool, METH_VARARGS },
    { "pyLSgetObjectiveRanges", pyLSgetObjectiveRanges, METH_VARARGS },
    { "pyLSgetMIPSolutionStatus", pyLSgetMIPSolutionStatus, METH_VARARGS },
    { "pyLSgetMIPSolution", pyLSgetMIPSolution, METH_VARARGS },
    { "pyLSgetObjective", pyLSgetObjective, METH_VARARGS },
    { "pyLSsetGOPVariablePriority", pyLSsetGOPVariablePriority, METH_VARARGS },
    { "pyLSgetStringValue", pyLSgetStringValue, METH_VARARGS },
    { "pyLSrepairQterms", pyLSrepairQterms, METH_VARARGS },
    { "pyLSsetMIPCCStrategy", pyLSsetMIPCCStrategy, METH_VARARGS },
    { "pyLSsetModelLogfunc", pyLSsetModelLogfunc, METH_VARARGS },
    { "pyLSsetEnvLogfunc", pyLSsetEnvLogfunc, METH_VARARGS },
    { "pyLSsetCallback", pyLSsetCallback, METH_VARARGS },
    { "pyLSsetMIPCallback", pyLSsetMIPCallback, METH_VARARGS },
    { "pyLSsetFuncalc", pyLSsetFuncalc, METH_VARARGS },
    { "pyLSsetGradcalc", pyLSsetGradcalc, METH_VARARGS },
    { "pyLSwriteTunerParameters", pyLSwriteTunerParameters, METH_VARARGS },
#ifdef _DEBUG
#include "pyLindo_defn.h"
#endif
    {NULL, NULL, 0}
};

#if PY_MAJOR_VERSION >= 3

static int lindo_traverse(PyObject *m, visitproc visit, void *arg)
{
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int lindo_clear(PyObject *m)
{
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef =
{
        PyModuleDef_HEAD_INIT,
        "lindo",
        NULL,
        sizeof(struct module_state),
        lindo_methods,
        NULL,
        lindo_traverse,
        lindo_clear,
        NULL
};

#define INITERROR return NULL

PyObject *PyInit_lindo(void)

#else
#define INITERROR return

void
initlindo(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("lindo", lindo_methods);
#endif

    import_array();  // to initialize NumPy

    if (module == NULL)
    {
        INITERROR;
    }

    {
        struct module_state *st = GETSTATE(module);

        st->error = PyErr_NewException("lindo.Error", NULL, NULL);
        if (st->error == NULL)
        {
            Py_DECREF(module);
            INITERROR;
        }
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}

#define PyCreatObj(dim,type,pyobj,array) \
dimension[0] = dim;\
pyobj = (PyArrayObject *)PyArray_SimpleNewFromData(1,dimension,type,(void *)(array));\
pyobj->flags |= NPY_OWNDATA;\

#if PY_MAJOR_VERSION < 3
    #define PyNewObjPtr(pointer_to_value)\
    PyCObject_FromVoidPtr ((void *)pointer_to_value, NULL)
#else
    #define PyNewObjPtr(pointer_to_value)\
    PyCapsule_New((void *)pointer_to_value, NULL, NULL)
#endif

#if PY_MAJOR_VERSION < 3
    #define PyGetObjPtr(pointer_to_value)\
    PyCObject_AsVoidPtr(pointer_to_value)
#else
    #define PyGetObjPtr(pointer_to_value)\
    PyCapsule_GetPointer(pointer_to_value, NULL)
#endif

#define CHECK_ENV\
    pEnv = PyGetObjPtr(pyEnv);\
    if(pEnv == NULL)\
    {\
        errorcode = LSERR_ILLEGAL_NULL_POINTER;\
        printf("Illegal NULL pointer (error %d)\n",errorcode);\
        return Py_BuildValue("i",errorcode);\
    }\

#define CHECK_MODEL\
    pModel = PyGetObjPtr(pyModel);\
    if(pModel == NULL)\
    {\
        errorcode = LSERR_ILLEGAL_NULL_POINTER;\
        printf("Illegal NULL pointer (error %d)\n",errorcode);\
        return Py_BuildValue("i",errorcode);\
    }\

#define CHECK_OBJ_NO_FAIL(pObj,pyObj)\
    pObj = PyGetObjPtr(pyObj);\

#define CHECK_RG\
    pRG = PyGetObjPtr(pyRG);\
    if(pRG == NULL)\
    {\
        errorcode = LSERR_ILLEGAL_NULL_POINTER;\
        printf("Illegal NULL pointer (error %d)\n",errorcode);\
        return Py_BuildValue("i",errorcode);\
    }\

#define CHECK_SAMPLE\
    pSample = PyGetObjPtr(pySample);\
    if(pSample == NULL)\
    {\
        errorcode = LSERR_ILLEGAL_NULL_POINTER;\
        printf("Illegal NULL pointer (error %d)\n",errorcode);\
        return Py_BuildValue("i",errorcode);\
    }\

static void LS_CALLTYPE pyPrintLog(pLSmodel model,
                                   char     *line,
                                   void     *notting)
{
    printf("%s",line);
}
/*********************************************************************
 * Structure Creation and Deletion Routines (6)                      *
 *********************************************************************/
PyObject *pyLScreateEnv(PyObject *self, PyObject *args)
{
    pLSenv    pEnv = NULL;
    int       *pnErrorCode = NULL;
    char      *pachLicenseKey = NULL;
    npy_intp  index[1] = {0};

    PyArrayObject   *pyErrorCode = NULL, *pyLicenseKey = NULL;

    if (!PyArg_ParseTuple(args, "O!O!",
                                 &PyArray_Type,&pyErrorCode,
                                 &PyArray_Type,&pyLicenseKey))
    {
        return NULL;
    }

    if(pyErrorCode && pyErrorCode->dimensions > 0)
        pnErrorCode = (int *)PyArray_GetPtr(pyErrorCode,index);

    if(pyLicenseKey)
        pachLicenseKey = (char *)pyLicenseKey->data;

    pEnv = LScreateEnv(pnErrorCode,pachLicenseKey);

    if(*pnErrorCode)
    {
        printf("Failed to load license key (error %d)\n",*pnErrorCode);
        return NULL;
    }

    return PyNewObjPtr(pEnv);
}

PyObject *pyLScreateModel(PyObject *self, PyObject *args)
{
    pLSmodel  pModel = NULL;
    pLSenv    pEnv;
    int       *pnErrorCode = NULL;
    npy_intp  index[1] = {0};

    PyObject        *pyEnv;
    PyArrayObject   *pyErrorCode = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyEnv,
                                 &PyArray_Type,&pyErrorCode))
    {
        return NULL;
    }

    if(pyErrorCode && pyErrorCode->dimensions > 0)
        pnErrorCode = (int *)PyArray_GetPtr(pyErrorCode,index);

    pEnv = PyGetObjPtr(pyEnv);
    if(pEnv == NULL)
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",*pnErrorCode);
        return NULL;
    };

    pModel = LScreateModel(pEnv,pnErrorCode);

    if(*pnErrorCode)
    {
        printf("Failed to create model (error %d)\n",*pnErrorCode);
        return NULL;
    }

    *pnErrorCode = LSsetModelLogfunc(pModel,(printLOG_t)pyPrintLog,NULL);
    if(*pnErrorCode)
    {
        printf("Failed to set print log (error %d)\n",*pnErrorCode);
        return NULL;
    }

    return PyNewObjPtr(pModel);
}

PyObject *pyLSdeleteModel(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;

    PyObject  *pyModel;

    if (!PyArg_ParseTuple(args, "O", &pyModel))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSdeleteModel(&pModel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteEnv(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;

    PyObject  *pyEnv;

    if (!PyArg_ParseTuple(args, "O", &pyEnv))
    {
        return NULL;
    }

    CHECK_ENV;

    errorcode = LSdeleteEnv(&pEnv);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLScopyParam(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  targetModel, sourceModel;
    int       mSolverType;

    PyObject  *pytargetModel, *pysourceModel;

    if (!PyArg_ParseTuple(args, "OOi",
                                 &pysourceModel,
                                 &pytargetModel,
                                 &mSolverType))
    {
        return NULL;
    }

    sourceModel = PyGetObjPtr(pysourceModel);
    targetModel = PyGetObjPtr(pytargetModel);
    if(sourceModel == NULL || targetModel == NULL)
    {
        errorcode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",errorcode);
        return NULL;
    };

    errorcode = LScopyParam(sourceModel,targetModel,mSolverType);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadLicenseString(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    char      *pszFname;
    char      *pachLicenseKey = NULL;
    npy_intp  index[1] = {0};

    PyArrayObject   *pyLicenseKey = NULL;

    if (!PyArg_ParseTuple(args, "sO!",
                                 &pszFname,
                                 &PyArray_Type,&pyLicenseKey))
    {
        return NULL;
    }

    if(pyLicenseKey)
        pachLicenseKey = (char *)PyArray_GetPtr(pyLicenseKey,index);

    errorcode = LSloadLicenseString(pszFname,pachLicenseKey);

    return Py_BuildValue("i",errorcode);
}


/********************************************************
 * Model I-O Routines (18)                              *
 ********************************************************/
PyObject *pyLSreadMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;
    int       nFormat;

    PyObject       *pyModel;


    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadMPSFile(pModel,pszFname,nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nFormat;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteMPSFile(pModel,pszFname,nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadLINDOFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadLINDOFile(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteLINDOFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteLINDOFile(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadLINDOStream(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nStreamLen;
    char      *pszStream;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszStream,
                                 &nStreamLen))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadLINDOStream(pModel,pszStream,nStreamLen);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteLINGOFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteLINGOFile(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteDualMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nFormat,nObjSense;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osii",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat,
                                 &nObjSense))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteDualMPSFile(pModel,pszFname,nFormat,nObjSense);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteSolution(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteSolutionOfType(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nFormat;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteSolutionOfType(pModel,pszFname,nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteIIS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteIIS(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteIUS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteIUS(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadMPIFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadMPIFile(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteMPIFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteMPIFile(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteWithSetsAndSC(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nFormat;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteWithSetsAndSC(pModel,pszFname,nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadBasis(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nFormat;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadBasis(pModel,pszFname,nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteBasis(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nFormat;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteBasis(pModel,pszFname,nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadLPFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadLPFile(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadLPStream(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nStreamLen;
    char      *pszStream;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszStream,
                                 &nStreamLen))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadLPStream(pModel,pszStream,nStreamLen);

    return Py_BuildValue("i",errorcode);
}

/********************************************************
 * Error Handling Routines (3)                          *
 ********************************************************/
PyObject *pyLSgetErrorMessage(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    char      *pachMessage = NULL;
    int       nErrorCode;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyMessage = NULL;

    if (!PyArg_ParseTuple(args, "OiO",
                                 &pyEnv,
                                 &nErrorCode,
                                 &pyMessage))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyMessage)
        pachMessage = (char *)PyArray_GetPtr(pyMessage,index);

    errorcode = LSgetErrorMessage(pEnv,nErrorCode,pachMessage);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVersionInfo(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    char      *ver_num = NULL, *build_date=NULL;
    npy_intp  index[1] = {0};

    PyArrayObject  *pyver_num = NULL;
    PyArrayObject  *pybuild_date = NULL;

    if (!PyArg_ParseTuple(args, "OO",
                                 &pyver_num,
                                 &pybuild_date))
    {
        return NULL;
    }

    if(pyver_num)
        ver_num = (char *)PyArray_GetPtr(pyver_num,index);

    if(pybuild_date)
        build_date = (char *)PyArray_GetPtr(pybuild_date,index);

    LSgetVersionInfo(ver_num,build_date);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetFileError(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pachLinetxt = NULL;
    int       *pnLinenum = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyLinetxt = NULL;
    PyArrayObject  *pyLinenum = NULL;

    if (!PyArg_ParseTuple(args, "OOO",
                                 &pyModel,
                                 &pyLinenum,
                                 &pyLinetxt))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyLinenum && pyLinenum->dimensions > 0)
        pnLinenum = (int *)PyArray_GetPtr(pyLinenum,index);
    if(pyLinetxt)
        pachLinetxt = (char *)PyArray_GetPtr(pyLinetxt,index);

    errorcode = LSgetFileError(pModel,pnLinenum,pachLinetxt);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetErrorRowIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *piRow = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyRow = NULL;

    if (!PyArg_ParseTuple(args, "OO",
                                 &pyModel,
                                 &pyRow))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRow && pyRow->dimensions > 0)
        piRow = (int *)PyArray_GetPtr(pyRow,index);

    errorcode = LSgetErrorRowIndex(pModel,piRow);

    return Py_BuildValue("i",errorcode);
}

/***********************************************************
 * Routines for Setting and Retrieving Parameter Values(21)*
 ***********************************************************/
PyObject *pyLSsetModelParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    void      *pvValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        pvValue = (void *)PyArray_GetPtr(pyValue,index);

    errorcode = LSsetModelParameter(pModel,nParameter,pvValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetModelParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    void      *pvValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        pvValue = (void *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetModelParameter(pModel,nParameter,pvValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetEnvParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    void      *pvValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyValue && pyValue->dimensions > 0)
        pvValue = (void *)PyArray_GetPtr(pyValue,index);

    errorcode = LSsetEnvParameter(pEnv,nParameter,pvValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetEnvParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    void      *pvValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyValue && pyValue->dimensions > 0)
        pvValue = (void *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetEnvParameter(pEnv,nParameter,pvValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetModelDouParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    double    dValue;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oid",
                                 &pyModel,
                                 &nParameter,
                                 &dValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSsetModelDouParameter(pModel,nParameter,dValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetModelDouParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    double    *pdValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        pdValue = (double *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetModelDouParameter(pModel,nParameter,pdValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetModelIntParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    int       nValue;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oii",
                                 &pyModel,
                                 &nParameter,
                                 &nValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSsetModelIntParameter(pModel,nParameter,nValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetModelIntParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    int       *pnValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        pnValue = (int *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetModelIntParameter(pModel,nParameter,pnValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetEnvDouParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    double    dValue;

    PyObject       *pyEnv;

    if (!PyArg_ParseTuple(args, "Oid",
                                 &pyEnv,
                                 &nParameter,
                                 &dValue))
    {
        return NULL;
    }

    CHECK_ENV;

    errorcode = LSsetEnvDouParameter(pEnv,nParameter,dValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetEnvDouParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    double    *pdValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyValue && pyValue->dimensions > 0)
        pdValue = (double *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetEnvDouParameter(pEnv,nParameter,pdValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetEnvIntParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    int       nValue;

    PyObject       *pyEnv;

    if (!PyArg_ParseTuple(args, "Oii",
                                 &pyEnv,
                                 &nParameter,
                                 &nValue))
    {
        return NULL;
    }

    CHECK_ENV;

    errorcode = LSsetEnvIntParameter(pEnv,nParameter,nValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetEnvIntParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    int       *pnValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyValue && pyValue->dimensions > 0)
        pnValue = (int *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetEnvIntParameter(pEnv,nParameter,pnValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadModelParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname = NULL;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadModelParameter(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadEnvParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    char      *pszFname = NULL;

    PyObject       *pyEnv;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyEnv,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_ENV;

    errorcode = LSreadEnvParameter(pEnv,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteModelParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname = NULL;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteModelParameter(pModel,pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetIntParameterRange(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    int       *pnValMIN = NULL;
    int       *pnValMAX = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValMIN = NULL;
    PyArrayObject  *pyValMAX = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nParameter,
                                 &PyArray_Type,&pyValMIN,
                                 &PyArray_Type,&pyValMAX))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValMIN && pyValMIN->dimensions > 0)
        pnValMIN = (int *)PyArray_GetPtr(pyValMIN,index);
    if(pyValMAX && pyValMAX->dimensions > 0)
        pnValMAX = (int *)PyArray_GetPtr(pyValMAX,index);

    errorcode = LSgetIntParameterRange(pModel,nParameter,pnValMIN,pnValMAX);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDouParameterRange(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nParameter;
    double    *pdValMIN = NULL;
    double    *pdValMAX = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValMIN = NULL;
    PyArrayObject  *pyValMAX = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nParameter,
                                 &PyArray_Type,&pyValMIN,
                                 &PyArray_Type,&pyValMAX))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValMIN && pyValMIN->dimensions > 0)
        pdValMIN = (double *)PyArray_GetPtr(pyValMIN,index);
    if(pyValMAX && pyValMAX->dimensions > 0)
        pdValMAX = (double *)PyArray_GetPtr(pyValMAX,index);

    errorcode = LSgetDouParameterRange(pModel,nParameter,pdValMIN,pdValMAX);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetParamShortDesc(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParam;
    char      *szDescription = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyDescription = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParam,
                                 &PyArray_Type,&pyDescription))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyDescription)
        szDescription = (char *)PyArray_GetPtr(pyDescription,index);

    errorcode = LSgetParamShortDesc(pEnv,nParam,szDescription);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetParamLongDesc(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParam;
    char      *szDescription = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyDescription = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParam,
                                 &PyArray_Type,&pyDescription))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyDescription)
        szDescription = (char *)PyArray_GetPtr(pyDescription,index);

    errorcode = LSgetParamLongDesc(pEnv,nParam,szDescription);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetParamMacroName(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParam;
    char      *szParam = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyParam = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParam,
                                 &PyArray_Type,&pyParam))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyParam)
        szParam = (char *)PyArray_GetPtr(pyParam,index);

    errorcode = LSgetParamMacroName(pEnv,nParam,szParam);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetParamMacroID(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    char      *szParam = NULL;
    int       *pnParamType = NULL;
    int       *pnParam = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyParamType = NULL;
    PyArrayObject  *pyParam = NULL;

    if (!PyArg_ParseTuple(args, "OsO!O!",
                                 &pyEnv,
                                 &szParam,
                                 &PyArray_Type,&pyParamType,
                                 &PyArray_Type,&pyParam))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyParamType && pyParamType->dimensions > 0)
        pnParamType = (int *)PyArray_GetPtr(pyParamType,index);
    if(pyParam && pyParam->dimensions > 0)
        pnParam = (int *)PyArray_GetPtr(pyParam,index);

    errorcode = LSgetParamMacroID(pEnv,szParam,pnParamType,pnParam);

    return Py_BuildValue("i",errorcode);
}

/********************************************************
* Model Loading Routines (10)                           *
*********************************************************/
PyObject *pyLSloadLPData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons, nVars, nObjSense, nAnnz;
    double    dObjConst;
    double    *padC = NULL, *padB = NULL;
    char      *pszConTypes = NULL;
    int       *paiAcols = NULL, *panAcols = NULL;
    double    *padAcoef = NULL;
    int       *paiArows = NULL;
    double    *padL = NULL, *padU = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyC = NULL,*pyB = NULL;
    PyArrayObject  *pyConTypes = NULL, *pyiAcols = NULL;
    PyArrayObject  *pynAcols = NULL,*pyAcoef = NULL;
    PyArrayObject  *pyArows = NULL, *pyL = NULL, *pyU = NULL;

    if (!PyArg_ParseTuple(args, "OiiidO!O!O!iO!O!O!O!O!O!",
                                 &pyModel,
                                 &nCons,
                                 &nVars,
                                 &nObjSense,
                                 &dObjConst,
                                 &PyArray_Type,&pyC,
                                 &PyArray_Type,&pyB,
                                 &PyArray_Type,&pyConTypes,
                                 &nAnnz,
                                 &PyArray_Type,&pyiAcols,
                                 &PyArray_Type,&pynAcols,
                                 &PyArray_Type,&pyAcoef,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyC && pyC->dimensions > 0)
        padC = (double *)pyC->data;
    if(pyB && pyB->dimensions > 0)
        padB = (double *)pyB->data;
    if(pyConTypes && pyConTypes->dimensions > 0)
        pszConTypes = (char *)pyConTypes->data;
    if(pyiAcols && pyiAcols->dimensions > 0)
        paiAcols = (int *)pyiAcols->data;
    if(pynAcols && pynAcols->dimensions > 0)
        panAcols = (int *)pynAcols->data;
    if(pyAcoef && pyAcoef->dimensions > 0)
        padAcoef = (double *)pyAcoef->data;
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)pyArows->data;
    if(pyL && pyL->dimensions > 0)
        padL = (double *)pyL->data;
    if(pyU && pyU->dimensions > 0)
        padU = (double *)pyU->data;

    errorcode = LSloadLPData(pModel,
                             nCons,
                             nVars,
                             nObjSense,
                             dObjConst,
                             padC,
                             padB,
                             pszConTypes,
                             nAnnz,
                             paiAcols,
                             panAcols,
                             padAcoef,
                             paiArows,
                             padL,
                             padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadQCData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nQCnnz;
    int       *paiQCrows = NULL,*paiQCcols1 = NULL,*paiQCcols2 = NULL;
    double    *padQCcoef = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyQCrows = NULL, *pyQCcols = NULL;
    PyArrayObject  *pyQCcols2 = NULL, *pyQCcoef = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &nQCnnz,
                                 &PyArray_Type,&pyQCrows,
                                 &PyArray_Type,&pyQCcols,
                                 &PyArray_Type,&pyQCcols2,
                                 &PyArray_Type,&pyQCcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

     if(pyQCrows && pyQCrows->dimensions > 0)
        paiQCrows = (int *)pyQCrows->data;
     if(pyQCcols && pyQCcols->dimensions > 0)
        paiQCcols1 = (int *)pyQCcols->data;
     if(pyQCcols2 && pyQCcols2->dimensions > 0)
        paiQCcols2 = (int *)pyQCcols2->data;
     if(pyQCcoef && pyQCcoef->dimensions > 0)
        padQCcoef = (double *)pyQCcoef->data;

    errorcode = LSloadQCData(pModel,
                             nQCnnz,
                             paiQCrows,
                             paiQCcols1,
                             paiQCcols2,
                             padQCcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadConeData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCone;
    char      *pszConeTypes = NULL;
    int       *paiConebegcone = NULL,*paiConecols = NULL;
	double   *padConeAlpha = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyConeTypes = NULL, *pyConebegcone = NULL;
    PyArrayObject  *pyConecols = NULL;
	PyArrayObject  *pyadConeAlpha;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &nCone,
                                 &PyArray_Type,&pyConeTypes,
								 &PyArray_Type,&pyadConeAlpha,
                                 &PyArray_Type,&pyConebegcone,
                                 &PyArray_Type,&pyConecols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConeTypes && pyConeTypes->dimensions > 0)
        pszConeTypes = (char *)pyConeTypes->data;
    if(pyConebegcone && pyConebegcone->dimensions > 0)
        paiConebegcone = (int *)pyConebegcone->data;
    if(pyConecols && pyConecols->dimensions > 0)
        paiConecols = (int *)pyConecols->data;
    if(pyadConeAlpha && pyadConeAlpha->dimensions > 0)
        padConeAlpha = (double *)pyadConeAlpha->data;
    errorcode = LSloadConeData(pModel,
                               nCone,
                               pszConeTypes,
                               padConeAlpha,
                               paiConebegcone,
                               paiConecols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadSETSData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSETS;
    char      *pszSETStype = NULL;
    int       *paiCARDnum = NULL, *paiSETSbegcol = NULL, *paiSETScols = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pySETStype = NULL, *pyCARDnum = NULL;
    PyArrayObject  *pySETSbegcol = NULL, *pySETScols = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &nSETS,
                                 &PyArray_Type,&pySETStype,
                                 &PyArray_Type,&pyCARDnum,
                                 &PyArray_Type,&pySETSbegcol,
                                 &PyArray_Type,&pySETScols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySETStype && pySETStype->dimensions > 0)
        pszSETStype = (char *)pySETStype->data;
    if(pyCARDnum && pyCARDnum->dimensions > 0)
        paiCARDnum = (int *)pyCARDnum->data;
    if(pySETSbegcol && pySETSbegcol->dimensions > 0)
        paiSETSbegcol = (int *)pySETSbegcol->data;
    if(pySETScols && pySETScols->dimensions > 0)
        paiSETScols = (int *)pySETScols->data;

    errorcode = LSloadSETSData(pModel,
                               nSETS,
                               pszSETStype,
                               paiCARDnum,
                               paiSETSbegcol,
                               paiSETScols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadSemiContData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSCVars;
    int       *paiVars = NULL;
    double    *padL = NULL, *padU = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVars = NULL, *pyL = NULL, *pyU = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &nSCVars,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVars && pyVars->dimensions > 0)
        paiVars = (int *)pyVars->data;
    if(pyL && pyL->dimensions > 0)
        padL = (double *)pyL->data;
    if(pyU && pyU->dimensions > 0)
        padU = (double *)pyU->data;

    errorcode = LSloadSemiContData(pModel,
                                   nSCVars,
                                   paiVars,
                                   padL,
                                   padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadVarType(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszVarTypes = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVarTypes = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyVarTypes))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVarTypes && pyVarTypes->dimensions > 0)
        pszVarTypes = (char *)pyVarTypes->data;

    errorcode = LSloadVarType(pModel,
                              pszVarTypes);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadNLPData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nNLPobj;
    int       *paiNLPcols = NULL,*panNLPcols = NULL;
    double    *padNLPcoef = NULL;
    int       *paiNLProws = NULL,*paiNLPobj = NULL;
    double    *padNLPobj = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyiNLPcols,*pynNLPcols,*pyNLPcoef,*pyNLProws;
    PyArrayObject  *pyiNLPobj,*pydNLPobj;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!iO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyiNLPcols,
                                 &PyArray_Type,&pynNLPcols,
                                 &PyArray_Type,&pyNLPcoef,
                                 &PyArray_Type,&pyNLProws,
                                 &nNLPobj,
                                 &PyArray_Type,&pyiNLPobj,
                                 &PyArray_Type,&pydNLPobj))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyiNLPcols && pyiNLPcols->dimensions > 0)
        paiNLPcols = (int *)pyiNLPcols->data;
    if(pynNLPcols && pynNLPcols->dimensions > 0)
        panNLPcols = (int *)pynNLPcols->data;
    if(pyNLPcoef && pyNLPcoef->dimensions > 0)
        padNLPcoef = (double *)pyNLPcoef->data;
    if(pyNLProws && pyNLProws->dimensions > 0)
        paiNLProws = (int *)pyNLProws->data;
    if(pyiNLPobj && pyiNLPobj->dimensions > 0)
        paiNLPobj = (int *)pyiNLPobj->data;
    if(pydNLPobj && pydNLPobj->dimensions > 0)
        padNLPobj = (double *)pydNLPobj->data;

    errorcode = LSloadNLPData(pModel,
                              paiNLPcols,
                              panNLPcols,
                              padNLPcoef,
                              paiNLProws,
                              nNLPobj,
                              paiNLPobj,
                              padNLPobj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadInstruct(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons,nObjs,nVars,nNumbers,nInstruct;
    int       *panObjSense = NULL;
    char      *pszConType = NULL, *pszVarType = NULL;
    int       *panInstruct = NULL, *paiVars =NULL;
    double    *padNumVal = NULL,*padVarVal = NULL;
    int       *paiObjBeg = NULL, *panObjLen =NULL;
    int       *paiConBeg = NULL, *panConLen =NULL;
    double    *padLB = NULL,*padUB = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyObjSense =NULL,*pyConType =NULL;
    PyArrayObject  *pyVarType =NULL,*pyInstruct =NULL;
    PyArrayObject  *pyVars =NULL,*pyNumVal =NULL;
    PyArrayObject  *pyVarVal =NULL,*pyObjBeg =NULL;
    PyArrayObject  *pyObjLen =NULL,*pyConBeg =NULL;
    PyArrayObject  *pyConLen =NULL,*pyLB =NULL,*pyUB =NULL;

    if (!PyArg_ParseTuple(args, "OiiiiO!O!O!O!iO!O!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &nCons,
                                 &nObjs,
                                 &nVars,
                                 &nNumbers,
                                 &PyArray_Type,&pyObjSense,
                                 &PyArray_Type,&pyConType,
                                 &PyArray_Type,&pyVarType,
                                 &PyArray_Type,&pyInstruct,
                                 &nInstruct,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyNumVal,
                                 &PyArray_Type,&pyVarVal,
                                 &PyArray_Type,&pyObjBeg,
                                 &PyArray_Type,&pyObjLen,
                                 &PyArray_Type,&pyConBeg,
                                 &PyArray_Type,&pyConLen,
                                 &PyArray_Type,&pyLB,
                                 &PyArray_Type,&pyUB))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyObjSense && pyObjSense->dimensions > 0)
        panObjSense = (int *)pyObjSense->data;
    if(pyConType && pyConType->dimensions > 0)
        pszConType = (char *)pyConType->data;
    if(pyVarType && pyVarType->dimensions > 0)
        pszVarType = (char *)pyVarType->data;
    if(pyInstruct && pyInstruct->dimensions > 0)
        panInstruct = (int *)pyInstruct->data;
    if(pyVars && pyVars->dimensions > 0)
        paiVars = (int *)pyVars->data;
    if(pyNumVal && pyNumVal->dimensions > 0)
        padNumVal = (double *)pyNumVal->data;
    if(pyVarVal && pyVarVal->dimensions > 0)
        padVarVal = (double *)pyVarVal->data;
    if(pyObjBeg && pyObjBeg->dimensions > 0)
        paiObjBeg = (int *)pyObjBeg->data;
    if(pyObjLen && pyObjLen->dimensions > 0)
        panObjLen = (int *)pyObjLen->data;
    if(pyConBeg && pyConBeg->dimensions > 0)
        paiConBeg = (int *)pyConBeg->data;
    if(pyConLen && pyConLen->dimensions > 0)
        panConLen = (int *)pyConLen->data;
    if(pyLB && pyLB->dimensions > 0)
        padLB = (double *)pyLB->data;
    if(pyUB && pyUB->dimensions > 0)
        padUB = (double *)pyUB->data;

    errorcode = LSloadInstruct(pModel,
                               nCons,
                               nObjs,
                               nVars,
                               nNumbers,
                               panObjSense,
                               pszConType,
                               pszVarType,
                               panInstruct,
                               nInstruct,
                               paiVars,
                               padNumVal,
                               padVarVal,
                               paiObjBeg,
                               panObjLen,
                               paiConBeg,
                               panConLen,
                               padLB,
                               padUB);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddInstruct(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons,nObjs,nVars,nNumbers,nInstruct;
    int       *panObjSense = NULL;
    char      *pszConType = NULL, *pszVarType = NULL;
    int       *panInstruct = NULL, *paiCons =NULL;
    double    *padNumVal = NULL,*padVarVal = NULL;
    int       *paiObjBeg = NULL, *panObjLen =NULL;
    int       *paiConBeg = NULL, *panConLen =NULL;
    double    *padLB = NULL,*padUB = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyObjSense =NULL,*pyConType =NULL;
    PyArrayObject  *pyVarType =NULL,*pyInstruct =NULL;
    PyArrayObject  *pyCons =NULL,*pyNumVal =NULL;
    PyArrayObject  *pyVarVal =NULL,*pyObjBeg =NULL;
    PyArrayObject  *pyObjLen =NULL,*pyConBeg =NULL;
    PyArrayObject  *pyConLen =NULL,*pyLB =NULL,*pyUB =NULL;

    if (!PyArg_ParseTuple(args, "OiiiiO!O!O!O!iO!O!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &nCons,
                                 &nObjs,
                                 &nVars,
                                 &nNumbers,
                                 &PyArray_Type,&pyObjSense,
                                 &PyArray_Type,&pyConType,
                                 &PyArray_Type,&pyVarType,
                                 &PyArray_Type,&pyInstruct,
                                 &nInstruct,
                                 &PyArray_Type,&pyCons,
                                 &PyArray_Type,&pyNumVal,
                                 &PyArray_Type,&pyVarVal,
                                 &PyArray_Type,&pyObjBeg,
                                 &PyArray_Type,&pyObjLen,
                                 &PyArray_Type,&pyConBeg,
                                 &PyArray_Type,&pyConLen,
                                 &PyArray_Type,&pyLB,
                                 &PyArray_Type,&pyUB))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyObjSense && pyObjSense->dimensions > 0)
        panObjSense = (int *)pyObjSense->data;
    if(pyConType && pyConType->dimensions > 0)
        pszConType = (char *)pyConType->data;
    if(pyVarType && pyVarType->dimensions > 0)
        pszVarType = (char *)pyVarType->data;
    if(pyInstruct && pyInstruct->dimensions > 0)
        panInstruct = (int *)pyInstruct->data;
    if(pyCons && pyCons->dimensions > 0)
        paiCons = (int *)pyCons->data;
    if(pyNumVal && pyNumVal->dimensions > 0)
        padNumVal = (double *)pyNumVal->data;
    if(pyVarVal && pyVarVal->dimensions > 0)
        padVarVal = (double *)pyVarVal->data;
    if(pyObjBeg && pyObjBeg->dimensions > 0)
        paiObjBeg = (int *)pyObjBeg->data;
    if(pyObjLen && pyObjLen->dimensions > 0)
        panObjLen = (int *)pyObjLen->data;
    if(pyConBeg && pyConBeg->dimensions > 0)
        paiConBeg = (int *)pyConBeg->data;
    if(pyConLen && pyConLen->dimensions > 0)
        panConLen = (int *)pyConLen->data;
    if(pyLB && pyLB->dimensions > 0)
        padLB = (double *)pyLB->data;
    if(pyUB && pyUB->dimensions > 0)
        padUB = (double *)pyUB->data;

    errorcode = LSaddInstruct(pModel,
                              nCons,
                              nObjs,
                              nVars,
                              nNumbers,
                              panObjSense,
                              pszConType,
                              pszVarType,
                              panInstruct,
                              nInstruct,
                              paiCons,
                              padNumVal,
                              padVarVal,
                              paiObjBeg,
                              panObjLen,
                              paiConBeg,
                              panConLen,
                              padLB,
                              padUB);

    return Py_BuildValue("i",errorcode);
}
/**********************************************************************
 * Solver Initialization Routines (9)                                 *
 **********************************************************************/
PyObject *pyLSloadBasis(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panCstatus = NULL, *panRstatus = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCstatus = NULL,*pyRstatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyCstatus,
                                 &PyArray_Type,&pyRstatus))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCstatus && pyCstatus->dimensions > 0)
        panCstatus = (int *)pyCstatus->data;
    if(pyRstatus && pyRstatus->dimensions > 0)
        panRstatus = (int *)pyRstatus->data;

    errorcode = LSloadBasis(pModel,
                            panCstatus,
                            panRstatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadVarPriorities(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panCprior = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCprior = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyCprior))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCprior && pyCprior->dimensions > 0)
        panCprior = (int *)pyCprior->data;

    errorcode = LSloadVarPriorities(pModel,
                                    panCprior);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadVarPriorities(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject  *pyModel;


    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadVarPriorities(pModel,
                                    pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadVarStartPoint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)pyPrimal->data;

    errorcode = LSloadVarStartPoint(pModel,
                                    padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadVarStartPointPartial(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCols;
    int       *paiCols = NULL;
    double    *padPrimal = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCols = NULL,*pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nCols,
                                 &PyArray_Type,&pyCols,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCols && pyCols->dimensions > 0)
        paiCols = (int *)pyCols->data;
    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)pyPrimal->data;

    errorcode = LSloadVarStartPointPartial(pModel,
                                           nCols,
                                           paiCols,
                                           padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadMIPVarStartPoint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)pyPrimal->data;

    errorcode = LSloadMIPVarStartPoint(pModel,
                                       padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadMIPVarStartPointPartial(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCols;
    int       *paiCols = NULL;
    int       *paiPrimal = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCols = NULL,*pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nCols,
                                 &PyArray_Type,&pyCols,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCols && pyCols->dimensions > 0)
        paiCols = (int *)pyCols->data;
    if(pyPrimal && pyPrimal->dimensions > 0)
        paiPrimal = (int *)pyPrimal->data;

    errorcode = LSloadMIPVarStartPointPartial(pModel,
                                              nCols,
                                              paiCols,
                                              paiPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadVarStartPoint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFname;

    PyObject  *pyModel;


    if (!PyArg_ParseTuple(args, "Os",
                                 &pyModel,
                                 &pszFname))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadVarStartPoint(pModel,
                                    pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadBlockStructure(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nBlock,nType;
    int       *panRblock = NULL, *panCblock = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyRblock = NULL,*pyCblock = NULL;


    if (!PyArg_ParseTuple(args, "OiO!O!i",
                                 &pyModel,
                                 &nBlock,
                                 &PyArray_Type,&pyRblock,
                                 &PyArray_Type,&pyCblock,
                                 &nType))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRblock && pyRblock->dimensions > 0)
        panRblock = (int *)pyRblock->data;
    if(pyCblock && pyCblock->dimensions > 0)
        panCblock = (int *)pyCblock->data;

    errorcode = LSloadBlockStructure(pModel,
                                     nBlock,
                                     panRblock,
                                     panCblock,
                                     nType);

    return Py_BuildValue("i",errorcode);
}

/**********************************************************************
 * Optimization Routines (6)                                          *
 **********************************************************************/
PyObject *pyLSoptimize(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nMethod;
    int       *pnStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStatus = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nMethod,
                                 &PyArray_Type,&pyStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStatus && pyStatus->dimensions > 0)
        pnStatus = (int *)PyArray_GetPtr(pyStatus,index);

    errorcode = LSoptimize(pModel,nMethod,pnStatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsolveMIP(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnMIPSolStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyMIPSolStatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyMIPSolStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyMIPSolStatus && pyMIPSolStatus->dimensions > 0)
        pnMIPSolStatus = (int *)PyArray_GetPtr(pyMIPSolStatus,index);

    errorcode = LSsolveMIP(pModel,pnMIPSolStatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsolveGOP(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnGOPSolStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyGOPSolStatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyGOPSolStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyGOPSolStatus && pyGOPSolStatus->dimensions > 0)
        pnGOPSolStatus = (int *)PyArray_GetPtr(pyGOPSolStatus,index);

    errorcode = LSsolveGOP(pModel,pnGOPSolStatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSoptimizeQP(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnQPSolStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyQPSolStatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyQPSolStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyQPSolStatus && pyQPSolStatus->dimensions > 0)
        pnQPSolStatus = (int *)PyArray_GetPtr(pyQPSolStatus,index);

    errorcode = LSoptimizeQP(pModel,pnQPSolStatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLScheckConvexity(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyModel))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LScheckConvexity(pModel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsolveSBD(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nStages;
    int       *pnStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStatus = NULL,*panColStage,*panRowStage;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &nStages,
                                 &PyArray_Type,&panRowStage,
                                 &PyArray_Type,&panColStage,
                                 &PyArray_Type,&pyStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStatus && pyStatus->dimensions > 0)
        pnStatus = (int *)PyArray_GetPtr(pyStatus,index);

    errorcode = LSsolveSBD(pModel,
                           nStages,
                           (int *)panRowStage->data,
                           (int *)panColStage->data,
                           pnStatus);

    return Py_BuildValue("i",errorcode);
}

/**********************************************************************
 * Solution Query Routines (14)                                       *
**********************************************************************/
PyObject *pyLSgetInfo(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel = NULL;
    int       nQuery;
    void      *pvResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel = NULL;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nQuery,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }
    if (nQuery!=LS_IINFO_ARCH_ID) {
      CHECK_MODEL;
    }

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSgetInfo(pModel,nQuery,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetPrimalSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)PyArray_GetPtr(pyPrimal,index);

    errorcode = LSgetPrimalSolution(pModel,padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDualSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padDual = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDual = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyDual))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDual && pyDual->dimensions > 0)
        padDual = (double *)PyArray_GetPtr(pyDual,index);

    errorcode = LSgetDualSolution(pModel,padDual);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetReducedCosts(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padRedcosts = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyRedcosts = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyRedcosts))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRedcosts && pyRedcosts->dimensions > 0)
        padRedcosts = (double *)PyArray_GetPtr(pyRedcosts,index);

    errorcode = LSgetReducedCosts(pModel,padRedcosts);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetReducedCostsCone(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padRedcosts = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyRedcosts = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyRedcosts))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRedcosts && pyRedcosts->dimensions > 0)
        padRedcosts = (double *)PyArray_GetPtr(pyRedcosts,index);

    errorcode = LSgetReducedCostsCone(pModel,padRedcosts);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetSlacks(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padSlacks = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySlacks = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pySlacks))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySlacks && pySlacks->dimensions > 0)
        padSlacks = (double *)PyArray_GetPtr(pySlacks,index);

    errorcode = LSgetSlacks(pModel,padSlacks);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetBasis(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panCstatus = NULL,*panRstatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyCstatus = NULL,*pyRstatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyCstatus,
                                 &PyArray_Type,&pyRstatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCstatus && pyCstatus->dimensions > 0)
        panCstatus = (int *)PyArray_GetPtr(pyCstatus,index);
    if(pyRstatus && pyRstatus->dimensions > 0)
        panRstatus = (int *)PyArray_GetPtr(pyRstatus,index);

    errorcode = LSgetBasis(pModel,panCstatus,panRstatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nWhich;
    double    *padVal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyVal = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nWhich,
                                 &PyArray_Type,&pyVal))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVal && pyVal->dimensions > 0)
        padVal = (double *)PyArray_GetPtr(pyVal,index);

    errorcode = LSgetSolution(pModel,nWhich,padVal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPPrimalSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)PyArray_GetPtr(pyPrimal,index);

    errorcode = LSgetMIPPrimalSolution(pModel,padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPDualSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padDual = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDual = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyDual))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDual && pyDual->dimensions > 0)
        padDual = (double *)PyArray_GetPtr(pyDual,index);

    errorcode = LSgetMIPDualSolution(pModel,padDual);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPReducedCosts(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padRedcosts = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyRedcosts = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyRedcosts))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRedcosts && pyRedcosts->dimensions > 0)
        padRedcosts = (double *)PyArray_GetPtr(pyRedcosts,index);

    errorcode = LSgetMIPReducedCosts(pModel,padRedcosts);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPSlacks(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padSlacks = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySlacks = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pySlacks))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySlacks && pySlacks->dimensions > 0)
        padSlacks = (double *)PyArray_GetPtr(pySlacks,index);

    errorcode = LSgetMIPSlacks(pModel,padSlacks);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPBasis(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panCstatus = NULL,*panRstatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyCstatus = NULL,*pyRstatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyCstatus,
                                 &PyArray_Type,&pyRstatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCstatus && pyCstatus->dimensions > 0)
        panCstatus = (int *)PyArray_GetPtr(pyCstatus,index);
    if(pyRstatus && pyRstatus->dimensions > 0)
        panRstatus = (int *)PyArray_GetPtr(pyRstatus,index);

    errorcode = LSgetMIPBasis(pModel,panCstatus,panRstatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNextBestMIPSol(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnIntModStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyIntModStatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyIntModStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyIntModStatus && pyIntModStatus->dimensions > 0)
        pnIntModStatus = (int *)PyArray_GetPtr(pyIntModStatus,index);

    errorcode = LSgetNextBestMIPSol(pModel,pnIntModStatus);

    return Py_BuildValue("i",errorcode);
}

/*********************************************************************
 *  Model Query Routines (30)                                        *
 *********************************************************************/
PyObject *pyLSgetLPData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnObjSense = NULL, *paiAcols = NULL;
    int       *panAcols = NULL, *paiArows = NULL;
    double    *pdObjConst = NULL, *padC = NULL, *padB = NULL;
    double    *padAcoef = NULL, *padL = NULL, *padU = NULL;
    char      *pachConTypes = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyObjSense = NULL,*pyiAcols = NULL,*pynAcols = NULL;
    PyArrayObject  *pyArows = NULL,*pyObjConst = NULL,*pyC = NULL;
    PyArrayObject  *pyB = NULL,*pyAcoef = NULL,*pyL = NULL;
    PyArrayObject  *pyU = NULL,*pyConTypes = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyObjSense,
                                 &PyArray_Type,&pyObjConst,
                                 &PyArray_Type,&pyC,
                                 &PyArray_Type,&pyB,
                                 &PyArray_Type,&pyConTypes,
                                 &PyArray_Type,&pyiAcols,
                                 &PyArray_Type,&pynAcols,
                                 &PyArray_Type,&pyAcoef,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyObjSense && pyObjSense->dimensions > 0)
        pnObjSense = (int *)PyArray_GetPtr(pyObjSense,index);
    if(pyiAcols && pyiAcols->dimensions > 0)
        paiAcols = (int *)PyArray_GetPtr(pyiAcols,index);
    if(pynAcols && pynAcols->dimensions > 0)
        panAcols = (int *)PyArray_GetPtr(pynAcols,index);
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)PyArray_GetPtr(pyArows,index);
    if(pyObjConst && pyObjConst->dimensions > 0)
        pdObjConst = (double *)PyArray_GetPtr(pyObjConst,index);
    if(pyC && pyC->dimensions > 0)
        padC = (double *)PyArray_GetPtr(pyC,index);
    if(pyB && pyB->dimensions > 0)
        padB = (double *)PyArray_GetPtr(pyB,index);
    if(pyAcoef && pyAcoef->dimensions > 0)
        padAcoef = (double *)PyArray_GetPtr(pyAcoef,index);
    if(pyL && pyL->dimensions > 0)
        padL = (double *)PyArray_GetPtr(pyL,index);
    if(pyU && pyU->dimensions > 0)
        padU = (double *)PyArray_GetPtr(pyU,index);
    if(pyConTypes)
        pachConTypes = (char *)PyArray_GetPtr(pyConTypes,index);

    errorcode = LSgetLPData(pModel,
                            pnObjSense,
                            pdObjConst,
                            padC,
                            padB,
                            pachConTypes,
                            paiAcols,
                            panAcols,
                            padAcoef,
                            paiArows,
                            padL,
                            padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetQCData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *paiQCrows = NULL, *paiQCcols1 = NULL;
    int       *paiQCcols2 = NULL;
    double    *padQCcoef = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyQCrows = NULL,*pyQCcols1 = NULL,*pyQCcols2 = NULL;
    PyArrayObject  *pyQCcoef = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyQCrows,
                                 &PyArray_Type,&pyQCcols1,
                                 &PyArray_Type,&pyQCcols2,
                                 &PyArray_Type,&pyQCcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyQCrows && pyQCrows->dimensions > 0)
        paiQCrows = (int *)PyArray_GetPtr(pyQCrows,index);
    if(pyQCcols1 && pyQCcols1->dimensions > 0)
        paiQCcols1 = (int *)PyArray_GetPtr(pyQCcols1,index);
    if(pyQCcols2 && pyQCcols2->dimensions > 0)
        paiQCcols2 = (int *)PyArray_GetPtr(pyQCcols2,index);
    if(pyQCcoef && pyQCcoef->dimensions > 0)
        padQCcoef = (double *)PyArray_GetPtr(pyQCcoef,index);


    errorcode = LSgetQCData(pModel,
                            paiQCrows,
                            paiQCcols1,
                            paiQCcols2,
                            padQCcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetQCDatai(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCon;
    int       *pnQCnnz = NULL, *paiQCcols1 = NULL;
    int       *paiQCcols2 = NULL;
    double    *padQCcoef = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyQCnnz = NULL,*pyQCcols1 = NULL,*pyQCcols2 = NULL;
    PyArrayObject  *pyQCcoef = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &iCon,
                                 &PyArray_Type,&pyQCnnz,
                                 &PyArray_Type,&pyQCcols1,
                                 &PyArray_Type,&pyQCcols2,
                                 &PyArray_Type,&pyQCcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyQCnnz && pyQCnnz->dimensions > 0)
        pnQCnnz = (int *)PyArray_GetPtr(pyQCnnz,index);
    if(pyQCcols1 && pyQCcols1->dimensions > 0)
        paiQCcols1 = (int *)PyArray_GetPtr(pyQCcols1,index);
    if(pyQCcols2 && pyQCcols2->dimensions > 0)
        paiQCcols2 = (int *)PyArray_GetPtr(pyQCcols2,index);
    if(pyQCcoef && pyQCcoef->dimensions > 0)
        padQCcoef = (double *)PyArray_GetPtr(pyQCcoef,index);


    errorcode = LSgetQCDatai(pModel,
                             iCon,
                             pnQCnnz,
                             paiQCcols1,
                             paiQCcols2,
                             padQCcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVarType(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pachVarTypes = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyVarTypes = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyVarTypes))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVarTypes)
        pachVarTypes = (char *)PyArray_GetPtr(pyVarTypes,index);

    errorcode = LSgetVarType(pModel,
                             pachVarTypes);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVarStartPoint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)PyArray_GetPtr(pyPrimal,index);

    errorcode = LSgetVarStartPoint(pModel,
                                   padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVarStartPointPartial(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panCols = NULL, *paiCols = NULL;
    double    *padPrimal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL, *pynCols = NULL, *pyiCols = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pynCols,
                                 &PyArray_Type,&pyiCols,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pynCols && pynCols->dimensions > 0)
        panCols = (int *)PyArray_GetPtr(pynCols,index);
    if(pyiCols && pyiCols->dimensions > 0)
        paiCols = (int *)PyArray_GetPtr(pyiCols,index);
    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)PyArray_GetPtr(pyPrimal,index);

    errorcode = LSgetVarStartPointPartial(pModel,
                                          panCols,
                                          paiCols,
                                          padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPVarStartPointPartial(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panCols = NULL, *paiCols = NULL;
    int       *paiPrimal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL, *pynCols = NULL, *pyiCols = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pynCols,
                                 &PyArray_Type,&pyiCols,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pynCols && pynCols->dimensions > 0)
        panCols = (int *)PyArray_GetPtr(pynCols,index);
    if(pyiCols && pyiCols->dimensions > 0)
        paiCols = (int *)PyArray_GetPtr(pyiCols,index);
    if(pyPrimal && pyPrimal->dimensions > 0)
        paiPrimal = (int *)PyArray_GetPtr(pyPrimal,index);

    errorcode = LSgetMIPVarStartPointPartial(pModel,
                                             panCols,
                                             paiCols,
                                             paiPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetMIPVarStartPoint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)PyArray_GetPtr(pyPrimal,index);

    errorcode = LSgetMIPVarStartPoint(pModel,
                                      padPrimal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetSETSData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *piNsets = NULL, *piNtnz = NULL;
    char      *pachSETtype = NULL;
    int       *piCardnum = NULL, *piNnz = NULL;
    int       *piBegset = NULL, *piVarndx = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyNsets = NULL,*pyNtnz = NULL,*pySETtype = NULL;
    PyArrayObject  *pyCardnum = NULL,*pyNnz = NULL,*pyBegset = NULL;
    PyArrayObject  *pyVarndx = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyNsets,
                                 &PyArray_Type,&pyNtnz,
                                 &PyArray_Type,&pySETtype,
                                 &PyArray_Type,&pyCardnum,
                                 &PyArray_Type,&pyNnz,
                                 &PyArray_Type,&pyBegset,
                                 &PyArray_Type,&pyVarndx))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyNsets && pyNsets->dimensions > 0)
        piNsets = (int *)PyArray_GetPtr(pyNsets,index);
    if(pyNtnz && pyNtnz->dimensions > 0)
        piNtnz = (int *)PyArray_GetPtr(pyNtnz,index);
    if(pySETtype)
        pachSETtype = (char *)PyArray_GetPtr(pySETtype,index);
    if(pyCardnum && pyCardnum->dimensions > 0)
        piCardnum = (int *)PyArray_GetPtr(pyCardnum,index);
    if(pyNnz && pyNnz->dimensions > 0)
        piNnz = (int *)PyArray_GetPtr(pyNnz,index);
    if(pyBegset && pyBegset->dimensions > 0)
        piBegset = (int *)PyArray_GetPtr(pyBegset,index);
    if(pyVarndx && pyVarndx->dimensions > 0)
        piVarndx = (int *)PyArray_GetPtr(pyVarndx,index);


    errorcode = LSgetSETSData(pModel,
                              piNsets,
                              piNtnz,
                              pachSETtype,
                              piCardnum,
                              piNnz,
                              piBegset,
                              piVarndx);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetSETSDatai(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iSet;
    char      *pachSETtype = NULL;
    int       *piCardnum = NULL, *piNnz = NULL;
    int       *piVarndx = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySETtype = NULL;
    PyArrayObject  *pyCardnum = NULL,*pyNnz = NULL;
    PyArrayObject  *pyVarndx = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &iSet,
                                 &PyArray_Type,&pySETtype,
                                 &PyArray_Type,&pyCardnum,
                                 &PyArray_Type,&pyNnz,
                                 &PyArray_Type,&pyVarndx))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySETtype)
        pachSETtype = (char *)PyArray_GetPtr(pySETtype,index);
    if(pyCardnum && pyCardnum->dimensions > 0)
        piCardnum = (int *)PyArray_GetPtr(pyCardnum,index);
    if(pyNnz && pyNnz->dimensions > 0)
        piNnz = (int *)PyArray_GetPtr(pyNnz,index);
    if(pyVarndx && pyVarndx->dimensions > 0)
        piVarndx = (int *)PyArray_GetPtr(pyVarndx,index);


    errorcode = LSgetSETSDatai(pModel,
                               iSet,
                               pachSETtype,
                               piCardnum,
                               piNnz,
                               piVarndx);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetSemiContData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *piNvars = NULL;
    int       *piVarndx = NULL;
    double    *padL = NULL, *padU = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyNvar = NULL;
    PyArrayObject  *pyVarndx = NULL;
    PyArrayObject  *pyL = NULL,*pyU = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyNvar,
                                 &PyArray_Type,&pyVarndx,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyNvar && pyNvar->dimensions > 0)
        piNvars = (int *)PyArray_GetPtr(pyNvar,index);
    if(pyVarndx && pyVarndx->dimensions > 0)
        piVarndx = (int *)PyArray_GetPtr(pyVarndx,index);
    if(pyL && pyL->dimensions > 0)
        padL = (double *)PyArray_GetPtr(pyL,index);
    if(pyU && pyU->dimensions > 0)
        padU = (double *)PyArray_GetPtr(pyU,index);


    errorcode = LSgetSemiContData(pModel,
                                  piNvars,
                                  piVarndx,
                                  padL,
                                  padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetLPVariableDataj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iVar;
    char      *pachVartype = NULL;
    double    *padC = NULL,*padL = NULL,*padU = NULL;
    int       *pnAnnz = NULL;
    int       *paiArows = NULL;
    double    *padAcoef = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyVartype = NULL;
    PyArrayObject  *pyC = NULL;
    PyArrayObject  *pyL = NULL,*pyU = NULL;
    PyArrayObject  *pyAnnz = NULL,*pyArows = NULL;
    PyArrayObject  *pyAcoef = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!O!O!",
                                 &pyModel,
                                 &iVar,
                                 &PyArray_Type,&pyVartype,
                                 &PyArray_Type,&pyC,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU,
                                 &PyArray_Type,&pyAnnz,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyAcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVartype)
        pachVartype = (char *)PyArray_GetPtr(pyVartype,index);
    if(pyC && pyC->dimensions > 0)
        padC = (double *)PyArray_GetPtr(pyC,index);
    if(pyL && pyL->dimensions > 0)
        padL = (double *)PyArray_GetPtr(pyL,index);
    if(pyU && pyU->dimensions > 0)
        padU = (double *)PyArray_GetPtr(pyU,index);
    if(pyAnnz && pyAnnz->dimensions > 0)
        pnAnnz = (int *)PyArray_GetPtr(pyAnnz,index);
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)PyArray_GetPtr(pyArows,index);
    if(pyAcoef && pyAcoef->dimensions > 0)
        padAcoef = (double *)PyArray_GetPtr(pyAcoef,index);


    errorcode = LSgetLPVariableDataj(pModel,
                                     iVar,
                                     pachVartype,
                                     padC,
                                     padL,
                                     padU,
                                     pnAnnz,
                                     paiArows,
                                     padAcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVariableNamej(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iVar;
    char      *pachVarName = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyVarName = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iVar,
                                 &PyArray_Type,&pyVarName))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVarName)
        pachVarName = (char *)PyArray_GetPtr(pyVarName,index);

    errorcode = LSgetVariableNamej(pModel,
                                   iVar,
                                   pachVarName);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVariableIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszVarName;
    int       *piVar = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyVar = NULL;

    if (!PyArg_ParseTuple(args, "OsO!",
                                 &pyModel,
                                 &pszVarName,
                                 &PyArray_Type,&pyVar))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVar && pyVar->dimensions > 0)
        piVar = (int *)PyArray_GetPtr(pyVar,index);

    errorcode = LSgetVariableIndex(pModel,
                                   pszVarName,
                                   piVar);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConstraintNamei(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCon;
    char      *pachConName = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyConName = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iCon,
                                 &PyArray_Type,&pyConName))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConName)
        pachConName = (char *)PyArray_GetPtr(pyConName,index);

    errorcode = LSgetConstraintNamei(pModel,
                                     iCon,
                                     pachConName);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConstraintIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszConName;
    int       *piCon = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyCon = NULL;

    if (!PyArg_ParseTuple(args, "OsO!",
                                 &pyModel,
                                 &pszConName,
                                 &PyArray_Type,&pyCon))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCon && pyCon->dimensions > 0)
        piCon = (int *)PyArray_GetPtr(pyCon,index);

    errorcode = LSgetConstraintIndex(pModel,
                                     pszConName,
                                     piCon);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConstraintDatai(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCon;
    char      *pachConType = NULL,*pachIsNlp = NULL;
    double    *pdB = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyConType = NULL, *pyIsNlp = NULL, *pyB = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &iCon,
                                 &PyArray_Type,&pyConType,
                                 &PyArray_Type,&pyIsNlp,
                                 &PyArray_Type,&pyB))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConType)
        pachConType = (char *)PyArray_GetPtr(pyConType,index);
    if(pyIsNlp)
        pachIsNlp = (char *)PyArray_GetPtr(pyIsNlp,index);
    if(pyB && pyB->dimensions > 0)
        pdB = (double *)PyArray_GetPtr(pyB,index);

    errorcode = LSgetConstraintDatai(pModel,
                                     iCon,
                                     pachConType,
                                     pachIsNlp,
                                     pdB);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetLPConstraintDatai(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCon;
    char      *pachConType = NULL;
    double    *pdB = NULL,*pdAcoef = NULL;
    int       *pnNnz = NULL, *piVar = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyConType = NULL, *pyAcoef = NULL, *pyB = NULL;
    PyArrayObject  *pyNnz = NULL, *pyVar = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
                                 &pyModel,
                                 &iCon,
                                 &PyArray_Type,&pyConType,
                                 &PyArray_Type,&pyB,
                                 &PyArray_Type,&pyNnz,
                                 &PyArray_Type,&pyVar,
                                 &PyArray_Type,&pyAcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConType)
        pachConType = (char *)PyArray_GetPtr(pyConType,index);
    if(pyB && pyB->dimensions > 0)
        pdB = (double *)PyArray_GetPtr(pyB,index);
    if(pyNnz && pyNnz->dimensions > 0)
        pnNnz = (int *)PyArray_GetPtr(pyNnz,index);
    if(pyVar && pyVar->dimensions > 0)
        piVar = (int *)PyArray_GetPtr(pyVar,index);
    if(pyAcoef && pyAcoef->dimensions > 0)
        pdAcoef = (double *)PyArray_GetPtr(pyAcoef,index);

    errorcode = LSgetLPConstraintDatai(pModel,
                                       iCon,
                                       pachConType,
                                       pdB,
                                       pnNnz,
                                       piVar,
                                       pdAcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConeNamei(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCone;
    char      *pachConeName = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyConeName = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iCone,
                                 &PyArray_Type,&pyConeName))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConeName)
        pachConeName = (char *)PyArray_GetPtr(pyConeName,index);

    errorcode = LSgetConeNamei(pModel,
                               iCone,
                               pachConeName);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConeIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszConeName;
    int       *piCone = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyCone = NULL;

    if (!PyArg_ParseTuple(args, "OsO!",
                                 &pyModel,
                                 &pszConeName,
                                 &PyArray_Type,&pyCone))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCone && pyCone->dimensions > 0)
        piCone = (int *)PyArray_GetPtr(pyCone,index);

    errorcode = LSgetConeIndex(pModel,
                               pszConeName,
                               piCone);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConeDatai(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCone;
    char      *pachConeType = NULL;
    int       *piNnz = NULL,*paiCols = NULL;
	double    *pdConeAlpha = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyConeType = NULL, *pyNnz = NULL, *pyCols = NULL, *pydConeAlpha=NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &iCone,
								 &PyArray_Type,&pyConeType,
                                 &PyArray_Type,&pydConeAlpha,
                                 &PyArray_Type,&pyNnz,
                                 &PyArray_Type,&pyCols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConeType)
        pachConeType = (char *)PyArray_GetPtr(pyConeType,index);
    if(pyNnz && pyNnz->dimensions > 0)
        piNnz = (int *)PyArray_GetPtr(pyNnz,index);
    if(pyCols && pyCols->dimensions > 0)
        paiCols = (int *)PyArray_GetPtr(pyCols,index);
    if(pydConeAlpha && pydConeAlpha->dimensions > 0)
        pdConeAlpha = (double *)PyArray_GetPtr(pydConeAlpha,index);
    errorcode = LSgetConeDatai(pModel,
                               iCone,
                               pachConeType,
							   pdConeAlpha,
                               piNnz,
                               paiCols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNLPData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *paiNLPcols = NULL,*panNLPcols = NULL;
    double    *padNLPcoef = NULL;
    int       *paiNLProws = NULL,*pnNLPobj = NULL;
    int       *paiNLPobj = NULL;
    double    *padNLPobj = NULL;
    char      *pachNLPConTypes = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyiNLPcols = NULL,*pynNLPcols = NULL;
    PyArrayObject  *pyNLPcoef = NULL;
    PyArrayObject  *pyNLProws = NULL,*pynNLPobj = NULL;
    PyArrayObject  *pyiNLPobj = NULL;
    PyArrayObject  *pydNLPobj = NULL;
    PyArrayObject  *pyNLPConTypes = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyiNLPcols,
                                 &PyArray_Type,&pynNLPcols,
                                 &PyArray_Type,&pyNLPcoef,
                                 &PyArray_Type,&pyNLProws,
                                 &PyArray_Type,&pynNLPobj,
                                 &PyArray_Type,&pyiNLPobj,
                                 &PyArray_Type,&pydNLPobj,
                                 &PyArray_Type,&pyNLPConTypes))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyiNLPcols && pyiNLPcols->dimensions > 0)
        paiNLPcols = (int *)PyArray_GetPtr(pyiNLPcols,index);
    if(pynNLPcols && pynNLPcols->dimensions > 0)
        panNLPcols = (int *)PyArray_GetPtr(pynNLPcols,index);
    if(pyNLPcoef && pyNLPcoef->dimensions > 0)
        padNLPcoef = (double *)PyArray_GetPtr(pyNLPcoef,index);
    if(pyNLProws && pyNLProws->dimensions > 0)
        paiNLProws = (int *)PyArray_GetPtr(pyNLProws,index);
    if(pynNLPobj && pynNLPobj->dimensions > 0)
        pnNLPobj = (int *)PyArray_GetPtr(pynNLPobj,index);
    if(pyiNLPobj && pyiNLPobj->dimensions > 0)
        paiNLPobj = (int *)PyArray_GetPtr(pyiNLPobj,index);
    if(pydNLPobj && pydNLPobj->dimensions > 0)
        padNLPobj = (double *)PyArray_GetPtr(pydNLPobj,index);
    if(pyNLPConTypes)
        pachNLPConTypes = (char *)PyArray_GetPtr(pyNLPConTypes,index);


    errorcode = LSgetNLPData(pModel,
                             paiNLPcols,
                             panNLPcols,
                             padNLPcoef,
                             paiNLProws,
                             pnNLPobj,
                             paiNLPobj,
                             padNLPobj,
                             pachNLPConTypes);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNLPConstraintDatai(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iCon;
    int       *pnNnz = NULL, *paiNLPcols = NULL;
    double    *padNLPcoef = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyNnz = NULL, *pyNLPcols = NULL, *pyNLPcoef = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &iCon,
                                 &PyArray_Type,&pyNnz,
                                 &PyArray_Type,&pyNLPcols,
                                 &PyArray_Type,&pyNLPcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyNnz && pyNnz->dimensions > 0)
        pnNnz = (int *)PyArray_GetPtr(pyNnz,index);
    if(pyNLPcols && pyNLPcols->dimensions > 0)
        paiNLPcols = (int *)PyArray_GetPtr(pyNLPcols,index);
    if(pyNLPcoef && pyNLPcoef->dimensions > 0)
        padNLPcoef = (double *)PyArray_GetPtr(pyNLPcoef,index);

    errorcode = LSgetNLPConstraintDatai(pModel,
                                        iCon,
                                        pnNnz,
                                        paiNLPcols,
                                        padNLPcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNLPVariableDataj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iVar;
    int       *pnNnz = NULL, *panNLProws = NULL;
    double    *padNLPcoef = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyNnz = NULL, *pyNLProws = NULL, *pyNLPcoef = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &iVar,
                                 &PyArray_Type,&pyNnz,
                                 &PyArray_Type,&pyNLProws,
                                 &PyArray_Type,&pyNLPcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyNnz && pyNnz->dimensions > 0)
        pnNnz = (int *)PyArray_GetPtr(pyNnz,index);
    if(pyNLProws && pyNLProws->dimensions > 0)
        panNLProws = (int *)PyArray_GetPtr(pyNLProws,index);
    if(pyNLPcoef && pyNLPcoef->dimensions > 0)
        padNLPcoef = (double *)PyArray_GetPtr(pyNLPcoef,index);

    errorcode = LSgetNLPVariableDataj(pModel,
                                      iVar,
                                      pnNnz,
                                      panNLProws,
                                      padNLPcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNLPObjectiveData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnNLPobjnnz = NULL, *paiNLPobj = NULL;
    double    *padNLPobj = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyNLPobjnnz = NULL, *pyiNLPobj = NULL, *pydNLPobj = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyNLPobjnnz,
                                 &PyArray_Type,&pyiNLPobj,
                                 &PyArray_Type,&pydNLPobj))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyNLPobjnnz && pyNLPobjnnz->dimensions > 0)
        pnNLPobjnnz = (int *)PyArray_GetPtr(pyNLPobjnnz,index);
    if(pyiNLPobj && pyiNLPobj->dimensions > 0)
        paiNLPobj = (int *)PyArray_GetPtr(pyiNLPobj,index);
    if(pydNLPobj && pydNLPobj->dimensions > 0)
        padNLPobj = (double *)PyArray_GetPtr(pydNLPobj,index);

    errorcode = LSgetNLPObjectiveData(pModel,
                                      pnNLPobjnnz,
                                      paiNLPobj,
                                      padNLPobj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDualModel(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    pLSmodel  pDualModel;


    PyObject       *pyModel;
    PyObject       *pyDualModel;


    if (!PyArg_ParseTuple(args, "OO",
                                 &pyModel,
                                 &pyDualModel))

    {
        return NULL;
    }

    CHECK_MODEL;

    pDualModel = PyGetObjPtr(pyDualModel);
    if(pDualModel == NULL)
    {
        errorcode = LSERR_ILLEGAL_NULL_POINTER;
        return Py_BuildValue("i",errorcode);
    }


    errorcode = LSgetDualModel(pModel,
                               pDualModel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetInstruct(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnObjSense = NULL;
    char      *pachConType = NULL,*pachVarType = NULL;
    int       *panCode = NULL;
    double    *padNumVal = NULL,*padVarVal = NULL;
    int       *panObjBeg = NULL,*panObjLength = NULL;
    int       *panConBeg = NULL,*panConLength = NULL;
    double    *padLwrBnd = NULL,*padUprBnd = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyObjSense = NULL, *pyConTyp = NULL, *pyVarType = NULL;
    PyArrayObject  *pyCode = NULL, *pyNumVa = NULL, *pyVarVal = NULL;
    PyArrayObject  *pyObjBeg = NULL, *pyObjLength = NULL, *pyConBeg = NULL;
    PyArrayObject  *pyConLength = NULL, *pyLwrBnd = NULL, *pyUprBnd = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyObjSense,
                                 &PyArray_Type,&pyConTyp,
                                 &PyArray_Type,&pyVarType,
                                 &PyArray_Type,&pyCode,
                                 &PyArray_Type,&pyNumVa,
                                 &PyArray_Type,&pyVarVal,
                                 &PyArray_Type,&pyObjBeg,
                                 &PyArray_Type,&pyObjLength,
                                 &PyArray_Type,&pyConBeg,
                                 &PyArray_Type,&pyConLength,
                                 &PyArray_Type,&pyLwrBnd,
                                 &PyArray_Type,&pyUprBnd))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyObjSense && pyObjSense->dimensions > 0)
        pnObjSense = (int *)PyArray_GetPtr(pyObjSense,index);
    if(pyConTyp)
        pachConType = (char *)PyArray_GetPtr(pyConTyp,index);
    if(pyVarType)
        pachVarType = (char *)PyArray_GetPtr(pyVarType,index);
    if(pyCode && pyCode->dimensions > 0)
        panCode = (int *)PyArray_GetPtr(pyCode,index);
    if(pyNumVa && pyNumVa->dimensions > 0)
        padNumVal = (double *)PyArray_GetPtr(pyNumVa,index);
    if(pyVarVal && pyVarVal->dimensions > 0)
        padVarVal = (double *)PyArray_GetPtr(pyVarVal,index);
    if(pyObjBeg && pyObjBeg->dimensions > 0)
        panObjBeg = (int *)PyArray_GetPtr(pyObjBeg,index);
    if(pyObjLength && pyObjLength->dimensions > 0)
        panObjLength = (int *)PyArray_GetPtr(pyObjLength,index);
    if(pyConBeg && pyConBeg->dimensions > 0)
        panConBeg = (int *)PyArray_GetPtr(pyConBeg,index);
    if(pyConLength && pyConLength->dimensions > 0)
        panConLength = (int *)PyArray_GetPtr(pyConLength,index);
    if(pyLwrBnd && pyLwrBnd->dimensions > 0)
        padLwrBnd = (double *)PyArray_GetPtr(pyLwrBnd,index);
    if(pyUprBnd && pyUprBnd->dimensions > 0)
        padUprBnd = (double *)PyArray_GetPtr(pyUprBnd,index);

    errorcode = LSgetInstruct(pModel,
                              pnObjSense,
                              pachConType,
                              pachVarType,
                              panCode,
                              padNumVal,
                              padVarVal,
                              panObjBeg,
                              panObjLength,
                              panConBeg,
                              panConLength,
                              padLwrBnd,
                              padUprBnd);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLScalinfeasMIPsolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *pdIntPfeas = NULL,*pbConsPfeas = NULL,*pdPrimalMipsol = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyIntPfeas = NULL, *pyConsPfeas = NULL, *pyPrimalMipsol = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyIntPfeas,
                                 &PyArray_Type,&pyConsPfeas,
                                 &PyArray_Type,&pyPrimalMipsol))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyIntPfeas && pyIntPfeas->dimensions > 0)
        pdIntPfeas = (double *)PyArray_GetPtr(pyIntPfeas,index);
    if(pyConsPfeas && pyConsPfeas->dimensions > 0)
        pbConsPfeas = (double *)PyArray_GetPtr(pyConsPfeas,index);
    if(pyPrimalMipsol && pyPrimalMipsol->dimensions > 0)
        pdPrimalMipsol = (double *)PyArray_GetPtr(pyPrimalMipsol,index);

    errorcode = LScalinfeasMIPsolution(pModel,
                                       pdIntPfeas,
                                       pbConsPfeas,
                                       pdPrimalMipsol);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetRoundMIPsolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padPrimal = NULL,*padPrimalRound = NULL;
    double    *padObjRound = NULL,*padPfeasRound = NULL;
    int       *pnstatus = NULL;
    int       iUseOpti;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyPrimal = NULL, *pyPrimalRound = NULL;
    PyArrayObject  *pyObjRound = NULL, *pyPfeasRound = NULL;
    PyArrayObject  *pystatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!i",
                                 &pyModel,
                                 &PyArray_Type,&pyPrimal,
                                 &PyArray_Type,&pyPrimalRound,
                                 &PyArray_Type,&pyObjRound,
                                 &PyArray_Type,&pyPfeasRound,
                                 &PyArray_Type,&pystatus,
                                 &iUseOpti))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyPrimal && pyPrimal->dimensions > 0)
        padPrimal = (double *)PyArray_GetPtr(pyPrimal,index);
    if(pyPrimalRound && pyPrimalRound->dimensions > 0)
        padPrimalRound = (double *)PyArray_GetPtr(pyPrimalRound,index);
    if(pyObjRound && pyObjRound->dimensions > 0)
        padObjRound = (double *)PyArray_GetPtr(pyObjRound,index);
    if(pyPfeasRound && pyPfeasRound->dimensions > 0)
        padPfeasRound = (double *)PyArray_GetPtr(pyPfeasRound,index);
    if(pystatus && pystatus->dimensions > 0)
        pnstatus = (int *)PyArray_GetPtr(pystatus,index);

    errorcode = LSgetRoundMIPsolution(pModel,
                                      padPrimal,
                                      padPrimalRound,
                                      padObjRound,
                                      padPfeasRound,
                                      pnstatus,
                                      iUseOpti);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDuplicateColumns(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnSets = NULL,*paiSetsBeg = NULL,*paiCols = NULL;
    int       nCheckVals;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySets = NULL, *pySetsBeg = NULL;
    PyArrayObject  *pyCols= NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &nCheckVals,
                                 &PyArray_Type,&pySets,
                                 &PyArray_Type,&pySetsBeg,
                                 &PyArray_Type,&pyCols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySets && pySets->dimensions > 0)
        pnSets = (int *)PyArray_GetPtr(pySets,index);
    if(pySetsBeg && pySetsBeg->dimensions > 0)
        paiSetsBeg = (int *)PyArray_GetPtr(pySetsBeg,index);
    if(pyCols && pyCols->dimensions > 0)
        paiCols = (int *)PyArray_GetPtr(pyCols,index);

    errorcode = LSgetDuplicateColumns(pModel,
                                      nCheckVals,
                                      pnSets,
                                      paiSetsBeg,
                                      paiCols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetRangeData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padR = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyR= NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyR))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyR && pyR->dimensions > 0)
        padR = (double *)PyArray_GetPtr(pyR,index);

    errorcode = LSgetRangeData(pModel,
                               padR);

    return Py_BuildValue("i",errorcode);
}

/**********************************************************************
 *  Model Modification Routines (26)                                  *
 **********************************************************************/
PyObject *pyLSaddConstraints(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nNumaddcons;
    char      *pszConTypes = NULL, **paszConNames = NULL;
    int       *paiArows = NULL;
    double    *padAcoef = NULL;
    int       *paiAcols = NULL;
    double    *padB = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyConTypes = NULL, *pyConNames = NULL, *pyArows = NULL;
    PyArrayObject  *pyAcoef = NULL, *pyAcols = NULL, *pyB = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!O!",
                                 &pyModel,
                                 &nNumaddcons,
                                 &PyArray_Type,&pyConTypes,
                                 &PyArray_Type,&pyConNames,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyAcoef,
                                 &PyArray_Type,&pyAcols,
                                 &PyArray_Type,&pyB))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConTypes && pyConTypes->dimensions > 0)
        pszConTypes = (char *)pyConTypes->data;
    if(pyConNames && pyConNames->dimensions > 0)
        paszConNames = (char **)pyConNames->data;
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)pyArows->data;
    if(pyAcoef && pyAcoef->dimensions > 0)
        padAcoef = (double *)pyAcoef->data;
    if(pyAcols && pyAcols->dimensions > 0)
        paiAcols = (int *)pyAcols->data;
    if(pyB && pyB->dimensions > 0)
        padB = (double *)pyB->data;

    errorcode = LSaddConstraints(pModel,
                                 nNumaddcons,
                                 pszConTypes,
                                 paszConNames,
                                 paiArows,
                                 padAcoef,
                                 paiAcols,
                                 padB);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddVariables(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nNumaddvars;
    char      *pszVarTypes = NULL, **paszVarNames = NULL;
    int       *paiAcols = NULL, *panAcols = NULL;
    double    *padAcoef = NULL;
    int       *paiArows = NULL;
    double    *padC = NULL,*padL = NULL,*padU = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVarTypes = NULL, *pyVarNames = NULL, *pyiAcols = NULL;
    PyArrayObject  *pynAcols = NULL, *pyAcoef = NULL, *pyArows = NULL;
    PyArrayObject  *pyC = NULL, *pyL = NULL, *pyU = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &nNumaddvars,
                                 &PyArray_Type,&pyVarTypes,
                                 &PyArray_Type,&pyVarNames,
                                 &PyArray_Type,&pyiAcols,
                                 &PyArray_Type,&pynAcols,
                                 &PyArray_Type,&pyAcoef,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyC,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVarTypes && pyVarTypes->dimensions > 0)
        pszVarTypes = (char *)pyVarTypes->data;
    if(pyVarNames && pyVarNames->dimensions > 0)
        paszVarNames = (char **)pyVarNames->data;
    if(pyiAcols && pyiAcols->dimensions > 0)
        paiAcols = (int *)pyiAcols->data;
    if(pynAcols && pynAcols->dimensions > 0)
        panAcols = (int *)pynAcols->data;
    if(pyAcoef && pyAcoef->dimensions > 0)
        padAcoef = (double *)pyAcoef->data;
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)pyArows->data;
    if(pyC && pyC->dimensions > 0)
        padC = (double *)pyC->data;
    if(pyL && pyL->dimensions > 0)
        padL = (double *)pyL->data;
    if(pyU && pyU->dimensions > 0)
        padU = (double *)pyU->data;

    errorcode = LSaddVariables(pModel,
                               nNumaddvars,
                               pszVarTypes,
                               paszVarNames,
                               paiAcols,
                               panAcols,
                               padAcoef,
                               paiArows,
                               padC,
                               padL,
                               padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddCones(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCone;
    char      *pszConeTypes = NULL, **paszConenames = NULL;
    int       *paiConebegcol = NULL, *paiConecols = NULL;
	double   *padConeAlpha=NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyConeTypes = NULL, *pyConenames = NULL;
    PyArrayObject  *pyConebegcol = NULL, *pyConecols = NULL, *pyadConeAlpha=NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
                                 &pyModel,
                                 &nCone,
                                 &PyArray_Type,&pyConeTypes,
								 &PyArray_Type,&pyadConeAlpha,
                                 &PyArray_Type,&pyConenames,
                                 &PyArray_Type,&pyConebegcol,
                                 &PyArray_Type,&pyConecols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConeTypes && pyConeTypes->dimensions > 0)
        pszConeTypes = (char *)pyConeTypes->data;
    if(pyConenames && pyConenames->dimensions > 0)
        paszConenames = (char **)pyConenames->data;
    if(pyConebegcol && pyConebegcol->dimensions > 0)
        paiConebegcol = (int *)pyConebegcol->data;
    if(pyConecols && pyConecols->dimensions > 0)
        paiConecols = (int *)pyConecols->data;
    if(pyadConeAlpha && pyadConeAlpha->dimensions > 0)
        padConeAlpha = (double *)pyadConeAlpha->data;
    errorcode = LSaddCones(pModel,
                           nCone,
                           pszConeTypes,
						   padConeAlpha,
                           paszConenames,
                           paiConebegcol,
                           paiConecols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddSETS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSETS;
    char      *pszSETStype = NULL;
    int       *paiCARDnum = NULL, *paiSETSbegcol = NULL;
    int       *paiSETScols = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pySETStype = NULL, *pyCARDnum = NULL;
    PyArrayObject  *pySETSbegcol = NULL, *pySETScols = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &nSETS,
                                 &PyArray_Type,&pySETStype,
                                 &PyArray_Type,&pyCARDnum,
                                 &PyArray_Type,&pySETSbegcol,
                                 &PyArray_Type,&pySETScols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySETStype && pySETStype->dimensions > 0)
        pszSETStype = (char *)pySETStype->data;
    if(pyCARDnum && pyCARDnum->dimensions > 0)
        paiCARDnum = (int *)pyCARDnum->data;
    if(pySETSbegcol && pySETSbegcol->dimensions > 0)
        paiSETSbegcol = (int *)pySETSbegcol->data;
    if(pySETScols && pySETScols->dimensions > 0)
        paiSETScols = (int *)pySETScols->data;

    errorcode = LSaddSETS(pModel,
                          nSETS,
                          pszSETStype,
                          paiCARDnum,
                          paiSETSbegcol,
                          paiSETScols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddQCterms(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nQCnonzeros;
    int       *paiQCconndx = NULL;
    int       *paiQCvarndx1 = NULL, *paiQCvarndx2 = NULL;
    double    *padQCcoef = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyQCconndx = NULL, *pyQCvarndx1 = NULL;
    PyArrayObject  *pyQCvarndx2 = NULL, *pyQCcoef = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
                                 &pyModel,
                                 &nQCnonzeros,
                                 &PyArray_Type,&pyQCconndx,
                                 &PyArray_Type,&pyQCvarndx1,
                                 &PyArray_Type,&pyQCvarndx2,
                                 &PyArray_Type,&pyQCcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyQCconndx && pyQCconndx->dimensions > 0) paiQCconndx = (int *)pyQCconndx->data;
    if(pyQCvarndx1 && pyQCvarndx1->dimensions > 0) paiQCvarndx1 = (int *)pyQCvarndx1->data;
    if(pyQCvarndx2 && pyQCvarndx2->dimensions > 0) paiQCvarndx2 = (int *)pyQCvarndx2->data;
    if(pyQCcoef && pyQCcoef->dimensions > 0) padQCcoef = (double *)pyQCcoef->data;

    errorcode = LSaddQCterms(pModel,
                             nQCnonzeros,
                             paiQCconndx,
                             paiQCvarndx1,
                             paiQCvarndx2,
                             padQCcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteConstraints(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons;
    int       *paiCons = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCons = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nCons,
                                 &PyArray_Type,&pyCons))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCons && pyCons->dimensions > 0) paiCons = (int *)pyCons->data;

    errorcode = LSdeleteConstraints(pModel,
                                    nCons,
                                    paiCons);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteCones(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCones;
    int       *paiCones = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCones = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nCones,
                                 &PyArray_Type,&pyCones))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCones && pyCones->dimensions > 0) paiCones = (int *)pyCones->data;

    errorcode = LSdeleteCones(pModel,
                              nCones,
                              paiCones);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteSETS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSETS;
    int       *paiSETS = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pySETS = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nSETS,
                                 &PyArray_Type,&pySETS))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySETS && pySETS->dimensions > 0) paiSETS = (int *)pySETS->data;

    errorcode = LSdeleteSETS(pModel,
                             nSETS,
                             paiSETS);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteSemiContVars(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSCVars;
    int       *paiSCVars = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pySCVars = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nSCVars,
                                 &PyArray_Type,&pySCVars))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySCVars && pySCVars->dimensions > 0) paiSCVars = (int *)pySCVars->data;

    errorcode = LSdeleteSemiContVars(pModel,
                                     nSCVars,
                                     paiSCVars);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteVariables(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nVars;
    int       *paiVars = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVars = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nVars,
                                 &PyArray_Type,&pyVars))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVars && pyVars->dimensions > 0) paiVars = (int *)pyVars->data;

    errorcode = LSdeleteVariables(pModel,
                                  nVars,
                                  paiVars);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteQCterms(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons;
    int       *paiCons = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCons = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nCons,
                                 &PyArray_Type,&pyCons))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCons && pyCons->dimensions > 0) paiCons = (int *)pyCons->data;

    errorcode = LSdeleteQCterms(pModel,
                                nCons,
                                paiCons);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteAj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iVar1,nRows;
    int       *paiRows = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyRows = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!",
                                 &pyModel,
                                 &iVar1,
                                 &nRows,
                                 &PyArray_Type,&pyRows))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRows && pyRows->dimensions > 0) paiRows = (int *)pyRows->data;

    errorcode = LSdeleteAj(pModel,
                           iVar1,
                           nRows,
                           paiRows);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyLowerBounds(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nVars;
    int       *paiVars = NULL;
    double    *padL = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVars = NULL,*pyL = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nVars,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyL))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVars && pyVars->dimensions > 0) paiVars = (int *)pyVars->data;
    if(pyL && pyL->dimensions > 0) padL = (double *)pyL->data;

    errorcode = LSmodifyLowerBounds(pModel,
                                    nVars,
                                    paiVars,
                                    padL);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyUpperBounds(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nVars;
    int       *paiVars = NULL;
    double    *padU = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVars = NULL,*pyU = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nVars,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVars && pyVars->dimensions > 0) paiVars = (int *)pyVars->data;
    if(pyU && pyU->dimensions > 0) padU = (double *)pyU->data;

    errorcode = LSmodifyUpperBounds(pModel,
                                    nVars,
                                    paiVars,
                                    padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyRHS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons;
    int       *paiCons = NULL;
    double    *padB = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCons = NULL,*pyB = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nCons,
                                 &PyArray_Type,&pyCons,
                                 &PyArray_Type,&pyB))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCons && pyCons->dimensions > 0) paiCons = (int *)pyCons->data;
    if(pyB && pyB->dimensions > 0) padB = (double *)pyB->data;

    errorcode = LSmodifyRHS(pModel,
                            nCons,
                            paiCons,
                            padB);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyObjective(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nVars;
    int       *paiVars = NULL;
    double    *padC = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVars = NULL,*pyC = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nVars,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyC))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVars && pyVars->dimensions > 0) paiVars = (int *)pyVars->data;
    if(pyC && pyC->dimensions > 0) padC = (double *)pyC->data;

    errorcode = LSmodifyObjective(pModel,
                                  nVars,
                                  paiVars,
                                  padC);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyObjConstant(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    dObjConst;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oi",
                                 &pyModel,
                                 &dObjConst))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSmodifyObjConstant(pModel,
                                    dObjConst);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyAj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iVar1,nRows;
    int       *paiRows = NULL;
    double    *padAj = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyRows = NULL, *pyAj = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!O!",
                                 &pyModel,
                                 &iVar1,
                                 &nRows,
                                 &PyArray_Type,&pyRows,
                                 &PyArray_Type,&pyAj))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRows && pyRows->dimensions > 0) paiRows = (int *)pyRows->data;
    if(pyAj && pyAj->dimensions > 0) padAj = (double *)pyAj->data;

    errorcode = LSmodifyAj(pModel,
                           iVar1,
                           nRows,
                           paiRows,
                           padAj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyCone(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      cConeType;
    int       iConeNum,iConeNnz;
    int       *paiConeCols = NULL;
	double    dConeAlpha;

    PyObject       *pyModel;
    PyArrayObject  *pyConeCols = NULL;

    if (!PyArg_ParseTuple(args, "OciiO!d",
                                 &pyModel,
                                 &cConeType,
                                 &iConeNum,
                                 &iConeNnz,
                                 &PyArray_Type,&pyConeCols,
								 &dConeAlpha))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyConeCols && pyConeCols->dimensions > 0) paiConeCols = (int *)pyConeCols->data;

    errorcode = LSmodifyCone(pModel,
                             cConeType,
                             iConeNum,
                             iConeNnz,
                             paiConeCols,
							 dConeAlpha);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifySET(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      cSETtype;
    int       iSETnum, iSETnnz;
    int       *paiSETcols = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pySETcols = NULL;

    if (!PyArg_ParseTuple(args, "OciiO!",
                                 &pyModel,
                                 &cSETtype,
                                 &iSETnum,
                                 &iSETnnz,
                                 &PyArray_Type,&pySETcols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySETcols && pySETcols->dimensions > 0) paiSETcols = (int *)pySETcols->data;

    errorcode = LSmodifySET(pModel,
                            cSETtype,
                            iSETnum,
                            iSETnnz,
                            paiSETcols);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifySemiContVars(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSCVars;
    int       *paiSCVars = NULL;
    double    *padL = NULL,*padU = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pySCVars = NULL,*pyL = NULL,*pyU = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
                                 &pyModel,
                                 &nSCVars,
                                 &PyArray_Type,&pySCVars,
                                 &PyArray_Type,&pyL,
                                 &PyArray_Type,&pyU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySCVars && pySCVars->dimensions > 0) paiSCVars = (int *)pySCVars->data;
    if(pyL && pyL->dimensions > 0) padL = (double *)pyL->data;
    if(pyU && pyU->dimensions > 0) padU = (double *)pyU->data;

    errorcode = LSmodifySemiContVars(pModel,
                                     nSCVars,
                                     paiSCVars,
                                     padL,
                                     padU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyConstraintType(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCons;
    int       *paiCons = NULL;
    char      *pszConTypes = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCons = NULL,*pyConTypes = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nCons,
                                 &PyArray_Type,&pyCons,
                                 &PyArray_Type,&pyConTypes))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCons && pyCons->dimensions > 0)
        paiCons = (int *)pyCons->data;
    if(pyConTypes && pyConTypes->dimensions > 0)
        pszConTypes = (char *)pyConTypes->data;

    errorcode = LSmodifyConstraintType(pModel,
                                       nCons,
                                       paiCons,
                                       pszConTypes);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSmodifyVariableType(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nVars;
    int       *paiVars = NULL;
    char      *pszVarTypes = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyVars = NULL,*pyVarTypes = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nVars,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyVarTypes))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVars && pyVars->dimensions > 0)
        paiVars = (int *)pyVars->data;
    if(pyVarTypes && pyVarTypes->dimensions > 0)
        pszVarTypes = (char *)pyVarTypes->data;

    errorcode = LSmodifyVariableType(pModel,
                                     nVars,
                                     paiVars,
                                     pszVarTypes);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddNLPAj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iVar1,nRows;
    int       *paiRows = NULL;
    double    *padAj = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyRows = NULL, *pyAj = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!O!",
                                 &pyModel,
                                 &iVar1,
                                 &nRows,
                                 &PyArray_Type,&pyRows,
                                 &PyArray_Type,&pyAj))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRows && pyRows->dimensions > 0) paiRows = (int *)pyRows->data;
    if(pyAj && pyAj->dimensions > 0) padAj = (double *)pyAj->data;

    errorcode = LSaddNLPAj(pModel,
                           iVar1,
                           nRows,
                           paiRows,
                           padAj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddNLPobj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCols;
    int       *paiCols = NULL;
    double    *padColj = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCols = NULL,*pyColj = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &nCols,
                                 &PyArray_Type,&pyCols,
                                 &PyArray_Type,&pyColj))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCols && pyCols->dimensions > 0) paiCols = (int *)pyCols->data;
    if(pyColj && pyColj->dimensions > 0) padColj = (double *)pyColj->data;

    errorcode = LSaddNLPobj(pModel,
                            nCols,
                            paiCols,
                            padColj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdeleteNLPobj(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nCols;
    int       *paiCols = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyCols = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nCols,
                                 &PyArray_Type,&pyCols))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCols && pyCols->dimensions > 0) paiCols = (int *)pyCols->data;

    errorcode = LSdeleteNLPobj(pModel,
                               nCols,
                               paiCols);

    return Py_BuildValue("i",errorcode);
}

/*********************************************************************
 *   Model & Solution Analysis Routines (8)                         *
 *********************************************************************/
PyObject *pyLSgetConstraintRanges(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padDec = NULL,*padInc = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDec = NULL, *pyInc = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyDec,
                                 &PyArray_Type,&pyInc))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDec && pyDec->dimensions > 0)
        padDec = (double *)PyArray_GetPtr(pyDec,index);
    if(pyInc && pyInc->dimensions > 0)
        padInc = (double *)PyArray_GetPtr(pyInc,index);

    errorcode = LSgetConstraintRanges(pModel,
                                      padDec,
                                      padInc);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetObjectiveRanges(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padDec = NULL,*padInc = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDec = NULL, *pyInc = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyDec,
                                 &PyArray_Type,&pyInc))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDec && pyDec->dimensions > 0)
        padDec = (double *)PyArray_GetPtr(pyDec,index);
    if(pyInc && pyInc->dimensions > 0)
        padInc = (double *)PyArray_GetPtr(pyInc,index);

    errorcode = LSgetObjectiveRanges(pModel,
                                     padDec,
                                     padInc);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetBoundRanges(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padDec = NULL,*padInc = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDec = NULL, *pyInc = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyDec,
                                 &PyArray_Type,&pyInc))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDec && pyDec->dimensions > 0)
        padDec = (double *)PyArray_GetPtr(pyDec,index);
    if(pyInc && pyInc->dimensions > 0)
        padInc = (double *)PyArray_GetPtr(pyInc,index);

    errorcode = LSgetBoundRanges(pModel,
                                 padDec,
                                 padInc);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetBestBounds(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    double    *padBestL = NULL,*padBestU = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyBestL = NULL, *pyBestU = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyBestL,
                                 &PyArray_Type,&pyBestU))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyBestL && pyBestL->dimensions > 0)
        padBestL = (double *)PyArray_GetPtr(pyBestL,index);
    if(pyBestU && pyBestU->dimensions > 0)
        padBestU = (double *)PyArray_GetPtr(pyBestU,index);

    errorcode = LSgetBestBounds(pModel,
                                 padBestL,
                                 padBestU);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSfindIIS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nLevel;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oi",
                                 &pyModel,
                                 &nLevel))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSfindIIS(pModel,
                          nLevel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSfindIUS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nLevel;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oi",
                                 &pyModel,
                                 &nLevel))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSfindIUS(pModel,
                          nLevel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSfindBlockStructure(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nBlock,nType;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oii",
                                 &pyModel,
                                 &nBlock,
                                 &nType))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSfindBlockStructure(pModel,
                                     nBlock,
                                     nType);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetIIS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnSuf_r = NULL,*pnIIS_r = NULL;
    int       *paiCons = NULL,*pnSuf_c = NULL;
    int       *pnIIS_c = NULL,*paiVars = NULL;
    int       *panBnds = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySuf_r = NULL, *pyIIS_r = NULL;
    PyArrayObject  *pyCons = NULL, *pySuf_c = NULL;
    PyArrayObject  *pyIIS_c = NULL, *pyVars = NULL;
    PyArrayObject  *pyBnds = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pySuf_r,
                                 &PyArray_Type,&pyIIS_r,
                                 &PyArray_Type,&pyCons,
                                 &PyArray_Type,&pySuf_c,
                                 &PyArray_Type,&pyIIS_c,
                                 &PyArray_Type,&pyVars,
                                 &PyArray_Type,&pyBnds))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySuf_r && pySuf_r->dimensions > 0)
        pnSuf_r = (int *)PyArray_GetPtr(pySuf_r,index);
    if(pyIIS_r && pyIIS_r->dimensions > 0)
        pnIIS_r = (int *)PyArray_GetPtr(pyIIS_r,index);
    if(pyCons && pyCons->dimensions > 0)
        paiCons = (int *)PyArray_GetPtr(pyCons,index);
    if(pySuf_c && pySuf_c->dimensions > 0)
        pnSuf_c = (int *)PyArray_GetPtr(pySuf_c,index);
    if(pyIIS_c && pyIIS_c->dimensions > 0)
        pnIIS_c = (int *)PyArray_GetPtr(pyIIS_c,index);
    if(pyVars && pyVars->dimensions > 0)
        paiVars = (int *)PyArray_GetPtr(pyVars,index);
    if(pyBnds && pyBnds->dimensions > 0)
        panBnds = (int *)PyArray_GetPtr(pyBnds,index);

    errorcode = LSgetIIS(pModel,
                         pnSuf_r,
                         pnIIS_r,
                         paiCons,
                         pnSuf_c,
                         pnIIS_c,
                         paiVars,
                         panBnds);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetIUS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnSuf = NULL,*pnIUS = NULL;
    int       *paiVars = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySuf = NULL, *pyIUS = NULL;
    PyArrayObject  *pyVars = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pySuf,
                                 &PyArray_Type,&pyIUS,
                                 &PyArray_Type,&pyVars))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySuf && pySuf->dimensions > 0)
        pnSuf = (int *)PyArray_GetPtr(pySuf,index);
    if(pyIUS && pyIUS->dimensions > 0)
        pnIUS = (int *)PyArray_GetPtr(pyIUS,index);
    if(pyVars && pyVars->dimensions > 0)
        paiVars = (int *)PyArray_GetPtr(pyVars,index);

    errorcode = LSgetIUS(pModel,
                         pnSuf,
                         pnIUS,
                         paiVars);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetBlockStructure(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnBlock = NULL,*panRblock = NULL;
    int       *panCblock = NULL,*pnType = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyBlock = NULL, *pyRblock = NULL;
    PyArrayObject  *pyCblock = NULL, *pyType = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyBlock,
                                 &PyArray_Type,&pyRblock,
                                 &PyArray_Type,&pyCblock,
                                 &PyArray_Type,&pyType))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyBlock && pyBlock->dimensions > 0)
        pnBlock = (int *)PyArray_GetPtr(pyBlock,index);
    if(pyRblock && pyRblock->dimensions > 0)
        panRblock = (int *)PyArray_GetPtr(pyRblock,index);
    if(pyCblock && pyCblock->dimensions > 0)
        panCblock = (int *)PyArray_GetPtr(pyCblock,index);
    if(pyType && pyType->dimensions > 0)
        pnType = (int *)PyArray_GetPtr(pyType,index);

    errorcode = LSgetBlockStructure(pModel,
                                    pnBlock,
                                    panRblock,
                                    panCblock,
                                    pnType);

    return Py_BuildValue("i",errorcode);
}

/*********************************************************************
 *    Stochastic Programming Interface (73)                          *
 *********************************************************************/
PyObject *pyLSwriteDeteqMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFilename;
    int       nFormat,iType;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osii",
                                 &pyModel,
                                 &pszFilename,
                                 &nFormat,
                                 &iType))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteDeteqMPSFile(pModel,pszFilename,nFormat,iType);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteDeteqLINDOFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszFilename;
    int       iType;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osi",
                                 &pyModel,
                                 &pszFilename,
                                 &iType))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteDeteqLINDOFile(pModel,pszFilename,iType);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteSMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszCorefile,*pszTimefile,*pszStocfile;
    int       nCoretype;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osssi",
                                 &pyModel,
                                 &pszCorefile,
                                 &pszTimefile,
                                 &pszStocfile,
                                 &nCoretype))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteSMPSFile(pModel,
                                pszCorefile,
                                pszTimefile,
                                pszStocfile,
                                nCoretype);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadSMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszCorefile,*pszTimefile,*pszStocfile;
    int       nCoretype;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osssi",
                                 &pyModel,
                                 &pszCorefile,
                                 &pszTimefile,
                                 &pszStocfile,
                                 &nCoretype))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadSMPSFile(pModel,
                               pszCorefile,
                               pszTimefile,
                               pszStocfile,
                               nCoretype);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteSMPIFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszCorefile,*pszTimefile,*pszStocfile;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osss",
                                 &pyModel,
                                 &pszCorefile,
                                 &pszTimefile,
                                 &pszStocfile))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteSMPIFile(pModel,
                                pszCorefile,
                                pszTimefile,
                                pszStocfile);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSreadSMPIFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszCorefile,*pszTimefile,*pszStocfile;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Osss",
                                 &pyModel,
                                 &pszCorefile,
                                 &pszTimefile,
                                 &pszStocfile))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSreadSMPIFile(pModel,
                               pszCorefile,
                               pszTimefile,
                               pszStocfile);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteScenarioSolutionFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Ois",
                                 &pyModel,
                                 &jScenario,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteScenarioSolutionFile(pModel,
                                            jScenario,
                                            pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteNodeSolutionFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario,iStage;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oiis",
                                 &pyModel,
                                 &jScenario,
                                 &iStage,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteNodeSolutionFile(pModel,
                                        jScenario,
                                        iStage,
                                        pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteScenarioMPIFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Ois",
                                 &pyModel,
                                 &jScenario,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteScenarioMPIFile(pModel,
                                       jScenario,
                                       pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteScenarioMPSFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    char      *pszFname;
    int       nFormat;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oisi",
                                 &pyModel,
                                 &jScenario,
                                 &pszFname,
                                 &nFormat))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteScenarioMPSFile(pModel,
                                       jScenario,
                                       pszFname,
                                       nFormat);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSwriteScenarioLINDOFile(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    char      *pszFname;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Ois",
                                 &pyModel,
                                 &jScenario,
                                 &pszFname))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSwriteScenarioLINDOFile(pModel,
                                         jScenario,
                                         pszFname);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetModelStocDouParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iPar;
    double    dVal;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oid",
                                 &pyModel,
                                 &iPar,
                                 &dVal))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSsetModelStocDouParameter(pModel,
                                           iPar,
                                           dVal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetModelStocDouParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iPar;
    double    *pdValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iPar,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        pdValue = (double *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetModelStocDouParameter(pModel,iPar,pdValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetModelStocIntParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iPar;
    int       iVal;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oid",
                                 &pyModel,
                                 &iPar,
                                 &iVal))
    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSsetModelStocIntParameter(pModel,
                                           iPar,
                                           iVal);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetModelStocIntParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iPar;
    int       *piValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iPar,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        piValue = (int *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetModelStocIntParameter(pModel,iPar,piValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszName;
    int       *pnIndex = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyIndex = NULL;

    if (!PyArg_ParseTuple(args, "OsO!",
                                 &pyModel,
                                 &pszName,
                                 &PyArray_Type,&pyIndex))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyIndex && pyIndex->dimensions > 0)
        pnIndex = (int *)PyArray_GetPtr(pyIndex,index);

    errorcode = LSgetScenarioIndex(pModel,pszName,pnIndex);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStageIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszName;
    int       *pnIndex = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyIndex = NULL;

    if (!PyArg_ParseTuple(args, "OsO!",
                                 &pyModel,
                                 &pszName,
                                 &PyArray_Type,&pyIndex))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyIndex && pyIndex->dimensions > 0)
        pnIndex = (int *)PyArray_GetPtr(pyIndex,index);

    errorcode = LSgetStageIndex(pModel,pszName,pnIndex);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocParIndex(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    char      *pszName;
    int       *pnIndex = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyIndex = NULL;

    if (!PyArg_ParseTuple(args, "OsO!",
                                 &pyModel,
                                 &pszName,
                                 &PyArray_Type,&pyIndex))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyIndex && pyIndex->dimensions > 0)
        pnIndex = (int *)PyArray_GetPtr(pyIndex,index);

    errorcode = LSgetStocParIndex(pModel,pszName,pnIndex);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocParName(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nIndex;
    char      *pachName = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyName = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nIndex,
                                 &PyArray_Type,&pyName))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyName)
        pachName = (char *)PyArray_GetPtr(pyName,index);

    errorcode = LSgetStocParName(pModel,nIndex,pachName);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioName(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nIndex;
    char      *pachName = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyName = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nIndex,
                                 &PyArray_Type,&pyName))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyName)
        pachName = (char *)PyArray_GetPtr(pyName,index);

    errorcode = LSgetScenarioName(pModel,nIndex,pachName);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStageName(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nIndex;
    char      *pachName = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyName = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nIndex,
                                 &PyArray_Type,&pyName))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyName)
        pachName = (char *)PyArray_GetPtr(pyName,index);

    errorcode = LSgetStageName(pModel,nIndex,pachName);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocInfo(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nQuery, nParam;
    void      *pvResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!",
                                 &pyModel,
                                 &nQuery,
                                 &nParam,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSgetStocInfo(pModel,nQuery,nParam,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocCCPInfo(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nQuery, nScenarioIndex, nCPPIndex;
    void      *pvResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiiiO!",
                                 &pyModel,
                                 &nQuery,
                                 &nScenarioIndex,
                                 &nCPPIndex,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSgetStocCCPInfo(pModel,nQuery,nScenarioIndex,nCPPIndex,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadSampleSizes(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panSampleSize = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySampleSize = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pySampleSize))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySampleSize && pySampleSize->dimensions > 0)
        panSampleSize = (void *)PyArray_GetPtr(pySampleSize,index);

    errorcode = LSloadSampleSizes(pModel,panSampleSize);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadConstraintStages(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panStage = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStage = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyStage))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStage && pyStage->dimensions > 0)
        panStage = (void *)PyArray_GetPtr(pyStage,index);

    errorcode = LSloadConstraintStages(pModel,panStage);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadVariableStages(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panStage = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStage = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyStage))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStage && pyStage->dimensions > 0)
        panStage = (void *)PyArray_GetPtr(pyStage,index);

    errorcode = LSloadVariableStages(pModel,panStage);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadStageData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       numStages;
    int       *panRstage = NULL, *panCstage = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyRstage = NULL,*pyCstage = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &numStages,
                                 &PyArray_Type,&pyRstage,
                                 &PyArray_Type,&pyCstage))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRstage && pyRstage->dimensions > 0)
        panRstage = (int *)PyArray_GetPtr(pyRstage,index);
    if(pyCstage && pyCstage->dimensions > 0)
        panCstage = (int *)PyArray_GetPtr(pyCstage,index);

    errorcode = LSloadStageData(pModel,numStages,panRstage,panCstage);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadStocParData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panSparStage = NULL;
    double    *padSparValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySparStage = NULL,*pySparValue = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pySparStage,
                                 &PyArray_Type,&pySparValue))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySparStage && pySparStage->dimensions > 0)
        panSparStage = (int *)PyArray_GetPtr(pySparStage,index);
    if(pySparValue && pySparValue->dimensions > 0)
        padSparValue = (double *)PyArray_GetPtr(pySparValue,index);

    errorcode = LSloadStocParData(pModel,panSparStage,padSparValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDeteqModel(PyObject *self, PyObject *args)
{
    pLSmodel  pDeteqModel = NULL;
    pLSmodel  pModel;
    int       iDeqType;
    int       *pnErrorCode = NULL;
    npy_intp  index[1] = {0};

    PyObject        *pyModel;
    PyArrayObject   *pyErrorCode = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iDeqType,
                                 &PyArray_Type,&pyErrorCode))
    {
        return NULL;
    }

    if(pyErrorCode && pyErrorCode->dimensions > 0)
        pnErrorCode = (int *)PyArray_GetPtr(pyErrorCode,index);

    pModel = PyGetObjPtr(pyModel);
    if(pModel == NULL)
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",*pnErrorCode);
        return NULL;
    }

    pDeteqModel = LSgetDeteqModel(pModel,iDeqType,pnErrorCode);

    return PyNewObjPtr(pDeteqModel);
}

PyObject *pyLSaggregateStages(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nLength;
    int       *panScheme = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyScheme = NULL;

    if (!PyArg_ParseTuple(args, "OO!i",
                                 &pyModel,
                                 &PyArray_Type,&pyScheme,
                                 &nLength))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyScheme && pyScheme->dimensions > 0)
        panScheme = (int *)pyScheme->data;

    errorcode = LSaggregateStages(pModel,panScheme,nLength);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStageAggScheme(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnLength = NULL;
    int       *panScheme = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyScheme = NULL, *pyLength = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyScheme,
                                 &PyArray_Type,&pyLength))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyScheme && pyScheme->dimensions > 0)
        panScheme = (int *)PyArray_GetPtr(pyScheme,index);
    if(pyLength && pyLength->dimensions > 0)
        pnLength = (int *)PyArray_GetPtr(pyLength,index);

    errorcode = LSgetStageAggScheme(pModel,panScheme,pnLength);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsolveSP(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *pnStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStatus = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStatus && pyStatus->dimensions > 0)
        pnStatus = (int *)PyArray_GetPtr(pyStatus,index);

    errorcode = LSsolveSP(pModel,pnStatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsolveHS(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nSearchMethod;
    int       *pnStatus = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStatus = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nSearchMethod,
                                 &PyArray_Type,&pyStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStatus && pyStatus->dimensions > 0)
        pnStatus = (int *)PyArray_GetPtr(pyStatus,index);

    errorcode = LSsolveHS(pModel,nSearchMethod,pnStatus);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioObjective(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *pObj = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyObj  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyObj))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyObj && pyObj->dimensions > 0)
        pObj = (double *)PyArray_GetPtr(pyObj,index);

    errorcode = LSgetScenarioObjective(pModel,jScenario,pObj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNodePrimalSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario,iStage;
    double    *padX = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyX  = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!",
                                 &pyModel,
                                 &jScenario,
                                 &iStage,
                                 &PyArray_Type,&pyX))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyX && pyX->dimensions > 0)
        padX = (double *)PyArray_GetPtr(pyX,index);

    errorcode = LSgetNodePrimalSolution(pModel,jScenario,iStage,padX);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNodeDualSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario,iStage;
    double    *padY = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyY  = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!",
                                 &pyModel,
                                 &jScenario,
                                 &iStage,
                                 &PyArray_Type,&pyY))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyY && pyY->dimensions > 0)
        padY = (double *)PyArray_GetPtr(pyY,index);

    errorcode = LSgetNodeDualSolution(pModel,jScenario,iStage,padY);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNodeReducedCost(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario,iStage;
    double    *padX = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyX  = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!",
                                 &pyModel,
                                 &jScenario,
                                 &iStage,
                                 &PyArray_Type,&pyX))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyX && pyX->dimensions > 0)
        padX = (double *)PyArray_GetPtr(pyX,index);

    errorcode = LSgetNodeReducedCost(pModel,jScenario,iStage,padX);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNodeSlacks(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario,iStage;
    double    *padY = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyY  = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!",
                                 &pyModel,
                                 &jScenario,
                                 &iStage,
                                 &PyArray_Type,&pyY))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyY && pyY->dimensions > 0)
        padY = (double *)PyArray_GetPtr(pyY,index);

    errorcode = LSgetNodeSlacks(pModel,jScenario,iStage,padY);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioPrimalSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *padX = NULL;
    double    *pObj = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyX  = NULL;
    PyArrayObject  *pyObj  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyX,
                                 &PyArray_Type,&pyObj))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyX && pyX->dimensions > 0)
        padX = (double *)PyArray_GetPtr(pyX,index);
    if(pyObj && pyObj->dimensions > 0)
        pObj = (double *)PyArray_GetPtr(pyObj,index);

    errorcode = LSgetScenarioPrimalSolution(pModel,jScenario,padX,pObj);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioReducedCost(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *padD = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyD  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyD))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyD && pyD->dimensions > 0)
        padD = (double *)PyArray_GetPtr(pyD,index);

    errorcode = LSgetScenarioReducedCost(pModel,jScenario,padD);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioDualSolution(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *padY = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyY  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyY))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyY && pyY->dimensions > 0)
        padY = (double *)PyArray_GetPtr(pyY,index);

    errorcode = LSgetScenarioDualSolution(pModel,jScenario,padY);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioSlacks(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *padS = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyS  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyS))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyS && pyS->dimensions > 0)
        padS = (double *)PyArray_GetPtr(pyS,index);

    errorcode = LSgetScenarioSlacks(pModel,jScenario,padS);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetNodeListByScenario(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    int       *paiNodes = NULL, *pnNodes = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyaiNodes  = NULL,*pynNodes  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyaiNodes,
                                 &PyArray_Type,&pynNodes))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyaiNodes && pyaiNodes->dimensions > 0)
        paiNodes = (int *)PyArray_GetPtr(pyaiNodes,index);
    if(pynNodes && pynNodes->dimensions > 0)
        pnNodes = (int *)PyArray_GetPtr(pynNodes,index);

    errorcode = LSgetNodeListByScenario(pModel,jScenario,paiNodes,pnNodes);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetProbabilityByScenario(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *pdProb = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyProb  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyProb))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyProb && pyProb->dimensions > 0)
        pdProb = (double *)PyArray_GetPtr(pyProb,index);

    errorcode = LSgetProbabilityByScenario(pModel,jScenario,pdProb);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetProbabilityByNode(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iNode;
    double    *pdProb = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyProb  = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &iNode,
                                 &PyArray_Type,&pyProb))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyProb && pyProb->dimensions > 0)
        pdProb = (double *)PyArray_GetPtr(pyProb,index);

    errorcode = LSgetProbabilityByNode(pModel,iNode,pdProb);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocParData(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *paiStages = NULL;
    double    *padVals = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStages = NULL,*pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pyModel,
                                 &PyArray_Type,&pyStages,
                                 &PyArray_Type,&pyVals))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStages && pyStages->dimensions > 0)
        paiStages = (int *)PyArray_GetPtr(pyStages,index);
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)PyArray_GetPtr(pyVals,index);

    errorcode = LSgetStocParData(pModel,paiStages,padVals);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddDiscreteBlocks(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iStage, nRealzBlock, nModifyRule;
    double    *padProb = NULL;
    int       *pakStart = NULL, *paiRows = NULL;
    int       *paiCols = NULL, *paiStvs = NULL;
    double    *padVals = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyProb = NULL,*pyStart = NULL;
    PyArrayObject  *pyRows = NULL, *pyCols = NULL;
    PyArrayObject  *pyStvs = NULL,*pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!O!O!O!O!O!i",
                                 &pyModel,
                                 &iStage,
                                 &nRealzBlock,
                                 &PyArray_Type,&pyProb,
                                 &PyArray_Type,&pyStart,
                                 &PyArray_Type,&pyRows,
                                 &PyArray_Type,&pyCols,
                                 &PyArray_Type,&pyStvs,
                                 &PyArray_Type,&pyVals,
                                 &nModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyProb && pyProb->dimensions > 0)
        padProb = (double *)pyProb->data;
    if(pyStart && pyStart->dimensions > 0)
        pakStart = (int *)pyStart->data;
    if(pyRows && pyRows->dimensions > 0)
        paiRows = (int *)pyRows->data;
    if(pyCols && pyCols->dimensions > 0)
        paiCols = (int *)pyCols->data;
    if(pyStvs && pyStvs->dimensions > 0)
        paiStvs = (int *)pyStvs->data;
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)pyVals->data;

    errorcode = LSaddDiscreteBlocks(pModel,
                                    iStage,
                                    nRealzBlock,
                                    padProb,
                                    pakStart,
                                    paiRows,
                                    paiCols,
                                    paiStvs,
                                    padVals,
                                    nModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddScenario(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario, iParentScen, iStage;
    double    dProb;
    int       nElems;
    int       *paiRows = NULL, *paiCols = NULL;
    int       *paiStvs = NULL;
    double    *padVals = NULL;
    int       nModifyRule;

    PyObject       *pyModel;
    PyArrayObject  *pyRows = NULL, *pyCols = NULL;
    PyArrayObject  *pyStvs = NULL,*pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OiiidiO!O!O!O!",
                                 &pyModel,
                                 &jScenario,
                                 &iParentScen,
                                 &iStage,
                                 &dProb,
                                 &nElems,
                                 &PyArray_Type,&pyRows,
                                 &PyArray_Type,&pyCols,
                                 &PyArray_Type,&pyStvs,
                                 &PyArray_Type,&pyVals,
                                 &nModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRows && pyRows->dimensions > 0)
        paiRows = (int *)pyRows->data;
    if(pyCols && pyCols->dimensions > 0)
        paiCols = (int *)pyCols->data;
    if(pyStvs && pyStvs->dimensions > 0)
        paiStvs = (int *)pyStvs->data;
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)pyVals->data;

    errorcode = LSaddScenario(pModel,
                              jScenario,
                              iParentScen,
                              iStage,
                              dProb,
                              nElems,
                              paiRows,
                              paiCols,
                              paiStvs,
                              padVals,
                              nModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddDiscreteIndep(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iRow, jCol, iStv, nRealizations;
    double    *padProbs = NULL;
    double    *padVals = NULL;
    int       nModifyRule;

    PyObject       *pyModel;
    PyArrayObject  *pyProbs = NULL,*pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OiiiiO!O!i",
                                 &pyModel,
                                 &iRow,
                                 &jCol,
                                 &iStv,
                                 &nRealizations,
                                 &PyArray_Type,&pyProbs,
                                 &PyArray_Type,&pyVals,
                                 &nModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyProbs && pyProbs->dimensions > 0)
        padProbs = (double *)pyProbs->data;
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)pyVals->data;

    errorcode = LSaddDiscreteIndep(pModel,
                                   iRow,
                                   jCol,
                                   iStv,
                                   nRealizations,
                                   padProbs,
                                   padVals,
                                   nModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddParamDistIndep(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iRow, jCol, iStv, nDistType, nParams;
    double    *padParams = NULL;
    int       nModifyRule;

    PyObject       *pyModel;
    PyArrayObject  *pyParams= NULL;

    if (!PyArg_ParseTuple(args, "OiiiiO!i",
                                 &pyModel,
                                 &iRow,
                                 &jCol,
                                 &iStv,
                                 &nDistType,
                                 &nParams,
                                 &PyArray_Type,&pyParams,
                                 &nModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyParams && pyParams->dimensions > 0)
        padParams = (double *)pyParams->data;

    errorcode = LSaddParamDistIndep(pModel,
                                   iRow,
                                   jCol,
                                   iStv,
                                   nDistType,
                                   nParams,
                                   padParams,
                                   nModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSaddChanceConstraint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iSense, nCons;
    int       *paiCons = NULL;
    double    dPrLevel, dObjWeight;

    PyObject       *pyModel;
    PyArrayObject  *pyCons= NULL;

    if (!PyArg_ParseTuple(args, "OiiO!dd",
                                 &pyModel,
                                 &iSense,
                                 &nCons,
                                 &PyArray_Type,&pyCons,
                                 &dPrLevel,
                                 &dObjWeight))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyCons && pyCons->dimensions > 0)
        paiCons = (int *)pyCons->data;

    errorcode = LSaddChanceConstraint(pModel,
                                      iSense,
                                      nCons,
                                      paiCons,
                                      dPrLevel,
                                      dObjWeight);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetNumStages(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       numStages;

    PyObject       *pyModel;

    if (!PyArg_ParseTuple(args, "Oi",
                                 &pyModel,
                                 &numStages))

    {
        return NULL;
    }

    CHECK_MODEL;

    errorcode = LSsetNumStages(pModel,
                               numStages);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocParOutcomes(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    double    *pdValue = NULL, *padProbs = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyValue = NULL, *pyProbs = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyValue,
                                 &PyArray_Type,&pyProbs))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyValue && pyValue->dimensions > 0)
        pdValue = (double *)PyArray_GetPtr(pyValue,index);
    if(pyProbs && pyProbs->dimensions > 0)
        padProbs = (double *)PyArray_GetPtr(pyProbs,index);

    errorcode = LSgetStocParOutcomes(pModel,jScenario,pdValue,padProbs);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSloadCorrelationMatrix(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nDim, nCorrType, nQCnnz;
    int       *paiQCcols1 = NULL, *paiQCcols2 = NULL;
    double    *padQCcoef = NULL;

    PyObject       *pyModel;
    PyArrayObject  *pyQCcols1= NULL,*pyQCcols2= NULL,*pyQCcoef= NULL;

    if (!PyArg_ParseTuple(args, "OiiiO!O!O!",
                                 &pyModel,
                                 &nDim,
                                 &nCorrType,
                                 &nQCnnz,
                                 &PyArray_Type,&pyQCcols1,
                                 &PyArray_Type,&pyQCcols2,
                                 &PyArray_Type,&pyQCcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyQCcols1 && pyQCcols1->dimensions > 0)
        paiQCcols1 = (int *)pyQCcols1->data;
    if(pyQCcols2 && pyQCcols2->dimensions > 0)
        paiQCcols2 = (int *)pyQCcols2->data;
    if(pyQCcoef && pyQCcoef->dimensions > 0)
        padQCcoef = (double *)pyQCcoef->data;

    errorcode = LSloadCorrelationMatrix(pModel,
                                        nDim,
                                        nCorrType,
                                        nQCnnz,
                                        paiQCcols1,
                                        paiQCcols2,
                                        padQCcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetCorrelationMatrix(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iFlag, nCorrType;
    int       *pnQCnnz = NULL;
    int       *paiQCcols1 = NULL, *paiQCcols2 = NULL;
    double    *padQCcoef = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyQCnnz = NULL;
    PyArrayObject  *pyQCcols1= NULL,*pyQCcols2= NULL,*pyQCcoef= NULL;

    if (!PyArg_ParseTuple(args, "OiiO!O!O!O!",
                                 &pyModel,
                                 &iFlag,
                                 &nCorrType,
                                 &PyArray_Type,&pyQCnnz,
                                 &PyArray_Type,&pyQCcols1,
                                 &PyArray_Type,&pyQCcols2,
                                 &PyArray_Type,&pyQCcoef))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyQCnnz && pyQCnnz->dimensions > 0)
        pnQCnnz = (int *)PyArray_GetPtr(pyQCnnz,index);
    if(pyQCcols1 && pyQCcols1->dimensions > 0)
        paiQCcols1 = (int *)PyArray_GetPtr(pyQCcols1,index);
    if(pyQCcols2 && pyQCcols2->dimensions > 0)
        paiQCcols2 = (int *)PyArray_GetPtr(pyQCcols2,index);
    if(pyQCcoef && pyQCcoef->dimensions > 0)
        padQCcoef = (double *)PyArray_GetPtr(pyQCcoef,index);

    errorcode = LSgetCorrelationMatrix(pModel,
                                       iFlag,
                                       nCorrType,
                                       pnQCnnz,
                                       paiQCcols1,
                                       paiQCcols2,
                                       padQCcoef);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocParSample(PyObject *self, PyObject *args)
{
    pLSsample pSample = NULL;
    pLSmodel  pModel;
    int       iStv,iRow,jCol;
    int       *pnErrorCode = NULL;
    npy_intp  index[1] = {0};

    PyObject        *pyModel;
    PyArrayObject   *pyErrorCode = NULL;

    if (!PyArg_ParseTuple(args, "OiiiO!",
                                 &pyModel,
                                 &iStv,
                                 &iRow,
                                 &jCol,
                                 &PyArray_Type,&pyErrorCode))
    {
        return NULL;
    }

    if(pyErrorCode && pyErrorCode->dimensions > 0)
        pnErrorCode = (int *)PyArray_GetPtr(pyErrorCode,index);

    pModel = PyGetObjPtr(pyModel);
    if(pModel == NULL)
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",*pnErrorCode);
        return NULL;
    }

    pSample = LSgetStocParSample(pModel,iStv,iRow,jCol,pnErrorCode);

    return PyNewObjPtr(pSample);
}

PyObject *pyLSgetDiscreteBlocks(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iEvent;
    int       *pnDistType = NULL;
    int       *piStage = NULL, *pnRealzBlock = NULL;
    double    *padProbs = NULL;
    int       *piModifyRule = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDistType = NULL;
    PyArrayObject  *pyStage= NULL,*pyRealzBlock= NULL,*pyProbs= NULL;
    PyArrayObject  *pyModifyRule = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
                                 &pyModel,
                                 &iEvent,
                                 &PyArray_Type,&pyDistType,
                                 &PyArray_Type,&pyStage,
                                 &PyArray_Type,&pyRealzBlock,
                                 &PyArray_Type,&pyProbs,
                                 &PyArray_Type,&pyModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDistType && pyDistType->dimensions > 0)
        pnDistType = (int *)PyArray_GetPtr(pyDistType,index);
    if(pyStage && pyStage->dimensions > 0)
        piStage = (int *)PyArray_GetPtr(pyStage,index);
    if(pyRealzBlock && pyRealzBlock->dimensions > 0)
        pnRealzBlock = (int *)PyArray_GetPtr(pyRealzBlock,index);
    if(pyProbs && pyProbs->dimensions > 0)
        padProbs = (double *)PyArray_GetPtr(pyProbs,index);
    if(pyModifyRule && pyModifyRule->dimensions > 0)
        piModifyRule = (int *)PyArray_GetPtr(pyModifyRule,index);

    errorcode = LSgetDiscreteBlocks(pModel,
                                    iEvent,
                                    pnDistType,
                                    piStage,
                                    pnRealzBlock,
                                    padProbs,
                                    piModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDiscreteBlockOutcomes(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iEvent,iRealz;
    int       *pnRealz = NULL;
    int       *paiArows = NULL, *paiAcols = NULL;
    int       *paiStvs = NULL;
    double    *padVals = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyRealz = NULL;
    PyArrayObject  *pyArows= NULL,*pyAcols= NULL,*pyStvs= NULL;
    PyArrayObject  *pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OiiO!O!O!O!O!",
                                 &pyModel,
                                 &iEvent,
                                 &iRealz,
                                 &PyArray_Type,&pyRealz,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyAcols,
                                 &PyArray_Type,&pyStvs,
                                 &PyArray_Type,&pyVals))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyRealz && pyRealz->dimensions > 0)
        pnRealz = (int *)PyArray_GetPtr(pyRealz,index);
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)PyArray_GetPtr(pyArows,index);
    if(pyAcols && pyAcols->dimensions > 0)
        paiAcols = (int *)PyArray_GetPtr(pyAcols,index);
    if(pyStvs && pyStvs->dimensions > 0)
        paiStvs = (int *)PyArray_GetPtr(pyStvs,index);
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)PyArray_GetPtr(pyVals,index);

    errorcode = LSgetDiscreteBlockOutcomes(pModel,
                                           iEvent,
                                           iRealz,
                                           pnRealz,
                                           paiArows,
                                           paiAcols,
                                           paiStvs,
                                           padVals);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDiscreteIndep(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iEvent;
    int       *pnDistType = NULL;
    int       *piStage = NULL, *piRow = NULL;
    int       *pjCol = NULL,*piStv = NULL;
    int       *pnRealizations = NULL;
    double    *padProbs = NULL, *padVals = NULL;
    int       *piModifyRule = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDistType = NULL;
    PyArrayObject  *pyStage= NULL,*pyRow= NULL,*pyCol= NULL;
    PyArrayObject  *pyStv = NULL,*pyRealizations = NULL,*pyProbs = NULL;
    PyArrayObject  *pyVals= NULL,*pyModifyRule= NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
                                 &pyModel,
                                 &iEvent,
                                 &PyArray_Type,&pyDistType,
                                 &PyArray_Type,&pyStage,
                                 &PyArray_Type,&pyRow,
                                 &PyArray_Type,&pyCol,
                                 &PyArray_Type,&pyStv,
                                 &PyArray_Type,&pyRealizations,
                                 &PyArray_Type,&pyProbs,
                                 &PyArray_Type,&pyVals,
                                 &PyArray_Type,&pyModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDistType && pyDistType->dimensions > 0)
        pnDistType = (int *)PyArray_GetPtr(pyDistType,index);
    if(pyStage && pyStage->dimensions > 0)
        piStage = (int *)PyArray_GetPtr(pyStage,index);
    if(pyRow && pyRow->dimensions > 0)
        piRow = (int *)PyArray_GetPtr(pyRow,index);
    if(pyCol && pyCol->dimensions > 0)
        pjCol = (int *)PyArray_GetPtr(pyCol,index);
    if(pyStv && pyStv->dimensions > 0)
        piStv = (int *)PyArray_GetPtr(pyStv,index);
    if(pyRealizations && pyRealizations->dimensions > 0)
        pnRealizations = (int *)PyArray_GetPtr(pyRealizations,index);
    if(pyProbs && pyProbs->dimensions > 0)
        padProbs = (double *)PyArray_GetPtr(pyProbs,index);
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)PyArray_GetPtr(pyVals,index);
    if(pyModifyRule && pyModifyRule->dimensions > 0)
        piModifyRule = (int *)PyArray_GetPtr(pyModifyRule,index);

    errorcode = LSgetDiscreteIndep(pModel,
                                   iEvent,
                                   pnDistType,
                                   piStage,
                                   piRow,
                                   pjCol,
                                   piStv,
                                   pnRealizations,
                                   padProbs,
                                   padVals,
                                   piModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetParamDistIndep(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iEvent;
    int       *pnDistType = NULL;
    int       *piStage = NULL, *piRow = NULL;
    int       *pjCol = NULL,*piStv = NULL;
    int       *pnParams = NULL;
    double    *padParams = NULL;
    int       *piModifyRule = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyDistType = NULL;
    PyArrayObject  *pyStage= NULL,*pyRow= NULL,*pyCol= NULL;
    PyArrayObject  *pyStv = NULL,*pynParams = NULL,*pydParams = NULL;
    PyArrayObject  *pyModifyRule= NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
                                 &pyModel,
                                 &iEvent,
                                 &PyArray_Type,&pyDistType,
                                 &PyArray_Type,&pyStage,
                                 &PyArray_Type,&pyRow,
                                 &PyArray_Type,&pyCol,
                                 &PyArray_Type,&pyStv,
                                 &PyArray_Type,&pynParams,
                                 &PyArray_Type,&pydParams,
                                 &PyArray_Type,&pyModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyDistType && pyDistType->dimensions > 0)
        pnDistType = (int *)PyArray_GetPtr(pyDistType,index);
    if(pyStage && pyStage->dimensions > 0)
        piStage = (int *)PyArray_GetPtr(pyStage,index);
    if(pyRow && pyRow->dimensions > 0)
        piRow = (int *)PyArray_GetPtr(pyRow,index);
    if(pyCol && pyCol->dimensions > 0)
        pjCol = (int *)PyArray_GetPtr(pyCol,index);
    if(pyStv && pyStv->dimensions > 0)
        piStv = (int *)PyArray_GetPtr(pyStv,index);
    if(pynParams && pynParams->dimensions > 0)
        pnParams = (int *)PyArray_GetPtr(pynParams,index);
    if(pydParams && pydParams->dimensions > 0)
        padParams = (double *)PyArray_GetPtr(pydParams,index);
    if(pyModifyRule && pyModifyRule->dimensions > 0)
        piModifyRule = (int *)PyArray_GetPtr(pyModifyRule,index);

    errorcode = LSgetParamDistIndep(pModel,
                                    iEvent,
                                    pnDistType,
                                    piStage,
                                    piRow,
                                    pjCol,
                                    piStv,
                                    pnParams,
                                    padParams,
                                    piModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenario(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       jScenario;
    int       *piParentScen = NULL;
    int       *piBranchStage = NULL;
    double    *pdProb = NULL;
    int       *pnRealz = NULL,*paiArows = NULL;
    int       *paiAcols = NULL, *paiStvs = NULL;
    double    *padVals = NULL;
    int       *piModifyRule = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyParentScen = NULL;
    PyArrayObject  *pyBranchStage = NULL,*pyProb = NULL,*pyRealz = NULL;
    PyArrayObject  *pyArows = NULL,*pyAcols = NULL,*pyStvs = NULL;
    PyArrayObject  *pyVals = NULL, *pyModifyRule = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!O!O!O!O!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyParentScen,
                                 &PyArray_Type,&pyBranchStage,
                                 &PyArray_Type,&pyProb,
                                 &PyArray_Type,&pyRealz,
                                 &PyArray_Type,&pyArows,
                                 &PyArray_Type,&pyAcols,
                                 &PyArray_Type,&pyStvs,
                                 &PyArray_Type,&pyVals,
                                 &PyArray_Type,&pyModifyRule))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyParentScen && pyParentScen->dimensions > 0)
        piParentScen = (int *)PyArray_GetPtr(pyParentScen,index);
    if(pyBranchStage && pyBranchStage->dimensions > 0)
        piBranchStage = (int *)PyArray_GetPtr(pyBranchStage,index);
    if(pyProb && pyProb->dimensions > 0)
        pdProb = (double *)PyArray_GetPtr(pyProb,index);
    if(pyRealz && pyRealz->dimensions > 0)
        pnRealz = (int *)PyArray_GetPtr(pyRealz,index);
    if(pyArows && pyArows->dimensions > 0)
        paiArows = (int *)PyArray_GetPtr(pyArows,index);
    if(pyAcols && pyAcols->dimensions > 0)
        paiAcols = (int *)PyArray_GetPtr(pyAcols,index);
    if(pyStvs && pyStvs->dimensions > 0)
        paiStvs = (int *)PyArray_GetPtr(pyStvs,index);
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)PyArray_GetPtr(pyVals,index);
    if(pyModifyRule && pyModifyRule->dimensions > 0)
        piModifyRule = (int *)PyArray_GetPtr(pyModifyRule,index);

    errorcode = LSgetScenario(pModel,
                              jScenario,
                              piParentScen,
                              piBranchStage,
                              pdProb,
                              pnRealz,
                              paiArows,
                              paiAcols,
                              paiStvs,
                              padVals,
                              piModifyRule);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetChanceConstraint(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       iChance;
    int       *piSense = NULL;
    int       *pnCons = NULL, *paiCons = NULL;
    double    *pdProb = NULL, *pdObjWeight = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySense = NULL;
    PyArrayObject  *pynCons = NULL,*pyiCons = NULL,*pyProb = NULL;
    PyArrayObject  *pyObjWeight = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
                                 &pyModel,
                                 &iChance,
                                 &PyArray_Type,&pySense,
                                 &PyArray_Type,&pynCons,
                                 &PyArray_Type,&pyiCons,
                                 &PyArray_Type,&pyProb,
                                 &PyArray_Type,&pyObjWeight))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySense && pySense->dimensions > 0)
        piSense = (int *)PyArray_GetPtr(pySense,index);
    if(pynCons && pynCons->dimensions > 0)
        pnCons = (int *)PyArray_GetPtr(pynCons,index);
    if(pyiCons && pyiCons->dimensions > 0)
        paiCons = (int *)PyArray_GetPtr(pyiCons,index);
    if(pyProb && pyProb->dimensions > 0)
        pdProb = (double *)PyArray_GetPtr(pyProb,index);
    if(pyObjWeight && pyObjWeight->dimensions > 0)
        pdObjWeight = (double *)PyArray_GetPtr(pyObjWeight,index);

    errorcode = LSgetChanceConstraint(pModel,
                                      iChance,
                                      piSense,
                                      pnCons,
                                      paiCons,
                                      pdProb,
                                      pdObjWeight);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetSampleSizes(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panSampleSize = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySampleSize = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pySampleSize))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySampleSize && pySampleSize->dimensions > 0)
        panSampleSize = (int *)PyArray_GetPtr(pySampleSize,index);

    errorcode = LSgetSampleSizes(pModel,
                                 panSampleSize);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetConstraintStages(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panStage = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStage = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyStage))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStage && pyStage->dimensions > 0)
        panStage = (int *)PyArray_GetPtr(pyStage,index);

    errorcode = LSgetConstraintStages(pModel,
                                      panStage);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetVariableStages(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *panStage = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStage = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pyStage))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStage && pyStage->dimensions > 0)
        panStage = (int *)PyArray_GetPtr(pyStage,index);

    errorcode = LSgetVariableStages(pModel,
                                    panStage);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetStocRowIndices(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       *paiSrows = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pySrows = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyModel,
                                 &PyArray_Type,&pySrows))

    {
        return NULL;
    }

    CHECK_MODEL;

    if(pySrows && pySrows->dimensions > 0)
        paiSrows = (int *)PyArray_GetPtr(pySrows,index);

    errorcode = LSgetStocRowIndices(pModel,
                                    paiSrows);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetStocParRG(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSmodel   pModel;
    int        iStv, iRow, jCol;
    pLSrandGen pRG;

    PyObject       *pyModel;
    PyObject       *pyRG;


    if (!PyArg_ParseTuple(args, "OiiiO",
                                 &pyModel,
                                 &iStv,
                                 &iRow,
                                 &jCol,
                                 &pyRG))

    {
        return NULL;
    }

    CHECK_MODEL;

    CHECK_RG;

    errorcode = LSsetStocParRG(pModel,iStv,iRow,jCol,pRG);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetScenarioModel(PyObject *self, PyObject *args)
{
    pLSmodel  pSmodel = NULL;
    pLSmodel  pModel;
    int       jScenario;
    int       *pnErrorCode = NULL;
    npy_intp  index[1] = {0};

    PyObject        *pyModel;
    PyArrayObject   *pyErrorCode = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &jScenario,
                                 &PyArray_Type,&pyErrorCode))
    {
        return NULL;
    }

    if(pyErrorCode && pyErrorCode->dimensions > 0)
        pnErrorCode = (int *)PyArray_GetPtr(pyErrorCode,index);

    pModel = PyGetObjPtr(pyModel);
    if(pModel == NULL)
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",*pnErrorCode);
        return NULL;
    }

    pSmodel = LSgetScenarioModel(pModel,jScenario,pnErrorCode);

    return PyNewObjPtr(pSmodel);
}

PyObject *pyLSfreeStocMemory(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;

    PyObject  *pyModel;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyModel))
    {
        return NULL;
    }

    CHECK_MODEL;

    LSfreeStocMemory(pModel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSfreeStocHashMemory(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;

    PyObject  *pyModel;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyModel))
    {
        return NULL;
    }

    CHECK_MODEL;

    LSfreeStocHashMemory(pModel);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetModelStocParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nQuery;
    void      *pvResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nQuery,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSgetModelStocParameter(pModel,nQuery,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetModelStocParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel;
    int       nQuery;
    void      *pvResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyModel,
                                 &nQuery,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSsetModelStocParameter(pModel,nQuery,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetEnvStocParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    void      *pvValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyValue && pyValue->dimensions > 0)
        pvValue = (void *)PyArray_GetPtr(pyValue,index);

    errorcode = LSsetEnvStocParameter(pEnv,nParameter,pvValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetEnvStocParameter(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSenv    pEnv;
    int       nParameter;
    void      *pvValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pyEnv;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nParameter,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_ENV;

    if(pyValue && pyValue->dimensions > 0)
        pvValue = (void *)PyArray_GetPtr(pyValue,index);

    errorcode = LSgetEnvStocParameter(pEnv,nParameter,pvValue);

    return Py_BuildValue("i",errorcode);
}

/*********************************************************************
 *    Statistical Calculations Interface (16)                        *
 *********************************************************************/
PyObject *pyLSsampCreate(PyObject *self, PyObject *args)
{
    pLSsample pSample = NULL;
    pLSenv    pEnv;
    int       nDistType;
    int       *pnErrorCode = NULL;
    npy_intp  index[1] = {0};

    PyObject        *pyEnv;
    PyArrayObject   *pyErrorCode = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nDistType,
                                 &PyArray_Type,&pyErrorCode))
    {
        return NULL;
    }

    if(pyErrorCode && pyErrorCode->dimensions > 0)
        pnErrorCode = (int *)PyArray_GetPtr(pyErrorCode,index);

    pEnv = PyGetObjPtr(pyEnv);
    if(pEnv == NULL)
    {
        *pnErrorCode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",*pnErrorCode);
        return NULL;
    };

    pSample = LSsampCreate(pEnv,nDistType,pnErrorCode);

    return PyNewObjPtr(pSample);
}

PyObject *pyLSsampDelete(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;

    PyObject  *pySample;

    if (!PyArg_ParseTuple(args, "O", &pySample))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    errorcode = LSsampDelete(&pSample);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampSetDistrParam(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nIndex;
    double    dValue;

    PyObject  *pySample;

    if (!PyArg_ParseTuple(args, "Oid",
                                 &pySample,
                                 &nIndex,
                                 &dValue))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    errorcode = LSsampSetDistrParam(pSample,nIndex,dValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampGetDistrParam(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nIndex;
    double    *pdValue = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pyValue = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pySample,
                                 &nIndex,
                                 &PyArray_Type,&pyValue))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyValue && pyValue->dimensions > 0)
        pdValue = (double *)PyArray_GetPtr(pyValue,index);

    errorcode = LSsampGetDistrParam(pSample,nIndex,pdValue);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampEvalDistr(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nFuncType;
    double    dXval;
    double    *pdResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OidO!",
                                 &pySample,
                                 &nFuncType,
                                 &dXval,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyResult && pyResult->dimensions > 0)
        pdResult = (double *)PyArray_GetPtr(pyResult,index);

    errorcode = LSsampEvalDistr(pSample,nFuncType,dXval,pdResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampEvalDistrLI(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nFuncType;
    double    dXval;
    double    *pdResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OidO!",
                                 &pySample,
                                 &nFuncType,
                                 &dXval,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyResult && pyResult->dimensions > 0)
        pdResult = (double *)PyArray_GetPtr(pyResult,index);

    errorcode = LSsampEvalDistrLI(pSample,nFuncType,dXval,pdResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampEvalUserDistr(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nFuncType;
    double    *padXval = NULL;
    int       nDim;
    double    *pdResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pyXval = NULL, *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiO!iO!",
                                 &pySample,
                                 &nFuncType,
                                 &PyArray_Type,&pyXval,
                                 &nDim,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyXval && pyXval->dimensions > 0)
        padXval = (double *)pyXval->data;

    if(pyResult && pyResult->dimensions > 0)
        pdResult = (double *)PyArray_GetPtr(pyResult,index);

    errorcode = LSsampEvalUserDistr(pSample,nFuncType,padXval,nDim,pdResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampSetRG(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSsample  pSample;
    pLSrandGen pRG;

    PyObject   *pySample, *pyRG;

    if (!PyArg_ParseTuple(args, "OO",
                                 &pySample,
                                 &pyRG))
    {
        return NULL;
    }

    CHECK_SAMPLE;
    CHECK_RG;

    errorcode = LSsampSetRG(pSample,(void *)pRG);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampGenerate(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nMethod, nSize;

    PyObject       *pySample;


    if (!PyArg_ParseTuple(args, "OiI",
                                 &pySample,
                                 &nMethod,
                                 &nSize))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    errorcode = LSsampGenerate(pSample,nMethod,nSize);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampGetPoints(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       *pnSampSize = NULL;
    double    *pdXval = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pySampSize = NULL, *pyXval = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pySample,
                                 &PyArray_Type,&pySampSize,
                                 &PyArray_Type,&pyXval))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pySampSize && pySampSize->dimensions > 0)
        pnSampSize = (int *)PyArray_GetPtr(pySampSize,index);
    if(pyXval && pyXval->dimensions > 0)
        pdXval = (double *)PyArray_GetPtr(pyXval,index);

    errorcode = LSsampGetPoints(pSample,pnSampSize,pdXval);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampLoadPoints(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nSampSize;
    double    *pdXval = NULL;

    PyObject       *pySample;
    PyArrayObject  *pyXval = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pySample,
                                 &nSampSize,
                                 &PyArray_Type,&pyXval))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyXval && pyXval->dimensions > 0)
        pdXval = (double *)pyXval->data;

    errorcode = LSsampLoadPoints(pSample,nSampSize,pdXval);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampGetCIPoints(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       *pnSampSize = NULL;
    double    *pdXval = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pySampSize = NULL, *pyXval = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!",
                                 &pySample,
                                 &PyArray_Type,&pySampSize,
                                 &PyArray_Type,&pyXval))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pySampSize && pySampSize->dimensions > 0)
        pnSampSize = (int *)PyArray_GetPtr(pySampSize,index);
    if(pyXval && pyXval->dimensions > 0)
        pdXval = (double *)PyArray_GetPtr(pyXval,index);

    errorcode = LSsampGetCIPoints(pSample,pnSampSize,pdXval);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampLoadDiscretePdfTable(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nLen;
    double    *padProb = NULL;
    double    *padVals = NULL;

    PyObject       *pySample;
    PyArrayObject  *pyProb = NULL,*pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!",
                                 &pySample,
                                 &nLen,
                                 &PyArray_Type,&pyProb,
                                 &PyArray_Type,&pyVals))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyProb && pyProb->dimensions > 0)
        padProb = (double *)pyProb->data;
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)pyVals->data;

    errorcode = LSsampLoadDiscretePdfTable(pSample,nLen,padProb,padVals);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampGetDiscretePdfTable(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       *pnLen = NULL;
    double    *padProb = NULL;
    double    *padVals = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pyLen = NULL,*pyProb = NULL,*pyVals = NULL;

    if (!PyArg_ParseTuple(args, "OO!O!O!",
                                 &pySample,
                                 &PyArray_Type,&pyLen,
                                 &PyArray_Type,&pyProb,
                                 &PyArray_Type,&pyVals))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyLen && pyLen->dimensions > 0)
        pnLen = (int *)PyArray_GetPtr(pyLen,index);
    if(pyProb && pyProb->dimensions > 0)
        padProb = (double *)PyArray_GetPtr(pyProb,index);
    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)PyArray_GetPtr(pyVals,index);

    errorcode = LSsampGetDiscretePdfTable(pSample,pnLen,padProb,padVals);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampGetInfo(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    int       nQuery;
    void      *pvResult = NULL;
    npy_intp  index[1] = {0};

    PyObject       *pySample;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pySample,
                                 &nQuery,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSsampGetInfo(pSample,nQuery,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsampAddUserFuncArg(PyObject *self, PyObject *args)
{
    int       errorcode = LSERR_NO_ERROR;
    pLSsample pSample;
    pLSsample pSampleSource;

    PyObject  *pySample, *pySampleSource;

    if (!PyArg_ParseTuple(args, "OO",
                                 &pySample,
                                 &pySampleSource))
    {
        return NULL;
    }

    CHECK_SAMPLE;

    pSampleSource = PyGetObjPtr(pySampleSource);
    if(pSampleSource == NULL)
    {
        errorcode = LSERR_ILLEGAL_NULL_POINTER;
        printf("Illegal NULL pointer (error %d)\n",errorcode);
        return Py_BuildValue("i",errorcode);
    }

    errorcode = LSsampAddUserFuncArg(pSample,pSampleSource);

    return Py_BuildValue("i",errorcode);
}

/*********************************************************************
 *      Random Number Generation Interface()                         *
 *********************************************************************/
PyObject *pyLScreateRG(PyObject *self, PyObject *args)
{
    pLSrandGen pRG = NULL;
    pLSenv     pEnv;
    int        nMethod;

    PyObject  *pyEnv;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nMethod))
    {
        return NULL;
    }

    pEnv = PyGetObjPtr(pyEnv);
    if(pEnv == NULL)
    {
        return NULL;
    }

    pRG = LScreateRG(pEnv,nMethod);

    return PyNewObjPtr(pRG);
}

PyObject *pyLScreateRGMT(PyObject *self, PyObject *args)
{
    pLSrandGen pRG = NULL;
    pLSenv     pEnv;
    int        nMethod;

    PyObject  *pyEnv;

    if (!PyArg_ParseTuple(args, "OiO!",
                                 &pyEnv,
                                 &nMethod))
    {
        return NULL;
    }

    pEnv = PyGetObjPtr(pyEnv);
    if(pEnv == NULL)
    {
        return NULL;
    }

    pRG = LScreateRGMT(pEnv,nMethod);

    return PyNewObjPtr(pRG);
}

PyObject *pyLSgetDoubleRV(PyObject *self, PyObject *args)
{
    double     dResult;
    pLSrandGen pRG;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyRG))
    {
        return NULL;
    }

    pRG = PyGetObjPtr(pyRG);

    dResult = LSgetDoubleRV(pRG);

    return Py_BuildValue("d",dResult);
}

PyObject *pyLSgetInt32RV(PyObject *self, PyObject *args)
{
    int        nResult;
    pLSrandGen pRG;
    int        iLow, iHigh;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "Oii",
                                 &pyRG,
                                 &iLow,
                                 &iHigh))
    {
        return NULL;
    }

    pRG = PyGetObjPtr(pyRG);

    nResult = LSgetInt32RV(pRG,iLow,iHigh);

    return Py_BuildValue("i",nResult);
}

PyObject *pyLSsetRGSeed(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;
    int        nSeed;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "Oi",
                                 &pyRG,
                                 &nSeed))
    {
        return NULL;
    }

    CHECK_RG;

    LSsetRGSeed(pRG,nSeed);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSdisposeRG(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyRG))
    {
        return NULL;
    }

    CHECK_RG;

    LSdisposeRG(&pRG);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetDistrParamRG(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;
    int        iParam;
    double     dParam;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "Oid",
                                 &pyRG,
                                 &iParam,
                                 &dParam))
    {
        return NULL;
    }

    CHECK_RG;

    errorcode = LSsetDistrParamRG(pRG,iParam,dParam);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsetDistrRG(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;
    int        nDistType;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "Oi",
                                 &pyRG,
                                 &nDistType))
    {
        return NULL;
    }

    CHECK_RG;

    errorcode = LSsetDistrRG(pRG,nDistType);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetDistrRV(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;
    void       *pvResult = NULL;
    npy_intp   index[1] = {0};

    PyObject       *pyRG;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyRG,
                                 &PyArray_Type,&pyResult))
    {
        return NULL;
    }

    CHECK_RG;

    if(pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult,index);

    errorcode = LSgetDistrRV(pRG,pvResult);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetInitSeed(PyObject *self, PyObject *args)
{
    int        nSeed;
    pLSrandGen pRG;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyRG))
    {
        return NULL;
    }

    pRG = PyGetObjPtr(pyRG);

    nSeed = LSgetInitSeed(pRG);

    return Py_BuildValue("i",nSeed);
}

PyObject *pyLSgetRGNumThreads(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;
    int        *pnThreads = NULL;
    npy_intp   index[1] = {0};

    PyObject       *pyRG;
    PyArrayObject  *pyThreads = NULL;

    if (!PyArg_ParseTuple(args, "OO!",
                                 &pyRG,
                                 &PyArray_Type,&pyThreads))
    {
        return NULL;
    }

    CHECK_RG;

    if(pyThreads && pyThreads->dimensions > 0)
        pnThreads = (int *)PyArray_GetPtr(pyThreads,index);

    errorcode = LSgetRGNumThreads(pRG,pnThreads);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSfillRGBuffer(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSrandGen pRG;

    PyObject   *pyRG;

    if (!PyArg_ParseTuple(args, "O",
                                 &pyRG))
    {
        return NULL;
    }

    CHECK_RG;

    errorcode = LSfillRGBuffer(pRG);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSgetHistogram(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSmodel   pModel;
    int        nSampSize;
    double     *padVals = NULL, *padWeights = NULL;
    double     dHistLow, dHistHigh;
    int        *pnBins = NULL, *panBinCounts = NULL;
    double     *padBinProbs = NULL, *padBinLow = NULL;
    double     *padBinHigh = NULL, *padBinLeftEdge = NULL;
    double     *padBinRightEdge = NULL;
    npy_intp   index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyVals = NULL,*pyWeights = NULL;
    PyArrayObject  *pyBins = NULL,*pyBinCounts = NULL;
    PyArrayObject  *pyBinProbs = NULL,*pyBinLow = NULL;
    PyArrayObject  *pyBinHigh = NULL,*pyBinLeftEdge = NULL;
    PyArrayObject  *pyBinRightEdge = NULL;

    if (!PyArg_ParseTuple(args, "OiO!O!ddO!O!O!O!O!O!O!",
                                 &pyModel,
                                 &nSampSize,
                                 &PyArray_Type,&pyVals,
                                 &PyArray_Type,&pyWeights,
                                 &dHistLow,
                                 &dHistHigh,
                                 &PyArray_Type,&pyBins,
                                 &PyArray_Type,&pyBinCounts,
                                 &PyArray_Type,&pyBinProbs,
                                 &PyArray_Type,&pyBinLow,
                                 &PyArray_Type,&pyBinHigh,
                                 &PyArray_Type,&pyBinLeftEdge,
                                 &PyArray_Type,&pyBinRightEdge))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyVals && pyVals->dimensions > 0)
        padVals = (double *)pyVals->data;
    if(pyWeights && pyWeights->dimensions > 0)
        padWeights = (double *)pyWeights->data;

    if(pyBins && pyBins->dimensions > 0)
        pnBins = (int *)PyArray_GetPtr(pyBins,index);
    if(pyBinCounts && pyBinCounts->dimensions > 0)
        panBinCounts = (int *)PyArray_GetPtr(pyBinCounts,index);
    if(pyBinProbs && pyBinProbs->dimensions > 0)
        padBinProbs = (double *)PyArray_GetPtr(pyBinProbs,index);
    if(pyBinLow && pyBinLow->dimensions > 0)
        padBinLow = (double *)PyArray_GetPtr(pyBinLow,index);
    if(pyBinHigh && pyBinHigh->dimensions > 0)
        padBinHigh = (double *)PyArray_GetPtr(pyBinHigh,index);
    if(pyBinLeftEdge && pyBinLeftEdge->dimensions > 0)
        padBinLeftEdge = (double *)PyArray_GetPtr(pyBinLeftEdge,index);
    if(pyBinRightEdge && pyBinRightEdge->dimensions > 0)
        padBinRightEdge = (double *)PyArray_GetPtr(pyBinRightEdge,index);

    errorcode = LSgetHistogram(pModel,
                               nSampSize,
                               padVals,
                               padWeights,
                               dHistLow,
                               dHistHigh,
                               pnBins,
                               panBinCounts,
                               padBinProbs,
                               padBinLow,
                               padBinHigh,
                               padBinLeftEdge,
                               padBinRightEdge);

    return Py_BuildValue("i",errorcode);
}

PyObject *pyLSsolveMipBnp(PyObject *self, PyObject *args)
{
    int        errorcode = LSERR_NO_ERROR;
    pLSmodel   pModel;
    int        nBlock;
    char       *pszFname;
    int        *pnStatus = NULL;
    npy_intp   index[1] = {0};

    PyObject       *pyModel;
    PyArrayObject  *pyStatus = NULL;

    if (!PyArg_ParseTuple(args, "OisO!",
                                 &pyModel,
                                 &nBlock,
                                 &pszFname,
                                 &PyArray_Type,&pyStatus))
    {
        return NULL;
    }

    CHECK_MODEL;

    if(pyStatus && pyStatus->dimensions > 0)
        pnStatus = (int *)PyArray_GetPtr(pyStatus,index);

    errorcode = LSsolveMipBnp(pModel,nBlock,pszFname,pnStatus);

    return Py_BuildValue("i",errorcode);
}

/*
* @brief LSwriteMPXFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteMPXFile(pModel,pszFname,mMask)
*/
PyObject *pyLSwriteMPXFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel  pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);


    if (!PyArg_ParseTuple(args, "Osi",
        &pyModel, //pModel
        &sbuf[2],  //*pszFname

        &ibuf[3])) {
        return NULL;
    }

    CHECK_MODEL;
    LSASSERT(errorcode);
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);

    errorcode = LSwriteMPXFile(pModel, sbuf[2], ibuf[3]);


ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}



/*
* @brief LSreadMPXFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSreadMPXFile(pModel,pszFname)
*/
PyObject *pyLSreadMPXFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_MODEL;
    LSASSERT(errorcode);
    // Get C pointers
    errorcode = LSreadMPXFile(pModel
        , sbuf[2]); //*pszFname

ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSwriteVarPriorities
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteVarPriorities(pModel,pszFname,nMode)
*/
PyObject *pyLSwriteVarPriorities(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osi",
        &pyModel, //pModel
        &sbuf[2],  //*pszFname
        &ibuf[3])) { //nMode
        return NULL;
    }

    CHECK_MODEL;
    LSASSERT(errorcode);
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSwriteVarPriorities(pModel
        , sbuf[2] //*pszFname
        , ibuf[3]); //nMode

ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSwriteNLSolution
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteNLSolution(pModel,pszFname)
*/
PyObject *pyLSwriteNLSolution(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_MODEL;  LSASSERT(errorcode);
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSwriteNLSolution(pModel
        , sbuf[2]); //*pszFname

ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSwriteTunerParameters
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteTunerParameters(pEnv,szFile,jInstance,mCriterion)
*/
PyObject *pyLSwriteTunerParameters(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osii",
        &pyEnv, //pEnv
        &sbuf[2],  //*szFile
        &ibuf[3], //jInstance
        &ibuf[4])) { //mCriterion
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSwriteTunerParameters(pEnv
        , sbuf[2] //*szFile
        , ibuf[3] //jInstance
        , ibuf[4]); //mCriterion

    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSwriteTunerConfigString
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteTunerConfigString(pEnv,szJsonString,szJsonFile)
*/
PyObject *pyLSwriteTunerConfigString(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oss",
        &pyEnv, //pEnv
        &sbuf[2],  //*szJsonString
        &sbuf[3])) {  //*szJsonFile
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSwriteTunerConfigString(pEnv
        , sbuf[2] //*szJsonString
        , sbuf[3]); //*szJsonFile

    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSwriteParameterAsciiDoc
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteParameterAsciiDoc(pEnv,pszFileName)
*/
PyObject *pyLSwriteParameterAsciiDoc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*pszFileName
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSwriteParameterAsciiDoc(pEnv
        , sbuf[2]); //*pszFileName

    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSwriteEnvParameter
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteEnvParameter(pEnv,pszFname)
*/
PyObject *pyLSwriteEnvParameter(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSwriteEnvParameter(pEnv
        , sbuf[2]); //*pszFname

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSwriteDualLINDOFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSwriteDualLINDOFile(pModel,pszFname,nObjSense)
*/
PyObject *pyLSwriteDualLINDOFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osi",
        &pyModel, //pModel
        &sbuf[2],  //*pszFname
        &ibuf[3])) { //nObjSense
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSwriteDualLINDOFile(pModel
        , sbuf[2] //*pszFname
        , ibuf[3]); //nObjSense

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSaddTunerInstance
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddTunerInstance(pEnv,szFile)
*/
PyObject *pyLSaddTunerInstance(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*szFile
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSaddTunerInstance(pEnv
        , sbuf[2]); //*szFile

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSaddTunerOption
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddTunerOption(pEnv,szKey,dValue)
*/
PyObject *pyLSaddTunerOption(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osd",
        &pyEnv, //pEnv
        &sbuf[2],  //*szKey
        &dbuf[3])) { //dValue
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSaddTunerOption(pEnv
        , sbuf[2] //*szKey
        , dbuf[3]); //dValue

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSaddTunerZDynamic
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddTunerZDynamic(pEnv,iParam)
*/
PyObject *pyLSaddTunerZDynamic(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oi",
        &pyEnv, //pEnv
        &ibuf[2])) { //iParam
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSaddTunerZDynamic(pEnv
        , ibuf[2]); //iParam

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSaddTunerZStatic
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddTunerZStatic(pEnv,jGroupId,iParam,dValue)
*/
PyObject *pyLSaddTunerZStatic(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oiid",
        &pyEnv, //pEnv
        &ibuf[2], //jGroupId
        &ibuf[3], //iParam
        &dbuf[4])) { //dValue
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSaddTunerZStatic(pEnv
        , ibuf[2] //jGroupId
        , ibuf[3] //iParam
        , dbuf[4]); //dValue

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSclearTuner
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSclearTuner(pEnv)
*/
PyObject *pyLSclearTuner(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyEnv)) { //pEnv
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSclearTuner(pEnv);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSdisplayTunerResults
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdisplayTunerResults(pEnv)
*/
PyObject *pyLSdisplayTunerResults(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyEnv)) { //pEnv
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSdisplayTunerResults(pEnv);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetTunerConfigString
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetTunerConfigString(pEnv,pszJsonString)
*/
PyObject *pyLSgetTunerConfigString(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyEnv, //pEnv
        &PyArray_Type,&pyArr[2])) {  //**pszJsonString
        return NULL;
    }

    CHECK_ENV;

    if (pyArr[2])
        svecptr[2] = (char *)PyArray_GetPtr(pyArr[2], index);

    // Get C pointers
    errorcode = LSgetTunerConfigString(pEnv
        ,&sbuf[2]); //**pszJsonString
    strcpy(svecptr[2], sbuf[2]);

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetTunerOption
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetTunerOption(pEnv,szkey,pdval)
*/
PyObject *pyLSgetTunerOption(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OsO!",
        &pyEnv, //pEnv
        &sbuf[2],  //*szkey
        &PyArray_Type, &pyArr[3])) {  //*pdval
        return NULL;
    }

    CHECK_ENV;

    if (pyArr[3])
        dvecptr[3] = (double *)PyArray_GetPtr(pyArr[3], index);

    // Get C pointers
    errorcode = LSgetTunerOption(pEnv
        , sbuf[2] //*szkey
        , dvecptr[3]); //*pdval

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetTunerResult
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetTunerResult(pEnv,szkey,jInstance,kConfig,pdval)
*/
PyObject *pyLSgetTunerResult(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OsiiO!",
        &pyEnv, //pEnv
        &sbuf[2],  //*szkey
        &ibuf[3], //jInstance
        &ibuf[4], //kConfig
        &PyArray_Type, &pyArr[5])) {  //*pdval
        return NULL;
    }

    CHECK_ENV;

    D_GET_VECPTR(5);

    // Get C pointers
    errorcode = LSgetTunerResult(pEnv
        , sbuf[2] //*szkey
        , ibuf[3] //jInstance
        , ibuf[4] //kConfig
        , dvecptr[5]); //*pdval

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetTunerSpace
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetTunerSpace(pEnv,panParamId,numParam)
*/
PyObject *pyLSgetTunerSpace(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!",
        &pyEnv, //pEnv
        &PyArray_Type, &pyArr[2],  //*panParamId
        &PyArray_Type, &pyArr[3])) {  //*numParam
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*panParamId

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*numParam

    errorcode = LSgetTunerSpace(pEnv
        , ivecptr[2] //*panParamId
        , ivecptr[3]); //*numParam


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSgetTunerStrOption
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetTunerStrOption(pEnv,szkey,szval)
*/
PyObject *pyLSgetTunerStrOption(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oss",
        &pyEnv, //pEnv
        &sbuf[2],  //*szkey
        &sbuf[3])) {  //*szval
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSgetTunerStrOption(pEnv
        , sbuf[2] //*szkey
        , sbuf[3]); //*szval

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadTunerConfigFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadTunerConfigFile(pEnv,szJsonFile)
*/
PyObject *pyLSloadTunerConfigFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*szJsonFile
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSloadTunerConfigFile(pEnv
        , sbuf[2]); //*szJsonFile

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadTunerConfigString
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadTunerConfigString(pEnv,szJsonString)
*/
PyObject *pyLSloadTunerConfigString(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*szJsonString
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSloadTunerConfigString(pEnv
        , sbuf[2]); //*szJsonString

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSprintTuner
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSprintTuner(pEnv)
*/
PyObject *pyLSprintTuner(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyEnv)) { //pEnv
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSprintTuner(pEnv);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSresetTuner
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSresetTuner(pEnv)
*/
PyObject *pyLSresetTuner(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyEnv)) { //pEnv
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSresetTuner(pEnv);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSrunTuner
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSrunTuner(pEnv)
*/
PyObject *pyLSrunTuner(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyEnv)) { //pEnv
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSrunTuner(pEnv);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSrunTunerFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSrunTunerFile(pEnv,szJsonFile)
*/
PyObject *pyLSrunTunerFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*szJsonFile
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSrunTunerFile(pEnv
        , sbuf[2]); //*szJsonFile

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSrunTunerString
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSrunTunerString(pEnv,szJsonString)
*/
PyObject *pyLSrunTunerString(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyEnv, //pEnv
        &sbuf[2])) {  //*szJsonString
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSrunTunerString(pEnv
        , sbuf[2]); //*szJsonString

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetTunerOption
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetTunerOption(pEnv,szKey,dval)
*/
PyObject *pyLSsetTunerOption(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osd",
        &pyEnv, //pEnv
        &sbuf[2],  //*szKey
        &dbuf[3])) { //dval
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSsetTunerOption(pEnv
        , sbuf[2] //*szKey
        , dbuf[3]); //dval

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetTunerStrOption
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetTunerStrOption(pEnv,szKey,szval)
*/
PyObject *pyLSsetTunerStrOption(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oss",
        &pyEnv, //pEnv
        &sbuf[2],  //*szKey
        &sbuf[3])) {  //*szval
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSsetTunerStrOption(pEnv
        , sbuf[2] //*szKey
        , sbuf[3]); //*szval

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSaddQCShift
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddQCShift(pModel,iRow,dShift)
*/
PyObject *pyLSaddQCShift(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oid",
        &pyModel, //pModel
        &ibuf[2], //iRow
        &dbuf[3])) { //dShift
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSaddQCShift(pModel
        , ibuf[2] //iRow
        , dbuf[3]); //dShift

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetQCShift
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetQCShift(pModel,iRow,pdShift)
*/
PyObject *pyLSgetQCShift(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel, //pModel
        &ibuf[2], //iRow
        &PyArray_Type, &pyArr[3])) {  //*pdShift
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);

    D_GET_VECPTR(3);

    // Get C pointers
    errorcode = LSgetQCShift(pModel
        , ibuf[2] //iRow
        , dvecptr[3]); //*pdShift

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSresetQCShift
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSresetQCShift(pModel,iRow)
*/
PyObject *pyLSresetQCShift(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oi",
        &pyModel, //pModel
        &ibuf[2])) { //iRow
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSresetQCShift(pModel
        , ibuf[2]); //iRow

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSreadCBFFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSreadCBFFile(pModel,pszFname)
*/
PyObject *pyLSreadCBFFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSreadCBFFile(pModel
        , sbuf[2]); //*pszFname

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSreadNLFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSreadNLFile(pModel,pszFname)
*/
PyObject *pyLSreadNLFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSreadNLFile(pModel
        , sbuf[2]); //*pszFname

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSreadSDPAFile
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSreadSDPAFile(pModel,pszFname)
*/
PyObject *pyLSreadSDPAFile(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSreadSDPAFile(pModel
        , sbuf[2]); //*pszFname

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsolveFileLP
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsolveFileLP(pModel,szFileNameMPS,szFileNameSol,nNoOfColsEvaluatedPerSet,nNoOfColsSelectedPerSet,nTimeLimitSec,pnSolStatusParam,pnNoOfConsMps)
*/
PyObject *pyLSsolveFileLP(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);
    errorcode = LSERR_NOT_SUPPORTED;
    return Py_BuildValue(osig, errorcode);
}

/*
* @brief LSgetProfilerContext
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetProfilerContext(pModel,mContext)
*/
PyObject *pyLSgetProfilerContext(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "s";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oi",
        &pyModel, //pModel
        &ibuf[2])) { //mContext
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    sbuf[0] = LSgetProfilerContext(pModel
        , ibuf[2]); //mContext

    //ErrorReturn:
    return Py_BuildValue(osig, sbuf[0]);

}

/*
* @brief LSgetProfilerInfo
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetProfilerInfo(pModel,mContext,pnCalls,pdElapsedTime)
*/
PyObject *pyLSgetProfilerInfo(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!",
        &pyModel, //pModel
        &ibuf[2], //mContext
        &PyArray_Type, &pyArr[3],  //*pnCalls
        &PyArray_Type, &pyArr[4])) {  //*pdElapsedTime
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);

    I_GET_VECPTR(3);
    D_GET_VECPTR(4);

    // Get C pointers
    errorcode = LSgetProfilerInfo(pModel
        , ibuf[2] //mContext
        , ivecptr[3] //*pnCalls
        , dvecptr[4]); //*pdElapsedTime

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSaddEmptySpacesAcolumns
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddEmptySpacesAcolumns(pModel,paiColnnz)
*/
PyObject *pyLSaddEmptySpacesAcolumns(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*paiColnnz
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)pyArr[2]->data;  //*paiColnnz

    errorcode = LSaddEmptySpacesAcolumns(pModel
        , ivecptr[2]); //*paiColnnz

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSaddEmptySpacesNLPAcolumns
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddEmptySpacesNLPAcolumns(pModel,paiColnnz)
*/
PyObject *pyLSaddEmptySpacesNLPAcolumns(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*paiColnnz
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)pyArr[2]->data;  //*paiColnnz

    errorcode = LSaddEmptySpacesNLPAcolumns(pModel
        , ivecptr[2]); //*paiColnnz

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSaddObjPool
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSaddObjPool(pModel,padC,mObjSense,mRank,dRelOptTol)
*/
PyObject *pyLSaddObjPool(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!iid",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*padC
        &ibuf[3], //mObjSense
        &ibuf[4], //mRank
        &dbuf[5])) { //dRelOptTol
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        dvecptr[2] = (double*)pyArr[2]->data;  //*padC

    errorcode = LSaddObjPool(pModel
        , dvecptr[2] //*padC
        , ibuf[3] //mObjSense
        , ibuf[4] //mRank
        , dbuf[5]); //dRelOptTol

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSapplyLtf
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSapplyLtf(pModel,panNewColIdx,panNewRowIdx,panNewColPos,panNewRowPos,nMode)
*/
PyObject *pyLSapplyLtf(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!i",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*panNewColIdx
        &PyArray_Type, &pyArr[3],  //*panNewRowIdx
        &PyArray_Type, &pyArr[4],  //*panNewColPos
        &PyArray_Type, &pyArr[5],  //*panNewRowPos
        &ibuf[6])) { //nMode
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)pyArr[2]->data;  //*panNewColIdx

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)pyArr[3]->data;  //*panNewRowIdx

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)pyArr[4]->data;  //*panNewColPos

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)pyArr[5]->data;  //*panNewRowPos

    errorcode = LSapplyLtf(pModel
        , ivecptr[2] //*panNewColIdx
        , ivecptr[3] //*panNewRowIdx
        , ivecptr[4] //*panNewColPos
        , ivecptr[5] //*panNewRowPos
        , ibuf[6]); //nMode

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSbnbSolve
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSbnbSolve(pModel,pszFname)
*/
PyObject *pyLSbnbSolve(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszFname
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSbnbSolve(pModel
        , sbuf[2]); //*pszFname

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSbuildStringData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSbuildStringData(pModel)
*/
PyObject *pyLSbuildStringData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSbuildStringData(pModel);

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LScalcConFunc
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LScalcConFunc(pModel,iRow,padPrimal,padSlacks)
*/
PyObject *pyLScalcConFunc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!",
        &pyModel, //pModel
        &ibuf[2], //iRow
        &PyArray_Type, &pyArr[3],  //*padPrimal
        &PyArray_Type, &pyArr[4])) {  //*padSlacks
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    D_VECDATA(3);
    D_GET_VECPTR(4);

    errorcode = LScalcConFunc(pModel
        , ibuf[2] //iRow
        , dvecptr[3] //*padPrimal
        , dvecptr[4]); //*padSlacks

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LScalcConGrad
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LScalcConGrad(pModel,irow,padPrimal,nParList,paiParList,padParGrad)
*/
PyObject *pyLScalcConGrad(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!iO!O!",
        &pyModel, //pModel
        &ibuf[2], //irow
        &PyArray_Type, &pyArr[3],  //*padPrimal
        &ibuf[4], //nParList
        &PyArray_Type, &pyArr[5],  //*paiParList
        &PyArray_Type, &pyArr[6])) {  //*padParGrad
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    D_VECDATA(3);
    D_VECDATA(5);

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        dvecptr[6] = (double*)PyArray_GetPtr(pyArr[6], index); //*padParGrad

    errorcode = LScalcConGrad(pModel
        , ibuf[2] //irow
        , dvecptr[3] //*padPrimal
        , ibuf[4] //nParList
        , ivecptr[5] //*paiParList
        , dvecptr[6]); //*padParGrad

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LScalcObjFunc
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LScalcObjFunc(pModel,padPrimal,pdObjval)
*/
PyObject *pyLScalcObjFunc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*padPrimal
        &PyArray_Type, &pyArr[3])) {  //*pdObjval
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    D_VECDATA(2);
    D_GET_VECPTR(3);

    errorcode = LScalcObjFunc(pModel
        , dvecptr[2] //*padPrimal
        , dvecptr[3]); //*pdObjval

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LScalcObjGrad
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LScalcObjGrad(pModel,padPrimal,nParList,paiParList,padParGrad)
*/
PyObject *pyLScalcObjGrad(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!iO!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*padPrimal
        &ibuf[3], //nParList
        &PyArray_Type, &pyArr[4],  //*paiParList
        &PyArray_Type, &pyArr[5])) {  //*padParGrad
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    D_VECDATA(2);

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)pyArr[4]->data;  //*paiParList

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        dvecptr[5] = (double*)PyArray_GetPtr(pyArr[5], index); //*padParGrad

    errorcode = LScalcObjGrad(pModel
        , dvecptr[2] //*padPrimal
        , ibuf[3] //nParList
        , ivecptr[4] //*paiParList
        , dvecptr[5]); //*padParGrad

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LScheckQterms
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LScheckQterms(pModel,nCons,paiCons,paiType)
*/
PyObject *pyLScheckQterms(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!",
        &pyModel, //pModel
        &ibuf[2], //nCons
        &PyArray_Type, &pyArr[3],  //*paiCons
        &PyArray_Type, &pyArr[4])) {  //*paiType
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_GET_VECPTR(3);
    I_GET_VECPTR(4);

    errorcode = LScheckQterms(pModel
        , ibuf[2] //nCons
        , ivecptr[3] //*paiCons
        , ivecptr[4]); //*paiType

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSdeduceStages
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdeduceStages(pModel,nMaxStage,panRowStagse,panColStages,panSparStage)
*/
PyObject *pyLSdeduceStages(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!O!",
        &pyModel, //pModel
        &ibuf[2], //nMaxStage
        &PyArray_Type, &pyArr[3],  //*panRowStagse
        &PyArray_Type, &pyArr[4],  //*panColStages
        &PyArray_Type, &pyArr[5])) {  //*panSparStage
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*panRowStagse

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*panColStages

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*panSparStage

    errorcode = LSdeduceStages(pModel
        , ibuf[2] //nMaxStage
        , ivecptr[3] //*panRowStagse
        , ivecptr[4] //*panColStages
        , ivecptr[5]); //*panSparStage


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSdeleteStringData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdeleteString(pModel)
*/
PyObject *pyLSdeleteString(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSdeleteString(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSdeleteStringData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdeleteStringData(pModel)
*/
PyObject *pyLSdeleteStringData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSdeleteStringData(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSdisplayBlockStructure
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdisplayBlockStructure(pModel,pnBlock,panNewColIdx,panNewRowIdx,panNewColPos,panNewRowPos)
*/
PyObject *pyLSdisplayBlockStructure(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnBlock
        &PyArray_Type, &pyArr[3],  //*panNewColIdx
        &PyArray_Type, &pyArr[4],  //*panNewRowIdx
        &PyArray_Type, &pyArr[5],  //*panNewColPos
        &PyArray_Type, &pyArr[6])) {  //*panNewRowPos
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*pnBlock

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*panNewColIdx

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*panNewRowIdx

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*panNewColPos

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        ivecptr[6] = (int*)PyArray_GetPtr(pyArr[6], index); //*panNewRowPos

    errorcode = LSdisplayBlockStructure(pModel
        , ivecptr[2] //*pnBlock
        , ivecptr[3] //*panNewColIdx
        , ivecptr[4] //*panNewRowIdx
        , ivecptr[5] //*panNewColPos
        , ivecptr[6]); //*panNewRowPos


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSdoBTRAN
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdoBTRAN(pModel,pcYnz,paiY,padY,pcXnz,paiX,padX)
*/
PyObject *pyLSdoBTRAN(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pcYnz
        &PyArray_Type, &pyArr[3],  //*paiY
        &PyArray_Type, &pyArr[4],  //*padY
        &PyArray_Type, &pyArr[5],  //*pcXnz
        &PyArray_Type, &pyArr[6],  //*paiX
        &PyArray_Type, &pyArr[7])) {  //*padX
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_VECDATA(2);
    I_VECDATA(3);
    D_VECDATA(4);

    I_GET_VECPTR(5);
    I_GET_VECPTR(6);
    if (pyArr[7] && pyArr[7]->dimensions > 0)
        dvecptr[7] = (double*)PyArray_GetPtr(pyArr[7], index); //*padX

    errorcode = LSdoBTRAN(pModel
        , ivecptr[2] //*pcYnz
        , ivecptr[3] //*paiY
        , dvecptr[4] //*padY
        , ivecptr[5] //*pcXnz
        , ivecptr[6] //*paiX
        , dvecptr[7]); //*padX

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSdoFTRAN
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSdoFTRAN(pModel,pcYnz,paiY,padY,pcXnz,paiX,padX)
*/
PyObject *pyLSdoFTRAN(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pcYnz
        &PyArray_Type, &pyArr[3],  //*paiY
        &PyArray_Type, &pyArr[4],  //*padY
        &PyArray_Type, &pyArr[5],  //*pcXnz
        &PyArray_Type, &pyArr[6],  //*paiX
        &PyArray_Type, &pyArr[7])) {  //*padX
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_VECDATA(2);
    I_VECDATA(3);
    D_VECDATA(4);

    I_GET_VECPTR(5);
    I_GET_VECPTR(6);
    if (pyArr[7] && pyArr[7]->dimensions > 0)
        dvecptr[7] = (double*)PyArray_GetPtr(pyArr[7], index); //*padX

    errorcode = LSdoFTRAN(pModel
        , ivecptr[2] //*pcYnz
        , ivecptr[3] //*paiY
        , dvecptr[4] //*padY
        , ivecptr[5] //*pcXnz
        , ivecptr[6] //*paiX
        , dvecptr[7]); //*padX

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfindLtf
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfindLtf(pModel,panNewColIdx,panNewRowIdx,panNewColPos,panNewRowPos)
*/
PyObject *pyLSfindLtf(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*panNewColIdx
        &PyArray_Type, &pyArr[3],  //*panNewRowIdx
        &PyArray_Type, &pyArr[4],  //*panNewColPos
        &PyArray_Type, &pyArr[5])) {  //*panNewRowPos
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*panNewColIdx

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*panNewRowIdx

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*panNewColPos

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*panNewRowPos

    errorcode = LSfindLtf(pModel
        , ivecptr[2] //*panNewColIdx
        , ivecptr[3] //*panNewRowIdx
        , ivecptr[4] //*panNewColPos
        , ivecptr[5]); //*panNewRowPos


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfindSymmetry
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfindSymmetry(pModel,pnerrorcode)
*/
PyObject *pyLSfindSymmetry(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    void *ptr;

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*pnerrorcode
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);

    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int *)PyArray_GetPtr(pyArr[2], index);

    // Get C pointers
    ptr = LSfindSymmetry(pModel
        , ivecptr[2]); //*pnerrorcode

    //ErrorReturn:
    return PyNewObjPtr(ptr);


}

/*
* @brief LSfreeGOPSolutionMemory
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfreeGOPSolutionMemory(pModel)
*/
PyObject *pyLSfreeGOPSolutionMemory(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    LSfreeGOPSolutionMemory(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfreeHashMemory
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfreeHashMemory(pModel)
*/
PyObject *pyLSfreeHashMemory(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    LSfreeHashMemory(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfreeMIPSolutionMemory
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfreeMIPSolutionMemory(pModel)
*/
PyObject *pyLSfreeMIPSolutionMemory(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    LSfreeMIPSolutionMemory(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfreeObjPool
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfreeObjPool(pModel)
*/
PyObject *pyLSfreeObjPool(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSfreeObjPool(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfreeSolutionMemory
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfreeSolutionMemory(pModel)
*/
PyObject *pyLSfreeSolutionMemory(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    LSfreeSolutionMemory(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSfreeSolverMemory
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSfreeSolverMemory(pModel)
*/
PyObject *pyLSfreeSolverMemory(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    LSfreeSolverMemory(pModel);

        //ErrorReturn:
        return Py_BuildValue(osig, errorcode);

}

PyObject *pyLSdeleteSymmetry(PyObject *self, PyObject *args)
{
    DCL_BUF(20);
    PyObject  *pyObj;
    void *ptr = NULL;
    npy_intp  index[1] = { 0 };

    ZERO_BUF(20);
    if (!PyArg_ParseTuple(args, "O", &pyObj))
    {
        return NULL;
    }

    CHECK_OBJ_NO_FAIL(ptr, pyObj)

    errorcode = LSdeleteSymmetry(ptr);

    return Py_BuildValue("i", errorcode);
}


/*
* @brief LSgetALLDIFFData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetALLDIFFData(pModel,pinALLDIFF,paiAlldiffDim,paiAlldiffL,paiAlldiffU,paiAlldiffBeg,paiAlldiffVar)
*/
PyObject *pyLSgetALLDIFFData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pinALLDIFF
        &PyArray_Type, &pyArr[3],  //*paiAlldiffDim
        &PyArray_Type, &pyArr[4],  //*paiAlldiffL
        &PyArray_Type, &pyArr[5],  //*paiAlldiffU
        &PyArray_Type, &pyArr[6],  //*paiAlldiffBeg
        &PyArray_Type, &pyArr[7])) {  //*paiAlldiffVar
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*pinALLDIFF

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*paiAlldiffDim

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*paiAlldiffL

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*paiAlldiffU

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        ivecptr[6] = (int*)PyArray_GetPtr(pyArr[6], index); //*paiAlldiffBeg

    if (pyArr[7] && pyArr[7]->dimensions > 0)
        ivecptr[7] = (int*)PyArray_GetPtr(pyArr[7], index); //*paiAlldiffVar

    errorcode = LSgetALLDIFFData(pModel
        , ivecptr[2] //*pinALLDIFF
        , ivecptr[3] //*paiAlldiffDim
        , ivecptr[4] //*paiAlldiffL
        , ivecptr[5] //*paiAlldiffU
        , ivecptr[6] //*paiAlldiffBeg
        , ivecptr[7]); //*paiAlldiffVar


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetALLDIFFDatai
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetALLDIFFDatai(pModel,iALLDIFF,piAlldiffDim,piAlldiffL,piAlldiffU,paiAlldiffVar)
*/
PyObject *pyLSgetALLDIFFDatai(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!",
        &pyModel, //pModel
        &ibuf[2], //iALLDIFF
        &PyArray_Type, &pyArr[3],  //*piAlldiffDim
        &PyArray_Type, &pyArr[4],  //*piAlldiffL
        &PyArray_Type, &pyArr[5],  //*piAlldiffU
        &PyArray_Type, &pyArr[6])) {  //*paiAlldiffVar
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*piAlldiffDim

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*piAlldiffL

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*piAlldiffU

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        ivecptr[6] = (int*)PyArray_GetPtr(pyArr[6], index); //*paiAlldiffVar

    errorcode = LSgetALLDIFFDatai(pModel
        , ibuf[2] //iALLDIFF
        , ivecptr[3] //*piAlldiffDim
        , ivecptr[4] //*piAlldiffL
        , ivecptr[5] //*piAlldiffU
        , ivecptr[6]); //*paiAlldiffVar


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSgetDimensions
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetDimensions(pModel,pnVars,pnCons,pnCones,pnAnnz,pnQCnnz,pnConennz,pnNLPnnz,pnNLPobjnnz,pnVarNamelen,pnConNamelen,pnConeNamelen)
*/
PyObject *pyLSgetDimensions(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    int k;

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnVars
        &PyArray_Type, &pyArr[3],  //*pnCons
        &PyArray_Type, &pyArr[4],  //*pnCones
        &PyArray_Type, &pyArr[5],  //*pnAnnz
        &PyArray_Type, &pyArr[6],  //*pnQCnnz
        &PyArray_Type, &pyArr[7],  //*pnConennz
        &PyArray_Type, &pyArr[8],  //*pnNLPnnz
        &PyArray_Type, &pyArr[9],  //*pnNLPobjnnz
        &PyArray_Type, &pyArr[10],  //*pnVarNamelen
        &PyArray_Type, &pyArr[11],  //*pnConNamelen
        &PyArray_Type, &pyArr[12])) {  //*pnConeNamelen
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);


    for (k = 2; k <= 12; k++) {
        I_GET_VECPTR(k);
    }

    // Get C pointers
    errorcode = LSgetDimensions(pModel
        , ivecptr[2] //*pnVars
        , ivecptr[3] //*pnCons
        , ivecptr[4] //*pnCones
        , ivecptr[5] //*pnAnnz
        , ivecptr[6] //*pnQCnnz
        , ivecptr[7] //*pnConennz
        , ivecptr[8] //*pnNLPnnz
        , ivecptr[9] //*pnNLPobjnnz
        , ivecptr[10] //*pnVarNamelen
        , ivecptr[11] //*pnConNamelen
        , ivecptr[12]); //*pnConeNamelen

      //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetDualMIPsolution
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetDualMIPsolution(pModel,padPrimal,padDual,padRedcosts,panCstatus,panRstatus)
*/
PyObject *pyLSgetDualMIPsolution(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*padPrimal
        &PyArray_Type, &pyArr[3],  //*padDual
        &PyArray_Type, &pyArr[4],  //*padRedcosts
        &PyArray_Type, &pyArr[5],  //*panCstatus
        &PyArray_Type, &pyArr[6])) {  //*panRstatus
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        dvecptr[2] = (double*)PyArray_GetPtr(pyArr[2], index); //*padPrimal

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        dvecptr[3] = (double*)PyArray_GetPtr(pyArr[3], index); //*padDual

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        dvecptr[4] = (double*)PyArray_GetPtr(pyArr[4], index); //*padRedcosts

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*panCstatus

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        ivecptr[6] = (int*)PyArray_GetPtr(pyArr[6], index); //*panRstatus

    errorcode = LSgetDualMIPsolution(pModel
        , dvecptr[2] //*padPrimal
        , dvecptr[3] //*padDual
        , dvecptr[4] //*padRedcosts
        , ivecptr[5] //*panCstatus
        , ivecptr[6]); //*panRstatus


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSgetGOPVariablePriority
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetGOPVariablePriority(pModel,ndxVar,pnPriority)
*/
PyObject *pyLSgetGOPVariablePriority(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel, //pModel
        &ibuf[2], //ndxVar
        &PyArray_Type, &pyArr[3])) {  //*pnPriority
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_GET_VECPTR(3);

    errorcode = LSgetGOPVariablePriority(pModel
        , ibuf[2] //ndxVar
        , ivecptr[3]); //*pnPriority

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetHess
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetHess(pModel,pnHnonzeros,paiHrows,paiHcol1,paiHcol2,padHcoef,padX)
*/
PyObject *pyLSgetHess(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnHnonzeros
        &PyArray_Type, &pyArr[3],  //*paiHrows
        &PyArray_Type, &pyArr[4],  //*paiHcol1
        &PyArray_Type, &pyArr[5],  //*paiHcol2
        &PyArray_Type, &pyArr[6],  //*padHcoef
        &PyArray_Type, &pyArr[7])) {  //*padX
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*pnHnonzeros

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*paiHrows

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*paiHcol1

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*paiHcol2

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        dvecptr[6] = (double*)PyArray_GetPtr(pyArr[6], index); //*padHcoef

    if (pyArr[7] && pyArr[7]->dimensions > 0)
        dvecptr[7] = (double*)PyArray_GetPtr(pyArr[7], index); //*padX

    errorcode = LSgetHess(pModel
        , ivecptr[2] //*pnHnonzeros
        , ivecptr[3] //*paiHrows
        , ivecptr[4] //*paiHcol1
        , ivecptr[5] //*paiHcol2
        , dvecptr[6] //*padHcoef
        , dvecptr[7]); //*padX


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetIISInts
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetIISInts(pModel,pnSuf_xnt,pnIIS_xnt,paiVars)
*/
PyObject *pyLSgetIISInts(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnSuf_xnt
        &PyArray_Type, &pyArr[3],  //*pnIIS_xnt
        &PyArray_Type, &pyArr[4])) {  //*paiVars
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*pnSuf_xnt

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*pnIIS_xnt

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*paiVars

    errorcode = LSgetIISInts(pModel
        , ivecptr[2] //*pnSuf_xnt
        , ivecptr[3] //*pnIIS_xnt
        , ivecptr[4]); //*paiVars


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetIISSETs
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetIISSETs(pModel,pnSuf_set,pnIIS_set,paiSets)
*/
PyObject *pyLSgetIISSETs(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnSuf_set
        &PyArray_Type, &pyArr[3],  //*pnIIS_set
        &PyArray_Type, &pyArr[4])) {  //*paiSets
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*pnSuf_set

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*pnIIS_set

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*paiSets

    errorcode = LSgetIISSETs(pModel
        , ivecptr[2] //*pnSuf_set
        , ivecptr[3] //*pnIIS_set
        , ivecptr[4]); //*paiSets


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetJac
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetJac(pModel,pnJnonzeros,pnJobjnnz,paiJrows,paiJcols,padJcoef,padX)
*/
PyObject *pyLSgetJac(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnJnonzeros
        &PyArray_Type, &pyArr[3],  //*pnJobjnnz
        &PyArray_Type, &pyArr[4],  //*paiJrows
        &PyArray_Type, &pyArr[5],  //*paiJcols
        &PyArray_Type, &pyArr[6],  //*padJcoef
        &PyArray_Type, &pyArr[7])) {  //*padX
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)PyArray_GetPtr(pyArr[2], index); //*pnJnonzeros

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*pnJobjnnz

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)PyArray_GetPtr(pyArr[4], index); //*paiJrows

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)PyArray_GetPtr(pyArr[5], index); //*paiJcols

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        dvecptr[6] = (double*)PyArray_GetPtr(pyArr[6], index); //*padJcoef

    if (pyArr[7] && pyArr[7]->dimensions > 0)
        dvecptr[7] = (double*)PyArray_GetPtr(pyArr[7], index); //*padX

    errorcode = LSgetJac(pModel
        , ivecptr[2] //*pnJnonzeros
        , ivecptr[3] //*pnJobjnnz
        , ivecptr[4] //*paiJrows
        , ivecptr[5] //*paiJcols
        , dvecptr[6] //*padJcoef
        , dvecptr[7]); //*padX


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetKBestMIPSols
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetKBestMIPSols(pModel,pszFname,nMaxSols)
*/
PyObject *pyLSgetKBestMIPSols(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osi",
        &pyModel, //pModel
        &sbuf[2],  //*pszFname
        &ibuf[3])) { //nMaxSols
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);


    // Get C pointers
    errorcode = LSgetKBestMIPSols(pModel
        , sbuf[2] //*pszFname
        , NULL
        , NULL
        , ibuf[3]); //nMaxSols

   //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetLicenseInfo
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetLicenseInfo(pModel,pnMaxcons,pnMaxvars,pnMaxintvars,int,pnReserved1,pnDaystoexp,pnDaystotrialexp,pnNlpAllowed,pnUsers,pnBarAllowed,pnRuntime,pnEdulicense,pachText)
*/
PyObject *pyLSgetLicenseInfo(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    int k = 0;

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnMaxcons
        &PyArray_Type, &pyArr[3],  //*pnMaxvars
        &PyArray_Type, &pyArr[4],  //*pnMaxintvars
        &PyArray_Type, &pyArr[5],  //*pnReserved1
        &PyArray_Type, &pyArr[6],  //*pnDaystoexp
        &PyArray_Type, &pyArr[7],  //*pnDaystotrialexp
        &PyArray_Type, &pyArr[8],  //*pnNlpAllowed
        &PyArray_Type, &pyArr[9],  //*pnUsers
        &PyArray_Type, &pyArr[10],  //*pnBarAllowed
        &PyArray_Type, &pyArr[11],  //*pnRuntime
        &PyArray_Type, &pyArr[12],  //*pnEdulicense
        &PyArray_Type, &pyArr[13])) {  //*pachText
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    for (k = 2; k <= 12; k++) {
        I_GET_VECPTR(k);
    }
    if (pyArr[13] && pyArr[13]->dimensions > 0)
        svecptr[13] = (char*)PyArray_GetPtr(pyArr[13], index); //*pachText

    errorcode = LSgetLicenseInfo(pModel
        , ivecptr[2] //*pnMaxcons
        , ivecptr[3] //*pnMaxvars
        , ivecptr[4] //*pnMaxintvars
        , ivecptr[5] //*pnReserved1
        , ivecptr[6] //*pnDaystoexp
        , ivecptr[7] //*pnDaystotrialexp
        , ivecptr[8] //*pnNlpAllowed
        , ivecptr[9] //*pnUsers
        , ivecptr[10] //*pnBarAllowed
        , ivecptr[11] //*pnRuntime
        , ivecptr[12] //*pnEdulicense
        , svecptr[13]); //*pachText

   //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetMasterModel
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetMasterModel(pModel)
*/
PyObject *pyLSgetMasterModel(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    pLSmodel     mModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "O",
        &pyModel)) { //pModel
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);

    // Get C pointers
    mModel = LSgetMasterModel(pModel); //nil

       //ErrorReturn:
    return PyNewObjPtr(mModel);

}

/*
* @brief LSgetMIPCallbackInfo
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetMIPCallbackInfo(pModel,nQuery)
*/
PyObject *pyLSgetMIPCallbackInfo(PyObject *self, PyObject *args) {
    int       errorcode = LSERR_NO_ERROR;
    pLSmodel  pModel = NULL;
    int       nQuery;
    void      *pvResult = NULL;
    npy_intp  index[1] = { 0 };

    PyObject       *pyModel = NULL;
    PyArrayObject  *pyResult = NULL;

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel,
        &nQuery,
        &PyArray_Type, &pyResult))
    {
        return NULL;
    }
    if (nQuery != LS_IINFO_ARCH_ID) {
        CHECK_MODEL;
    }

    if (pyResult && pyResult->dimensions > 0)
        pvResult = (void *)PyArray_GetPtr(pyResult, index);

    errorcode = LSgetMIPCallbackInfo(pModel, nQuery, pvResult);

    return Py_BuildValue("i", errorcode);

}

/*
* @brief LSgetMIPSolutionStatus
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetMIPSolutionStatus(pModel,pnStatus)
*/
PyObject *pyLSgetMIPSolutionStatus(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*pnStatus
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_GET_VECPTR(2);
    errorcode = LSgetMIPSolutionStatus(pModel
        , ivecptr[2]); //*pnStatus

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSgetNextBestSol
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetNextBestSol(pModel,pnModStatus)
*/
PyObject *pyLSgetNextBestSol(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*pnModStatus
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_GET_VECPTR(2);
    errorcode = LSgetNextBestSol(pModel
        , ivecptr[2]); //*pnModStatus

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetNnzData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetNnzData(pModel,mStat,panOutput)
*/
PyObject *pyLSgetNnzData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel, //pModel
        &ibuf[2], //mStat
        &PyArray_Type, &pyArr[3])) {  //*panOutput
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)PyArray_GetPtr(pyArr[3], index); //*panOutput

    errorcode = LSgetNnzData(pModel
        , ibuf[2] //mStat
        , ivecptr[3]); //*panOutput


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSgetObjPoolNumSol
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetObjPoolNumSol(pModel,nObjIndex,pNumSol)
*/
PyObject *pyLSgetObjPoolNumSol(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel, //pModel
        &ibuf[2], //nObjIndex
        &PyArray_Type, &pyArr[3])) {  //*pNumSol
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_GET_VECPTR(3);
    errorcode = LSgetObjPoolNumSol(pModel
        , ibuf[2] //nObjIndex
        , ivecptr[3]); //*pNumSol

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSgetOrbitInfo
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetOrbitInfo(pModel,pnNumGenerators,pnNumOfOrbits,panOrbitBeg,panOrbits)
*/
PyObject *pyLSgetOrbitInfo(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    void     *pSym = NULL;
    PyObject *pySym = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!",
        &pySym, //pModel
        &PyArray_Type, &pyArr[2],  //*pnNumGenerators
        &PyArray_Type, &pyArr[3],  //*pnNumOfOrbits
        &PyArray_Type, &pyArr[4],  //*panOrbitBeg
        &PyArray_Type, &pyArr[5])) {  //*panOrbits
        return NULL;
    }

    CHECK_OBJ_NO_FAIL(pSym,pySym);

    // Get C pointers
    I_GET_VECPTR(2);
    I_GET_VECPTR(3);
    I_GET_VECPTR(4);
    I_GET_VECPTR(5);

    errorcode = LSgetOrbitInfo(pSym
        , ivecptr[2] //*pnNumGenerators
        , ivecptr[3] //*pnNumOfOrbits
        , ivecptr[4] //*panOrbitBeg
        , ivecptr[5]); //*panOrbits

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetPOSDData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetPOSDData(pModel,pinPOSD,paiPOSDdim,paiPOSDnnz,paiPOSDbeg,paiPOSDrowndx,paiPOSDcolndx,paiPOSDvarndx)
*/
PyObject *pyLSgetPOSDData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    int k;

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pinPOSD
        &PyArray_Type, &pyArr[3],  //*paiPOSDdim
        &PyArray_Type, &pyArr[4],  //*paiPOSDnnz
        &PyArray_Type, &pyArr[5],  //*paiPOSDbeg
        &PyArray_Type, &pyArr[6],  //*paiPOSDrowndx
        &PyArray_Type, &pyArr[7],  //*paiPOSDcolndx
        &PyArray_Type, &pyArr[8])) {  //*paiPOSDvarndx
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    for (k = 2; k <= 8; k++) {
        I_GET_VECPTR(k);
    }

    errorcode = LSgetPOSDData(pModel
        , ivecptr[2] //*pinPOSD
        , ivecptr[3] //*paiPOSDdim
        , ivecptr[4] //*paiPOSDnnz
        , ivecptr[5] //*paiPOSDbeg
        , ivecptr[6] //*paiPOSDrowndx
        , ivecptr[7] //*paiPOSDcolndx
        , ivecptr[8]); //*paiPOSDvarndx

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetPOSDDatai
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetPOSDDatai(pModel,iPOSD,piPOSDdim,piPOSDnnz,paiPOSDrowndx,paiPOSDcolndx,paiPOSDvarndx)
*/
PyObject *pyLSgetPOSDDatai(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    int k;

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
        &pyModel, //pModel
        &ibuf[2], //iPOSD
        &PyArray_Type, &pyArr[3],  //*piPOSDdim
        &PyArray_Type, &pyArr[4],  //*piPOSDnnz
        &PyArray_Type, &pyArr[5],  //*paiPOSDrowndx
        &PyArray_Type, &pyArr[6],  //*paiPOSDcolndx
        &PyArray_Type, &pyArr[7])) {  //*paiPOSDvarndx
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    for (k = 3; k <= 7; k++) {
        I_GET_VECPTR(k);
    }

    errorcode = LSgetPOSDDatai(pModel
        , ibuf[2] //iPOSD
        , ivecptr[3] //*piPOSDdim
        , ivecptr[4] //*piPOSDnnz
        , ivecptr[5] //*paiPOSDrowndx
        , ivecptr[6] //*paiPOSDcolndx
        , ivecptr[7]); //*paiPOSDvarndx

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}



/*
* @brief LSgetProgressInfo
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetProgressInfo(pModel,nLocation,nQuery)
*/
PyObject *pyLSgetProgressInfo(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiiO!",
        &pyModel, //pModel
        &ibuf[2], //nLocation
        &ibuf[3], //nQuery
        &PyArray_Type, &pyArr[4])) { //Value
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);


    // Get C pointers
    D_GET_VECPTR(4);
    errorcode = LSgetProgressInfo(pModel
        , ibuf[2] //nLocation
        , ibuf[3] //nQuery
        , dvecptr[4]);

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetSolutionInfo
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetSolutionInfo(pModel,pnMethod,pnElapsed,pnSpxiter,pnBariter,pnNlpiter,pnPrimStatus,pnDualStatus,pnBasStatus,pdPobjval,pdDobjval,pdPinfeas,pdDinfeas)
*/
PyObject *pyLSgetSolutionInfo(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    int k;

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!O!O!O!O!O!O!O!O!O!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pnMethod
        &PyArray_Type, &pyArr[3],  //*pnElapsed
        &PyArray_Type, &pyArr[4],  //*pnSpxiter
        &PyArray_Type, &pyArr[5],  //*pnBariter
        &PyArray_Type, &pyArr[6],  //*pnNlpiter
        &PyArray_Type, &pyArr[7],  //*pnPrimStatus
        &PyArray_Type, &pyArr[8],  //*pnDualStatus
        &PyArray_Type, &pyArr[9],  //*pnBasStatus
        &PyArray_Type, &pyArr[10],  //*pdPobjval
        &PyArray_Type, &pyArr[11],  //*pdDobjval
        &PyArray_Type, &pyArr[12],  //*pdPinfeas
        &PyArray_Type, &pyArr[13])) {  //*pdDinfeas
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    for (k = 2; k <= 9; k++) {
        I_GET_VECPTR(k);
    }
    for (     ; k <= 13; k++) {
        D_GET_VECPTR(k);
    }

    errorcode = LSgetSolutionInfo(pModel
        , ivecptr[2] //*pnMethod
        , ivecptr[3] //*pnElapsed
        , ivecptr[4] //*pnSpxiter
        , ivecptr[5] //*pnBariter
        , ivecptr[6] //*pnNlpiter
        , ivecptr[7] //*pnPrimStatus
        , ivecptr[8] //*pnDualStatus
        , ivecptr[9] //*pnBasStatus
        , dvecptr[10] //*pdPobjval
        , dvecptr[11] //*pdDobjval
        , dvecptr[12] //*pdPinfeas
        , dvecptr[13]); //*pdDinfeas

      //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetSolutionStatus
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetSolutionStatus(pModel,nStatus)
*/
PyObject *pyLSgetSolutionStatus(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*nStatus
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    I_GET_VECPTR(2);
    errorcode = LSgetSolutionStatus(pModel
        , ivecptr[2]); //*nStatus

     //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetXSolverLibrary
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetXSolverLibrary(pEnv,mVendorId,szLibrary)
*/
PyObject *pyLSgetXSolverLibrary(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Ois",
        &pyEnv, //pEnv
        &ibuf[2], //mVendorId
        &PyArray_Type, &pyArr[3])) {  //*szLibrary
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    S_GET_VECPTR(3);
    errorcode = LSgetXSolverLibrary(pEnv
        , ibuf[2] //mVendorId
        , svecptr[3]); //*szLibrary

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadALLDIFFData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadALLDIFFData(pModel,nALLDIFF,paiAlldiffDim,paiAlldiffL,paiAlldiffU,paiAlldiffBeg,paiAlldiffVar)
*/
PyObject *pyLSloadALLDIFFData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
        &pyModel, //pModel
        &ibuf[2], //nALLDIFF
        &PyArray_Type, &pyArr[3],  //*paiAlldiffDim
        &PyArray_Type, &pyArr[4],  //*paiAlldiffL
        &PyArray_Type, &pyArr[5],  //*paiAlldiffU
        &PyArray_Type, &pyArr[6],  //*paiAlldiffBeg
        &PyArray_Type, &pyArr[7])) {  //*paiAlldiffVar
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)pyArr[3]->data;  //*paiAlldiffDim

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)pyArr[4]->data;  //*paiAlldiffL

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)pyArr[5]->data;  //*paiAlldiffU

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        ivecptr[6] = (int*)pyArr[6]->data;  //*paiAlldiffBeg

    if (pyArr[7] && pyArr[7]->dimensions > 0)
        ivecptr[7] = (int*)pyArr[7]->data;  //*paiAlldiffVar

    errorcode = LSloadALLDIFFData(pModel
        , ibuf[2] //nALLDIFF
        , ivecptr[3] //*paiAlldiffDim
        , ivecptr[4] //*paiAlldiffL
        , ivecptr[5] //*paiAlldiffU
        , ivecptr[6] //*paiAlldiffBeg
        , ivecptr[7]); //*paiAlldiffVar

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadGASolution
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadGASolution(pModel,nIndex)
*/
PyObject *pyLSloadGASolution(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oi",
        &pyModel, //pModel
        &ibuf[2])) { //nIndex
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSloadGASolution(pModel
        , ibuf[2]); //nIndex

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadIISPriorities
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadIISPriorities(pModel,panRprior,panCprior)
*/
PyObject *pyLSloadIISPriorities(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*panRprior
        &PyArray_Type, &pyArr[3])) {  //*panCprior
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        ivecptr[2] = (int*)pyArr[2]->data;  //*panRprior

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)pyArr[3]->data;  //*panCprior

    errorcode = LSloadIISPriorities(pModel
        , ivecptr[2] //*panRprior
        , ivecptr[3]); //*panCprior

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadMultiStartSolution
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadMultiStartSolution(pModel,nIndex)
*/
PyObject *pyLSloadMultiStartSolution(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oi",
        &pyModel, //pModel
        &ibuf[2])) { //nIndex
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSloadMultiStartSolution(pModel
        , ibuf[2]); //nIndex

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadNLPDense
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadNLPDense(pModel,nCons,nVars,dObjSense,pszConTypes,pszVarTypes,padX0,padL,padU)
*/
PyObject *pyLSloadNLPDense(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiiissO!O!O!",
        &pyModel, //pModel
        &ibuf[2], //nCons
        &ibuf[3], //nVars
        &ibuf[4], //dObjSense
        &PyArray_Type, &pyArr[5],  //*pszConTypes
        &PyArray_Type, &pyArr[6],  //*pszVarTypes
        &PyArray_Type, &pyArr[7],  //*padX0
        &PyArray_Type, &pyArr[8],  //*padL
        &PyArray_Type, &pyArr[9])) {  //*padU
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    S_GET_VECPTR(5);
    S_GET_VECPTR(6);
    if (pyArr[7] && pyArr[7]->dimensions > 0)
        dvecptr[7] = (double*)pyArr[7]->data;  //*padX0

    if (pyArr[8] && pyArr[8]->dimensions > 0)
        dvecptr[8] = (double*)pyArr[8]->data;  //*padL

    if (pyArr[9] && pyArr[9]->dimensions > 0)
        dvecptr[9] = (double*)pyArr[9]->data;  //*padU

    errorcode = LSloadNLPDense(pModel
        , ibuf[2] //nCons
        , ibuf[3] //nVars
        , ibuf[4] //dObjSense
        , svecptr[5] //*pszConTypes
        , svecptr[6] //*pszVarTypes
        , dvecptr[7] //*padX0
        , dvecptr[8] //*padL
        , dvecptr[9]); //*padU

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadPOSDData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadPOSDData(pModel,nPOSD,paiPOSDdim,paiPOSDbeg,paiPOSDrowndx,paiPOSDcolndx,paiPOSDvarndx)
*/
PyObject *pyLSloadPOSDData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!O!O!O!",
        &pyModel, //pModel
        &ibuf[2], //nPOSD
        &PyArray_Type, &pyArr[3],  //*paiPOSDdim
        &PyArray_Type, &pyArr[4],  //*paiPOSDbeg
        &PyArray_Type, &pyArr[5],  //*paiPOSDrowndx
        &PyArray_Type, &pyArr[6],  //*paiPOSDcolndx
        &PyArray_Type, &pyArr[7])) {  //*paiPOSDvarndx
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)pyArr[3]->data;  //*paiPOSDdim

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)pyArr[4]->data;  //*paiPOSDbeg

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        ivecptr[5] = (int*)pyArr[5]->data;  //*paiPOSDrowndx

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        ivecptr[6] = (int*)pyArr[6]->data;  //*paiPOSDcolndx

    if (pyArr[7] && pyArr[7]->dimensions > 0)
        ivecptr[7] = (int*)pyArr[7]->data;  //*paiPOSDvarndx

    errorcode = LSloadPOSDData(pModel
        , ibuf[2] //nPOSD
        , ivecptr[3] //*paiPOSDdim
        , ivecptr[4] //*paiPOSDbeg
        , ivecptr[5] //*paiPOSDrowndx
        , ivecptr[6] //*paiPOSDcolndx
        , ivecptr[7]); //*paiPOSDvarndx

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadString
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadString(pModel,pszString)
*/
PyObject *pyLSloadString(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Os",
        &pyModel, //pModel
        &sbuf[2])) {  //*pszString
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSloadString(pModel
        , sbuf[2]); //*pszString

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadStringData
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadString(pModel,paszStringData)
*/
PyObject *pyLSloadStringData(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel, //pModel
        &ibuf[2], //nStrings
        &PyArray_Type, &pyArr[3])) {  //**paszStringData
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        svecptr[3] = (char*)pyArr[3]->data;  //**paszStringData

    errorcode = LSloadStringData(pModel
        , ibuf[2] //nStrings
        , NULL); //**paszStringData

       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSreadMPXStream
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSreadMPXStream(pModel,pszStream,nStreamLen)
*/
PyObject *pyLSreadMPXStream(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Osi",
        &pyModel, //pModel
        &sbuf[2],  //*pszStream
        &ibuf[3])) { //nStreamLen
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSreadMPXStream(pModel
        , sbuf[2] //*pszStream
        , ibuf[3]); //nStreamLen

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSloadSolutionAt
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSloadSolutionAt(pModel,nObjIndex,nSolIndex)
*/
PyObject *pyLSloadSolutionAt(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oii",
        &pyModel, //pModel
        &ibuf[2], //nObjIndex
        &ibuf[3])) { //nSolIndex
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSloadSolutionAt(pModel
        , ibuf[2] //nObjIndex
        , ibuf[3]); //nSolIndex


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSsetObjPoolParam
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetObjPoolParam(pModel,nObjIndex,mInfo,dValue)
*/
PyObject *pyLSsetObjPoolParam(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oiid",
        &pyModel, //pModel
        &ibuf[2], //nObjIndex
        &ibuf[3], //mInfo
        &dbuf[4])) { //dValue
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetObjPoolParam(pModel
        , ibuf[2] //nObjIndex
        , ibuf[3] //mInfo
        , dbuf[4]); //dValue


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetProbAllocSizes
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetProbAllocSizes(pModel,n_vars_alloc,n_cons_alloc,n_QC_alloc,n_Annz_alloc,n_Qnnz_alloc,n_NLPnnz_alloc)
*/
PyObject *pyLSsetProbAllocSizes(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oiiiiii",
        &pyModel, //pModel
        &ibuf[2], //n_vars_alloc
        &ibuf[3], //n_cons_alloc
        &ibuf[4], //n_QC_alloc
        &ibuf[5], //n_Annz_alloc
        &ibuf[6], //n_Qnnz_alloc
        &ibuf[7])) { //n_NLPnnz_alloc
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetProbAllocSizes(pModel
        , ibuf[2] //n_vars_alloc
        , ibuf[3] //n_cons_alloc
        , ibuf[4] //n_QC_alloc
        , ibuf[5] //n_Annz_alloc
        , ibuf[6] //n_Qnnz_alloc
        , ibuf[7]); //n_NLPnnz_alloc


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetProbNameAllocSizes
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetProbNameAllocSizes(pModel,n_varname_alloc,n_rowname_alloc)
*/
PyObject *pyLSsetProbNameAllocSizes(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oii",
        &pyModel, //pModel
        &ibuf[2], //n_varname_alloc
        &ibuf[3])) { //n_rowname_alloc
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetProbNameAllocSizes(pModel
        , ibuf[2] //n_varname_alloc
        , ibuf[3]); //n_rowname_alloc


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetSETSStatei
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetSETSStatei(pModel,iSet,mState)
*/
PyObject *pyLSsetSETSStatei(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oii",
        &pyModel, //pModel
        &ibuf[2], //iSet
        &ibuf[3])) { //mState
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetSETSStatei(pModel
        , ibuf[2] //iSet
        , ibuf[3]); //mState


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetXSolverLibrary
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetXSolverLibrary(pEnv,mVendorId,szLibrary)
*/
PyObject *pyLSsetXSolverLibrary(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv     pEnv = NULL;
    PyObject *pyEnv = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Ois",
        &pyEnv, //pEnv
        &ibuf[2], //mVendorId
        &sbuf[3])) {  //*szLibrary
        return NULL;
    }

    CHECK_ENV;

    // Get C pointers
    errorcode = LSsetXSolverLibrary(pEnv
        , ibuf[2] //mVendorId
        , sbuf[3]); //*szLibrary


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetConstraintProperty
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetConstraintProperty(pModel,ndxCons,nConptype)
*/
PyObject *pyLSsetConstraintProperty(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oii",
        &pyModel, //pModel
        &ibuf[2], //ndxCons
        &ibuf[3])) { //nConptype
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetConstraintProperty(pModel
        , ibuf[2] //ndxCons
        , ibuf[3]); //nConptype


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSregress
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSregress(pModel,nNdim,nPdim,padU,padX,padB,pdB0,padR,padstats)
*/
PyObject *pyLSregress(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "iiO!O!O!O!O!O!",
        &ibuf[2], //nNdim
        &ibuf[3], //nPdim
        &PyArray_Type, &pyArr[4],  //*padU
        &PyArray_Type, &pyArr[5],  //*padX
        &PyArray_Type, &pyArr[6],  //*padB
        &PyArray_Type, &pyArr[7],  //*pdB0
        &PyArray_Type, &pyArr[8],  //*padR
        &PyArray_Type, &pyArr[9])) {  //*padstats
        return NULL;
    }


    // Get C pointers
    if (pyArr[4] && pyArr[4]->dimensions > 0)
        dvecptr[4] = (double*)PyArray_GetPtr(pyArr[4], index); //*padU

    if (pyArr[5] && pyArr[5]->dimensions > 0)
        dvecptr[5] = (double*)PyArray_GetPtr(pyArr[5], index); //*padX

    if (pyArr[6] && pyArr[6]->dimensions > 0)
        dvecptr[6] = (double*)PyArray_GetPtr(pyArr[6], index); //*padB

    if (pyArr[7] && pyArr[7]->dimensions > 0)
        dvecptr[7] = (double*)PyArray_GetPtr(pyArr[7], index); //*pdB0

    if (pyArr[8] && pyArr[8]->dimensions > 0)
        dvecptr[8] = (double*)PyArray_GetPtr(pyArr[8], index); //*padR

    if (pyArr[9] && pyArr[9]->dimensions > 0)
        dvecptr[9] = (double*)PyArray_GetPtr(pyArr[9], index); //*padstats

    errorcode = LSregress(
          ibuf[2] //nNdim
        , ibuf[3] //nPdim
        , dvecptr[4] //*padU
        , dvecptr[5] //*padX
        , dvecptr[6] //*padB
        , dvecptr[7] //*pdB0
        , dvecptr[8] //*padR
        , dvecptr[9]); //*padstats


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSremObjPool
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSremObjPool(pModel,nObjIndex)
*/
PyObject *pyLSremObjPool(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oi",
        &pyModel, //pModel
        &ibuf[2])) { //nObjIndex
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSremObjPool(pModel
        , ibuf[2]); //nObjIndex


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}



/*
* @brief LSgetMIPSolution
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetMIPSolution(pModel,pdPobjval,padPrimal)
*/
PyObject *pyLSgetMIPSolution(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!O!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2],  //*pdPobjval
        &PyArray_Type, &pyArr[3])) {  //*padPrimal
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        dvecptr[2] = (double*)PyArray_GetPtr(pyArr[2], index); //*pdPobjval

    if (pyArr[3] && pyArr[3]->dimensions > 0)
        dvecptr[3] = (double*)PyArray_GetPtr(pyArr[3], index); //*padPrimal

    errorcode = LSgetMIPSolution(pModel
        , dvecptr[2] //*pdPobjval
        , dvecptr[3]); //*padPrimal


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetObjective
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetObjective(pModel,pdObjval)
*/
PyObject *pyLSgetObjective(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OO!",
        &pyModel, //pModel
        &PyArray_Type, &pyArr[2])) {  //*pdObjval
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[2] && pyArr[2]->dimensions > 0)
        dvecptr[2] = (double*)PyArray_GetPtr(pyArr[2], index); //*pdObjval

    errorcode = LSgetObjective(pModel
        , dvecptr[2]); //*pdObjval


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetGOPVariablePriority
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetGOPVariablePriority(pModel,ndxVar,nPriority)
*/
PyObject *pyLSsetGOPVariablePriority(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Oii",
        &pyModel, //pModel
        &ibuf[2], //ndxVar
        &ibuf[3])) { //nPriority
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetGOPVariablePriority(pModel
        , ibuf[2] //ndxVar
        , ibuf[3]); //nPriority


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetStringValue
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetStringValue(pModel,iString,pdValue)
*/
PyObject *pyLSgetStringValue(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!",
        &pyModel, //pModel
        &ibuf[2], //iString
        &PyArray_Type, &pyArr[3])) {  //*pdValue
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        dvecptr[3] = (double*)PyArray_GetPtr(pyArr[3], index); //*pdValue

    errorcode = LSgetStringValue(pModel
        , ibuf[2] //iString
        , dvecptr[3]); //*pdValue


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSrepairQterms
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSrepairQterms(pModel,nCons,paiCons,paiType)
*/
PyObject *pyLSrepairQterms(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "OiO!O!",
        &pyModel, //pModel
        &ibuf[2], //nCons
        &PyArray_Type, &pyArr[3],  //*paiCons
        &PyArray_Type, &pyArr[4])) {  //*paiType
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    if (pyArr[3] && pyArr[3]->dimensions > 0)
        ivecptr[3] = (int*)pyArr[3]->data;  //*paiCons

    if (pyArr[4] && pyArr[4]->dimensions > 0)
        ivecptr[4] = (int*)pyArr[4]->data;  //*paiType

    errorcode = LSrepairQterms(pModel
        , ibuf[2] //nCons
        , ivecptr[3] //*paiCons
        , ivecptr[4]); //*paiType


                       //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief LSsetMIPCCStrategy
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetMIPCCStrategy(pModel,nRunId,szParamFile)
*/
PyObject *pyLSsetMIPCCStrategy(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel     pModel = NULL;
    PyObject *pyModel = NULL;
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";

    // zero-out temp vectors
    ZERO_BUF(20);

    if (!PyArg_ParseTuple(args, "Ois",
        &pyModel, //pModel
        &ibuf[2], //nRunId
        &sbuf[3])) {  //*szParamFile
        return NULL;
    }

    CHECK_MODEL;
    LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
    LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



    // Get C pointers
    errorcode = LSsetMIPCCStrategy(pModel
        , NULL
        , ibuf[2] //nRunId
        , sbuf[3] //*szParamFile
        , NULL);


                    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

typedef struct pyLindoData_t {
    void *pModel;
    void *pyModel;
    void *pEnv;
    void *pyEnv;
    void *locFunc;
    void *locData;
    void *cbFunc;
    void *cbData;
    void *mipFunc;
    void *mipData;
    void *Funcalc_func;
    void *FData;
    void *Grad_func;
    void *Grad_func2; //partial gradients
    void *GData;
    void *Hessdc_func;
    void *HDCdata;
} pyLindoData_t;


/*
* @brief LSsetModelLogfunc
* @param[in,out] pModel
* @param[in,out] line
* @return int
* @remark errorcode = lindo.LSsetModelLogfunc(pModel,cbfun,cbdata)
*/
void LS_CALLTYPE relayModelLogfunc(pLSmodel pModel, char *line, void *userdata)
{
    pyLindoData_t *pyudata = (pyLindoData_t*)userdata;
    PyObject *arglist = NULL;
    PyObject *result = NULL;
    if (line)
    {
        // Build up the argument list...
        arglist = Py_BuildValue("(OsO)", pyudata->pyModel, line, pyudata->locData);
        // ...for calling the Python cb function
        if (arglist)
            result = PyEval_CallObject(pyudata->locFunc, arglist);
        //printf("%s", line);
    } /*if*/

    Py_XDECREF(result);
    Py_DECREF(arglist);

    return;
} /*relayModelLogfunc*/

/*
* @brief LSsetModelLogfunc
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetModelLogfunc(pModel,cbfun,cbdata)
*/
PyObject *pyLSsetModelLogfunc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel  pModel = NULL;
    PyObject *pyModel = NULL;
    PyObject *pyObj[5];
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    pyLindoData_t *pyudata=NULL;

    // zero-out temp vectors
    ZERO_BUF(20);
    memset(pyObj, 0, 5 * sizeof(PyObject*));
    if (!PyArg_ParseTuple(args, "OOO",
        &pyModel, //pModel
        &pyObj[2], //locFunc
        &pyObj[3])) {  //locData
        return NULL;
    }

    if (!PyCallable_Check(pyObj[2])) {
        PyErr_SetString(PyExc_TypeError, "Need a callable object!");
    }
    CHECK_MODEL;
    pyudata = (pyLindoData_t*) LSgetObjHandle(pModel, LS_PTR_MODEL, LS_REF_LOCDATA);
    if (pyudata) {
        free(pyudata);
    }
    pyudata = malloc(sizeof(pyLindoData_t));
    memset(pyudata, 0, sizeof(pyLindoData_t));
    if (pyObj[2]) {
        pyudata->pModel = pModel;
        pyudata->pyModel = pyModel;
        pyudata->locFunc = pyObj[2];
        pyudata->locData = pyObj[3];
    }

    // Get C pointers
    errorcode = LSsetModelLogfunc(pModel
        , relayModelLogfunc
        , pyudata);

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetModelLogfunc
* @param[in,out] pModel
* @param[in,out] line
* @return int
* @remark errorcode = lindo.LSsetModelLogfunc(pModel,cbfun,cbdata)
*/
int LS_CALLTYPE relayCallback(pLSmodel pModel, int iLoc, void *userdata)
{
    int retvalue = 0;
    pyLindoData_t *pyudata = (pyLindoData_t*)userdata;
    PyObject *arglist = NULL;
    PyObject *result = NULL;
    {
        // Build up the argument list...
        arglist = Py_BuildValue("(OiO)", pyudata->pyModel,iLoc, pyudata->cbData);
        // ...for calling the Python cb function
        if (arglist)
            result = PyEval_CallObject(pyudata->cbFunc, arglist);
    } /*if*/
    if (result && PyLong_Check(result)) {
        retvalue = PyLong_AsLong(result);
    }

    Py_XDECREF(result);
    Py_DECREF(arglist);

    return retvalue;
} /*relayModelLogfunc*/

/*
* @brief LSsetCallback
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetCallback(pModel,cbfun,cbdata)
*/
PyObject *pyLSsetCallback(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel  pModel = NULL;
    PyObject *pyModel = NULL;
    PyObject *pyObj[5];
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    pyLindoData_t *pyudata = NULL;

    // zero-out temp vectors
    ZERO_BUF(20);
    memset(pyObj, 0, 5 * sizeof(PyObject*));
    if (!PyArg_ParseTuple(args, "OOO",
        &pyModel, //pModel
        &pyObj[2], //cbFunc
        &pyObj[3])) {  //cbData
        return NULL;
    }

    if (!PyCallable_Check(pyObj[2])) {
        PyErr_SetString(PyExc_TypeError, "Need a callable object!");
    }
    CHECK_MODEL;
    pyudata = (pyLindoData_t*)LSgetObjHandle(pModel, LS_PTR_MODEL, LS_REF_CBDATA);
    if (!pyudata) {
        free(pyudata);
    }
    pyudata = malloc(sizeof(pyLindoData_t));
    memset(pyudata, 0, sizeof(pyLindoData_t));
    if (pyObj[2]) {
        pyudata->pModel = pModel;
        pyudata->pyModel = pyModel;
        pyudata->cbFunc = pyObj[2];
        pyudata->cbData = pyObj[3];
    }

    // Get C pointers
    errorcode = LSsetCallback(pModel
        , relayCallback
        , pyudata);

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


/*
* @brief relayMIPCallback
* @param[in,out] pModel
* @param[in,out] line
* @return int
* @remark errorcode = lindo.LSsetModelLogfunc(pModel,cbfun,cbdata)
*/
int LS_CALLTYPE relayMIPCallback(pLSmodel pModel, void *userdata, double dObjval, double *padPrimal)
{
    int retvalue = 0;
    pyLindoData_t *pyudata = (pyLindoData_t*)userdata;
    PyObject *arglist = NULL;
    PyObject *result = NULL;
    PyObject *pyPrimal = NULL;
    {
        int n_dim=1;
        npy_intp dim[1] = { 0 };
        LSgetInfo(pyudata->pModel, LS_IINFO_NUM_VARS, &dim[0]);
        if (!dim[0]) return 0;
        pyPrimal = PyArray_SimpleNewFromData(n_dim, dim, PyArray_DOUBLE, (char*)padPrimal);
        // Build up the argument list...
        if (pyPrimal)
            arglist = Py_BuildValue("(OOdO)", pyudata->pyModel, pyudata->mipData, dObjval, pyPrimal);
        // ...for calling the Python cb function
        if (arglist)
            result = PyEval_CallObject(pyudata->mipFunc, arglist);
    } /*if*/
    if (result && PyLong_Check(result)) {
        retvalue = PyLong_AsLong(result);
    }
    {
        Py_XDECREF(result);
        Py_DECREF(arglist);
    }

    return retvalue;
} /*relayMIPCallback*/

/*
* @brief LSsetMIPCallback
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetMIPCallback(pModel,cbfun,cbdata)
*/
PyObject *pyLSsetMIPCallback(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel  pModel = NULL;
    PyObject *pyModel = NULL;
    PyObject *pyObj[5];
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    pyLindoData_t *pyudata = NULL;

    // zero-out temp vectors
    ZERO_BUF(20);
    memset(pyObj, 0, 5 * sizeof(PyObject*));
    if (!PyArg_ParseTuple(args, "OOO",
        &pyModel, //pModel
        &pyObj[2], //mipFunc
        &pyObj[3])) {  //mipData
        return NULL;
    }

    if (!PyCallable_Check(pyObj[2])) {
        PyErr_SetString(PyExc_TypeError, "Need a callable object!");
    }
    CHECK_MODEL;
    pyudata = (pyLindoData_t*)LSgetObjHandle(pModel, LS_PTR_MODEL, LS_REF_MIPDATA);
    if (pyudata) {
        free(pyudata);
    }
    pyudata = malloc(sizeof(pyLindoData_t));
    memset(pyudata, 0, sizeof(pyLindoData_t));
    if (pyObj[2]) {
        pyudata->pModel = pModel;
        pyudata->pyModel = pyModel;
        pyudata->mipFunc = pyObj[2];
        pyudata->mipData = pyObj[3];
    }

    // Get C pointers
    errorcode = LSsetMIPCallback(pModel
        , relayMIPCallback
        , pyudata);
    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

int    LS_CALLTYPE relayFuncalc(pLSmodel pModel, void    *userdata,
    int      nRow, double  *padPrimal,
    int      nJDiff, double  dXJBase,
    double   *pdFuncVal, void  *pReserved)
{
    int nerr = 0;
    pyLindoData_t *pyudata = (pyLindoData_t*)userdata;
    PyObject *arglist = NULL;
    PyObject *result = NULL;
    PyObject *pyPrimal = NULL;
    PyObject *pyFuncVal = NULL;
    {
        int n_dim = 1;
        npy_intp dim[2] = { 0, 1 };
        LSgetInfo(pyudata->pModel, LS_IINFO_NUM_VARS, &dim[0]);
        if (!dim[0]) return 0;
        pyPrimal = PyArray_SimpleNewFromData(n_dim, dim, PyArray_DOUBLE, (char*)padPrimal);
        pyFuncVal = PyArray_SimpleNewFromData(n_dim, &dim[1], PyArray_DOUBLE, (char*)pdFuncVal);
        // Build up the argument list...
        if (pyPrimal)
            arglist = Py_BuildValue("(OOiOidOO)", pyudata->pyModel, pyudata->FData, nRow, pyPrimal, nJDiff, dXJBase, pyFuncVal, pyPrimal);
        // ...for calling the Python cb function
        if (arglist)
            result = PyEval_CallObject(pyudata->Funcalc_func, arglist);
    } /*if*/
    if (result && PyLong_Check(result)) {
        nerr = PyLong_AsLong(result);
    }
    {
        Py_XDECREF(result);
        Py_DECREF(arglist);
    }

    return nerr;
} /*Funcalc8*/

  /*
  * @brief LSsetFuncalc
  * @param[in,out] self Pointer to self
  * @param[in,out] args Pointer to args
  * @return int
  * @remark errorcode = lindo.LSsetFuncalc(pModel,funcalc8,cbdata)
  */
PyObject *pyLSsetFuncalc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel  pModel = NULL;
    PyObject *pyModel = NULL;
    PyObject *pyObj[5];
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    pyLindoData_t *pyudata = NULL;

    // zero-out temp vectors
    ZERO_BUF(20);
    memset(pyObj, 0, 5 * sizeof(PyObject*));
    if (!PyArg_ParseTuple(args, "OOO",
        &pyModel, //pModel
        &pyObj[2], //Funcalc_func
        &pyObj[3])) {  //FData
        return NULL;
    }

    if (!PyCallable_Check(pyObj[2])) {
        PyErr_SetString(PyExc_TypeError, "Need a callable object!");
    }
    CHECK_MODEL;
    pyudata = (pyLindoData_t*)LSgetObjHandle(pModel, LS_PTR_MODEL, LS_REF_FDATA);
    if (pyudata) {
        free(pyudata);
    }
    pyudata = malloc(sizeof(pyLindoData_t));
    memset(pyudata, 0, sizeof(pyLindoData_t));
    if (pyObj[2]) {
        pyudata->pModel = pModel;
        pyudata->pyModel = pyModel;
        pyudata->Funcalc_func = pyObj[2];
        pyudata->FData = pyObj[3];
    }

    // Get C pointers
    errorcode = LSsetFuncalc(pModel
        , relayFuncalc
        , pyudata);
    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}


int    LS_CALLTYPE relayGradcalc(pLSmodel pModel, void *userdata,
    int nRow, double *padPrimal, double *lb,
    double *ub, int nNewPnt, int nNPar,
    int *parlist, double *partial)
{
    int nerr = 0;
    pyLindoData_t *pyudata = (pyLindoData_t*)userdata;
    PyObject *arglist = NULL;
    PyObject *result = NULL;
    PyObject *pyPrimal = NULL;
    PyObject *pyLB = NULL;
    PyObject *pyUB = NULL;
    PyObject *pyPartial = NULL;
    PyObject *pyParlist = NULL;
    {
        int n_dim = 1;
        npy_intp dim[2] = { 0, 0 };
        LSgetInfo(pyudata->pModel, LS_IINFO_NUM_VARS, &dim[0]);
        if (!dim[0]) return 0;
        pyPrimal = PyArray_SimpleNewFromData(n_dim, dim, PyArray_DOUBLE, (char*)padPrimal);
        pyLB = PyArray_SimpleNewFromData(n_dim, dim, PyArray_DOUBLE, (char*)lb);
        pyUB = PyArray_SimpleNewFromData(n_dim, dim, PyArray_DOUBLE, (char*)ub);
        dim[1] = nNPar;
        pyPartial = PyArray_SimpleNewFromData(n_dim, &dim[1], PyArray_DOUBLE, (char*)partial);
        pyParlist = PyArray_SimpleNewFromData(n_dim, &dim[1], PyArray_INT32, (char*)parlist);
        // Build up the argument list...
        if (pyPrimal)
            arglist = Py_BuildValue("(OOiOOOiiOO)", pyudata->pyModel, pyudata->GData, nRow, pyPrimal, pyLB, pyUB, nNewPnt, nNPar, pyParlist, pyPartial);
        // ...for calling the Python cb function
        if (arglist)
            result = PyEval_CallObject(pyudata->Grad_func, arglist);
    } /*if*/
    if (result && PyLong_Check(result)) {
        nerr = PyLong_AsLong(result);
    }
    {
        Py_XDECREF(result);
        Py_DECREF(arglist);
    }

    return nerr;
}
/*
* @brief LSsetGradcalc
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSsetGradcalc(pModel,gradCalc,cbdata,nLenUseGrad,pnUseGrad)
*/
PyObject *pyLSsetGradcalc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSmodel  pModel = NULL;
    PyObject *pyModel = NULL;
    PyObject *pyObj[5];
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    pyLindoData_t *pyudata = NULL;

    // zero-out temp vectors
    ZERO_BUF(20);
    memset(pyObj, 0, 5 * sizeof(PyObject*));
    if (!PyArg_ParseTuple(args, "OOO",
        &pyModel, //pModel
        &pyObj[2], //Grad_func
        &pyObj[3], //GData
        &ibuf[4],
        &PyArray_Type, &pyArr[5])) {
        return NULL;
    }

    if (!PyCallable_Check(pyObj[2])) {
        PyErr_SetString(PyExc_TypeError, "Need a callable object!");
    }
    CHECK_MODEL;
    pyudata = (pyLindoData_t*)LSgetObjHandle(pModel, LS_PTR_MODEL, LS_REF_GDATA);
    if (pyudata) {
        free(pyudata);
    }
    pyudata = malloc(sizeof(pyLindoData_t));
    memset(pyudata, 0, sizeof(pyLindoData_t));
    if (pyObj[2]) {
        pyudata->pModel = pModel;
        pyudata->pyModel = pyModel;
        pyudata->Grad_func = pyObj[2];
        pyudata->GData = pyObj[3];
    }

    // Get C pointers
    I_GET_VECPTR(5);

    errorcode = LSsetGradcalc(pModel
        , relayGradcalc
        , pyudata
        , ibuf[4]
        , ivecptr[5]);
    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSsetEnvLogfunc
* @param[in,out] pEnv
* @param[in,out] line
* @return int
* @remark errorcode = lindo.LSsetEnvLogfunc(pEnv,cbfun,cbdata)
*/
void LS_CALLTYPE relayEnvLogfunc(pLSenv pEnv, char *line, void *userdata)
{
    pyLindoData_t *pyudata = (pyLindoData_t*)userdata;
    PyObject *arglist = NULL;
    PyObject *result = NULL;
    if (line)
    {
        // Build up the argument list...
        arglist = Py_BuildValue("(OsO)", pyudata->pyEnv, line, pyudata->locData);
        // ...for calling the Python cb function
        if (arglist)
            result = PyEval_CallObject(pyudata->locFunc, arglist);
        //printf("%s", line);
    } /*if*/

    Py_XDECREF(result);
    Py_DECREF(arglist);

    return;
} /*relayEnvLogfunc*/

  /*
  * @brief LSsetEnvLogfunc
  * @param[in,out] self Pointer to self
  * @param[in,out] args Pointer to args
  * @return int
  * @remark errorcode = lindo.LSsetEnvLogfunc(pEnv,cbfun,cbdata)
  */
PyObject *pyLSsetEnvLogfunc(PyObject *self, PyObject *args) {
    DCL_BUF(20);
    pLSenv  pEnv = NULL;
    PyObject *pyEnv = NULL;
    PyObject *pyObj[5];
    npy_intp  index[1] = { 0 };
    char osig[255] = "i";
    pyLindoData_t *pyudata = NULL;

    // zero-out temp vectors
    ZERO_BUF(20);
    memset(pyObj, 0, 5 * sizeof(PyObject*));
    if (!PyArg_ParseTuple(args, "OOO",
        &pyEnv, //pEnv
        &pyObj[2], //locFunc
        &pyObj[3])) {  //locData
        return NULL;
    }

    if (!PyCallable_Check(pyObj[2])) {
        PyErr_SetString(PyExc_TypeError, "Need a callable object!");
    }
    CHECK_ENV;
    pyudata = (pyLindoData_t*)LSgetObjHandle(pEnv, LS_PTR_ENV, LS_REF_LOCDATA);
    if (pyudata) {
        free(pyudata);
    }
    pyudata = malloc(sizeof(pyLindoData_t));
    memset(pyudata, 0, sizeof(pyLindoData_t));
    if (pyObj[2]) {
        pyudata->pEnv = pEnv;
        pyudata->pyEnv = pyEnv;
        pyudata->locFunc = pyObj[2];
        pyudata->locData = pyObj[3];
    }

    // Get C pointers
    errorcode = LSsetEnvLogfunc(pEnv
        , relayEnvLogfunc
        , pyudata);

    //ErrorReturn:
    return Py_BuildValue(osig, errorcode);

}

/*
* @brief LSgetObjPoolParam
* @param[in,out] self Pointer to self
* @param[in,out] args Pointer to args
* @return int
* @remark errorcode = lindo.LSgetObjPoolParam(pModel,nObjIndex,mParam,pdValue)
*/
PyObject *pyLSgetObjPoolParam(PyObject *self, PyObject *args) {
  DCL_BUF(20);
  pLSmodel     pModel = NULL;
  PyObject *pyModel = NULL;
  npy_intp  index[1] = { 0 };
  char osig[255] = "i";

  // zero-out temp vectors
  ZERO_BUF(20);

  if (!PyArg_ParseTuple(args, "OiiO!",
    &pyModel, //pModel
    &ibuf[2], //nObjIndex
    &ibuf[3], //mParam
    &PyArray_Type, &pyArr[4])) {  //*pdValue
    return NULL;
  }

  CHECK_MODEL;
  LSgetInfo(pModel, LS_IINFO_NUM_VARS, &n);
  LSgetInfo(pModel, LS_IINFO_NUM_CONS, &m);



  // Get C pointers
  if (pyArr[4] && pyArr[4]->dimensions > 0)
    dvecptr[4] = (double*)PyArray_GetPtr(pyArr[4], index); //*pdValue

  errorcode = LSgetObjPoolParam(pModel
    , ibuf[2] //nObjIndex
    , ibuf[3] //mParam
    , dvecptr[4]); //*pdValue


                   //ErrorReturn:
  return Py_BuildValue(osig, errorcode);

}
