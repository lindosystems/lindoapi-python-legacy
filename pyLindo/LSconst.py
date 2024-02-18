#####################################################################
##
##    LINDO API Version 13.0
##    Copyright (c) 2000-2020
##
##    LINDO Systems, Inc.            312.988.7422
##    1415 North Dayton St.          info@lindo.com
##    Chicago, IL 60622              http://www.lindo.com
##
 ##    $Id: lindo.r 2950 2020-06-06 09:22:43Z mka $
##
#####################################################################/


#####################################################################
#                        Constant Definitions                       #
#####################################################################/

# Version macros #/
LS_MAJOR_VER_NUMBER                                          = 13
LS_MINOR_VER_NUMBER                                          = 0
LS_REV_VER_NUMBER                                            = 183
LS_VER_NUMBER                                                = 1300
LS_BUILD_VER_NUMBER                                          = 4099

LS_MIN                                                       = +1
LS_MAX                                                       = -1

LS_CONTYPE_GE                                                = 'G'
LS_CONTYPE_LE                                                = 'L'
LS_CONTYPE_EQ                                                = 'E'
LS_CONTYPE_FR                                                = 'N'

LS_CONETYPE_QUAD                                             = 'Q'
LS_CONETYPE_RQUAD                                            = 'R'
LS_CONETYPE_PEXP                                             = 'E'
LS_CONETYPE_PPOW                                             = 'P'

LS_VARTYPE_CONT                                              = 'C'
LS_VARTYPE_BIN                                               = 'B'
LS_VARTYPE_INT                                               = 'I'
LS_VARTYPE_SC                                                = 'S'

LS_INFINITY                                                  = 1.0E+30

LS_BASTYPE_BAS                                               = 0
LS_BASTYPE_ATLO                                              = -1
LS_BASTYPE_ATUP                                              = -2
LS_BASTYPE_FNUL                                              = -3
LS_BASTYPE_SBAS                                              = -4

LS_UNFORMATTED_MPS                                           = 0
LS_FORMATTED_MPS                                             = 1
LS_UNFORMATTED_MPS_COMP                                      = 2
LS_FORMATTED_MPS_COMP                                        = 3

LS_SOLUTION_OPT                                              = 0
LS_SOLUTION_MIP                                              = 1
LS_SOLUTION_OPT_IPM                                          = 2
LS_SOLUTION_OPT_OLD                                          = 3
LS_SOLUTION_MIP_OLD                                          = 4

LS_BASFILE_BIN                                               = 1
LS_BASFILE_MPS                                               = 2
LS_BASFILE_TXT                                               = 3
LS_BASFILE_MTX                                               = 4

LS_INT_TYPE                                                  = 4
LS_DOUBLE_TYPE                                               = 8

LS_MAX_ERROR_MESSAGE_LENGTH                                  = 1024

LS_DEFAULT                                                   = -1
LS_MAX_JOBJECTS                                              = 100

LS_PROPERTY_UNKNOWN                                          = 0
LS_PROPERTY_CONST                                            = 1
LS_PROPERTY_LINEAR                                           = 2
LS_PROPERTY_CONVEX                                           = 3
LS_PROPERTY_CONCAVE                                          = 4
LS_PROPERTY_QUASI_CONVEX                                     = 5
LS_PROPERTY_QUASI_CONCAVE                                    = 6
LS_PROPERTY_MAX                                              = 7
LS_PROPERTY_MONO_INCREASE                                    = 8
LS_PROPERTY_MONO_DECREASE                                    = 9

# bitmasks for LScopyModel #/
LS_RAW_COPY                                                  = 0
LS_DEEP_COPY                                                 = 1
LS_TIME_COPY                                                 = 2
LS_STOC_COPY                                                 = 4
LS_SNGSTG_COPY                                               = 8

LS_LANG_C                                                    = 0
LS_LANG_CS                                                   = 1
LS_LANG_VB                                                   = 2
LS_LANG_LUA                                                  = 3

# Time frames in seconds #/
LSSEC01                                                      = 1
LSSEC02                                                      = 2
LSSEC03                                                      = 3
LSSEC04                                                      = 4
LSSEC05                                                      = 5
LSSEC06                                                      = 6
LSSEC10                                                      = 10
LSSEC15                                                      = 15
LSSEC20                                                      = 20
LSSEC30                                                      = 30
LSMIN01                                                      = 60
LSMIN02                                                      = 120
LSMIN03                                                      = 180
LSMIN05                                                      = 300
LSMIN06                                                      = 600
LSMIN10                                                      = 600
LSMIN15                                                      = 900
LSMIN20                                                      = 1200
LSMIN30                                                      = 1800
LSHOUR01                                                     = 3600
LSHOUR02                                                     = 7200
LSHOUR03                                                     = 10800
LSHOUR05                                                     = 18000
LSHOUR06                                                     = 21600
LSHOUR08                                                     = 28800
LSHOUR12                                                     = 43200
LSDAY                                                        = 86400
LSWEEK                                                       = 604800
LSMONTH                                                      = 2592000
LSQUARTER                                                    = 7776000
LSYEAR                                                       = 31104000

# Days of week #/
LSSUNDAY                                                     = 0
LSMONDAY                                                     = 1
LSTUESDAY                                                    = 2
LSWEDNESDAY                                                  = 3
LSTHURSDAY                                                   = 4
LSFRIDAY                                                     = 5
LSSATURDAY                                                   = 6

# bitmask for components #/
LS_DATA_CORE                                                 = 1
LS_DATA_TIME                                                 = 2
LS_DATA_STOC                                                 = 4
LS_DATA_FILE                                                 = 8

# external solvers #/
LS_XSOLVER_MSKLP                                             = 1
LS_XSOLVER_GRBLP                                             = 2
LS_XSOLVER_GRBCL                                             = 3
LS_XSOLVER_GRBMIP                                            = 4
LS_XSOLVER_CPXLP                                             = 5
LS_XSOLVER_CPXMIP                                            = 6
LS_XSOLVER_OSI                                               = 7
LS_XSOLVER_CLP                                               = 8
LS_XSOLVER_MSK                                               = 9
LS_XSOLVER_COI                                               = 10
LS_XSOLVER_SOP                                               = 11
LS_XSOLVER_CBC                                               = 12
LS_XSOLVER_XPR                                               = 13
LS_XSOLVER_XLINDO                                            = 99

 # ref types #/
LS_REF_LOCFUN                                                = -1
LS_REF_MIPFUN                                                = -2
LS_REF_CBFUN                                                 = -3
LS_REF_FUNCALC                                               = -4
LS_REF_GRADCALC                                              = -5
LS_REF_HESSCALC                                              = -6
LS_REF_LOCDATA                                               = -11
LS_REF_MIPDATA                                               = -12
LS_REF_CBDATA                                                = -13
LS_REF_FDATA                                                 = -14
LS_REF_GDATA                                                 = -15
LS_REF_HDATA                                                 = -16
LS_REF_PREMODEL                                              = -30

#####################################################################
#                      Macro Type Definitions                       #
#####################################################################/

# Solution or model status (1-20) #/
LS_STATUS_OPTIMAL                                            = 1
LS_STATUS_BASIC_OPTIMAL                                      = 2
LS_STATUS_INFEASIBLE                                         = 3
LS_STATUS_UNBOUNDED                                          = 4
LS_STATUS_FEASIBLE                                           = 5
LS_STATUS_INFORUNB                                           = 6
LS_STATUS_NEAR_OPTIMAL                                       = 7
LS_STATUS_LOCAL_OPTIMAL                                      = 8
LS_STATUS_LOCAL_INFEASIBLE                                   = 9
LS_STATUS_CUTOFF                                             = 10
LS_STATUS_NUMERICAL_ERROR                                    = 11
LS_STATUS_UNKNOWN                                            = 12
LS_STATUS_UNLOADED                                           = 13
LS_STATUS_LOADED                                             = 14
LS_STATUS_BOUNDED                                            = 15


# Parameter codes (21-999) #/
# General parameters (1021 - 1099) #/
LS_IPARAM_OBJSENSE                                           = 1022
LS_DPARAM_CALLBACKFREQ                                       = 1023
LS_DPARAM_OBJPRINTMUL                                        = 1024
LS_IPARAM_CHECK_FOR_ERRORS                                   = 1025
LS_IPARAM_ALLOW_CNTRLBREAK                                   = 1026
LS_IPARAM_DECOMPOSITION_TYPE                                 = 1027
LS_IPARAM_BARRIER_SOLVER                                     = 1033
LS_IPARAM_MPS_OBJ_WRITESTYLE                                 = 1036
LS_IPARAM_SOL_REPORT_STYLE                                   = 1038
LS_IPARAM_INSTRUCT_LOADTYPE                                  = 1039
LS_IPARAM_STRING_LENLMT                                      = 1042
LS_IPARAM_USE_NAMEDATA                                       = 1043
LS_IPARAM_COPY_MODE                                          = 1046
LS_IPARAM_SBD_NUM_THREADS                                    = 1047
LS_IPARAM_NUM_THREADS                                        = 1048
LS_IPARAM_MULTITHREAD_MODE                                   = 1049
LS_IPARAM_FIND_BLOCK                                         = 1050
LS_IPARAM_PROFILER_LEVEL                                     = 1051
LS_IPARAM_INSTRUCT_READMODE                                  = 1052
LS_IPARAM_INSTRUCT_SUBOUT                                    = 1053
LS_IPARAM_SOLPOOL_LIM                                        = 1054
LS_IPARAM_FIND_SYMMETRY_LEVEL                                = 1055
LS_IPARAM_FIND_SYMMETRY_PRINT_LEVEL                          = 1056
LS_IPARAM_TUNER_PRINT_LEVEL                                  = 1057

# Generic solver parameters (1251 - 1500) #/
LS_IPARAM_SOLVER_IUSOL                                       = 1251
LS_IPARAM_SOLVER_TIMLMT                                      = 1252
LS_DPARAM_SOLVER_CUTOFFVAL                                   = 1253
LS_DPARAM_SOLVER_FEASTOL                                     = 1254
LS_IPARAM_SOLVER_RESTART                                     = 1255
LS_IPARAM_SOLVER_IPMSOL                                      = 1256
LS_DPARAM_SOLVER_OPTTOL                                      = 1257
LS_IPARAM_SOLVER_USECUTOFFVAL                                = 1258
LS_IPARAM_SOLVER_PRE_ELIM_FILL                               = 1259
LS_DPARAM_SOLVER_TIMLMT                                      = 1260
LS_IPARAM_SOLVER_CONCURRENT_OPTMODE                          = 1261
LS_DPARAM_SOLVER_PERT_FEASTOL                                = 1262
LS_IPARAM_SOLVER_PARTIALSOL_LEVEL                            = 1263
LS_IPARAM_SOLVER_MODE                                        = 1264
LS_IPARAM_SOLVER_METHOD                                      = 1265

# Advanced parameters for the simplex method (4000 - 41++) #/
LS_IPARAM_LP_SCALE                                           = 4029
LS_IPARAM_LP_ITRLMT                                          = 4030
LS_IPARAM_SPLEX_PPRICING                                     = 4031
LS_IPARAM_SPLEX_REFACFRQ                                     = 4032
LS_IPARAM_PROB_TO_SOLVE                                      = 4034
LS_IPARAM_LP_PRINTLEVEL                                      = 4035
LS_IPARAM_SPLEX_DPRICING                                     = 4037
LS_IPARAM_SPLEX_DUAL_PHASE                                   = 4040
LS_IPARAM_LP_PRELEVEL                                        = 4041
LS_IPARAM_SPLEX_USE_EXTERNAL                                 = 4044
LS_DPARAM_LP_ITRLMT                                          = 4045
LS_DPARAM_LP_MIN_FEASTOL                                     = 4060
LS_DPARAM_LP_MAX_FEASTOL                                     = 4061
LS_DPARAM_LP_MIN_OPTTOL                                      = 4062
LS_DPARAM_LP_MAX_OPTTOL                                      = 4063
LS_DPARAM_LP_MIN_PIVTOL                                      = 4064
LS_DPARAM_LP_MAX_PIVTOL                                      = 4065
LS_DPARAM_LP_AIJ_ZEROTOL                                     = 4066
LS_DPARAM_LP_PIV_ZEROTOL                                     = 4067
LS_DPARAM_LP_PIV_BIGTOL                                      = 4068
LS_DPARAM_LP_BIGM                                            = 4069
LS_DPARAM_LP_BNDINF                                          = 4070
LS_DPARAM_LP_INFINITY                                        = 4071
LS_IPARAM_LP_PPARTIAL                                        = 4072
LS_IPARAM_LP_DPARTIAL                                        = 4073
LS_IPARAM_LP_DRATIO                                          = 4074
LS_IPARAM_LP_PRATIO                                          = 4075
LS_IPARAM_LP_RATRANGE                                        = 4076
LS_IPARAM_LP_DPSWITCH                                        = 4077
LS_IPARAM_LP_PALLOC                                          = 4078
LS_IPARAM_LP_PRTFG                                           = 4079
LS_IPARAM_LP_OPRFREE                                         = 4080
LS_IPARAM_LP_SPRINT_SUB                                      = 4081
LS_IPARAM_LP_XMODE                                           = 4082
LS_IPARAM_LP_PCOLAL_FACTOR                                   = 4083
LS_IPARAM_LP_MAXMERGE                                        = 4084
LS_DPARAM_LP_PERTFACT                                        = 4085
LS_DPARAM_LP_DYNOBJFACT                                      = 4086
LS_IPARAM_LP_DYNOBJMODE                                      = 4087
LS_DPARAM_LP_MERGEFACT                                       = 4088
LS_IPARAM_LP_UMODE                                           = 4089
LS_IPARAM_LP_SPRINT_MAXPASS                                  = 4090
LS_IPARAM_LP_SPRINT_COLFACT                                  = 4091
LS_IPARAM_LP_BASRECOV_METHOD                                 = 4092
LS_IPARAM_LP_BASPOLISH_ITRLMT                                = 4093
LS_IPARAM_LP_BASPOLISH_DEPTH                                 = 4094
LS_IPARAM_LP_BASPOLISH_MODE                                  = 4095

# Advanced parameters for LU decomposition (4800 - 4+++) #/
LS_IPARAM_LU_NUM_CANDITS                                     = 4800
LS_IPARAM_LU_MAX_UPDATES                                     = 4801
LS_IPARAM_LU_PRINT_LEVEL                                     = 4802
LS_IPARAM_LU_UPDATE_TYPE                                     = 4803
LS_IPARAM_LU_MODE                                            = 4804
LS_IPARAM_LU_PIVMOD                                          = 4806
LS_DPARAM_LU_EPS_DIAG                                        = 4900
LS_DPARAM_LU_EPS_NONZ                                        = 4901
LS_DPARAM_LU_EPS_PIVABS                                      = 4902
LS_DPARAM_LU_EPS_PIVREL                                      = 4903
LS_DPARAM_LU_INI_RCOND                                       = 4904
LS_DPARAM_LU_SPVTOL_UPDATE                                   = 4905
LS_DPARAM_LU_SPVTOL_FTRAN                                    = 4906
LS_DPARAM_LU_SPVTOL_BTRAN                                    = 4907
LS_IPARAM_LU_CORE                                            = 4908

# Parameters for the IPM method (3000 - 3+++) #/
LS_DPARAM_IPM_TOL_INFEAS                                     = 3150
LS_DPARAM_IPM_TOL_PATH                                       = 3151
LS_DPARAM_IPM_TOL_PFEAS                                      = 3152
LS_DPARAM_IPM_TOL_REL_STEP                                   = 3153
LS_DPARAM_IPM_TOL_PSAFE                                      = 3154
LS_DPARAM_IPM_TOL_DFEAS                                      = 3155
LS_DPARAM_IPM_TOL_DSAFE                                      = 3156
LS_DPARAM_IPM_TOL_MU_RED                                     = 3157
LS_DPARAM_IPM_BASIS_REL_TOL_S                                = 3158
LS_DPARAM_IPM_BASIS_TOL_S                                    = 3159
LS_DPARAM_IPM_BASIS_TOL_X                                    = 3160
LS_DPARAM_IPM_BI_LU_TOL_REL_PIV                              = 3161
LS_DPARAM_IPM_CO_TOL_INFEAS                                  = 3162
LS_DPARAM_IPM_CO_TOL_PFEAS                                   = 3163
LS_DPARAM_IPM_CO_TOL_DFEAS                                   = 3164
LS_DPARAM_IPM_CO_TOL_MU_RED                                  = 3165
LS_IPARAM_IPM_MAX_ITERATIONS                                 = 3166
LS_IPARAM_IPM_OFF_COL_TRH                                    = 3167
LS_IPARAM_IPM_NUM_THREADS                                    = 3168
LS_IPARAM_IPM_CHECK_CONVEXITY                                = 3169

# Nonlinear programming (NLP) parameters (2500 - 25++) #/
LS_IPARAM_NLP_SOLVE_AS_LP                                    = 2500
LS_IPARAM_NLP_SOLVER                                         = 2501
LS_IPARAM_NLP_SUBSOLVER                                      = 2502
LS_IPARAM_NLP_PRINTLEVEL                                     = 2503
LS_DPARAM_NLP_PSTEP_FINITEDIFF                               = 2504
LS_IPARAM_NLP_DERIV_DIFFTYPE                                 = 2505
LS_DPARAM_NLP_FEASTOL                                        = 2506
LS_DPARAM_NLP_REDGTOL                                        = 2507
LS_IPARAM_NLP_USE_CRASH                                      = 2508
LS_IPARAM_NLP_USE_STEEPEDGE                                  = 2509
LS_IPARAM_NLP_USE_SLP                                        = 2510
LS_IPARAM_NLP_USE_SELCONEVAL                                 = 2511
LS_IPARAM_NLP_PRELEVEL                                       = 2512
LS_IPARAM_NLP_ITRLMT                                         = 2513
LS_IPARAM_NLP_LINEARZ                                        = 2514
LS_IPARAM_NLP_LINEARITY                                      = 2515
LS_IPARAM_NLP_STARTPOINT                                     = 2516
LS_IPARAM_NLP_CONVEXRELAX                                    = 2517
LS_IPARAM_NLP_CR_ALG_REFORM                                  = 2518
LS_IPARAM_NLP_QUADCHK                                        = 2519
LS_IPARAM_NLP_AUTODERIV                                      = 2520
LS_IPARAM_NLP_MAXLOCALSEARCH                                 = 2521
LS_IPARAM_NLP_CONVEX                                         = 2522
LS_IPARAM_NLP_CONOPT_VER                                     = 2523
LS_IPARAM_NLP_USE_LINDO_CRASH                                = 2524
LS_IPARAM_NLP_STALL_ITRLMT                                   = 2525
LS_IPARAM_NLP_AUTOHESS                                       = 2526
LS_IPARAM_NLP_FEASCHK                                        = 2527
LS_DPARAM_NLP_ITRLMT                                         = 2528
LS_IPARAM_NLP_MAXSUP                                         = 2529
LS_IPARAM_NLP_MSW_SOLIDX                                     = 2530
LS_IPARAM_NLP_ITERS_PER_LOGLINE                              = 2531
LS_IPARAM_NLP_MAX_RETRY                                      = 2532
LS_IPARAM_NLP_MSW_NORM                                       = 2533
LS_IPARAM_NLP_MSW_POPSIZE                                    = 2534
LS_IPARAM_NLP_MSW_MAXPOP                                     = 2535
LS_IPARAM_NLP_MSW_MAXNOIMP                                   = 2536
LS_IPARAM_NLP_MSW_FILTMODE                                   = 2537
LS_DPARAM_NLP_MSW_POXDIST_THRES                              = 2538
LS_DPARAM_NLP_MSW_EUCDIST_THRES                              = 2539
LS_DPARAM_NLP_MSW_XNULRAD_FACTOR                             = 2540
LS_DPARAM_NLP_MSW_XKKTRAD_FACTOR                             = 2541
LS_IPARAM_NLP_MAXLOCALSEARCH_TREE                            = 2542
LS_IPARAM_NLP_MSW_NUM_THREADS                                = 2543
LS_IPARAM_NLP_MSW_RG_SEED                                    = 2544
LS_IPARAM_NLP_MSW_PREPMODE                                   = 2545
LS_IPARAM_NLP_MSW_RMAPMODE                                   = 2546
LS_IPARAM_NLP_XSMODE                                         = 2547
LS_DPARAM_NLP_MSW_OVERLAP_RATIO                              = 2548
LS_DPARAM_NLP_INF                                            = 2549
LS_IPARAM_NLP_IPM2GRG                                        = 2550
LS_IPARAM_NLP_USE_SDP                                        = 2551
LS_IPARAM_NLP_LINEARZ_WB_CONSISTENT                          = 2552
LS_DPARAM_NLP_CUTOFFOBJ                                      = 2553
LS_IPARAM_NLP_USECUTOFFOBJ                                   = 2554
LS_IPARAM_NLP_CONIC_REFORM                                   = 2555

# Mixed integer programming (MIP) parameters (5000 - 5+++) #/
LS_IPARAM_MIP_TIMLIM                                         = 5300
LS_IPARAM_MIP_AOPTTIMLIM                                     = 5301
LS_IPARAM_MIP_LSOLTIMLIM                                     = 5302
LS_IPARAM_MIP_PRELEVEL                                       = 5303
LS_IPARAM_MIP_NODESELRULE                                    = 5304
LS_DPARAM_MIP_INTTOL                                         = 5305
LS_DPARAM_MIP_RELINTTOL                                      = 5306
LS_DPARAM_MIP_RELOPTTOL                                      = 5307
LS_DPARAM_MIP_PEROPTTOL                                      = 5308
LS_IPARAM_MIP_MAXCUTPASS_TOP                                 = 5309
LS_IPARAM_MIP_MAXCUTPASS_TREE                                = 5310
LS_DPARAM_MIP_ADDCUTPER                                      = 5311
LS_DPARAM_MIP_ADDCUTPER_TREE                                 = 5312
LS_IPARAM_MIP_MAXNONIMP_CUTPASS                              = 5313
LS_IPARAM_MIP_CUTLEVEL_TOP                                   = 5314
LS_IPARAM_MIP_CUTLEVEL_TREE                                  = 5315
LS_IPARAM_MIP_CUTTIMLIM                                      = 5316
LS_IPARAM_MIP_CUTDEPTH                                       = 5317
LS_IPARAM_MIP_CUTFREQ                                        = 5318
LS_IPARAM_MIP_HEULEVEL                                       = 5319
LS_IPARAM_MIP_PRINTLEVEL                                     = 5320
LS_IPARAM_MIP_PREPRINTLEVEL                                  = 5321
LS_DPARAM_MIP_CUTOFFOBJ                                      = 5322
LS_IPARAM_MIP_USECUTOFFOBJ                                   = 5323
LS_IPARAM_MIP_STRONGBRANCHLEVEL                              = 5324
LS_IPARAM_MIP_TREEREORDERLEVEL                               = 5325
LS_IPARAM_MIP_BRANCHDIR                                      = 5326
LS_IPARAM_MIP_TOPOPT                                         = 5327
LS_IPARAM_MIP_REOPT                                          = 5328
LS_IPARAM_MIP_SOLVERTYPE                                     = 5329
LS_IPARAM_MIP_KEEPINMEM                                      = 5330
LS_IPARAM_MIP_BRANCHRULE                                     = 5331
LS_DPARAM_MIP_REDCOSTFIX_CUTOFF                              = 5332
LS_DPARAM_MIP_ADDCUTOBJTOL                                   = 5333
LS_IPARAM_MIP_HEUMINTIMLIM                                   = 5334
LS_IPARAM_MIP_BRANCH_PRIO                                    = 5335
LS_IPARAM_MIP_SCALING_BOUND                                  = 5336
LS_DPARAM_MIP_PSEUDOCOST_WEIGT                               = 5337
LS_DPARAM_MIP_LBIGM                                          = 5338
LS_DPARAM_MIP_DELTA                                          = 5339
LS_IPARAM_MIP_DUAL_SOLUTION                                  = 5340
LS_IPARAM_MIP_BRANCH_LIMIT                                   = 5341
LS_DPARAM_MIP_ITRLIM                                         = 5342
LS_IPARAM_MIP_AGGCUTLIM_TOP                                  = 5343
LS_IPARAM_MIP_AGGCUTLIM_TREE                                 = 5344
LS_DPARAM_MIP_SWITCHFAC_SIM_IPM_ITER                         = 5345
LS_IPARAM_MIP_ANODES_SWITCH_DF                               = 5346
LS_DPARAM_MIP_ABSOPTTOL                                      = 5347
LS_DPARAM_MIP_MINABSOBJSTEP                                  = 5348
LS_IPARAM_MIP_PSEUDOCOST_RULE                                = 5349
LS_IPARAM_MIP_ENUM_HEUMODE                                   = 5350
LS_IPARAM_MIP_PRELEVEL_TREE                                  = 5351
LS_DPARAM_MIP_REDCOSTFIX_CUTOFF_TREE                         = 5352
LS_IPARAM_MIP_USE_INT_ZERO_TOL                               = 5353
LS_IPARAM_MIP_USE_CUTS_HEU                                   = 5354
LS_DPARAM_MIP_BIGM_FOR_INTTOL                                = 5355
LS_IPARAM_MIP_STRONGBRANCHDONUM                              = 5366
LS_IPARAM_MIP_MAKECUT_INACTIVE_COUNT                         = 5367
LS_IPARAM_MIP_PRE_ELIM_FILL                                  = 5368
LS_IPARAM_MIP_HEU_MODE                                       = 5369
LS_DPARAM_MIP_TIMLIM                                         = 5370
LS_DPARAM_MIP_AOPTTIMLIM                                     = 5371
LS_DPARAM_MIP_LSOLTIMLIM                                     = 5372
LS_DPARAM_MIP_CUTTIMLIM                                      = 5373
LS_DPARAM_MIP_HEUMINTIMLIM                                   = 5374
LS_IPARAM_MIP_FP_MODE                                        = 5375
LS_DPARAM_MIP_FP_WEIGHT                                      = 5376
LS_IPARAM_MIP_FP_OPT_METHOD                                  = 5377
LS_DPARAM_MIP_FP_TIMLIM                                      = 5378
LS_IPARAM_MIP_FP_ITRLIM                                      = 5379
LS_IPARAM_MIP_FP_HEU_MODE                                    = 5380
LS_DPARAM_MIP_OBJ_THRESHOLD                                  = 5381
LS_IPARAM_MIP_LOCALBRANCHNUM                                 = 5382
LS_DPARAM_MIP_SWITCHFAC_SIM_IPM_TIME                         = 5383
LS_DPARAM_MIP_ITRLIM_SIM                                     = 5384
LS_DPARAM_MIP_ITRLIM_NLP                                     = 5385
LS_DPARAM_MIP_ITRLIM_IPM                                     = 5386
LS_IPARAM_MIP_MAXNUM_MIP_SOL_STORAGE                         = 5387
LS_IPARAM_MIP_CONCURRENT_TOPOPTMODE                          = 5388
LS_IPARAM_MIP_CONCURRENT_REOPTMODE                           = 5389
LS_IPARAM_MIP_PREHEU_LEVEL                                   = 5390
LS_IPARAM_MIP_PREHEU_PRE_LEVEL                               = 5391
LS_IPARAM_MIP_PREHEU_PRINT_LEVEL                             = 5392
LS_IPARAM_MIP_PREHEU_TC_ITERLIM                              = 5393
LS_IPARAM_MIP_PREHEU_DFE_VSTLIM                              = 5394
LS_IPARAM_MIP_PREHEU_VAR_SEQ                                 = 5395
LS_IPARAM_MIP_USE_PARTIALSOL_LEVEL                           = 5396
LS_IPARAM_MIP_GENERAL_MODE                                   = 5397
LS_IPARAM_MIP_NUM_THREADS                                    = 5398
LS_IPARAM_MIP_POLISH_NUM_BRANCH_NEXT                         = 5399
LS_IPARAM_MIP_POLISH_MAX_BRANCH_COUNT                        = 5400
LS_DPARAM_MIP_POLISH_ALPHA_TARGET                            = 5401
LS_IPARAM_MIP_CONCURRENT_STRATEGY                            = 5402
LS_DPARAM_MIP_BRANCH_TOP_VAL_DIFF_WEIGHT                     = 5403
LS_IPARAM_MIP_BASCUTS_DONUM                                  = 5404
LS_IPARAM_MIP_PARA_SUB                                       = 5405
LS_DPARAM_MIP_PARA_RND_ITRLMT                                = 5406
LS_DPARAM_MIP_PARA_INIT_NODE                                 = 5407
LS_IPARAM_MIP_PARA_ITR_MODE                                  = 5408
LS_IPARAM_MIP_PARA_FP                                        = 5409
LS_IPARAM_MIP_PARA_FP_MODE                                   = 5410
LS_IPARAM_MIP_HEU_DROP_OBJ                                   = 5411
LS_DPARAM_MIP_ABSCUTTOL                                      = 5412
LS_IPARAM_MIP_PERSPECTIVE_REFORM                             = 5413
LS_IPARAM_MIP_TREEREORDERMODE                                = 5414
LS_IPARAM_MIP_XSOLVER                                        = 5415
LS_IPARAM_MIP_BNB_TRY_BNP                                    = 5416
LS_IPARAM_MIP_KBEST_USE_GOP                                  = 5417
LS_IPARAM_MIP_SYMMETRY_MODE                                  = 5418
LS_IPARAM_MIP_ALLDIFF_METHOD                                 = 5419
LS_IPARAM_MIP_SOLLIM                                         = 5420

# Global optimization (GOP) parameters (6000 - 6+++) #/
LS_DPARAM_GOP_RELOPTTOL                                      = 6400
LS_DPARAM_GOP_FLTTOL                                         = 6401
LS_DPARAM_GOP_BOXTOL                                         = 6402
LS_DPARAM_GOP_WIDTOL                                         = 6403
LS_DPARAM_GOP_DELTATOL                                       = 6404
LS_DPARAM_GOP_BNDLIM                                         = 6405
LS_IPARAM_GOP_TIMLIM                                         = 6406
LS_IPARAM_GOP_OPTCHKMD                                       = 6407
LS_IPARAM_GOP_BRANCHMD                                       = 6408
LS_IPARAM_GOP_MAXWIDMD                                       = 6409
LS_IPARAM_GOP_PRELEVEL                                       = 6410
LS_IPARAM_GOP_POSTLEVEL                                      = 6411
LS_IPARAM_GOP_BBSRCHMD                                       = 6412
LS_IPARAM_GOP_DECOMPPTMD                                     = 6413
LS_IPARAM_GOP_ALGREFORMMD                                    = 6414
LS_IPARAM_GOP_RELBRNDMD                                      = 6415
LS_IPARAM_GOP_PRINTLEVEL                                     = 6416
LS_IPARAM_GOP_BNDLIM_MODE                                    = 6417
LS_IPARAM_GOP_BRANCH_LIMIT                                   = 6418
LS_IPARAM_GOP_CORELEVEL                                      = 6419
LS_IPARAM_GOP_OPT_MODE                                       = 6420
LS_IPARAM_GOP_HEU_MODE                                       = 6421
LS_IPARAM_GOP_SUBOUT_MODE                                    = 6422
LS_IPARAM_GOP_USE_NLPSOLVE                                   = 6423
LS_IPARAM_GOP_LSOLBRANLIM                                    = 6424
LS_IPARAM_GOP_LPSOPT                                         = 6425
LS_DPARAM_GOP_TIMLIM                                         = 6426
LS_DPARAM_GOP_BRANCH_LIMIT                                   = 6427
LS_IPARAM_GOP_QUADMD                                         = 6428
LS_IPARAM_GOP_LIM_MODE                                       = 6429
LS_DPARAM_GOP_ITRLIM                                         = 6430
LS_DPARAM_GOP_ITRLIM_SIM                                     = 6431
LS_DPARAM_GOP_ITRLIM_IPM                                     = 6432
LS_DPARAM_GOP_ITRLIM_NLP                                     = 6433
LS_DPARAM_GOP_ABSOPTTOL                                      = 6434
LS_DPARAM_GOP_PEROPTTOL                                      = 6435
LS_DPARAM_GOP_AOPTTIMLIM                                     = 6436
LS_IPARAM_GOP_LINEARZ                                        = 6437
LS_IPARAM_GOP_NUM_THREADS                                    = 6438
LS_IPARAM_GOP_MULTILINEAR                                    = 6439
LS_DPARAM_GOP_OBJ_THRESHOLD                                  = 6440
LS_IPARAM_GOP_QUAD_METHOD                                    = 6441
LS_IPARAM_GOP_SOLLIM                                         = 6442
LS_IPARAM_GOP_CMINLP                                         = 6443
LS_IPARAM_GOP_CONIC_REFORM                                   = 6444

# License information parameters #/
LS_IPARAM_LIC_CONSTRAINTS                                    = 500
LS_IPARAM_LIC_VARIABLES                                      = 501
LS_IPARAM_LIC_INTEGERS                                       = 502
LS_IPARAM_LIC_NONLINEARVARS                                  = 503
LS_IPARAM_LIC_GOP_INTEGERS                                   = 504
LS_IPARAM_LIC_GOP_NONLINEARVARS                              = 505
LS_IPARAM_LIC_DAYSTOEXP                                      = 506
LS_IPARAM_LIC_DAYSTOTRIALEXP                                 = 507
LS_IPARAM_LIC_NONLINEAR                                      = 508
LS_IPARAM_LIC_EDUCATIONAL                                    = 509
LS_IPARAM_LIC_RUNTIME                                        = 510
LS_IPARAM_LIC_NUMUSERS                                       = 511
LS_IPARAM_LIC_BARRIER                                        = 512
LS_IPARAM_LIC_GLOBAL                                         = 513
LS_IPARAM_LIC_PLATFORM                                       = 514
LS_IPARAM_LIC_MIP                                            = 515
LS_IPARAM_LIC_SP                                             = 516
LS_IPARAM_LIC_CONIC                                          = 517
LS_IPARAM_LIC_RESERVED1                                      = 519

# Model analysis parameters (1500 - 15++) #/
LS_IPARAM_IIS_ANALYZE_LEVEL                                  = 1550
LS_IPARAM_IUS_ANALYZE_LEVEL                                  = 1551
LS_IPARAM_IIS_TOPOPT                                         = 1552
LS_IPARAM_IIS_REOPT                                          = 1553
LS_IPARAM_IIS_USE_SFILTER                                    = 1554
LS_IPARAM_IIS_PRINT_LEVEL                                    = 1555
LS_IPARAM_IIS_INFEAS_NORM                                    = 1556
LS_IPARAM_IIS_ITER_LIMIT                                     = 1557
LS_DPARAM_IIS_ITER_LIMIT                                     = 1558
LS_IPARAM_IIS_TIME_LIMIT                                     = 1559
LS_IPARAM_IIS_METHOD                                         = 1560
LS_IPARAM_IIS_USE_EFILTER                                    = 1561
LS_IPARAM_IIS_USE_GOP                                        = 1562
LS_IPARAM_IIS_NUM_THREADS                                    = 1563
LS_IPARAM_IIS_GETMODE                                        = 1564

# Output log format parameter #/
LS_IPARAM_FMT_ISSQL                                          = 1590

# Stochastic Parameters (6000 - 6+++) #/

#! @ingroup LSstocParam @{ #/
#! Common sample size per stochastic parameter. #/
LS_IPARAM_STOC_NSAMPLE_SPAR                                  = 6600
#! Common sample size per stage.  #/
LS_IPARAM_STOC_NSAMPLE_STAGE                                 = 6601
#! Seed to initialize the random number generator. #/
LS_IPARAM_STOC_RG_SEED                                       = 6602
#! Stochastic optimization method to solve the model. #/
LS_IPARAM_STOC_METHOD                                        = 6603
#! Reoptimization method to solve the node-models. #/
LS_IPARAM_STOC_REOPT                                         = 6604
#! Optimization method to solve the root problem. #/
LS_IPARAM_STOC_TOPOPT                                        = 6605
#! Iteration limit for stochastic solver. #/
LS_IPARAM_STOC_ITER_LIM                                      = 6606
#! Print level to display progress information during optimization #/
LS_IPARAM_STOC_PRINT_LEVEL                                   = 6607
#! Type of deterministic equivalent #/
LS_IPARAM_STOC_DETEQ_TYPE                                    = 6608
#! Flag to enable/disable calculation of EVPI. #/
LS_IPARAM_STOC_CALC_EVPI                                     = 6609

#! Flag to restrict sampling to continuous stochastic parameters only or not.#/
LS_IPARAM_STOC_SAMP_CONT_ONLY                                = 6611

#! Bucket size in Benders decomposition #/
LS_IPARAM_STOC_BUCKET_SIZE                                   = 6612
#! Maximum number of scenarios before forcing automatic sampling #/
LS_IPARAM_STOC_MAX_NUMSCENS                                  = 6613
#! Stage beyond which node-models are shared #/
LS_IPARAM_STOC_SHARE_BEGSTAGE                                = 6614
#! Print level to display progress information during optimization of node models #/
LS_IPARAM_STOC_NODELP_PRELEVEL                               = 6615

#! Time limit for stochastic solver.#/
LS_DPARAM_STOC_TIME_LIM                                      = 6616
#! Relative optimality tolerance (w.r.t lower and upper bounds on the true objective) to stop the solver. #/
LS_DPARAM_STOC_RELOPTTOL                                     = 6617
#! Absolute optimality tolerance (w.r.t lower and upper bounds on the true objective) to stop the solver. #/
LS_DPARAM_STOC_ABSOPTTOL                                     = 6618
#! Internal mask #/
LS_IPARAM_STOC_DEBUG_MASK                                    = 6619
#! Sampling method for variance reduction. #/
LS_IPARAM_STOC_VARCONTROL_METHOD                             = 6620
#! Correlation type associated with correlation matrix.  #/
LS_IPARAM_STOC_CORRELATION_TYPE                              = 6621
#! Warm start basis for wait-see model  .  #/
LS_IPARAM_STOC_WSBAS                                         = 6622

#! Outer loop iteration limit for ALD  .  #/
LS_IPARAM_STOC_ALD_OUTER_ITER_LIM                            = 6623
#! Inner loop iteration limit for ALD  .  #/
LS_IPARAM_STOC_ALD_INNER_ITER_LIM                            = 6624
#! Dual feasibility tolerance for ALD  .  #/
LS_DPARAM_STOC_ALD_DUAL_FEASTOL                              = 6625
#! Primal feasibility tolerance for ALD  .  #/
LS_DPARAM_STOC_ALD_PRIMAL_FEASTOL                            = 6626
#! Dual step length for ALD  .  #/
LS_DPARAM_STOC_ALD_DUAL_STEPLEN                              = 6627
#! Primal step length for ALD  .  #/
LS_DPARAM_STOC_ALD_PRIMAL_STEPLEN                            = 6628
#! Order nontemporal models or not.  #/
LS_IPARAM_CORE_ORDER_BY_STAGE                                = 6629

#! Node name format.  #/
LS_SPARAM_STOC_FMT_NODE_NAME                                 = 6630
#! Scenario name format.  #/
LS_SPARAM_STOC_FMT_SCENARIO_NAME                             = 6631
#! Flag to specify whether stochastic parameters in MPI will be mapped as LP matrix elements.  #/
LS_IPARAM_STOC_MAP_MPI2LP                                    = 6632
#! Flag to enable or disable autoaggregation #/
LS_IPARAM_STOC_AUTOAGGR                                      = 6633
#! Benchmark scenario to compare EVPI and EVMU against#/
LS_IPARAM_STOC_BENCHMARK_SCEN                                = 6634
#! Value to truncate infinite bounds at non-leaf nodes #/
LS_DPARAM_STOC_INFBND                                        = 6635
#! Flag to use add-instructions mode when building deteq #/
LS_IPARAM_STOC_ADD_MPI                                       = 6636
# Flag to enable elimination of fixed variables from deteq MPI #/
LS_IPARAM_STOC_ELIM_FXVAR                                    = 6637
#! RHS value of objective cut in SBD master problem.  #/
LS_DPARAM_STOC_SBD_OBJCUTVAL                                 = 6638
#! Flag to enable objective cut in SBD master problem.  #/
LS_IPARAM_STOC_SBD_OBJCUTFLAG                                = 6639
#! Maximum number of candidate solutions to generate at SBD root #/
LS_IPARAM_STOC_SBD_NUMCANDID                                 = 6640
#! Big-M value for linearization and penalty functions #/
LS_DPARAM_STOC_BIGM                                          = 6641
#! Name data level #/
LS_IPARAM_STOC_NAMEDATA_LEVEL                                = 6642
#! Max cuts to generate for master problem #/
LS_IPARAM_STOC_SBD_MAXCUTS                                   = 6643
#! Optimization method to solve the deteq problem. #/
LS_IPARAM_STOC_DEQOPT                                        = 6644
#! Subproblem formulation to use in DirectSearch. #/
LS_IPARAM_STOC_DS_SUBFORM                                    = 6645
#! Primal-step tolerance #/
LS_DPARAM_STOC_REL_PSTEPTOL                                  = 6646
#! Dual-step tolerance #/
LS_DPARAM_STOC_REL_DSTEPTOL                                  = 6647
#! Number of parallel threads #/
LS_IPARAM_STOC_NUM_THREADS                                   = 6648
#! Number of deteq blocks #/
LS_IPARAM_STOC_DETEQ_NBLOCKS                                 = 6649

# Sampling parameters (7000 - 7+++) #/

#! Bitmask to enable methods for solving the nearest correlation matrix (NCM) subproblem #/
LS_IPARAM_SAMP_NCM_METHOD                                    = 7701
#! Objective cutoff (target) value to stop the nearest correlation matrix (NCM) subproblem #/
LS_DPARAM_SAMP_NCM_CUTOBJ                                    = 7702
#! Flag to enable/disable sparse mode in NCM computations #/
LS_IPARAM_SAMP_NCM_DSTORAGE                                  = 7703
#! Correlation matrix diagonal shift increment #/
LS_DPARAM_SAMP_CDSINC                                        = 7704
#! Flag to enable scaling of raw sample data #/
LS_IPARAM_SAMP_SCALE                                         = 7705
#! Iteration limit for NCM method #/
LS_IPARAM_SAMP_NCM_ITERLIM                                   = 7706
#! Optimality tolerance for NCM method #/
LS_DPARAM_SAMP_NCM_OPTTOL                                    = 7707
#! Number of parallel threads #/
LS_IPARAM_SAMP_NUM_THREADS                                   = 7708
#! Buffer size for random number generators #/
LS_IPARAM_SAMP_RG_BUFFER_SIZE                                = 7709

#Branch And Price parameters (8000 - 8499) #/

#bound size when subproblem is unbounded#/
LS_DPARAM_BNP_INFBND                                         = 8010
#branch and bound type#/
LS_IPARAM_BNP_LEVEL                                          = 8011
#print level#/
LS_IPARAM_BNP_PRINT_LEVEL                                    = 8012
#box size for BOXSTEP method#/
LS_DPARAM_BNP_BOX_SIZE                                       = 8013
#number of threads in bnp#/
LS_IPARAM_BNP_NUM_THREADS                                    = 8014
#relative optimality tolerance for subproblems#/
LS_DPARAM_BNP_SUB_ITRLMT                                     = 8015
#method for finding block structure#/
LS_IPARAM_BNP_FIND_BLK                                       = 8016
#pre level#/
LS_IPARAM_BNP_PRELEVEL                                       = 8017
#column limit#/
LS_DPARAM_BNP_COL_LMT                                        = 8018
#time limit for bnp#/
LS_DPARAM_BNP_TIMLIM                                         = 8019
#simplex limit for bnp#/
LS_DPARAM_BNP_ITRLIM_SIM                                     = 8020
#ipm limit for bnp#/
LS_DPARAM_BNP_ITRLIM_IPM                                     = 8021
#branch limit for bnp#/
LS_IPARAM_BNP_BRANCH_LIMIT                                   = 8022
#iteration limit for bnp#/
LS_DPARAM_BNP_ITRLIM                                         = 8023

# Genetic Algorithm Parameters (8500-8+++) #/

#  Probability of crossover for continuous variables #/
LS_DPARAM_GA_CXOVER_PROB                                     = 8501
#  Spreading factor for crossover #/
LS_DPARAM_GA_XOVER_SPREAD                                    = 8502
#  Probability of crossover for integer variables #/
LS_DPARAM_GA_IXOVER_PROB                                     = 8503
#  Probability of mutation for continuous variables #/
LS_DPARAM_GA_CMUTAT_PROB                                     = 8504
#  Spreading factor for mutation #/
LS_DPARAM_GA_MUTAT_SPREAD                                    = 8505
#  Probability of mutation for integer variables #/
LS_DPARAM_GA_IMUTAT_PROB                                     = 8506
#  Numeric zero tolerance in GA #/
LS_DPARAM_GA_TOL_ZERO                                        = 8507
#  Primal feasibility tolerance in GA #/
LS_DPARAM_GA_TOL_PFEAS                                       = 8508
#  Numeric infinity in GA #/
LS_DPARAM_GA_INF                                             = 8509
#  Infinity threshold for finite bounds in GA #/
LS_DPARAM_GA_INFBND                                          = 8510
#  Alpha parameter in Blending Alpha Crossover method #/
LS_DPARAM_GA_BLXA                                            = 8511
#  Beta parameter in Blending Alpha-Beta Crossover method #/
LS_DPARAM_GA_BLXB                                            = 8512
#  Method of crossover for continuous variables #/
LS_IPARAM_GA_CXOVER_METHOD                                   = 8513
#  Method of crossover for integer variables #/
LS_IPARAM_GA_IXOVER_METHOD                                   = 8514
#  Method of mutation for continuous variables #/
LS_IPARAM_GA_CMUTAT_METHOD                                   = 8515
#  Method of mutation for integer variables #/
LS_IPARAM_GA_IMUTAT_METHOD                                   = 8516
#  RNG seed for GA #/
LS_IPARAM_GA_SEED                                            = 8517
#  Number of generations in GA #/
LS_IPARAM_GA_NGEN                                            = 8518
#  Population size in GA #/
LS_IPARAM_GA_POPSIZE                                         = 8519
#  Print level to log files #/
LS_IPARAM_GA_FILEOUT                                         = 8520
#  Print level for GA #/
LS_IPARAM_GA_PRINTLEVEL                                      = 8521
#  Flag to specify whether an optimum individual will be injected #/
LS_IPARAM_GA_INJECT_OPT                                      = 8522
#  Number of threads in GA #/
LS_IPARAM_GA_NUM_THREADS                                     = 8523
#  Objective function sense #/
LS_IPARAM_GA_OBJDIR                                          = 8524
#  Target objective function value #/
LS_DPARAM_GA_OBJSTOP                                         = 8525
#  Migration probability  #/
LS_DPARAM_GA_MIGRATE_PROB                                    = 8526
#  Search space or search mode  #/
LS_IPARAM_GA_SSPACE                                          = 8527
#! @} #/

# Version info #/
LS_IPARAM_VER_MAJOR                                          = 990
LS_IPARAM_VER_MINOR                                          = 991
LS_IPARAM_VER_BUILD                                          = 992
LS_IPARAM_VER_REVISION                                       = 993

# Last card for parameters #/
LS_IPARAM_VER_NUMBER                                         = 999


# Math operator codes (1000-1500) #/
EP_NO_OP                                                     = 0000
EP_PLUS                                                      = 1001
EP_MINUS                                                     = 1002
EP_MULTIPLY                                                  = 1003
EP_DIVIDE                                                    = 1004
EP_POWER                                                     = 1005
EP_EQUAL                                                     = 1006
EP_NOT_EQUAL                                                 = 1007
EP_LTOREQ                                                    = 1008
EP_GTOREQ                                                    = 1009
EP_LTHAN                                                     = 1010
EP_GTHAN                                                     = 1011
EP_AND                                                       = 1012
EP_OR                                                        = 1013
EP_NOT                                                       = 1014
EP_PERCENT                                                   = 1015
EP_POSATE                                                    = 1016
EP_NEGATE                                                    = 1017
EP_ABS                                                       = 1018
EP_SQRT                                                      = 1019
EP_LOG                                                       = 1020
EP_LN                                                        = 1021
EP_PI                                                        = 1022
EP_SIN                                                       = 1023
EP_COS                                                       = 1024
EP_TAN                                                       = 1025
EP_ATAN2                                                     = 1026
EP_ATAN                                                      = 1027
EP_ASIN                                                      = 1028
EP_ACOS                                                      = 1029
EP_EXP                                                       = 1030
EP_MOD                                                       = 1031
EP_FALSE                                                     = 1032
EP_TRUE                                                      = 1033
EP_IF                                                        = 1034
EP_PSN                                                       = 1035
EP_PSL                                                       = 1036
EP_LGM                                                       = 1037
EP_SIGN                                                      = 1038
EP_FLOOR                                                     = 1039
EP_FPA                                                       = 1040
EP_FPL                                                       = 1041
EP_PEL                                                       = 1042
EP_PEB                                                       = 1043
EP_PPS                                                       = 1044
EP_PPL                                                       = 1045
EP_PTD                                                       = 1046
EP_PCX                                                       = 1047
EP_WRAP                                                      = 1048
EP_PBNO                                                      = 1049
EP_PFS                                                       = 1050
EP_PFD                                                       = 1051
EP_PHG                                                       = 1052
EP_RAND                                                      = 1053
EP_USER                                                      = 1054
EP_SUM                                                       = 1055
EP_AVG                                                       = 1056
EP_MIN                                                       = 1057
EP_MAX                                                       = 1058
EP_NPV                                                       = 1059
EP_VAND                                                      = 1060
EP_VOR                                                       = 1061
EP_PUSH_NUM                                                  = 1062
EP_PUSH_VAR                                                  = 1063
EP_NORMDENS                                                  = 1064
EP_NORMINV                                                   = 1065
EP_TRIAINV                                                   = 1066
EP_EXPOINV                                                   = 1067
EP_UNIFINV                                                   = 1068
EP_MULTINV                                                   = 1069
EP_USRCOD                                                    = 1070
EP_SUMPROD                                                   = 1071
EP_SUMIF                                                     = 1072
EP_VLOOKUP                                                   = 1073
EP_VPUSH_NUM                                                 = 1074
EP_VPUSH_VAR                                                 = 1075
EP_VMULT                                                     = 1076
EP_SQR                                                       = 1077
EP_SINH                                                      = 1078
EP_COSH                                                      = 1079
EP_TANH                                                      = 1080
EP_ASINH                                                     = 1081
EP_ACOSH                                                     = 1082
EP_ATANH                                                     = 1083
EP_LOGB                                                      = 1084
EP_LOGX                                                      = 1085
EP_LNX                                                       = 1086
EP_TRUNC                                                     = 1087
EP_NORMSINV                                                  = 1088
EP_INT                                                       = 1089
EP_PUSH_STR                                                  = 1090
EP_VPUSH_STR                                                 = 1091
EP_PUSH_SPAR                                                 = 1092
EP_NORMPDF                                                   = 1093
EP_NORMCDF                                                   = 1094
EP_LSQ                                                       = 1095
EP_LNPSNX                                                    = 1096
EP_LNCPSN                                                    = 1097
EP_XEXPNAX                                                   = 1098
EP_XNEXPMX                                                   = 1099
# Probability density functions #/
EP_PBT                                                       = 1100
EP_PBTINV                                                    = 1101
EP_PBNINV                                                    = 1102
EP_PCC                                                       = 1103
EP_PCCINV                                                    = 1104
EP_PCXINV                                                    = 1105
EP_EXPN                                                      = 1106
EP_PFDINV                                                    = 1107
EP_PGA                                                       = 1108
EP_PGAINV                                                    = 1109
EP_PGE                                                       = 1110
EP_PGEINV                                                    = 1111
EP_PGU                                                       = 1112
EP_PGUINV                                                    = 1113
EP_PHGINV                                                    = 1114
EP_PLA                                                       = 1115
EP_PLAINV                                                    = 1116
EP_PLG                                                       = 1117
EP_PLGINV                                                    = 1118
EP_LGT                                                       = 1119
EP_LGTINV                                                    = 1120
EP_LGNM                                                      = 1121
EP_LGNMINV                                                   = 1122
EP_NGBN                                                      = 1123
EP_NGBNINV                                                   = 1124
EP_NRM                                                       = 1125
EP_PPT                                                       = 1126
EP_PPTINV                                                    = 1127
EP_PPSINV                                                    = 1128
EP_PTDINV                                                    = 1129
EP_TRIAN                                                     = 1130
EP_UNIFM                                                     = 1131
EP_PWB                                                       = 1132
EP_PWBINV                                                    = 1133
EP_NRMINV                                                    = 1134
EP_TRIANINV                                                  = 1135
EP_EXPNINV                                                   = 1136
EP_UNIFMINV                                                  = 1137
EP_MLTNMINV                                                  = 1138
EP_BTDENS                                                    = 1139
EP_BNDENS                                                    = 1140
EP_CCDENS                                                    = 1141
EP_CXDENS                                                    = 1142
EP_EXPDENS                                                   = 1143
EP_FDENS                                                     = 1144
EP_GADENS                                                    = 1145
EP_GEDENS                                                    = 1146
EP_GUDENS                                                    = 1147
EP_HGDENS                                                    = 1148
EP_LADENS                                                    = 1149
EP_LGDENS                                                    = 1150
EP_LGTDENS                                                   = 1151
EP_LGNMDENS                                                  = 1152
EP_NGBNDENS                                                  = 1153
EP_NRMDENS                                                   = 1154
EP_PTDENS                                                    = 1155
EP_PSDENS                                                    = 1156
EP_TDENS                                                     = 1157
EP_TRIADENS                                                  = 1158
EP_UNIFDENS                                                  = 1159
EP_WBDENS                                                    = 1160
EP_RADIANS                                                   = 1161
EP_DEGREES                                                   = 1162
EP_ROUND                                                     = 1163
EP_ROUNDUP                                                   = 1164
EP_ROUNDDOWN                                                 = 1165
EP_ERF                                                       = 1166
EP_PBN                                                       = 1167
EP_PBB                                                       = 1168
EP_PBBINV                                                    = 1169
EP_BBDENS                                                    = 1170
EP_PSS                                                       = 1171
EP_SSDENS                                                    = 1172
EP_SSINV                                                     = 1173
EP_POSD                                                      = 1174
EP_SETS                                                      = 1175
EP_CARD                                                      = 1176
EP_STDEV                                                     = 1177
EP_LMTD                                                      = 1178
EP_RLMTD                                                     = 1179
EP_LOGIT                                                     = 1180
EP_ALLDIFF                                                   = 1181
EP_SIGNPOWER                                                 = 1182
EP_QUADPROD                                                  = 1183
EP_ATAN2R                                                    = 1184
EP_XPOWDIVAB                                                 = 1185
EP_LOGABEXPX                                                 = 1186
EP_LOGSUMEXP                                                 = 1187
EP_LOGSUMAEXP                                                = 1188


# Model and solution information codes ( 110xx-140xx) #/
# Model statistics (11001-11199)#/
LS_IINFO_NUM_NONZ_OBJ                                        = 11001
LS_IINFO_NUM_SEMICONT                                        = 11002
LS_IINFO_NUM_SETS                                            = 11003
LS_IINFO_NUM_SETS_NNZ                                        = 11004
LS_IINFO_NUM_QCP_CONS                                        = 11005
LS_IINFO_NUM_CONT_CONS                                       = 11006
LS_IINFO_NUM_INT_CONS                                        = 11007
LS_IINFO_NUM_BIN_CONS                                        = 11008
LS_IINFO_NUM_QCP_VARS                                        = 11009
LS_IINFO_NUM_CONS                                            = 11010
LS_IINFO_NUM_VARS                                            = 11011
LS_IINFO_NUM_NONZ                                            = 11012
LS_IINFO_NUM_BIN                                             = 11013
LS_IINFO_NUM_INT                                             = 11014
LS_IINFO_NUM_CONT                                            = 11015
LS_IINFO_NUM_QC_NONZ                                         = 11016
LS_IINFO_NUM_NLP_NONZ                                        = 11017
LS_IINFO_NUM_NLPOBJ_NONZ                                     = 11018
LS_IINFO_NUM_RDCONS                                          = 11019
LS_IINFO_NUM_RDVARS                                          = 11020
LS_IINFO_NUM_RDNONZ                                          = 11021
LS_IINFO_NUM_RDINT                                           = 11022
LS_IINFO_LEN_VARNAMES                                        = 11023
LS_IINFO_LEN_CONNAMES                                        = 11024
LS_IINFO_NUM_NLP_CONS                                        = 11025
LS_IINFO_NUM_NLP_VARS                                        = 11026
LS_IINFO_NUM_SUF_ROWS                                        = 11027
LS_IINFO_NUM_IIS_ROWS                                        = 11028
LS_IINFO_NUM_SUF_BNDS                                        = 11029
LS_IINFO_NUM_IIS_BNDS                                        = 11030
LS_IINFO_NUM_SUF_COLS                                        = 11031
LS_IINFO_NUM_IUS_COLS                                        = 11032
LS_IINFO_NUM_CONES                                           = 11033
LS_IINFO_NUM_CONE_NONZ                                       = 11034
LS_IINFO_LEN_CONENAMES                                       = 11035
LS_DINFO_INST_VAL_MIN_COEF                                   = 11036
LS_IINFO_INST_VARNDX_MIN_COEF                                = 11037
LS_IINFO_INST_CONNDX_MIN_COEF                                = 11038
LS_DINFO_INST_VAL_MAX_COEF                                   = 11039
LS_IINFO_INST_VARNDX_MAX_COEF                                = 11040
LS_IINFO_INST_CONNDX_MAX_COEF                                = 11041
LS_IINFO_NUM_VARS_CARD                                       = 11042
LS_IINFO_NUM_VARS_SOS1                                       = 11043
LS_IINFO_NUM_VARS_SOS2                                       = 11044
LS_IINFO_NUM_VARS_SOS3                                       = 11045
LS_IINFO_NUM_VARS_SCONT                                      = 11046
LS_IINFO_NUM_CONS_L                                          = 11047
LS_IINFO_NUM_CONS_E                                          = 11048
LS_IINFO_NUM_CONS_G                                          = 11049
LS_IINFO_NUM_CONS_R                                          = 11050
LS_IINFO_NUM_CONS_N                                          = 11051
LS_IINFO_NUM_VARS_LB                                         = 11052
LS_IINFO_NUM_VARS_UB                                         = 11053
LS_IINFO_NUM_VARS_LUB                                        = 11054
LS_IINFO_NUM_VARS_FR                                         = 11055
LS_IINFO_NUM_VARS_FX                                         = 11056
LS_IINFO_NUM_INST_CODES                                      = 11057
LS_IINFO_NUM_INST_REAL_NUM                                   = 11058
LS_IINFO_NUM_SPARS                                           = 11059
LS_IINFO_NUM_PROCS                                           = 11060
LS_IINFO_NUM_POSDS                                           = 11061
LS_IINFO_NUM_SUF_INTS                                        = 11062
LS_IINFO_NUM_IIS_INTS                                        = 11063
LS_IINFO_NUM_OBJPOOL                                         = 11064
LS_IINFO_NUM_SOLPOOL                                         = 11065
LS_IINFO_NUM_ALLDIFF                                         = 11066
LS_IINFO_MAX_RNONZ                                           = 11067
LS_IINFO_MAX_CNONZ                                           = 11068
LS_DINFO_AVG_RNONZ                                           = 11069
LS_DINFO_AVG_CNONZ                                           = 11070
LS_IINFO_OBJIDX                                              = 11071
LS_IINFO_SOLIDX                                              = 11072
LS_DINFO_OBJRANK                                             = 11073
LS_DINFO_OBJWEIGHT                                           = 11074
LS_DINFO_OBJSENSE                                            = 11075
LS_DINFO_OBJRELTOL                                           = 11076
LS_DINFO_OBJABSTOL                                           = 11077

# LP and NLP related info (11200-11299)#/
LS_IINFO_METHOD                                              = 11200
LS_DINFO_POBJ                                                = 11201
LS_DINFO_DOBJ                                                = 11202
LS_DINFO_PINFEAS                                             = 11203
LS_DINFO_DINFEAS                                             = 11204
LS_IINFO_MODEL_STATUS                                        = 11205
LS_IINFO_PRIMAL_STATUS                                       = 11206
LS_IINFO_DUAL_STATUS                                         = 11207
LS_IINFO_BASIC_STATUS                                        = 11208
LS_IINFO_BAR_ITER                                            = 11209
LS_IINFO_SIM_ITER                                            = 11210
LS_IINFO_NLP_ITER                                            = 11211
LS_IINFO_ELAPSED_TIME                                        = 11212
LS_DINFO_MSW_POBJ                                            = 11213
LS_IINFO_MSW_PASS                                            = 11214
LS_IINFO_MSW_NSOL                                            = 11215
LS_IINFO_IPM_STATUS                                          = 11216
LS_DINFO_IPM_POBJ                                            = 11217
LS_DINFO_IPM_DOBJ                                            = 11218
LS_DINFO_IPM_PINFEAS                                         = 11219
LS_DINFO_IPM_DINFEAS                                         = 11220
LS_IINFO_NLP_CALL_FUN                                        = 11221
LS_IINFO_NLP_CALL_DEV                                        = 11222
LS_IINFO_NLP_CALL_HES                                        = 11223
LS_IINFO_CONCURRENT_OPTIMIZER                                = 11224
LS_IINFO_LEN_STAGENAMES                                      = 11225
LS_DINFO_BAR_ITER                                            = 11226
LS_DINFO_SIM_ITER                                            = 11227
LS_DINFO_NLP_ITER                                            = 11228
LS_IINFO_BAR_THREADS                                         = 11229
LS_IINFO_NLP_THREADS                                         = 11230
LS_IINFO_SIM_THREADS                                         = 11231
LS_DINFO_NLP_THRIMBL                                         = 11232
LS_SINFO_NLP_THREAD_LOAD                                     = 11233
LS_SINFO_BAR_THREAD_LOAD                                     = 11234
LS_SINFO_SIM_THREAD_LOAD                                     = 11235
LS_SINFO_ARCH                                                = 11236
LS_IINFO_ARCH_ID                                             = 11237
LS_IINFO_MSW_BESTRUNIDX                                      = 11238
LS_DINFO_ACONDEST                                            = 11239
LS_DINFO_BCONDEST                                            = 11240
LS_IINFO_LPTOOL                                              = 11241
LS_SINFO_MODEL_TYPE                                          = 11242
LS_IINFO_NLP_LINEARITY                                       = 11243
LS_DINFO_ALL_ITER                                            = 11244

# MIP and MINLP related info (11300-11400) #/
LS_IINFO_MIP_STATUS                                          = 11300
LS_DINFO_MIP_OBJ                                             = 11301
LS_DINFO_MIP_BESTBOUND                                       = 11302
LS_IINFO_MIP_SIM_ITER                                        = 11303
LS_IINFO_MIP_BAR_ITER                                        = 11304
LS_IINFO_MIP_NLP_ITER                                        = 11305
LS_IINFO_MIP_BRANCHCOUNT                                     = 11306
LS_IINFO_MIP_NEWIPSOL                                        = 11307
LS_IINFO_MIP_LPCOUNT                                         = 11308
LS_IINFO_MIP_ACTIVENODES                                     = 11309
LS_IINFO_MIP_LTYPE                                           = 11310
LS_IINFO_MIP_AOPTTIMETOSTOP                                  = 11311
LS_IINFO_MIP_NUM_TOTAL_CUTS                                  = 11312
LS_IINFO_MIP_GUB_COVER_CUTS                                  = 11313
LS_IINFO_MIP_FLOW_COVER_CUTS                                 = 11314
LS_IINFO_MIP_LIFT_CUTS                                       = 11315
LS_IINFO_MIP_PLAN_LOC_CUTS                                   = 11316
LS_IINFO_MIP_DISAGG_CUTS                                     = 11317
LS_IINFO_MIP_KNAPSUR_COVER_CUTS                              = 11318
LS_IINFO_MIP_LATTICE_CUTS                                    = 11319
LS_IINFO_MIP_GOMORY_CUTS                                     = 11320
LS_IINFO_MIP_COEF_REDC_CUTS                                  = 11321
LS_IINFO_MIP_GCD_CUTS                                        = 11322
LS_IINFO_MIP_OBJ_CUT                                         = 11323
LS_IINFO_MIP_BASIS_CUTS                                      = 11324
LS_IINFO_MIP_CARDGUB_CUTS                                    = 11325
LS_IINFO_MIP_CLIQUE_CUTS                                     = 11326
LS_IINFO_MIP_CONTRA_CUTS                                     = 11327
LS_IINFO_MIP_GUB_CONS                                        = 11328
LS_IINFO_MIP_GLB_CONS                                        = 11329
LS_IINFO_MIP_PLANTLOC_CONS                                   = 11330
LS_IINFO_MIP_DISAGG_CONS                                     = 11331
LS_IINFO_MIP_SB_CONS                                         = 11332
LS_IINFO_MIP_IKNAP_CONS                                      = 11333
LS_IINFO_MIP_KNAP_CONS                                       = 11334
LS_IINFO_MIP_NLP_CONS                                        = 11335
LS_IINFO_MIP_CONT_CONS                                       = 11336
LS_DINFO_MIP_TOT_TIME                                        = 11347
LS_DINFO_MIP_OPT_TIME                                        = 11348
LS_DINFO_MIP_HEU_TIME                                        = 11349
LS_IINFO_MIP_SOLSTATUS_LAST_BRANCH                           = 11350
LS_DINFO_MIP_SOLOBJVAL_LAST_BRANCH                           = 11351
LS_IINFO_MIP_HEU_LEVEL                                       = 11352
LS_DINFO_MIP_PFEAS                                           = 11353
LS_DINFO_MIP_INTPFEAS                                        = 11354
LS_IINFO_MIP_WHERE_IN_CODE                                   = 11355
LS_IINFO_MIP_FP_ITER                                         = 11356
LS_DINFO_MIP_FP_SUMFEAS                                      = 11357
LS_DINFO_MIP_RELMIPGAP                                       = 11358
LS_DINFO_MIP_ROOT_OPT_TIME                                   = 11359
LS_DINFO_MIP_ROOT_PRE_TIME                                   = 11360
LS_IINFO_MIP_ROOT_METHOD                                     = 11361
LS_DINFO_MIP_SIM_ITER                                        = 11362
LS_DINFO_MIP_BAR_ITER                                        = 11363
LS_DINFO_MIP_NLP_ITER                                        = 11364
LS_IINFO_MIP_TOP_RELAX_IS_NON_CONVEX                         = 11365
LS_DINFO_MIP_FP_TIME                                         = 11366
LS_IINFO_MIP_THREADS                                         = 11367
LS_SINFO_MIP_THREAD_LOAD                                     = 11368
LS_DINFO_MIP_ABSGAP                                          = 11369
LS_DINFO_MIP_RELGAP                                          = 11370
LS_IINFO_MIP_SOFTKNAP_CUTS                                   = 11371
LS_IINFO_MIP_LP_ROUND_CUTS                                   = 11372
LS_IINFO_MIP_PERSPECTIVE_CUTS                                = 11373
LS_IINFO_MIP_STRATEGY_MASK                                   = 11374
LS_DINFO_MIP_ALL_ITER                                        = 11375

# GOP related info (11601-11699) #/
LS_DINFO_GOP_OBJ                                             = 11600
LS_IINFO_GOP_SIM_ITER                                        = 11601
LS_IINFO_GOP_BAR_ITER                                        = 11602
LS_IINFO_GOP_NLP_ITER                                        = 11603
LS_DINFO_GOP_BESTBOUND                                       = 11604
LS_IINFO_GOP_STATUS                                          = 11605
LS_IINFO_GOP_LPCOUNT                                         = 11606
LS_IINFO_GOP_NLPCOUNT                                        = 11607
LS_IINFO_GOP_MIPCOUNT                                        = 11608
LS_IINFO_GOP_NEWSOL                                          = 11609
LS_IINFO_GOP_BOX                                             = 11610
LS_IINFO_GOP_BBITER                                          = 11611
LS_IINFO_GOP_SUBITER                                         = 11612
LS_IINFO_GOP_MIPBRANCH                                       = 11613
LS_IINFO_GOP_ACTIVEBOXES                                     = 11614
LS_IINFO_GOP_TOT_TIME                                        = 11615
LS_IINFO_GOP_MAXDEPTH                                        = 11616
LS_DINFO_GOP_PFEAS                                           = 11617
LS_DINFO_GOP_INTPFEAS                                        = 11618
LS_DINFO_GOP_SIM_ITER                                        = 11619
LS_DINFO_GOP_BAR_ITER                                        = 11620
LS_DINFO_GOP_NLP_ITER                                        = 11621
LS_DINFO_GOP_LPCOUNT                                         = 11622
LS_DINFO_GOP_NLPCOUNT                                        = 11623
LS_DINFO_GOP_MIPCOUNT                                        = 11624
LS_DINFO_GOP_BBITER                                          = 11625
LS_DINFO_GOP_SUBITER                                         = 11626
LS_DINFO_GOP_MIPBRANCH                                       = 11627
LS_DINFO_GOP_FIRST_TIME                                      = 11628
LS_DINFO_GOP_BEST_TIME                                       = 11629
LS_DINFO_GOP_TOT_TIME                                        = 11630
LS_IINFO_GOP_THREADS                                         = 11631
LS_SINFO_GOP_THREAD_LOAD                                     = 11632
LS_DINFO_GOP_ABSGAP                                          = 11633
LS_DINFO_GOP_RELGAP                                          = 11634

# Progress info during callbacks #/
LS_DINFO_SUB_OBJ                                             = 11700
LS_DINFO_SUB_PINF                                            = 11701
LS_DINFO_CUR_OBJ                                             = 11702
LS_IINFO_CUR_ITER                                            = 11703
LS_DINFO_CUR_BEST_BOUND                                      = 11704
LS_IINFO_CUR_STATUS                                          = 11705
LS_IINFO_CUR_LP_COUNT                                        = 11706
LS_IINFO_CUR_BRANCH_COUNT                                    = 11707
LS_IINFO_CUR_ACTIVE_COUNT                                    = 11708
LS_IINFO_CUR_NLP_COUNT                                       = 11709
LS_IINFO_CUR_MIP_COUNT                                       = 11710
LS_IINFO_CUR_CUT_COUNT                                       = 11711
LS_DINFO_CUR_ITER                                            = 11712
LS_DINFO_CUR_TIME                                            = 11713
LS_IINFO_CUR_OBJIDX                                          = 11714
LS_IINFO_LAST_OBJIDX_SOL                                     = 11715
LS_IINFO_LAST_OBJIDX_OPT                                     = 11716

# Model generation progress info (1800+)#/
LS_DINFO_GEN_PERCENT                                         = 11800
LS_IINFO_GEN_NONZ_TTL                                        = 11801
LS_IINFO_GEN_NONZ_NL                                         = 11802
LS_IINFO_GEN_ROW_NL                                          = 11803
LS_IINFO_GEN_VAR_NL                                          = 11804

# IIS-IUS info #/
LS_IINFO_IIS_BAR_ITER                                        = 11850
LS_IINFO_IIS_SIM_ITER                                        = 11851
LS_IINFO_IIS_NLP_ITER                                        = 11852
LS_DINFO_IIS_BAR_ITER                                        = 11853
LS_DINFO_IIS_SIM_ITER                                        = 11854
LS_DINFO_IIS_NLP_ITER                                        = 11855
LS_IINFO_IIS_TOT_TIME                                        = 11856
LS_IINFO_IIS_ACT_NODE                                        = 11857
LS_IINFO_IIS_LPCOUNT                                         = 11858
LS_IINFO_IIS_NLPCOUNT                                        = 11859
LS_IINFO_IIS_MIPCOUNT                                        = 11860
LS_IINFO_IIS_THREADS                                         = 11861
LS_SINFO_IIS_THREAD_LOAD                                     = 11862
LS_IINFO_IIS_STATUS                                          = 11863

LS_IINFO_IUS_BAR_ITER                                        = 11875
LS_IINFO_IUS_SIM_ITER                                        = 11876
LS_IINFO_IUS_NLP_ITER                                        = 11877
LS_DINFO_IUS_BAR_ITER                                        = 11878
LS_DINFO_IUS_SIM_ITER                                        = 11879
LS_DINFO_IUS_NLP_ITER                                        = 11880
LS_IINFO_IUS_TOT_TIME                                        = 11881
LS_IINFO_IUS_ACT_NODE                                        = 11882
LS_IINFO_IUS_LPCOUNT                                         = 11883
LS_IINFO_IUS_NLPCOUNT                                        = 11884
LS_IINFO_IUS_MIPCOUNT                                        = 11885
LS_IINFO_IUS_THREADS                                         = 11886
LS_SINFO_IUS_THREAD_LOAD                                     = 11887
LS_IINFO_IUS_STATUS                                          = 11888

# Presolve info    #/
LS_IINFO_PRE_NUM_RED                                         = 11900
LS_IINFO_PRE_TYPE_RED                                        = 11901
LS_IINFO_PRE_NUM_RDCONS                                      = 11902
LS_IINFO_PRE_NUM_RDVARS                                      = 11903
LS_IINFO_PRE_NUM_RDNONZ                                      = 11904
LS_IINFO_PRE_NUM_RDINT                                       = 11905

# Error info #/
LS_IINFO_ERR_OPTIM                                           = 11999

# Profiler contexts #/
# IIS Profiler #/
LS_DINFO_PROFILE_BASE                                        = 12000
LS_DINFO_PROFILE_IIS_FIND_NEC_ROWS                           = 12050
LS_DINFO_PROFILE_IIS_FIND_NEC_COLS                           = 12051
LS_DINFO_PROFILE_IIS_FIND_SUF_ROWS                           = 12052
LS_DINFO_PROFILE_IIS_FIND_SUF_COLS                           = 12053
# MIP Profiler #/
LS_DINFO_PROFILE_MIP_ROOT_LP                                 = 12101
LS_DINFO_PROFILE_MIP_TOTAL_LP                                = 12102
LS_DINFO_PROFILE_MIP_LP_SIM_PRIMAL                           = 12103
LS_DINFO_PROFILE_MIP_LP_SIM_DUAL                             = 12104
LS_DINFO_PROFILE_MIP_LP_SIM_BARRIER                          = 12105
LS_DINFO_PROFILE_MIP_PRE_PROCESS                             = 12106
LS_DINFO_PROFILE_MIP_FEA_PUMP                                = 12107
LS_DINFO_PROFILE_MIP_TOP_HEURISTIC                           = 12108
LS_DINFO_PROFILE_MIP_BNB_HEURISTIC                           = 12109
LS_DINFO_PROFILE_MIP_BNB_MAIN_LOOP                           = 12110
LS_DINFO_PROFILE_MIP_BNB_SUB_LOOP                            = 12111
LS_DINFO_PROFILE_MIP_BNB_BEFORE_BEST                         = 12112
LS_DINFO_PROFILE_MIP_BNB_AFTER_BEST                          = 12113
LS_DINFO_PROFILE_MIP_TOP_CUT                                 = 12114
LS_DINFO_PROFILE_MIP_BNB_CUT                                 = 12115
LS_DINFO_PROFILE_MIP_LP_NON_BNB_LOOP                         = 12116
LS_DINFO_PROFILE_MIP_LP_BNB_LOOP_MAIN                        = 12117
LS_DINFO_PROFILE_MIP_LP_BNB_LOOP_SUB                         = 12118
LS_DINFO_PROFILE_MIP_NODE_PRESOLVE                           = 12119
LS_DINFO_PROFILE_MIP_BNB_BRANCHING                           = 12120
LS_DINFO_PROFILE_MIP_BNB_BRANCHING_MAIN                      = 12121
LS_DINFO_PROFILE_MIP_BNB_BRANCHING_SUB                       = 12122
# GOP Profiler #/
LS_DINFO_PROFILE_GOP_SUB_LP_SOLVER                           = 12251
LS_DINFO_PROFILE_GOP_SUB_NLP_SOLVER                          = 12252
LS_DINFO_PROFILE_GOP_SUB_MIP_SOLVER                          = 12253
LS_DINFO_PROFILE_GOP_SUB_GOP_SOLVER                          = 12254
LS_DINFO_PROFILE_GOP_CONS_PROP_LP                            = 12255
LS_DINFO_PROFILE_GOP_CONS_PROP_NLP                           = 12256
LS_DINFO_PROFILE_GOP_VAR_MIN_MAX                             = 12257

# Misc info #/
LS_SINFO_MODEL_FILENAME                                      = 12950
LS_SINFO_MODEL_SOURCE                                        = 12951
LS_IINFO_MODEL_TYPE                                          = 12952
LS_SINFO_CORE_FILENAME                                       = 12953
LS_SINFO_STOC_FILENAME                                       = 12954
LS_SINFO_TIME_FILENAME                                       = 12955
LS_IINFO_ASSIGNED_MODEL_TYPE                                 = 12956
LS_IINFO_NZCINDEX                                            = 12957
LS_IINFO_NZRINDEX                                            = 12958
LS_IINFO_NZCRANK                                             = 12959
LS_IINFO_NZRRANK                                             = 12960
LS_IINFO_NZCCOUNT                                            = 12961
LS_IINFO_NZRCOUNT                                            = 12962

# Stochastic Information #/

#! @ingroup LSstocInfo @{ #/
#! Expected value of the objective function.  #/
LS_DINFO_STOC_EVOBJ                                          = 13201
#! Expected value of perfect information.  #/
LS_DINFO_STOC_EVPI                                           = 13202
#! Primal infeasibility of the first stage solution.  #/
LS_DINFO_STOC_PINFEAS                                        = 13203
#! Dual infeasibility of the first stage solution.  #/
LS_DINFO_STOC_DINFEAS                                        = 13204
#! Relative optimality gap at current solution.  #/
LS_DINFO_STOC_RELOPT_GAP                                     = 13205
#! Absolute optimality gap at current solution.  #/
LS_DINFO_STOC_ABSOPT_GAP                                     = 13206
#! Number of simplex iterations performed.  #/
LS_IINFO_STOC_SIM_ITER                                       = 13207
#! Number of barrier iterations performed.  #/
LS_IINFO_STOC_BAR_ITER                                       = 13208
#! Number of nonlinear iterations performed.  #/
LS_IINFO_STOC_NLP_ITER                                       = 13209
#! Number of stochastic parameters in the RHS.  #/
LS_IINFO_NUM_STOCPAR_RHS                                     = 13210
#! Number of stochastic parameters in the objective function.  #/
LS_IINFO_NUM_STOCPAR_OBJ                                     = 13211
#! Number of stochastic parameters in the lower bound.  #/
LS_IINFO_NUM_STOCPAR_LB                                      = 13212
#! Number of stochastic parameters in the upper bound.  #/
LS_IINFO_NUM_STOCPAR_UB                                      = 13213
#! Number of stochastic parameters in the instructions constituting the objective.  #/
LS_IINFO_NUM_STOCPAR_INSTR_OBJS                              = 13214
#! Number of stochastic parameters in the instructions constituting the constraints.  #/
LS_IINFO_NUM_STOCPAR_INSTR_CONS                              = 13215
#! Number of stochastic parameters in the LP matrix.  #/
LS_IINFO_NUM_STOCPAR_AIJ                                     = 13216
#! Total time elapsed in seconds to solve the model  #/
LS_DINFO_STOC_TOTAL_TIME                                     = 13217
#! Status of the SP model.  #/
LS_IINFO_STOC_STATUS                                         = 13218
#! Stage of the specified node.  #/
LS_IINFO_STOC_STAGE_BY_NODE                                  = 13219
#! Number of scenarios (integer) in the scenario tree. #/
LS_IINFO_STOC_NUM_SCENARIOS                                  = 13220
#! Number of scenarios (double) in the scenario tree. #/
LS_DINFO_STOC_NUM_SCENARIOS                                  = 13221
#! Number of stages in the model. #/
LS_IINFO_STOC_NUM_STAGES                                     = 13222
#! Number of nodes in the scenario tree (integer). #/
LS_IINFO_STOC_NUM_NODES                                      = 13223
#! Number of nodes in the scenario tree (double). #/
LS_DINFO_STOC_NUM_NODES                                      = 13224
#! Number of nodes that belong to specified stage in the scenario tree (integer). #/
LS_IINFO_STOC_NUM_NODES_STAGE                                = 13225
#! Number of nodes that belong to specified stage in the scenario tree (double). #/
LS_DINFO_STOC_NUM_NODES_STAGE                                = 13226
#! Number of node-models created or to be created. #/
LS_IINFO_STOC_NUM_NODE_MODELS                                = 13227
#! Column offset in DEQ of the first variable associated with the specified node.  #/
LS_IINFO_STOC_NUM_COLS_BEFORE_NODE                           = 13228
#! Row offset in DEQ of the first variable associated with the specified node. #/
LS_IINFO_STOC_NUM_ROWS_BEFORE_NODE                           = 13229
#! Total number of columns in the implicit DEQ (integer). #/
LS_IINFO_STOC_NUM_COLS_DETEQI                                = 13230
#! Total number of columns in the implicit DEQ (double). #/
LS_DINFO_STOC_NUM_COLS_DETEQI                                = 13231
#! Total number of rows in the implicit DEQ (integer). #/
LS_IINFO_STOC_NUM_ROWS_DETEQI                                = 13232
#! Total number of rows in the implicit DEQ (double). #/
LS_DINFO_STOC_NUM_ROWS_DETEQI                                = 13233
#! Total number of columns in the explict DEQ (integer). #/
LS_IINFO_STOC_NUM_COLS_DETEQE                                = 13234
#! Total number of columns in the explict DEQ (double). #/
LS_DINFO_STOC_NUM_COLS_DETEQE                                = 13235
#! Total number of rows in the explict DEQ (integer). #/
LS_IINFO_STOC_NUM_ROWS_DETEQE                                = 13236
#! Total number of rows in the explict DEQ (double). #/
LS_DINFO_STOC_NUM_ROWS_DETEQE                                = 13237
#! Total number of columns in non-anticipativity block. #/
LS_IINFO_STOC_NUM_COLS_NAC                                   = 13238
#! Total number of rows in non-anticipativity block. #/
LS_IINFO_STOC_NUM_ROWS_NAC                                   = 13239
#! Total number of columns in core model. #/
LS_IINFO_STOC_NUM_COLS_CORE                                  = 13240
#! Total number of rows in core model. #/
LS_IINFO_STOC_NUM_ROWS_CORE                                  = 13241
#! Total number of columns in core model in the specified stage. #/
LS_IINFO_STOC_NUM_COLS_STAGE                                 = 13242
#! Total number of rows in core model in the specified stage. #/
LS_IINFO_STOC_NUM_ROWS_STAGE                                 = 13243
#! Total number of feasibility cuts generated during NBD iterations. #/
LS_IINFO_STOC_NUM_NBF_CUTS                                   = 13244
#! Total number of optimality cuts generated during NBD iterations. #/
LS_IINFO_STOC_NUM_NBO_CUTS                                   = 13245
#! Distribution type of the sample #/
LS_IINFO_DIST_TYPE                                           = 13246
#! Sample size. #/
LS_IINFO_SAMP_SIZE                                           = 13247
#! Sample mean. #/
LS_DINFO_SAMP_MEAN                                           = 13248
#! Sample standard deviation. #/
LS_DINFO_SAMP_STD                                            = 13249
#! Sample skewness. #/
LS_DINFO_SAMP_SKEWNESS                                       = 13250
#! Sample kurtosis. #/
LS_DINFO_SAMP_KURTOSIS                                       = 13251
#! Total number of quadratic constraints in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_QCP_CONS_DETEQE                            = 13252
#! Total number of continuous constraints in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_CONT_CONS_DETEQE                           = 13253
#! Total number of constraints with general integer variables in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_INT_CONS_DETEQE                            = 13254
#! Total number of constraints with binary variables in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_BIN_CONS_DETEQE                            = 13255
#! Total number of quadratic variables in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_QCP_VARS_DETEQE                            = 13256
#! Total number of nonzeros in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NONZ_DETEQE                                = 13259
#! Total number of binaries in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_BIN_DETEQE                                 = 13260
#! Total number of general integer variables in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_INT_DETEQE                                 = 13261
#! Total number of continuous variables in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_CONT_DETEQE                                = 13262
#! Total number of quadratic nonzeros in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_QC_NONZ_DETEQE                             = 13263
#! Total number of nonlinear nonzeros in the constraints of explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_NONZ_DETEQE                            = 13264
#! Total number of nonlinear nonzeros in the objective function of explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLPOBJ_NONZ_DETEQE                         = 13265
#! Total number of quadratic constraints in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_QCP_CONS_DETEQI                            = 13266
#! Total number of continuous constraints in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_CONT_CONS_DETEQI                           = 13267
#! Total number of constraints with general integer variables in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_INT_CONS_DETEQI                            = 13268
#! Total number of constraints with binary variables in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_BIN_CONS_DETEQI                            = 13269
#! Total number of quadratic variables in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_QCP_VARS_DETEQI                            = 13270
#! Total number of nonzeros in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NONZ_DETEQI                                = 13271
#! Total number of binaries in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_BIN_DETEQI                                 = 13272
#! Total number of general integer variables in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_INT_DETEQI                                 = 13273
#! Total number of continuous variables in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_CONT_DETEQI                                = 13274
#! Total number of quadratic nonzeros in the implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_QC_NONZ_DETEQI                             = 13275
#! Total number of nonlinear nonzeros in the constraints of implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_NONZ_DETEQI                            = 13276
#! Total number of nonlinear nonzeros in the objective function of implicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLPOBJ_NONZ_DETEQI                         = 13277
#! Total number of block events. #/
LS_IINFO_STOC_NUM_EVENTS_BLOCK                               = 13278
#! Total number of independent events with a discrete distribution. #/
LS_IINFO_STOC_NUM_EVENTS_DISCRETE                            = 13279
#! Total number of independent events with a parametric distribution. #/
LS_IINFO_STOC_NUM_EVENTS_PARAMETRIC                          = 13280
#! Total number of events loaded explictly as a scenario #/
LS_IINFO_STOC_NUM_EXPLICIT_SCENARIOS                         = 13281
#! Index of a node's parent#/
LS_IINFO_STOC_PARENT_NODE                                    = 13282
#! Index of a node's eldest child#/
LS_IINFO_STOC_ELDEST_CHILD_NODE                              = 13283
#! Total number of childs a node has #/
LS_IINFO_STOC_NUM_CHILD_NODES                                = 13284
#! Number of stochastic parameters in the instruction list.  #/
LS_IINFO_NUM_STOCPAR_INSTR                                   = 13285
#! The index of the scenario which is infeasible or unbounded.  #/
LS_IINFO_INFORUNB_SCEN_IDX                                   = 13286
#! Expected value of modeling uncertainity.  #/
LS_DINFO_STOC_EVMU                                           = 13287
#! Expected value of wait-and-see model's objective.  #/
LS_DINFO_STOC_EVWS                                           = 13288
#! Expected value of the objective based on average model's first-stage optimal decisions.  #/
LS_DINFO_STOC_EVAVR                                          = 13289
#! Number of arguments of a distribution sample.  #/
LS_IINFO_DIST_NARG                                           = 13290
#! Variance reduction/control method used in generating the sample.  #/
LS_IINFO_SAMP_VARCONTROL_METHOD                              = 13291
#! Total number of nonlinear variables in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_VARS_DETEQE                            = 13292
#! Total number of nonlinear constraints in the explicit deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_CONS_DETEQE                            = 13293
#! Best lower bound on expected value of the objective function.  #/
LS_DINFO_STOC_EVOBJ_LB                                       = 13294
#! Best upper bound on expected value of the objective function.  #/
LS_DINFO_STOC_EVOBJ_UB                                       = 13295
#! Expected value of average model's objective.  #/
LS_DINFO_STOC_AVROBJ                                         = 13296
#! Sample median. #/
LS_DINFO_SAMP_MEDIAN                                         = 13297
#! Distribution (population) median. #/
LS_DINFO_DIST_MEDIAN                                         = 13298
#! Number of chance-constraints. #/
LS_IINFO_STOC_NUM_CC                                         = 13299
#! Number of rows in chance-constraints. #/
LS_IINFO_STOC_NUM_ROWS_CC                                    = 13300
#! Internal. #/
LS_IINFO_STOC_ISCBACK                                        = 13301
#! Total number of LPs solved. #/
LS_IINFO_STOC_LP_COUNT                                       = 13302
#! Total number of NLPs solved. #/
LS_IINFO_STOC_NLP_COUNT                                      = 13303
#! Total number of MILPs solved. #/
LS_IINFO_STOC_MIP_COUNT                                      = 13304
#! Time elapsed in seconds in the optimizer (excluding setup)  #/
LS_DINFO_STOC_OPT_TIME                                       = 13305
#! Difference between underlying sample's correlation (S) and target correlation (T) loaded.  #/
LS_DINFO_SAMP_CORRDIFF_ST                                    = 13306
#! Difference between underlying sample's induced correlation (C) and target correlation (T) loaded.  #/
LS_DINFO_SAMP_CORRDIFF_CT                                    = 13307
#! Difference between underlying sample's correlation (S) and induced correlation (C).  #/
LS_DINFO_SAMP_CORRDIFF_SC                                    = 13308
#! Number of rows with equality type in chance-constraints. #/
LS_IINFO_STOC_NUM_EQROWS_CC                                  = 13309
#! Number of stochastic rows#/
LS_IINFO_STOC_NUM_ROWS                                       = 13310
#! Number of chance sets violated over all scenarios #/
LS_IINFO_STOC_NUM_CC_VIOLATED                                = 13311
#! Total number of columns in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_COLS_DETEQC                                = 13312
#! Total number of rows in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_ROWS_DETEQC                                = 13313
#! Total number of quadratic constraints in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_QCP_CONS_DETEQC                            = 13314
#! Total number of continuous constraints in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_CONT_CONS_DETEQC                           = 13315
#! Total number of constraints with general integer variables in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_INT_CONS_DETEQC                            = 13316
#! Total number of constraints with binary variables in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_BIN_CONS_DETEQC                            = 13317
#! Total number of quadratic variables in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_QCP_VARS_DETEQC                            = 13318
#! Total number of nonzeros in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_NONZ_DETEQC                                = 13319
#! Total number of binaries in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_BIN_DETEQC                                 = 13320
#! Total number of general integer variables in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_INT_DETEQC                                 = 13321
#! Total number of continuous variables in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_CONT_DETEQC                                = 13322
#! Total number of quadratic nonzeros in the chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_QC_NONZ_DETEQC                             = 13323
#! Total number of nonlinear nonzeros in the constraints of chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_NONZ_DETEQC                            = 13324
#! Total number of nonlinear nonzeros in the objective function of chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLPOBJ_NONZ_DETEQC                         = 13325
#! Total number of nonlinear constraints in the constraints of chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_CONS_DETEQC                            = 13326
#! Total number of nonlinear variables in the constraints of chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_NLP_VARS_DETEQC                            = 13327
#! Total number of nonzeros in the objective of chance deterministic equivalent. #/
LS_IINFO_STOC_NUM_NONZ_OBJ_DETEQC                            = 13328
#! Total number of nonzeros in the objective of explict deterministic equivalent. #/
LS_IINFO_STOC_NUM_NONZ_OBJ_DETEQE                            = 13329
#! p-level for chance constraint #/
LS_DINFO_STOC_CC_PLEVEL                                      = 13340
#! Number of parallel threads used #/
LS_IINFO_STOC_THREADS                                        = 13341
#! Work imbalance across threads #/
LS_DINFO_STOC_THRIMBL                                        = 13342
#! Number of EQ type stochastic rows#/
LS_IINFO_STOC_NUM_EQROWS                                     = 13343
#! Thread workloads #/
LS_SINFO_STOC_THREAD_LOAD                                    = 13344
#! Number of buckets #/
LS_IINFO_STOC_NUM_BUCKETS                                    = 13345

#BNP information#/
LS_IINFO_BNP_SIM_ITER                                        = 14000
LS_IINFO_BNP_LPCOUNT                                         = 14001
LS_IINFO_BNP_NUMCOL                                          = 14002
LS_DINFO_BNP_BESTBOUND                                       = 14003
LS_DINFO_BNP_BESTOBJ                                         = 14004

#! @} #/



# Error codes (2001-2299) #/
LSERR_NO_ERROR                                               = 0000
LSERR_OUT_OF_MEMORY                                          = 2001
LSERR_CANNOT_OPEN_FILE                                       = 2002
LSERR_BAD_MPS_FILE                                           = 2003
LSERR_BAD_CONSTRAINT_TYPE                                    = 2004
LSERR_BAD_MODEL                                              = 2005
LSERR_BAD_SOLVER_TYPE                                        = 2006
LSERR_BAD_OBJECTIVE_SENSE                                    = 2007
LSERR_BAD_MPI_FILE                                           = 2008
LSERR_INFO_NOT_AVAILABLE                                     = 2009
LSERR_ILLEGAL_NULL_POINTER                                   = 2010
LSERR_UNABLE_TO_SET_PARAM                                    = 2011
LSERR_INDEX_OUT_OF_RANGE                                     = 2012
LSERR_ERRMSG_FILE_NOT_FOUND                                  = 2013
LSERR_VARIABLE_NOT_FOUND                                     = 2014
LSERR_INTERNAL_ERROR                                         = 2015
LSERR_ITER_LIMIT                                             = 2016
LSERR_TIME_LIMIT                                             = 2017
LSERR_NOT_CONVEX                                             = 2018
LSERR_NUMERIC_INSTABILITY                                    = 2019
LSERR_STEP_TOO_SMALL                                         = 2021
LSERR_USER_INTERRUPT                                         = 2023
LSERR_PARAMETER_OUT_OF_RANGE                                 = 2024
LSERR_ERROR_IN_INPUT                                         = 2025
LSERR_TOO_SMALL_LICENSE                                      = 2026
LSERR_NO_VALID_LICENSE                                       = 2027
LSERR_NO_METHOD_LICENSE                                      = 2028
LSERR_NOT_SUPPORTED                                          = 2029
LSERR_MODEL_ALREADY_LOADED                                   = 2030
LSERR_MODEL_NOT_LOADED                                       = 2031
LSERR_INDEX_DUPLICATE                                        = 2032
LSERR_INSTRUCT_NOT_LOADED                                    = 2033
LSERR_OLD_LICENSE                                            = 2034
LSERR_NO_LICENSE_FILE                                        = 2035
LSERR_BAD_LICENSE_FILE                                       = 2036
LSERR_MIP_BRANCH_LIMIT                                       = 2037
LSERR_GOP_FUNC_NOT_SUPPORTED                                 = 2038
LSERR_GOP_BRANCH_LIMIT                                       = 2039
LSERR_BAD_DECOMPOSITION_TYPE                                 = 2040
LSERR_BAD_VARIABLE_TYPE                                      = 2041
LSERR_BASIS_BOUND_MISMATCH                                   = 2042
LSERR_BASIS_COL_STATUS                                       = 2043
LSERR_BASIS_INVALID                                          = 2044
LSERR_BASIS_ROW_STATUS                                       = 2045
LSERR_BLOCK_OF_BLOCK                                         = 2046
LSERR_BOUND_OUT_OF_RANGE                                     = 2047
LSERR_COL_BEGIN_INDEX                                        = 2048
LSERR_COL_INDEX_OUT_OF_RANGE                                 = 2049
LSERR_COL_NONZCOUNT                                          = 2050
LSERR_INVALID_ERRORCODE                                      = 2051
LSERR_ROW_INDEX_OUT_OF_RANGE                                 = 2052
LSERR_TOTAL_NONZCOUNT                                        = 2053
LSERR_MODEL_NOT_LINEAR                                       = 2054
LSERR_CHECKSUM                                               = 2055
LSERR_USER_FUNCTION_NOT_FOUND                                = 2056
LSERR_TRUNCATED_NAME_DATA                                    = 2057
LSERR_ILLEGAL_STRING_OPERATION                               = 2058
LSERR_STRING_ALREADY_LOADED                                  = 2059
LSERR_STRING_NOT_LOADED                                      = 2060
LSERR_STRING_LENGTH_LIMIT                                    = 2061
LSERR_DATA_TERM_EXIST                                        = 2062
LSERR_NOT_SORTED_ORDER                                       = 2063
LSERR_INST_MISS_ELEMENTS                                     = 2064
LSERR_INST_TOO_SHORT                                         = 2065
LSERR_INST_INVALID_BOUND                                     = 2066
LSERR_INST_SYNTAX_ERROR                                      = 2067
LSERR_COL_TOKEN_NOT_FOUND                                    = 2068
LSERR_ROW_TOKEN_NOT_FOUND                                    = 2069
LSERR_NAME_TOKEN_NOT_FOUND                                   = 2070
LSERR_NOT_LSQ_MODEL                                          = 2071
LSERR_INCOMPATBLE_DECOMPOSITION                              = 2072
LSERR_NO_MULTITHREAD_SUPPORT                                 = 2073
LSERR_INVALID_PARAMID                                        = 2074
LSERR_INVALID_NTHREADS                                       = 2075
LSERR_COL_LIMIT                                              = 2076
LSERR_QCDATA_NOT_LOADED                                      = 2077
LSERR_NO_QCDATA_IN_ROW                                       = 2078
LSERR_CLOCK_SETBACK                                          = 2079
LSERR_XSOLVER_LOAD                                           = 2080
LSERR_XSOLVER_NO_FILENAME                                    = 2081
LSERR_XSOLVER_ALREADY_LOADED                                 = 2082
LSERR_XSOLVER_FUNC_NOT_INSTALLED                             = 2083
LSERR_XSOLVER_LIB_NOT_INSTALLED                              = 2084
LSERR_ZLIB_LOAD                                              = 2085
LSERR_XSOLVER_ENV_NOT_CREATED                                = 2086
LSERR_SOLPOOL_EMPTY                                          = 2087
LSERR_SOLPOOL_FULL                                           = 2088
LSERR_SOL_LIMIT                                              = 2089
LSERR_TUNER_NOT_SETUP                                        = 2090
LSERR_XSOLVER_NOT_SUPPORTED                                  = 2091
LSERR_XSOLVER_INVALID_VERSION                                = 2092
LSERR_FDE_NOT_INSTALLED                                      = 2093

#! @ingroup LSmatrixOps @{ #/

# Error in LDLt factorization #/
LSERR_LDL_FACTORIZATION                                      = 2201
# Empty column detected in LDLt factorization #/
LSERR_LDL_EMPTY_COL                                          = 2202
# Matrix data is invalid or has bad input in LDLt factorization #/
LSERR_LDL_BAD_MATRIX_DATA                                    = 2203
# Invalid matrix or vector dimension #/
LSERR_LDL_INVALID_DIM                                        = 2204
# Matrix or vector is empty #/
LSERR_LDL_EMPTY_MATRIX                                       = 2205
# Matrix is not symmetric #/
LSERR_LDL_MATRIX_NOTSYM                                      = 2206
# Matrix has zero diagonal #/
LSERR_LDL_ZERO_DIAG                                          = 2207
# Invalid permutation #/
LSERR_LDL_INVALID_PERM                                       = 2208
# Duplicate elements detected in LDLt factorization #/
LSERR_LDL_DUPELEM                                            = 2209
# Detected rank deficiency in LDLt factorization #/
LSERR_LDL_RANK                                               = 2210
#! @} #/

#! @ingroup LSstocError @{ #/
#! Core MPS file/model has an error #/
LSERR_BAD_SMPS_CORE_FILE                                     = 2301
#! Time file/model has an error #/
LSERR_BAD_SMPS_TIME_FILE                                     = 2302
#! Stoc file/model has an error #/
LSERR_BAD_SMPS_STOC_FILE                                     = 2303
#! Core MPI file/model has an error #/
LSERR_BAD_SMPI_CORE_FILE                                     = 2304
#! Stoc file associated with Core MPI file has an error #/
LSERR_BAD_SMPI_STOC_FILE                                     = 2305
#! Unable to open Core file #/
LSERR_CANNOT_OPEN_CORE_FILE                                  = 2306
#! Unable to open Time file #/
LSERR_CANNOT_OPEN_TIME_FILE                                  = 2307
#! Unable to open Stoc file #/
LSERR_CANNOT_OPEN_STOC_FILE                                  = 2308
#! Stochastic model/data has not been loaded yet. #/
LSERR_STOC_MODEL_NOT_LOADED                                  = 2309
#! Stochastic parameter specified in Stoc file has not been found . #/
LSERR_STOC_SPAR_NOT_FOUND                                    = 2310
#! Stochastic parameter specified in Time file has not been found . #/
LSERR_TIME_SPAR_NOT_FOUND                                    = 2311
#! Specified scenario index is out of sequence #/
LSERR_SCEN_INDEX_OUT_OF_SEQUENCE                             = 2312
#! Stochastic model/data has already been loaded. #/
LSERR_STOC_MODEL_ALREADY_PARSED                              = 2313
#! Specified scenario CDF is invalid, e.g. scenario probabilities don't sum to 1.0#/
LSERR_STOC_INVALID_SCENARIO_CDF                              = 2314
#! No stochastic parameters was found in the Core file #/
LSERR_CORE_SPAR_NOT_FOUND                                    = 2315
#! Number of stochastic parameters found in Core file don't match to that of Time file #/
LSERR_CORE_SPAR_COUNT_MISMATCH                               = 2316
#! Specified stochastic parameter index is invalid #/
LSERR_CORE_INVALID_SPAR_INDEX                                = 2317
#! A stochastic parameter was not expected in Time file. #/
LSERR_TIME_SPAR_NOT_EXPECTED                                 = 2318
#! Number of stochastic parameters found in Time file don't match to that of Stoc file #/
LSERR_TIME_SPAR_COUNT_MISMATCH                               = 2319
#! Specified stochastic parameter doesn't have a valid outcome value #/
LSERR_CORE_SPAR_VALUE_NOT_FOUND                              = 2320
#! Requested information is unavailable #/
LSERR_INFO_UNAVAILABLE                                       = 2321
#! Core file doesn't have a valid bound name tag #/
LSERR_STOC_MISSING_BNDNAME                                   = 2322
#! Core file doesn't have a valid objective name tag #/
LSERR_STOC_MISSING_OBJNAME                                   = 2323
#! Core file doesn't have a valid right-hand-side name tag #/
LSERR_STOC_MISSING_RHSNAME                                   = 2324
#! Core file doesn't have a valid range name tag #/
LSERR_STOC_MISSING_RNGNAME                                   = 2325
#! Stoc file doesn't have an expected token name. #/
LSERR_MISSING_TOKEN_NAME                                     = 2326
#! Stoc file doesn't have a 'ROOT' token to specify a root scenario #/
LSERR_MISSING_TOKEN_ROOT                                     = 2327
#! Node model is unbounded #/
LSERR_STOC_NODE_UNBOUNDED                                    = 2328
#! Node model is infeasible #/
LSERR_STOC_NODE_INFEASIBLE                                   = 2329
#! Stochastic model has too many scenarios to solve with specified solver #/
LSERR_STOC_TOO_MANY_SCENARIOS                                = 2330
#! One or more node-models have irrecoverable numerical problems #/
LSERR_STOC_BAD_PRECISION                                     = 2331
#! Specified aggregation structure is not compatible with model's stage structure #/
LSERR_CORE_BAD_AGGREGATION                                   = 2332
#! Event tree is either not initialized yet or was too big to create #/
LSERR_STOC_NULL_EVENT_TREE                                   = 2333
#! Specified stage index is invalid #/
LSERR_CORE_BAD_STAGE_INDEX                                   = 2334
#! Specified algorithm/method is invalid or not supported #/
LSERR_STOC_BAD_ALGORITHM                                     = 2335
#! Specified number of stages in Core model is invalid #/
LSERR_CORE_BAD_NUMSTAGES                                     = 2336
#! Underlying model has an invalid temporal order #/
LSERR_TIME_BAD_TEMPORAL_ORDER                                = 2337
#! Number of stages specified in Time structure is invalid #/
LSERR_TIME_BAD_NUMSTAGES                                     = 2338
#! Core and Time data are inconsistent #/
LSERR_CORE_TIME_MISMATCH                                     = 2339
#! Specified stochastic structure has an invalid CDF #/
LSERR_STOC_INVALID_CDF                                       = 2340
#! Specified distribution type is invalid or not supported. #/
LSERR_BAD_DISTRIBUTION_TYPE                                  = 2341
#! Scale parameter for specified distribution is out of range. #/
LSERR_DIST_SCALE_OUT_OF_RANGE                                = 2342
#! Shape parameter for specified distribution is out of range. #/
LSERR_DIST_SHAPE_OUT_OF_RANGE                                = 2343
#! Specified probabability value is invalid #/
LSERR_DIST_INVALID_PROBABILITY                               = 2344
#! Derivative information is unavailable #/
LSERR_DIST_NO_DERIVATIVE                                     = 2345
#! Specified standard deviation is invalid #/
LSERR_DIST_INVALID_SD                                        = 2346
#! Specified value is invalid #/
LSERR_DIST_INVALID_X                                         = 2347
#! Specified parameters are invalid for the given distribution. #/
LSERR_DIST_INVALID_PARAMS                                    = 2348
#! Iteration limit has been reached during a root finding operation #/
LSERR_DIST_ROOTER_ITERLIM                                    = 2349
#! Given array is out of bounds #/
LSERR_ARRAY_OUT_OF_BOUNDS                                    = 2350
#! Limiting PDF does not exist #/
LSERR_DIST_NO_PDF_LIMIT                                      = 2351

#! A random number generator is not set. #/
LSERR_RG_NOT_SET                                             = 2352
#! Distribution function value was truncated during calculations #/
LSERR_DIST_TRUNCATED                                         = 2353
#! Stoc file has a parameter value missing #/
LSERR_STOC_MISSING_PARAM_TOKEN                               = 2354
#! Distribution has invalid number of parameters #/
LSERR_DIST_INVALID_NUMPARAM                                  = 2355
#! Core file/model is not in temporal order #/
LSERR_CORE_NOT_IN_TEMPORAL_ORDER                             = 2357
#! Specified sample size is invalid #/
LSERR_STOC_INVALID_SAMPLE_SIZE                               = 2358
#! Node probability cannot be computed due to presence of continuous stochastic parameters #/
LSERR_STOC_NOT_DISCRETE                                      = 2359
#! Event tree exceeds the maximum number of scenarios allowed to attempt an exact solution.#/
LSERR_STOC_SCENARIO_LIMIT                                    = 2360
#! Specified correlation type is invalid #/
LSERR_DIST_BAD_CORRELATION_TYPE                              = 2361
#! Number of stages in the model is not set yet. #/
LSERR_TIME_NUMSTAGES_NOT_SET                                 = 2362
#! Model already contains a sampled tree #/
LSERR_STOC_SAMPLE_ALREADY_LOADED                             = 2363
#! Stochastic events are not loaded yet #/
LSERR_STOC_EVENTS_NOT_LOADED                                 = 2364
#! Stochastic tree already initialized #/
LSERR_STOC_TREE_ALREADY_INIT                                 = 2365
#! Random number generator seed not initialized #/
LSERR_RG_SEED_NOT_SET                                        = 2366
#! All sample points in the sample has been used. Resampling may be required. #/
LSERR_STOC_OUT_OF_SAMPLE_POINTS                              = 2367
#! Sampling is not supported for models with explicit scenarios. #/
LSERR_STOC_SCENARIO_SAMPLING_NOT_SUPPORTED                   = 2368
#! Sample points are not yet generated for a stochastic parameter. #/
LSERR_STOC_SAMPLE_NOT_GENERATED                              = 2369
#! Sample points are already generated for a stochastic parameter. #/
LSERR_STOC_SAMPLE_ALREADY_GENERATED                          = 2370
#! Sample sizes selected are too small. #/
LSERR_STOC_SAMPLE_SIZE_TOO_SMALL                             = 2371
#! A random number generator is already set. #/
LSERR_RG_ALREADY_SET                                         = 2372
#! Sampling is not allowed for block/joint distributions. #/
LSERR_STOC_BLOCK_SAMPLING_NOT_SUPPORTED                      = 2373
#! No stochastic parameters were assigned to one of the stages. #/
LSERR_EMPTY_SPAR_STAGE                                       = 2374
#! No rows were assigned to one of the stages. #/
LSERR_EMPTY_ROW_STAGE                                        = 2375
#! No columns were assigned to one of the stages. #/
LSERR_EMPTY_COL_STAGE                                        = 2376
#! Default sample sizes per stoc.pars and stage are in conflict. #/
LSERR_STOC_CONFLICTING_SAMP_SIZES                            = 2377
#! Empty scenario data #/
LSERR_STOC_EMPTY_SCENARIO_DATA                               = 2378
#! A correlation structure has not been induced yet #/
LSERR_STOC_CORRELATION_NOT_INDUCED                           = 2379
#! A discrete PDF table has not been loaded #/
LSERR_STOC_PDF_TABLE_NOT_LOADED                              = 2380
#! No continously distributed random parameters are found #/
LSERR_STOC_NO_CONTINUOUS_SPAR_FOUND                          = 2381
#! One or more rows already belong to another chance constraint #/
LSERR_STOC_ROW_ALREADY_IN_CC                                 = 2382
#! No chance-constraints were loaded #/
LSERR_STOC_CC_NOT_LOADED                                     = 2383
#! Cut limit has been reached #/
LSERR_STOC_CUT_LIMIT                                         = 2384
#! GA object has not been initialized yet #/
LSERR_STOC_GA_NOT_INIT                                       = 2385
#! There exists stochastic rows not loaded to any chance constraints yet.#/
LSERR_STOC_ROWS_NOT_LOADED_IN_CC                             = 2386
#! Specified sample is already assigned as the source for the target sample. #/
LSERR_SAMP_ALREADY_SOURCE                                    = 2387
#! No user-defined distribution function has been set for the specified sample. #/
LSERR_SAMP_USERFUNC_NOT_SET                                  = 2388
#! Specified sample does not support the function call or it is incompatible with the argument list. #/
LSERR_SAMP_INVALID_CALL                                      = 2389
#! Mapping stochastic instructions leads to multiple occurrences in matrix model. #/
LSERR_STOC_MAP_MULTI_SPAR                                    = 2390
#! Two or more stochastic instructions maps to the same position in matrix model. #/
LSERR_STOC_MAP_SAME_SPAR                                     = 2391
#! A stochastic parameter was not expected in the objective function. #/
LSERR_STOC_SPAR_NOT_EXPECTED_OBJ                             = 2392
#! One of the distribution parameters of the specified sample was not set. #/
LSERR_DIST_PARAM_NOT_SET                                     = 2393
#! Specified stochastic input is invalid. #/
LSERR_STOC_INVALID_INPUT                                     = 2394

# Error codes for the sprint method. #/

LSERR_SPRINT_MISSING_TAG_ROWS                                = 2577
LSERR_SPRINT_MISSING_TAG_COLS                                = 2578
LSERR_SPRINT_MISSING_TAG_RHS                                 = 2579
LSERR_SPRINT_MISSING_TAG_ENDATA                              = 2580
LSERR_SPRINT_MISSING_VALUE_ROW                               = 2581
LSERR_SPRINT_EXTRA_VALUE_ROW                                 = 2582
LSERR_SPRINT_MISSING_VALUE_COL                               = 2583
LSERR_SPRINT_EXTRA_VALUE_COL                                 = 2584
LSERR_SPRINT_MISSING_VALUE_RHS                               = 2585
LSERR_SPRINT_EXTRA_VALUE_RHS                                 = 2586
LSERR_SPRINT_MISSING_VALUE_BOUND                             = 2587
LSERR_SPRINT_EXTRA_VALUE_BOUND                               = 2588

LSERR_SPRINT_INTEGER_VARS_IN_MPS                             = 2589
LSERR_SPRINT_BINARY_VARS_IN_MPS                              = 2590
LSERR_SPRINT_SEMI_CONT_VARS_IN_MPS                           = 2591
LSERR_SPRINT_UNKNOWN_TAG_BOUNDS                              = 2592
LSERR_SPRINT_MULTIPLE_OBJ_ROWS                               = 2593

LSERR_SPRINT_COULD_NOT_SOLVE_SUBPROBLEM                      = 2594

LSERR_COULD_NOT_WRITE_TO_FILE                                = 2595
LSERR_COULD_NOT_READ_FROM_FILE                               = 2596
LSERR_READING_PAST_EOF                                       = 2597

# Error codes associated with scripting 2700-2750 #/
LSERR_SCRIPT                                                 = 2700

#! @} #/

LSERR_LAST_ERROR                                             = 2751


# Callback locations #/
LSLOC_PRIMAL                                                 = 0
LSLOC_DUAL                                                   = 1
LSLOC_BARRIER                                                = 2
LSLOC_CROSSOVER                                              = 3
LSLOC_CONOPT                                                 = 4
LSLOC_MIP                                                    = 5
LSLOC_LOCAL_OPT                                              = 6
LSLOC_GEN_START                                              = 7
LSLOC_GEN_PROCESSING                                         = 8
LSLOC_GEN_END                                                = 9
LSLOC_GOP                                                    = 10
LSLOC_EXIT_SOLVER                                            = 11
LSLOC_PRESOLVE                                               = 12
LSLOC_MSW                                                    = 13
LSLOC_FUNC_CALC                                              = 14
LSLOC_IISIUS                                                 = 15
LSLOC_SP                                                     = 16
LSLOC_GEN_SP_START                                           = 17
LSLOC_GEN_SP                                                 = 18
LSLOC_GEN_SP_END                                             = 19
LSLOC_SP_WS                                                  = 20
LSLOC_LSQ                                                    = 21
LSLOC_SP_WS_START                                            = 22
LSLOC_SP_WS_END                                              = 23
LSLOC_SP_BENCH_START                                         = 24
LSLOC_SP_BENCH_END                                           = 25
LSLOC_BNP                                                    = 26
LSLOC_OBJPOOL                                                = 27


LS_METHOD_FREE                                               = 0
LS_METHOD_PSIMPLEX                                           = 1
LS_METHOD_DSIMPLEX                                           = 2
LS_METHOD_BARRIER                                            = 3
LS_METHOD_NLP                                                = 4
LS_METHOD_MIP                                                = 5
LS_METHOD_MULTIS                                             = 6
LS_METHOD_GOP                                                = 7
LS_METHOD_IIS                                                = 8
LS_METHOD_IUS                                                = 9
LS_METHOD_SBD                                                = 10
LS_METHOD_SPRINT                                             = 11
LS_METHOD_GA                                                 = 12


LS_STRATEGY_USER                                             = 0
LS_STRATEGY_PRIMIP                                           = 1
LS_STRATEGY_NODEMIP                                          = 2
LS_STRATEGY_HEUMIP                                           = 3


LS_NMETHOD_FREE                                              = 4
LS_NMETHOD_LSQ                                               = 5
LS_NMETHOD_QP                                                = 6
LS_NMETHOD_CONOPT                                            = 7
LS_NMETHOD_SLP                                               = 8
LS_NMETHOD_MSW_GRG                                           = 9
LS_NMETHOD_IPOPT                                             = 10


LS_PROB_SOLVE_FREE                                           = 0
LS_PROB_SOLVE_PRIMAL                                         = 1
LS_PROB_SOLVE_DUAL                                           = 2
LS_BAR_METHOD_FREE                                           = 4
LS_BAR_METHOD_INTPNT                                         = 5
LS_BAR_METHOD_CONIC                                          = 6
LS_BAR_METHOD_QCONE                                          = 7

LSSOL_BASIC_PRIMAL                                           = 11
LSSOL_BASIC_DUAL                                             = 12
LSSOL_BASIC_SLACK                                            = 13
LSSOL_BASIC_REDCOST                                          = 14
LSSOL_INTERIOR_PRIMAL                                        = 15
LSSOL_INTERIOR_DUAL                                          = 16
LSSOL_INTERIOR_SLACK                                         = 17
LSSOL_INTERIOR_REDCOST                                       = 18



# Model types #/
# linear programs                          #/
LS_LP                                                        = 10

# quadratic programs                       #/
LS_QP                                                        = 11

# conic programs                           #/
LS_SOCP                                                      = 12

# semidefinite programs                    #/
LS_SDP                                                       = 13

# nonlinear programs                       #/
LS_NLP                                                       = 14

# mixed-integer linear programs            #/
LS_MILP                                                      = 15

# mixed-integer quadratic programs         #/
LS_MIQP                                                      = 16

# mixed-integer conic programs             #/
LS_MISOCP                                                    = 17

# mixed-integer semidefinite programs      #/
LS_MISDP                                                     = 18

# mixed-integer nonlinear programs         #/
LS_MINLP                                                     = 19

# convex QP #/
LS_CONVEX_QP                                                 = 20

#convex NLP #/
LS_CONVEX_NLP                                                = 21

#convex MIQP #/
LS_CONVEX_MIQP                                               = 22

#convex MINLP #/
LS_CONVEX_MINLP                                              = 23

# undetermined   #/
LS_UNDETERMINED                                              = -1


LS_LINK_BLOCKS_FREE                                          = 0
LS_LINK_BLOCKS_SELF                                          = 1
LS_LINK_BLOCKS_NONE                                          = 2
LS_LINK_BLOCKS_COLS                                          = 3
LS_LINK_BLOCKS_ROWS                                          = 4
LS_LINK_BLOCKS_BOTH                                          = 5
LS_LINK_BLOCKS_MATRIX                                        = 6


# Controls the way objective function and
# objective sense are printed when writing
# LS_MAX type problems in MPS format.
#/
LS_MPS_USE_MAX_NOTE                                          = 0
LS_MPS_USE_MAX_CARD                                          = 1
LS_MPS_USE_MAX_FLIP                                          = 2


# Finite differences methods #/
LS_DERIV_FREE                                                = 0
LS_DERIV_FORWARD_DIFFERENCE                                  = 1
LS_DERIV_BACKWARD_DIFFERENCE                                 = 2
LS_DERIV_CENTER_DIFFERENCE                                   = 3


# MIP Sets
#  SOS1: S={x_1,...,x_p}  only one x_j can be different from zero
#  SOS2: S={x_1,...,x_p}  at most two x_j can be different from zero
#                         and  when they are they have to be adjacent
#  SOS3: S={x_1,...,x_p}  @sum(j: x_j      )  = 1;  x_j >=0,
#  CARD: S={x_1,...,x_p}  @sum(j: sign(x_j)) <= k;  x_j >=0
#/
LS_MIP_SET_CARD                                              = 4
LS_MIP_SET_SOS1                                              = 1
LS_MIP_SET_SOS2                                              = 2
LS_MIP_SET_SOS3                                              = 3



LS_QTERM_NONE                                                = 0
LS_QTERM_INDEF                                               = 1
LS_QTERM_POSDEF                                              = 2
LS_QTERM_NEGDEF                                              = 3
LS_QTERM_POS_SEMIDEF                                         = 4
LS_QTERM_NEG_SEMIDEF                                         = 5


# Bit masks for general MIP mode. Use sums
# to enable a collection of available levels.
#/
LS_MIP_MODE_NO_TIME_EVENTS                                   = 2
LS_MIP_MODE_FAST_FEASIBILITY                                 = 4
LS_MIP_MODE_FAST_OPTIMALITY                                  = 8
LS_MIP_MODE_NO_BRANCH_CUTS                                   = 16
LS_MIP_MODE_NO_LP_BARRIER                                    = 32


# Bit mask for cut generation levels. Use sums to
# enable a collection of available cuts.
#/
LS_MIP_GUB_COVER_CUTS                                        = 2
LS_MIP_FLOW_COVER_CUTS                                       = 4
LS_MIP_LIFT_CUTS                                             = 8
LS_MIP_PLAN_LOC_CUTS                                         = 16
LS_MIP_DISAGG_CUTS                                           = 32
LS_MIP_KNAPSUR_COVER_CUTS                                    = 64
LS_MIP_LATTICE_CUTS                                          = 128
LS_MIP_GOMORY_CUTS                                           = 256
LS_MIP_COEF_REDC_CUTS                                        = 512
LS_MIP_GCD_CUTS                                              = 1024
LS_MIP_OBJ_CUT                                               = 2048
LS_MIP_BASIS_CUTS                                            = 4096
LS_MIP_CARDGUB_CUTS                                          = 8192
LS_MIP_DISJUN_CUTS                                           = 16384


# Bit masks for MIP preprocessing levels. Use sums
# to enable a collection of available levels.
#/
LS_MIP_PREP_SPRE                                             = 2
LS_MIP_PREP_PROB                                             = 4
LS_MIP_PREP_COEF                                             = 8
LS_MIP_PREP_ELIM                                             = 16
LS_MIP_PREP_DUAL                                             = 32
LS_MIP_PREP_DBACK                                            = 64
LS_MIP_PREP_BINROWS                                          = 128
LS_MIP_PREP_AGGROWS                                          = 256
LS_MIP_PREP_COEF_LIFTING                                     = 512
LS_MIP_PREP_MAXPASS                                          = 1024
LS_MIP_PREP_SIMROW                                           = 2048


# Bit masks for solver preprocessing levels. Use sums
# to enable a collection of available levels.
#/
LS_SOLVER_PREP_SPRE                                          = 2
LS_SOLVER_PREP_PFOR                                          = 4
LS_SOLVER_PREP_DFOR                                          = 8
LS_SOLVER_PREP_ELIM                                          = 16
LS_SOLVER_PREP_DCOL                                          = 32
LS_SOLVER_PREP_DROW                                          = 64
LS_SOLVER_PREP_CONE                                          = 128
LS_SOLVER_PREP_MAXPASS                                       = 1024
LS_SOLVER_PREP_DECOMP                                        = 4096
LS_SOLVER_PREP_LOWMEM                                        = 8192
LS_SOLVER_PREP_EXTERNAL                                      = 16384


# Bit masks for IIS & IUS analysis levels. Use sums to
# enable a collection of available levels.
#/
LS_NECESSARY_ROWS                                            = 1
LS_NECESSARY_COLS                                            = 2
LS_SUFFICIENT_ROWS                                           = 4
LS_SUFFICIENT_COLS                                           = 8
LS_IIS_INTS                                                  = 16
LS_IISRANK_LTF                                               = 32
LS_IISRANK_DECOMP                                            = 64
LS_IISRANK_NNZ                                               = 128
LS_IISLIMIT_MIS                                              = 256
LS_IIS_MASK_IISCOLS                                          = 512
LS_IIS_SETS                                                  = 1024


# Infeasibility norms for IIS finder #/
LS_IIS_NORM_FREE                                             = 0
LS_IIS_NORM_ONE                                              = 1
LS_IIS_NORM_INFINITY                                         = 2


# IIS methods #/
LS_IIS_DEFAULT                                               = 0
LS_IIS_DEL_FILTER                                            = 1
LS_IIS_ADD_FILTER                                            = 2
LS_IIS_GBS_FILTER                                            = 3
LS_IIS_DFBS_FILTER                                           = 4
LS_IIS_FSC_FILTER                                            = 5
LS_IIS_ELS_FILTER                                            = 6


#codes for IINFO_MIP_WHERE_IN_CODE#/
LS_MIP_IN_PRESOLVE                                           = 0
LS_MIP_IN_FP_MODE                                            = 1
LS_MIP_IN_HEU_MODE                                           = 2
LS_MIP_IN_ENUM                                               = 3
LS_MIP_IN_CUT_ADD_TOP                                        = 4
LS_MIP_IN_CUT_ADD_TREE                                       = 5
LS_MIP_IN_BANDB                                              = 6


##
# @ingroup LSstocOptDataTypes
#/
#! Stochastic parameter is an instruction code  #/
LS_JCOL_INST                                                 = -8
#! Stochastic parameter is a RHS upper bound (reserved for future use)#/
LS_JCOL_RUB                                                  = -7
#! Stochastic parameter is a RHS lower bound (reserved for future use)#/
LS_JCOL_RLB                                                  = -6
#! Stochastic parameter is a RHS value (belongs to RHS column)      #/
LS_JCOL_RHS                                                  = -5
#! Stochastic parameter is an objective coefficient (belongs to OBJ row)   #/
LS_IROW_OBJ                                                  = -1
#! Stochastic parameter is a variable lower bound (belongs to LO row) #/
LS_IROW_VUB                                                  = -3
#! Stochastic parameter is a variable upper bound (belongs to UP row) #/
LS_IROW_VLB                                                  = -2
#! Stochastic parameter is a variable fixed bound (belongs to FX row) #/
LS_IROW_VFX                                                  = -4
#! Stochastic parameter is an LP matrix entry. #/
LS_IMAT_AIJ                                                  = 0


##
# @ingroup LSstocOptDistribFun
#/
# discrete distributions #/
LSDIST_TYPE_BINOMIAL                                         = 701
LSDIST_TYPE_DISCRETE                                         = 702
LSDIST_TYPE_DISCRETE_BLOCK                                   = 703
LSDIST_TYPE_NEGATIVE_BINOMIAL                                = 704
LSDIST_TYPE_GEOMETRIC                                        = 705
LSDIST_TYPE_POISSON                                          = 706
LSDIST_TYPE_LOGARITHMIC                                      = 707
LSDIST_TYPE_HYPER_GEOMETRIC                                  = 708
LSDIST_TYPE_LINTRAN_BLOCK                                    = 709
LSDIST_TYPE_SUB_BLOCK                                        = 710
LSDIST_TYPE_SUB                                              = 711
LSDIST_TYPE_USER                                             = 712

# continuous distributions #/
LSDIST_TYPE_BETA                                             = 801
LSDIST_TYPE_CAUCHY                                           = 802
LSDIST_TYPE_CHI_SQUARE                                       = 803
LSDIST_TYPE_EXPONENTIAL                                      = 804
LSDIST_TYPE_F_DISTRIBUTION                                   = 805
LSDIST_TYPE_GAMMA                                            = 806
LSDIST_TYPE_GUMBEL                                           = 807
LSDIST_TYPE_LAPLACE                                          = 808
LSDIST_TYPE_LOGNORMAL                                        = 809
LSDIST_TYPE_LOGISTIC                                         = 810
LSDIST_TYPE_NORMAL                                           = 811
LSDIST_TYPE_PARETO                                           = 812
LSDIST_TYPE_STABLE_PARETIAN                                  = 813
LSDIST_TYPE_STUDENTS_T                                       = 814
LSDIST_TYPE_TRIANGULAR                                       = 815
LSDIST_TYPE_UNIFORM                                          = 816
LSDIST_TYPE_WEIBULL                                          = 817
LSDIST_TYPE_WILCOXON                                         = 818
LSDIST_TYPE_BETABINOMIAL                                     = 819
LSDIST_TYPE_SYMMETRICSTABLE                                  = 820


# supported operations modifying the core. #/
LS_REPLACE                                                   = 0
LS_ADD                                                       = 1
LS_SUB                                                       = 2
LS_MULTIPLY                                                  = 3
LS_DIVIDE                                                    = 4


# scenario indices for special cases #/
LS_SCEN_ROOT                                                 = -1
LS_SCEN_AVRG                                                 = -2
LS_SCEN_MEDIAN                                               = -3
LS_SCEN_USER                                                 = -4
LS_SCEN_NONE                                                 = -5


# warmstart rule in optimizing wait-see model #/
LS_WSBAS_FREE                                                = -1
LS_WSBAS_NONE                                                = 0
LS_WSBAS_AVRG                                                = 1
LS_WSBAS_LAST                                                = 2


##
# @ingroup LSstocOptSolver
#/
#! Solve with the method chosen by the solver. #/
LS_METHOD_STOC_FREE                                          = -1

#! Solve the deterministic equivalent (DETEQ).  #/
LS_METHOD_STOC_DETEQ                                         = 0

#! Solve with the Nested Benders Decomposition (NBD) method. #/
LS_METHOD_STOC_NBD                                           = 1

#! Solve with the Augmented Lagrangian Decomposition (ALD) method. #/
LS_METHOD_STOC_ALD                                           = 2

#! Solve with the Heuristic-Search (HS) method. #/
LS_METHOD_STOC_HS                                            = 4



#
# @ingroup LSstocOptDeteqType
#/
LS_DETEQ_FREE                                                = -1
LS_DETEQ_IMPLICIT                                            = 0
LS_DETEQ_EXPLICIT                                            = 1
LS_DETEQ_CHANCE                                              = 2


# Distribution functions #/
LS_USER                                                      = 0
LS_PDF                                                       = 1
LS_CDF                                                       = 2
LS_CDFINV                                                    = 3
LS_PDFDIFF                                                   = 4


# Correlation types #/
LS_CORR_TARGET                                               = -1
LS_CORR_LINEAR                                               = 0
LS_CORR_PEARSON                                              = 0
LS_CORR_KENDALL                                              = 1
LS_CORR_SPEARMAN                                             = 2


# Sampling types #/
LS_MONTECARLO                                                = 0
LS_LATINSQUARE                                               = 1
LS_ANTITHETIC                                                = 2


# Random number generator algorithms #/
LS_RANDGEN_FREE                                              = -1
LS_RANDGEN_SYSTEM                                            = 0
LS_RANDGEN_LINDO1                                            = 1
LS_RANDGEN_LINDO2                                            = 2
LS_RANDGEN_LIN1                                              = 3
LS_RANDGEN_MULT1                                             = 4
LS_RANDGEN_MULT2                                             = 5
LS_RANDGEN_MERSENNE                                          = 6


# NCM methods #/
LS_NCM_STD                                                   = 	1
LS_NCM_GA                                                    = 2
LS_NCM_ALTP                                                  = 4
LS_NCM_L2NORM_CONE                                           = 8
LS_NCM_L2NORM_NLP                                            = 16


# pointer types used #/
LS_PTR_ENV                                                   = 0
LS_PTR_MODEL                                                 = 1
LS_PTR_SAMPLE                                                = 2
LS_PTR_RG                                                    = 3


# multithreading mode #/
LS_MTMODE_FREE                                               = -1
LS_MTMODE_EXPLCT                                             = 0
LS_MTMODE_PPCC                                               = 1
LS_MTMODE_PP                                                 = 2
LS_MTMODE_CCPP                                               = 3
LS_MTMODE_CC                                                 = 4


# Output file types created by the Sprint code#/
LS_SPRINT_OUTPUT_FILE_FREE                                   = 0
LS_SPRINT_OUTPUT_FILE_BIN                                    = 1
LS_SPRINT_OUTPUT_FILE_TXT                                    = 2


LS_MSW_MODE_TRUNCATE_FREE                                    = 1
LS_MSW_MODE_SCALE_REFSET                                     = 2
LS_MSW_MODE_EXPAND_RADIUS                                    = 4
LS_MSW_MODE_SKEWED_SAMPLE                                    = 8
LS_MSW_MODE_BEST_LOCAL_BND                                   = 16
LS_MSW_MODE_BEST_GLOBAL_BND                                  = 32
LS_MSW_MODE_SAMPLE_FREEVARS                                  = 64
LS_MSW_MODE_PRECOLLECT                                       = 128
LS_MSW_MODE_POWER_SOLVE                                      = 256


LS_GA_CROSS_SBX                                              = 101
LS_GA_CROSS_BLXA                                             = 102
LS_GA_CROSS_BLXAB                                            = 103
LS_GA_CROSS_HEU                                              = 104
LS_GA_CROSS_ONEPOINT                                         = 201
LS_GA_CROSS_TWOPOINT                                         = 202


#! scan for basic solutions for pool #/
LS_SOLVER_MODE_POOLBAS                                       = 1
#! scan for edge solutions for pool #/
LS_SOLVER_MODE_POOLEDGE                                      = 2
#! scan for integer basic solutions #/
LS_SOLVER_MODE_INTBAS                                        = 4


LS_PARCLASS_BITMASK                                          = 1
LS_PARCLASS_MULSTEP                                          = 2
LS_PARCLASS_TUNPAR                                           = 4
LS_PARCLASS_LP                                               = 32
LS_PARCLASS_QUAD                                             = 64
LS_PARCLASS_NLP                                              = 128
LS_PARCLASS_GOP                                              = 256
LS_PARCLASS_MIP                                              = 512
LS_PARCLASS_ENV                                              = 1024
LS_PARCLASS_MOD                                              = 2048
LS_PARCLASS_HIT                                              = 4096
LS_PARCLASS_ZSTATIC                                          = 8192


# Equivalences #/
LS_IINFO_OBJSENSE                                            = LS_IPARAM_OBJSENSE
LS_IINFO_VER_MAJOR                                           = LS_IPARAM_VER_MAJOR
LS_IINFO_VER_MINOR                                           = LS_IPARAM_VER_MINOR
LS_IINFO_VER_BUILD                                           = LS_IPARAM_VER_BUILD
LS_IINFO_VER_REVISION                                        = LS_IPARAM_VER_REVISION
# Conic vs Second-Order-Cone equivalence#/
LS_CONIC                                                     = LS_SOCP
LS_MICONIC                                                   = LS_MISOCP

#####################################################################
#                   Conversion to version 1.x                       #
#####################################################################/

# old parameter names, changed in 12.x #/
LS_INT_PARAMETER_TYPE                                        = LS_INT_TYPE
LS_DOUBLE_PARAMETER_TYPE                                     = LS_DOUBLE_TYPE
# old parameter names, changed in 8.x #/
LS_IPARAM_NLP_MSW_MAXREF                                     = LS_IPARAM_NLP_MSW_POPSIZE
LS_IPARAM_STOC_DEBUG_LEVEL                                   = LS_IPARAM_STOC_DEBUG_MASK

# old parameter names changed in 6.x #/
LS_SPRINT_OUTPUT_FILE_DEFAULT                                = LS_SPRINT_OUTPUT_FILE_FREE

# old parameter names changed in 5.x #/
LS_IPARAM_SPLEX_SCALE                                        = LS_IPARAM_LP_SCALE
LS_IPARAM_SPLEX_ITRLMT                                       = LS_IPARAM_LP_ITRLMT
LS_IPARAM_MIP_USE_ENUM_HEU                                   = LS_IPARAM_MIP_ENUM_HEUMODE
LS_IPARAM_SOLVER_USE_CONCURRENT_OPT                          = LS_IPARAM_SOLVER_CONCURRENT_OPTMODE
LS_IPARAM_GOP_USEBNDLIM                                      = LS_IPARAM_GOP_BNDLIM_MODE
# old parameter names changed in 4.x or older#/
LSLOC_BANDB                                                  = LSLOC_MIP
LS_IPARAM_ITRLMT                                             = LS_IPARAM_SPLEX_ITRLMT
LS_IPARAM_PRICING                                            = LS_IPARAM_SPLEX_PPRICING
LS_IPARAM_SCALE                                              = LS_IPARAM_SPLEX_SCALE
LS_IPARAM_TIMLMT                                             = LS_IPARAM_SOLVER_TIMLMT
LS_DPARAM_CUTOFFVAL                                          = LS_DPARAM_SOLVER_CUTOFFVAL
LS_IPARAM_RESTART                                            = LS_IPARAM_SOLVER_RESTART
LS_DPARAM_FEASTOL                                            = LS_DPARAM_SOLVER_FEASTOL
LS_IPARAM_IUSOL                                              = LS_IPARAM_SOLVER_IUSOL
LS_IPARAM_MIPTIMLIM                                          = LS_IPARAM_MIP_TIMLIM
LS_IPARAM_MIPAOPTTIMLIM                                      = LS_IPARAM_MIP_AOPTTIMLIM
LS_IPARAM_MIPPRELEVEL                                        = LS_IPARAM_MIP_PRELEVEL
LS_IPARAM_MIPNODESELRULE                                     = LS_IPARAM_MIP_NODESELRULE
LS_DPARAM_MIPINTTOL                                          = LS_DPARAM_MIP_INTTOL
LS_DPARAM_MIPRELINTTOL                                       = LS_DPARAM_MIP_RELINTTOL
LS_DPARAM_MIP_OPTTOL                                         = LS_DPARAM_MIP_RELOPTTOL
LS_DPARAM_MIPOPTTOL                                          = LS_DPARAM_MIP_OPTTOL
LS_DPARAM_MIPPEROPTTOL                                       = LS_DPARAM_MIP_PEROPTTOL
LS_IPARAM_MIPMAXCUTPASS                                      = LS_IPARAM_MIP_MAXCUTPASS_TOP
LS_DPARAM_MIPADDCUTPER                                       = LS_DPARAM_MIP_ADDCUTPER
LS_IPARAM_MIPCUTLEVEL                                        = LS_IPARAM_MIP_CUTLEVEL_TOP
LS_IPARAM_MIPHEULEVEL                                        = LS_IPARAM_MIP_HEULEVEL
LS_IPARAM_MIPPRINTLEVEL                                      = LS_IPARAM_MIP_PRINTLEVEL
LS_IPARAM_MIPPREPRINTLEVEL                                   = LS_IPARAM_MIP_PREPRINTLEVEL
LS_DPARAM_MIPCUTOFFOBJ                                       = LS_DPARAM_MIP_CUTOFFOBJ
LS_IPARAM_MIPSTRONGBRANCHLEVEL                               = LS_IPARAM_MIP_STRONGBRANCHLEVEL
LS_IPARAM_MIPBRANCHDIR                                       = LS_IPARAM_MIP_BRANCHDIR
LS_IPARAM_MIPTOPOPT                                          = LS_IPARAM_MIP_TOPOPT
LS_IPARAM_MIPREOPT                                           = LS_IPARAM_MIP_REOPT
LS_IPARAM_MIPSOLVERTYPE                                      = LS_IPARAM_MIP_SOLVERTYPE
LS_IPARAM_MIPKEEPINMEM                                       = LS_IPARAM_MIP_KEEPINMEM
LS_DPARAM_MIP_REDCOSTFIXING_CUTOFF                           = LS_DPARAM_MIP_REDCOSTFIX_CUTOFF
LS_IPARAM_NLPPRINTLEVEL                                      = LS_IPARAM_NLP_PRINTLEVEL
LS_IPARAM_LPPRINTLEVEL                                       = LS_IPARAM_LP_PRINTLEVEL
LS_IPARAM_NLPSOLVER                                          = LS_IPARAM_NLP_SOLVER
LS_IPARAM_MODEL_CONVEX_FLAG                                  = LS_IPARAM_NLP_CONVEX
LS_IPARAM_NLP_SOLVEASLP                                      = LS_IPARAM_NLP_SOLVE_AS_LP
LS_DINFO_MIPBESTBOUND                                        = LS_DINFO_MIP_BESTBOUND
LS_IINFO_MIPBRANCHCOUNT                                      = LS_IINFO_MIP_BRANCHCOUNT
LS_IINFO_MIPSTATUS                                           = LS_IINFO_MIP_STATUS
LS_IINFO_MIPNEWIPSOL                                         = LS_IINFO_MIP_NEWIPSOL
LS_IINFO_MIPLPCOUNT                                          = LS_IINFO_MIP_LPCOUNT
LS_IINFO_MIPACTIVENODES                                      = LS_IINFO_MIP_ACTIVENODES
LS_IINFO_MIPLTYPE                                            = LS_IINFO_MIP_LTYPE
LS_IINFO_MIPAOPTTIMETOSTOP                                   = LS_IINFO_MIP_AOPTTIMETOSTOP
LS_DINFO_MIPOBJ                                              = LS_DINFO_MIP_OBJ
LS_IPARAM_BARRIER_PROB_TO_SOLVE                              = LS_IPARAM_PROB_TO_SOLVE
LS_IINFO_STATUS                                              = LS_IINFO_PRIMAL_STATUS
LS_GOPSOLSTAT_GLOBAL_OPTIMAL                                 = LS_STATUS_OPTIMAL
LS_GOPSOLSTAT_LOCAL_OPTIMAL                                  = LS_STATUS_LOCAL_OPTIMAL
LS_GOPSOLSTAT_INFEASIBLE                                     = LS_STATUS_INFEASIBLE
LS_GOPSOLSTAT_TOPUNBOUNDED                                   = LS_STATUS_UNBOUNDED
LS_GOPSOLSTAT_FEASIBLE                                       = LS_STATUS_FEASIBLE
LS_GOPSOLSTAT_UNKNOWN                                        = LS_STATUS_UNKNOWN
LS_GOPSOLSTAT_NUMERICAL_ERROR                                = LS_STATUS_NUMERICAL_ERROR
LS_IIS_NORM_NONE                                             = LS_IIS_NORM_FREE
LS_IPARAM_STOC_SAMPLING_METHOD                               = LS_IPARAM_STOC_VARCONTROL_METHOD
LS_DPARAM_GOP_OPTTOL                                         = LS_DPARAM_GOP_RELOPTTOL
# old operator names #/
EP_EXT_AND                                                   = EP_VAND
EP_EXT_OR                                                    = EP_VOR
EP_MULTMULT                                                  = EP_VMULT
EP_PUSH_SVAR                                                 = EP_PUSH_SPAR

#####################################################################
