/*
 * SimpleFOC.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "SimpleFOC".
 *
 * Model version              : 1.19
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Fri Jun 30 17:30:08 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SimpleFOC_h_
#define RTW_HEADER_SimpleFOC_h_
#ifndef SimpleFOC_COMMON_INCLUDES_
#define SimpleFOC_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* SimpleFOC_COMMON_INCLUDES_ */

#include "SimpleFOC_types.h"
#include "rtGetNaN.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Pos0;                         /* '<S8>/Pos0' */
  real_T Integrator;                   /* '<S15>/Integrator' */
  real_T polepair1;                    /* '<S7>/pole-pair1' */
  real_T Mod;                          /* '<S7>/Mod' */
  real_T SinCos_o1;                    /* '<S5>/SinCos' */
  real_T SinCos_o2;                    /* '<S5>/SinCos' */
  real_T TmpSignalConversionAtMatrixMult[2];
  real_T MatrixMultiply[2];            /* '<S5>/MatrixMultiply' */
  real_T MatrixMultiply1[2];           /* '<S5>/MatrixMultiply1' */
  real_T MatrixConcatenate1[9];        /* '<S5>/Matrix Concatenate1' */
  real_T Id_0;                         /* '<S16>/Id_0' */
  real_T Integrator_d;                 /* '<S19>/Integrator' */
  real_T Id_0_e;                       /* '<S17>/Id_0' */
  real_T Integrator_a;                 /* '<S21>/Integrator' */
  real_T TmpSignalConversionAtMatrixMu_m[3];
  real_T MatrixMultiply2[3];           /* '<S4>/MatrixMultiply2' */
  real_T Bias3;                        /* '<S24>/Bias3' */
  real_T Mod_i;                        /* '<S24>/Mod' */
  real_T Switch;                       /* '<S24>/Switch' */
  real_T Switch1;                      /* '<S24>/Switch1' */
  real_T Switch2;                      /* '<S24>/Switch2' */
  real_T Switch3;                      /* '<S24>/Switch3' */
  real_T Switch4;                      /* '<S24>/Switch4' */
  real_T Add;                          /* '<S24>/Add' */
  real_T Bias3_c;                      /* '<S25>/Bias3' */
  real_T Mod_f;                        /* '<S25>/Mod' */
  real_T Switch_d;                     /* '<S25>/Switch' */
  real_T Switch1_k;                    /* '<S25>/Switch1' */
  real_T Switch2_j;                    /* '<S25>/Switch2' */
  real_T Switch3_j;                    /* '<S25>/Switch3' */
  real_T Switch4_g;                    /* '<S25>/Switch4' */
  real_T Add_h;                        /* '<S25>/Add' */
  real_T Bias3_n;                      /* '<S26>/Bias3' */
  real_T Mod_a;                        /* '<S26>/Mod' */
  real_T Switch_g;                     /* '<S26>/Switch' */
  real_T Switch1_j;                    /* '<S26>/Switch1' */
  real_T Switch2_g;                    /* '<S26>/Switch2' */
  real_T Switch3_k;                    /* '<S26>/Switch3' */
  real_T Switch4_h;                    /* '<S26>/Switch4' */
  real_T Add_l;                        /* '<S26>/Add' */
  real_T Max_Lampda_PM_rate[3];        /* '<S11>/Max_Lampda_PM_rate' */
  real_T Product2[3];                  /* '<S4>/Product2' */
  real_T SumofElements;                /* '<S4>/Sum of Elements' */
  real_T Gain1;                        /* '<S4>/Gain1' */
  real_T Product;                      /* '<S4>/Product' */
  real_T Subtract2;                    /* '<S4>/Subtract2' */
  real_T Product1;                     /* '<S4>/Product1' */
  real_T Gain3;                        /* '<S4>/Gain3' */
  real_T Add_i;                        /* '<S4>/Add' */
  real_T SinCos_o1_p;                  /* '<S6>/SinCos' */
  real_T SinCos_o2_j;                  /* '<S6>/SinCos' */
  real_T Gain;                         /* '<S6>/Gain' */
  real_T TmpSignalConversionAtMatrixMu_a[2];
  real_T MatrixMultiply_c[2];          /* '<S6>/MatrixMultiply' */
  real_T Gain2;                        /* '<S6>/Gain2' */
  real_T MatrixMultiply1_c[2];         /* '<S6>/MatrixMultiply1' */
  real_T Gain3_m;                      /* '<S6>/Gain3' */
  real_T MatrixConcatenate1_h[9];      /* '<S6>/Matrix Concatenate1' */
  real_T Gain1_i[9];                   /* '<S6>/Gain1' */
  real_T IaStator;                     /* '<Root>/Unit Delay' */
  real_T IbStator;                     /* '<Root>/Unit Delay' */
  real_T MtrPos;                       /* '<Root>/Unit Delay' */
  real_T convert_pu;                   /* '<S181>/convert_pu' */
  real_T Merge;                        /* '<S181>/Merge' */
  real_T indexing;                     /* '<S61>/indexing' */
  real_T Lookup[4];                    /* '<S61>/Lookup' */
  real_T Sum3;                         /* '<S180>/Sum3' */
  real_T DataTypeConversion1;          /* '<S61>/Data Type Conversion1' */
  real_T Sum2;                         /* '<S61>/Sum2' */
  real_T Product_d;                    /* '<S180>/Product' */
  real_T Sum4;                         /* '<S180>/Sum4' */
  real_T Sum5;                         /* '<S180>/Sum5' */
  real_T Product1_i;                   /* '<S180>/Product1' */
  real_T Sum6;                         /* '<S180>/Sum6' */
  real_T ErrorQC;                      /* '<S2>/Sum2' */
  real_T ProportionalGain;             /* '<S160>/Proportional Gain' */
  real_T Integrator_l;                 /* '<S155>/Integrator' */
  real_T Sum;                          /* '<S164>/Sum' */
  real_T ErrorDC;                      /* '<S2>/Sum1' */
  real_T ProportionalGain_j;           /* '<S112>/Proportional Gain' */
  real_T Integrator_g;                 /* '<S107>/Integrator' */
  real_T Sum_d;                        /* '<S116>/Sum' */
  real_T Switch_i;                     /* '<S64>/Switch' */
  real_T Product_dk;                   /* '<S64>/Product' */
  real_T Product_b;                    /* '<S65>/Product' */
  real_T Product1_h;                   /* '<S65>/Product1' */
  real_T Sum1;                         /* '<S65>/Sum1' */
  real_T Merge_e[2];                   /* '<S52>/Merge' */
  real_T one_by_two;                   /* '<S55>/one_by_two' */
  real_T sqrt3_by_two;                 /* '<S55>/sqrt3_by_two' */
  real_T add_b;                        /* '<S55>/add_b' */
  real_T add_c;                        /* '<S55>/add_c' */
  real_T Max;                          /* '<S177>/Max' */
  real_T Min;                          /* '<S177>/Min' */
  real_T Add_k;                        /* '<S177>/Add' */
  real_T one_by_two_d;                 /* '<S177>/one_by_two' */
  real_T Add3;                         /* '<S176>/Add3' */
  real_T Add1;                         /* '<S176>/Add1' */
  real_T Add2;                         /* '<S176>/Add2' */
  real_T Gain_a[3];                    /* '<S176>/Gain' */
  real_T Gain1_d[3];                   /* '<S58>/Gain1' */
  real_T PWM_Duty_Cycles[3];           /* '<S58>/Sum' */
  real_T Switch_k;                     /* '<S173>/Switch' */
  real_T Product_l[3];                 /* '<S173>/Product' */
  real_T Rs[3];                        /* '<S1>/Rs' */
  real_T Subtract[3];                  /* '<S1>/Subtract' */
  real_T TorqueSetpoint;               /* '<Root>/Torque Setpoint' */
  real_T Speed0;                       /* '<S8>/Speed0' */
  real_T Integrator_h;                 /* '<S14>/Integrator' */
  real_T Trq_Or_Spd;                   /* '<S8>/Trq_Or_Spd' */
  real_T polepair;                     /* '<S1>/pole-pair' */
  real_T Product_m[3];                 /* '<S1>/Product' */
  real_T Subtract1[3];                 /* '<S1>/Subtract1' */
  real_T MatrixMultiply_g[3];          /* '<S1>/MatrixMultiply' */
  real_T Product_j;                    /* '<S8>/Product' */
  real_T Subtract_k;                   /* '<S8>/Subtract' */
  real_T uJ;                           /* '<S8>/1//J' */
  real_T Divide1;                      /* '<S16>/Divide1' */
  real_T Divide2;                      /* '<S16>/Divide2' */
  real_T Product1_g;                   /* '<S16>/Product1' */
  real_T Product2_a;                   /* '<S16>/Product2' */
  real_T Add_j;                        /* '<S16>/Add' */
  real_T Divide1_a;                    /* '<S17>/Divide1' */
  real_T Divide2_e;                    /* '<S17>/Divide2' */
  real_T Product1_l;                   /* '<S17>/Product1' */
  real_T Product2_m;                   /* '<S17>/Product2' */
  real_T Add_c;                        /* '<S17>/Add' */
  real_T IntegralGain;                 /* '<S104>/Integral Gain' */
  real_T IntegralGain_b;               /* '<S152>/Integral Gain' */
  real_T Convert_back;                 /* '<S184>/Convert_back' */
  real_T Convert_back_k;               /* '<S183>/Convert_back' */
  real_T bcos;                         /* '<S60>/bcos' */
  real_T asin_d;                       /* '<S60>/asin' */
  real_T sum_Qs;                       /* '<S60>/sum_Qs' */
  real_T acos_f;                       /* '<S60>/acos' */
  real_T bsin;                         /* '<S60>/bsin' */
  real_T sum_Ds;                       /* '<S60>/sum_Ds' */
  real_T Switch_a[2];                  /* '<S179>/Switch' */
  real_T algDD_o1;
  real_T algDD_o2;
  real_T Unary_Minus;                  /* '<S179>/Unary_Minus' */
  real_T qcos;                         /* '<S56>/qcos' */
  real_T dsin;                         /* '<S56>/dsin' */
  real_T sum_beta;                     /* '<S56>/sum_beta' */
  real_T dcos;                         /* '<S56>/dcos' */
  real_T qsin;                         /* '<S56>/qsin' */
  real_T sum_alpha;                    /* '<S56>/sum_alpha' */
  real_T Switch_m[2];                  /* '<S172>/Switch' */
  real_T algDD_o1_c;
  real_T algDD_o2_d;
  real_T Unary_Minus_a;                /* '<S172>/Unary_Minus' */
  real_T Product_b2[2];                /* '<S66>/Product' */
  real_T SquareRoot;                   /* '<S66>/Square Root' */
  real_T Switch_h;                     /* '<S66>/Switch' */
  real_T Reciprocal;                   /* '<S66>/Reciprocal' */
  real_T Switch_az[2];                 /* '<S63>/Switch' */
  real_T Switch2_h;                    /* '<S73>/Switch2' */
  real_T Product_p;                    /* '<S72>/Product' */
  real_T Sum_m;                        /* '<S72>/Sum' */
  real_T Product2_l;                   /* '<S72>/Product2' */
  real_T Merge_o;                      /* '<S72>/Merge' */
  real_T Gain_e;                       /* '<S72>/Gain' */
  real_T Switch_l;                     /* '<S73>/Switch' */
  real_T Switch1_d;                    /* '<S74>/Switch1' */
  real_T Sqrt;                         /* '<S74>/Sqrt' */
  real_T Gain_m;                       /* '<S74>/Gain' */
  real_T a_plus_2b;                    /* '<S51>/a_plus_2b' */
  real_T one_by_sqrt3;                 /* '<S51>/one_by_sqrt3' */
  real_T algDD_o1_e;
  real_T algDD_o2_h;
  real_T Gain_g;                       /* '<S26>/Gain' */
  real_T Bias1;                        /* '<S26>/Bias1' */
  real_T Gain2_n;                      /* '<S26>/Gain2' */
  real_T Bias2;                        /* '<S26>/Bias2' */
  real_T Gain1_e;                      /* '<S26>/Gain1' */
  real_T Bias;                         /* '<S26>/Bias' */
  real_T Gain_h;                       /* '<S25>/Gain' */
  real_T Bias1_p;                      /* '<S25>/Bias1' */
  real_T Gain2_e;                      /* '<S25>/Gain2' */
  real_T Bias2_k;                      /* '<S25>/Bias2' */
  real_T Gain1_l;                      /* '<S25>/Gain1' */
  real_T Bias_o;                       /* '<S25>/Bias' */
  real_T Gain_n;                       /* '<S24>/Gain' */
  real_T Bias1_m;                      /* '<S24>/Bias1' */
  real_T Gain2_ng;                     /* '<S24>/Gain2' */
  real_T Bias2_b;                      /* '<S24>/Bias2' */
  real_T Gain1_k;                      /* '<S24>/Gain1' */
  real_T Bias_k;                       /* '<S24>/Bias' */
  uint32_T Sum_l[4];                   /* '<S61>/Sum' */
  real32_T SPQC;                       /* '<S2>/Constant1' */
  real32_T SPDC;                       /* '<S2>/Constant' */
  real32_T DataTypeConversion1_h[3];   /* '<S57>/Data Type Conversion1' */
  real32_T Saturation2[3];             /* '<S173>/Saturation2' */
  real32_T Sum_f;                      /* '<S173>/Sum' */
  real32_T Gain_i;                     /* '<S173>/Gain' */
  real32_T Sum1_l;                     /* '<S173>/Sum1' */
  real32_T Sum2_f;                     /* '<S173>/Sum2' */
  real32_T Sum3_c;                     /* '<S173>/Sum3' */
  real32_T DataTypeConversion2;        /* '<S3>/Data Type Conversion2' */
  real32_T Product_h;                  /* '<S188>/Product' */
  real32_T UnitDelay;                  /* '<S188>/Unit Delay' */
  real32_T Product1_b;                 /* '<S188>/Product1' */
  real32_T Add1_n;                     /* '<S188>/Add1' */
  uint16_T Switch1_o;                  /* '<S64>/Switch1' */
  uint16_T DataTypeConversion;         /* '<S181>/Data Type Conversion' */
  uint16_T Get_Integer;                /* '<S61>/Get_Integer' */
  uint16_T DataTypeConversion_d;       /* '<S62>/Data Type Conversion' */
  uint16_T DataTypeConversion_j;       /* '<S72>/Data Type Conversion' */
  int16_T Convert_uint16;              /* '<S184>/Convert_uint16' */
  int16_T Convert_uint16_n;            /* '<S183>/Convert_uint16' */
  boolean_T Compare;                   /* '<S27>/Compare' */
  boolean_T Compare_n;                 /* '<S28>/Compare' */
  boolean_T Compare_k;                 /* '<S29>/Compare' */
  boolean_T AND;                       /* '<S24>/AND' */
  boolean_T Compare_p;                 /* '<S30>/Compare' */
  boolean_T Compare_c;                 /* '<S31>/Compare' */
  boolean_T AND1;                      /* '<S24>/AND1' */
  boolean_T Compare_m;                 /* '<S32>/Compare' */
  boolean_T Compare_h;                 /* '<S33>/Compare' */
  boolean_T AND3;                      /* '<S24>/AND3' */
  boolean_T Compare_h4;                /* '<S34>/Compare' */
  boolean_T Compare_cg;                /* '<S35>/Compare' */
  boolean_T Compare_i;                 /* '<S36>/Compare' */
  boolean_T Compare_nw;                /* '<S37>/Compare' */
  boolean_T AND_n;                     /* '<S25>/AND' */
  boolean_T Compare_hx;                /* '<S38>/Compare' */
  boolean_T Compare_cy;                /* '<S39>/Compare' */
  boolean_T AND1_j;                    /* '<S25>/AND1' */
  boolean_T Compare_l;                 /* '<S40>/Compare' */
  boolean_T Compare_b;                 /* '<S41>/Compare' */
  boolean_T AND3_p;                    /* '<S25>/AND3' */
  boolean_T Compare_hm;                /* '<S42>/Compare' */
  boolean_T Compare_mi;                /* '<S43>/Compare' */
  boolean_T Compare_he;                /* '<S44>/Compare' */
  boolean_T Compare_hr;                /* '<S45>/Compare' */
  boolean_T AND_nc;                    /* '<S26>/AND' */
  boolean_T Compare_g;                 /* '<S46>/Compare' */
  boolean_T Compare_pv;                /* '<S47>/Compare' */
  boolean_T AND1_i;                    /* '<S26>/AND1' */
  boolean_T Compare_bo;                /* '<S48>/Compare' */
  boolean_T Compare_ka;                /* '<S49>/Compare' */
  boolean_T AND3_a;                    /* '<S26>/AND3' */
  boolean_T Compare_f;                 /* '<S50>/Compare' */
  boolean_T Compare_pg;                /* '<S182>/Compare' */
  boolean_T RelationalOperator;        /* '<S62>/Relational Operator' */
  boolean_T Compare_o;                 /* '<S68>/Compare' */
  boolean_T Compare_c0;                /* '<S69>/Compare' */
  boolean_T LowerRelop1;               /* '<S73>/LowerRelop1' */
  boolean_T RelationalOperator_g;      /* '<S72>/Relational Operator' */
  boolean_T UpperRelop;                /* '<S73>/UpperRelop' */
} B_SimpleFOC_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_1_DSTATE;           /* '<Root>/Unit Delay' */
  real_T UnitDelay_2_DSTATE;           /* '<Root>/Unit Delay' */
  real_T UnitDelay_9_DSTATE;           /* '<Root>/Unit Delay' */
  real_T Sum2_DWORK1;                  /* '<S2>/Sum2' */
  real_T Subtract_DWORK1;              /* '<S8>/Subtract' */
  real32_T UnitDelay_DSTATE;           /* '<S188>/Unit Delay' */
  uint32_T Sum_DWORK1[4];              /* '<S61>/Sum' */
  int_T Integrator_IWORK;              /* '<S15>/Integrator' */
  int_T Integrator_IWORK_n;            /* '<S19>/Integrator' */
  int_T Integrator_IWORK_o;            /* '<S21>/Integrator' */
  int_T Integrator_IWORK_a;            /* '<S14>/Integrator' */
  int8_T If_ActiveSubsystem;           /* '<S181>/If' */
  int8_T If_ActiveSubsystem_p;         /* '<S52>/If' */
} DW_SimpleFOC_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S19>/Integrator' */
  real_T Integrator_CSTATE_g;          /* '<S21>/Integrator' */
  real_T Integrator_CSTATE_lo;         /* '<S155>/Integrator' */
  real_T Integrator_CSTATE_p;          /* '<S107>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S14>/Integrator' */
} X_SimpleFOC_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S15>/Integrator' */
  real_T Integrator_CSTATE_l;          /* '<S19>/Integrator' */
  real_T Integrator_CSTATE_g;          /* '<S21>/Integrator' */
  real_T Integrator_CSTATE_lo;         /* '<S155>/Integrator' */
  real_T Integrator_CSTATE_p;          /* '<S107>/Integrator' */
  real_T Integrator_CSTATE_c;          /* '<S14>/Integrator' */
} XDot_SimpleFOC_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S15>/Integrator' */
  boolean_T Integrator_CSTATE_l;       /* '<S19>/Integrator' */
  boolean_T Integrator_CSTATE_g;       /* '<S21>/Integrator' */
  boolean_T Integrator_CSTATE_lo;      /* '<S155>/Integrator' */
  boolean_T Integrator_CSTATE_p;       /* '<S107>/Integrator' */
  boolean_T Integrator_CSTATE_c;       /* '<S14>/Integrator' */
} XDis_SimpleFOC_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_SimpleFOC_T_ {
  struct_maxBupWeQJ2AuQC08ctECC Initial;/* Variable: Initial
                                         * Referenced by:
                                         *   '<Root>/Torque Setpoint'
                                         *   '<S2>/12V'
                                         *   '<S8>/Pos0'
                                         *   '<S16>/Id_0'
                                         *   '<S17>/Id_0'
                                         */
  real_T Ki_id;                        /* Variable: Ki_id
                                        * Referenced by: '<S104>/Integral Gain'
                                        */
  real_T Ki_iq;                        /* Variable: Ki_iq
                                        * Referenced by: '<S152>/Integral Gain'
                                        */
  real_T Kp_id;                        /* Variable: Kp_id
                                        * Referenced by: '<S112>/Proportional Gain'
                                        */
  real_T Kp_iq;                        /* Variable: Kp_iq
                                        * Referenced by: '<S160>/Proportional Gain'
                                        */
  real_T BLDC_B;                       /* Mask Parameter: BLDC_B
                                        * Referenced by: '<S8>/Viscous'
                                        */
  real_T BLDC_F;                       /* Mask Parameter: BLDC_F
                                        * Referenced by: '<S8>/FrictionT'
                                        */
  real_T DiscreteQuadratureCurrentContro;
                              /* Mask Parameter: DiscreteQuadratureCurrentContro
                               * Referenced by: '<S155>/Integrator'
                               */
  real_T DiscreteDirectCurrentController;
                              /* Mask Parameter: DiscreteDirectCurrentController
                               * Referenced by: '<S107>/Integrator'
                               */
  real_T BLDC_J;                       /* Mask Parameter: BLDC_J
                                        * Referenced by: '<S8>/1//J'
                                        */
  real_T BLDC_Lambda;                  /* Mask Parameter: BLDC_Lambda
                                        * Referenced by: '<S11>/Max_Lampda_PM_rate'
                                        */
  real_T BLDC_Ld;                      /* Mask Parameter: BLDC_Ld
                                        * Referenced by:
                                        *   '<S4>/Ld'
                                        *   '<S16>/Ld'
                                        *   '<S17>/Ld'
                                        */
  real_T BLDC_Lq;                      /* Mask Parameter: BLDC_Lq
                                        * Referenced by:
                                        *   '<S4>/Lq'
                                        *   '<S16>/Lq'
                                        *   '<S17>/Lq'
                                        */
  real_T BLDC_MechInput;               /* Mask Parameter: BLDC_MechInput
                                        * Referenced by: '<S8>/Constant3'
                                        */
  real_T BLDC_Omega_init;              /* Mask Parameter: BLDC_Omega_init
                                        * Referenced by: '<S8>/Speed0'
                                        */
  real_T BLDC_Rs;                      /* Mask Parameter: BLDC_Rs
                                        * Referenced by: '<S1>/Rs'
                                        */
  real_T CompareToConstant_const;     /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S27>/Constant'
                                       */
  real_T CompareToConstant1_const;   /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S28>/Constant'
                                      */
  real_T CompareToConstant2_const;   /* Mask Parameter: CompareToConstant2_const
                                      * Referenced by: '<S29>/Constant'
                                      */
  real_T CompareToConstant3_const;   /* Mask Parameter: CompareToConstant3_const
                                      * Referenced by: '<S30>/Constant'
                                      */
  real_T CompareToConstant6_const;   /* Mask Parameter: CompareToConstant6_const
                                      * Referenced by: '<S31>/Constant'
                                      */
  real_T CompareToConstant7_const;   /* Mask Parameter: CompareToConstant7_const
                                      * Referenced by: '<S32>/Constant'
                                      */
  real_T CompareToConstant8_const;   /* Mask Parameter: CompareToConstant8_const
                                      * Referenced by: '<S33>/Constant'
                                      */
  real_T CompareToConstant9_const;   /* Mask Parameter: CompareToConstant9_const
                                      * Referenced by: '<S34>/Constant'
                                      */
  real_T CompareToConstant_const_f; /* Mask Parameter: CompareToConstant_const_f
                                     * Referenced by: '<S35>/Constant'
                                     */
  real_T CompareToConstant1_const_l;
                                   /* Mask Parameter: CompareToConstant1_const_l
                                    * Referenced by: '<S36>/Constant'
                                    */
  real_T CompareToConstant2_const_f;
                                   /* Mask Parameter: CompareToConstant2_const_f
                                    * Referenced by: '<S37>/Constant'
                                    */
  real_T CompareToConstant3_const_b;
                                   /* Mask Parameter: CompareToConstant3_const_b
                                    * Referenced by: '<S38>/Constant'
                                    */
  real_T CompareToConstant6_const_k;
                                   /* Mask Parameter: CompareToConstant6_const_k
                                    * Referenced by: '<S39>/Constant'
                                    */
  real_T CompareToConstant7_const_o;
                                   /* Mask Parameter: CompareToConstant7_const_o
                                    * Referenced by: '<S40>/Constant'
                                    */
  real_T CompareToConstant8_const_l;
                                   /* Mask Parameter: CompareToConstant8_const_l
                                    * Referenced by: '<S41>/Constant'
                                    */
  real_T CompareToConstant9_const_c;
                                   /* Mask Parameter: CompareToConstant9_const_c
                                    * Referenced by: '<S42>/Constant'
                                    */
  real_T CompareToConstant_const_b; /* Mask Parameter: CompareToConstant_const_b
                                     * Referenced by: '<S43>/Constant'
                                     */
  real_T CompareToConstant1_const_lf;
                                  /* Mask Parameter: CompareToConstant1_const_lf
                                   * Referenced by: '<S44>/Constant'
                                   */
  real_T CompareToConstant2_const_c;
                                   /* Mask Parameter: CompareToConstant2_const_c
                                    * Referenced by: '<S45>/Constant'
                                    */
  real_T CompareToConstant3_const_k;
                                   /* Mask Parameter: CompareToConstant3_const_k
                                    * Referenced by: '<S46>/Constant'
                                    */
  real_T CompareToConstant6_const_f;
                                   /* Mask Parameter: CompareToConstant6_const_f
                                    * Referenced by: '<S47>/Constant'
                                    */
  real_T CompareToConstant7_const_b;
                                   /* Mask Parameter: CompareToConstant7_const_b
                                    * Referenced by: '<S48>/Constant'
                                    */
  real_T CompareToConstant8_const_b;
                                   /* Mask Parameter: CompareToConstant8_const_b
                                    * Referenced by: '<S49>/Constant'
                                    */
  real_T CompareToConstant9_const_g;
                                   /* Mask Parameter: CompareToConstant9_const_g
                                    * Referenced by: '<S50>/Constant'
                                    */
  real_T BLDC_p;                       /* Mask Parameter: BLDC_p
                                        * Referenced by:
                                        *   '<S1>/pole-pair'
                                        *   '<S4>/Gain1'
                                        *   '<S4>/Gain3'
                                        *   '<S7>/pole-pair1'
                                        */
  uint16_T CompareToConstant_const_j;
                                    /* Mask Parameter: CompareToConstant_const_j
                                     * Referenced by: '<S68>/Constant'
                                     */
  uint16_T CompareToConstant1_const_a;
                                   /* Mask Parameter: CompareToConstant1_const_a
                                    * Referenced by: '<S69>/Constant'
                                    */
  real_T Gain1_Gain;                   /* Expression: 1/(pi/6)
                                        * Referenced by: '<S24>/Gain1'
                                        */
  real_T Bias_Bias;                 /* Expression: -((pi/6) + (2*pi/3))/(pi/6)-1
                                     * Referenced by: '<S24>/Bias'
                                     */
  real_T Gain2_Gain;                   /* Expression: -1/(pi/6)
                                        * Referenced by: '<S24>/Gain2'
                                        */
  real_T Bias2_Bias;            /* Expression: (pi + (pi/6) + (2*pi/3))/(pi/6)+1
                                 * Referenced by: '<S24>/Bias2'
                                 */
  real_T Gain_Gain;                    /* Expression: -1/(pi/6)
                                        * Referenced by: '<S24>/Gain'
                                        */
  real_T Bias1_Bias;                   /* Expression: -(0)/(pi/6)-0
                                        * Referenced by: '<S24>/Bias1'
                                        */
  real_T Gain1_Gain_l;                 /* Expression: 1/(pi/6)
                                        * Referenced by: '<S25>/Gain1'
                                        */
  real_T Bias_Bias_a;               /* Expression: -((pi/6) + (2*pi/3))/(pi/6)-1
                                     * Referenced by: '<S25>/Bias'
                                     */
  real_T Gain2_Gain_b;                 /* Expression: -1/(pi/6)
                                        * Referenced by: '<S25>/Gain2'
                                        */
  real_T Bias2_Bias_j;          /* Expression: (pi + (pi/6) + (2*pi/3))/(pi/6)+1
                                 * Referenced by: '<S25>/Bias2'
                                 */
  real_T Gain_Gain_c;                  /* Expression: -1/(pi/6)
                                        * Referenced by: '<S25>/Gain'
                                        */
  real_T Bias1_Bias_a;                 /* Expression: -(0)/(pi/6)-0
                                        * Referenced by: '<S25>/Bias1'
                                        */
  real_T Gain1_Gain_f;                 /* Expression: 1/(pi/6)
                                        * Referenced by: '<S26>/Gain1'
                                        */
  real_T Bias_Bias_h;               /* Expression: -((pi/6) + (2*pi/3))/(pi/6)-1
                                     * Referenced by: '<S26>/Bias'
                                     */
  real_T Gain2_Gain_p;                 /* Expression: -1/(pi/6)
                                        * Referenced by: '<S26>/Gain2'
                                        */
  real_T Bias2_Bias_c;          /* Expression: (pi + (pi/6) + (2*pi/3))/(pi/6)+1
                                 * Referenced by: '<S26>/Bias2'
                                 */
  real_T Gain_Gain_o;                  /* Expression: -1/(pi/6)
                                        * Referenced by: '<S26>/Gain'
                                        */
  real_T Bias1_Bias_h;                 /* Expression: -(0)/(pi/6)-0
                                        * Referenced by: '<S26>/Bias1'
                                        */
  real_T one_by_sqrt3_Gain;            /* Expression: 1/sqrt(3)
                                        * Referenced by: '<S51>/one_by_sqrt3'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S74>/Constant'
                                        */
  real_T Gain_Gain_p;                  /* Expression: -1
                                        * Referenced by: '<S74>/Gain'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S74>/Switch1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S74>/Switch'
                                        */
  real_T Gain_Gain_k;                  /* Expression: -1
                                        * Referenced by: '<S72>/Gain'
                                        */
  real_T Constant_Value_o;             /* Expression: 1
                                        * Referenced by: '<S66>/Constant'
                                        */
  real_T ReplaceInport_satLim_Value;   /* Expression: 0
                                        * Referenced by: '<S52>/ReplaceInport_satLim'
                                        */
  real_T Constant3_Value;              /* Expression: Vmax
                                        * Referenced by: '<S64>/Constant3'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * Referenced by: '<S173>/Constant'
                                        */
  real_T Constant_Value_h;             /* Expression: 0
                                        * Referenced by: '<S182>/Constant'
                                        */
  real_T Constant_Value_k;             /* Expression: 2*pi
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Minus120_Value[4];
               /* Expression: [cos(2*pi/3) -sin(2*pi/3);sin(2*pi/3) cos(2*pi/3)]
                * Referenced by: '<S5>/Minus120'
                */
  real_T Plus120_Value[4];
               /* Expression: [cos(2*pi/3) sin(2*pi/3);-sin(2*pi/3) cos(2*pi/3)]
                * Referenced by: '<S5>/Plus120'
                */
  real_T Gain2_Gain_n;                 /* Expression: -1
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real_T Constant2_Value;              /* Expression: 1
                                        * Referenced by: '<S5>/Constant2'
                                        */
  real_T Constant_Value_mp;            /* Expression: 0
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Bias3_Bias;                   /* Expression: 0
                                        * Referenced by: '<S24>/Bias3'
                                        */
  real_T Constant7_Value;              /* Expression: 2*pi
                                        * Referenced by: '<S24>/Constant7'
                                        */
  real_T Constant8_Value;              /* Expression: 0
                                        * Referenced by: '<S24>/Constant8'
                                        */
  real_T Constant1_Value;              /* Expression: -1
                                        * Referenced by: '<S24>/Constant1'
                                        */
  real_T Constant3_Value_l;            /* Expression: 0
                                        * Referenced by: '<S24>/Constant3'
                                        */
  real_T Constant2_Value_i;            /* Expression: 0
                                        * Referenced by: '<S24>/Constant2'
                                        */
  real_T Constant4_Value;              /* Expression: 1
                                        * Referenced by: '<S24>/Constant4'
                                        */
  real_T Constant5_Value;              /* Expression: 0
                                        * Referenced by: '<S24>/Constant5'
                                        */
  real_T Constant6_Value;              /* Expression: 0
                                        * Referenced by: '<S24>/Constant6'
                                        */
  real_T Bias3_Bias_g;                 /* Expression: -2*pi/3
                                        * Referenced by: '<S25>/Bias3'
                                        */
  real_T Constant7_Value_n;            /* Expression: 2*pi
                                        * Referenced by: '<S25>/Constant7'
                                        */
  real_T Constant8_Value_h;            /* Expression: 0
                                        * Referenced by: '<S25>/Constant8'
                                        */
  real_T Constant1_Value_d;            /* Expression: -1
                                        * Referenced by: '<S25>/Constant1'
                                        */
  real_T Constant3_Value_l3;           /* Expression: 0
                                        * Referenced by: '<S25>/Constant3'
                                        */
  real_T Constant2_Value_l;            /* Expression: 0
                                        * Referenced by: '<S25>/Constant2'
                                        */
  real_T Constant4_Value_k;            /* Expression: 1
                                        * Referenced by: '<S25>/Constant4'
                                        */
  real_T Constant5_Value_a;            /* Expression: 0
                                        * Referenced by: '<S25>/Constant5'
                                        */
  real_T Constant6_Value_h;            /* Expression: 0
                                        * Referenced by: '<S25>/Constant6'
                                        */
  real_T Bias3_Bias_f;                 /* Expression: -4*pi/3
                                        * Referenced by: '<S26>/Bias3'
                                        */
  real_T Constant7_Value_k;            /* Expression: 2*pi
                                        * Referenced by: '<S26>/Constant7'
                                        */
  real_T Constant8_Value_g;            /* Expression: 0
                                        * Referenced by: '<S26>/Constant8'
                                        */
  real_T Constant1_Value_j;            /* Expression: -1
                                        * Referenced by: '<S26>/Constant1'
                                        */
  real_T Constant3_Value_o;            /* Expression: 0
                                        * Referenced by: '<S26>/Constant3'
                                        */
  real_T Constant2_Value_c;            /* Expression: 0
                                        * Referenced by: '<S26>/Constant2'
                                        */
  real_T Constant4_Value_l;            /* Expression: 1
                                        * Referenced by: '<S26>/Constant4'
                                        */
  real_T Constant5_Value_ay;           /* Expression: 0
                                        * Referenced by: '<S26>/Constant5'
                                        */
  real_T Constant6_Value_b;            /* Expression: 0
                                        * Referenced by: '<S26>/Constant6'
                                        */
  real_T Gain_Gain_pp;                 /* Expression: -1
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Constant2_Value_h;            /* Expression: 0.5
                                        * Referenced by: '<S6>/Constant2'
                                        */
  real_T Minus120_Value_i[4];
               /* Expression: [cos(2*pi/3) -sin(2*pi/3);sin(2*pi/3) cos(2*pi/3)]
                * Referenced by: '<S6>/Minus120'
                */
  real_T Gain2_Gain_bt;                /* Expression: -1
                                        * Referenced by: '<S6>/Gain2'
                                        */
  real_T Plus120_Value_j[4];
               /* Expression: [cos(2*pi/3) sin(2*pi/3);-sin(2*pi/3) cos(2*pi/3)]
                * Referenced by: '<S6>/Plus120'
                */
  real_T Gain3_Gain;                   /* Expression: -1
                                        * Referenced by: '<S6>/Gain3'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: 2/3
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real_T UnitDelay_1_InitialCondition; /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T UnitDelay_2_InitialCondition; /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T sine_table_values_Value[1002];/* Expression: dlgSett.sin_table
                                        * Referenced by: '<S61>/sine_table_values'
                                        */
  real_T UnitDelay_9_InitialCondition; /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T convert_pu_Gain;              /* Expression: 1/(dlgSett.UpperSatLimit)
                                        * Referenced by: '<S181>/convert_pu'
                                        */
  real_T indexing_Gain;                /* Expression: dlgSett.index_gain
                                        * Referenced by: '<S61>/indexing'
                                        */
  real_T one_by_two_Gain;              /* Expression: 1/2
                                        * Referenced by: '<S55>/one_by_two'
                                        */
  real_T sqrt3_by_two_Gain;            /* Expression: sqrt(3)/2
                                        * Referenced by: '<S55>/sqrt3_by_two'
                                        */
  real_T one_by_two_Gain_o;            /* Expression: -0.5
                                        * Referenced by: '<S177>/one_by_two'
                                        */
  real_T Gain_Gain_e;                  /* Expression: 2/sqrt(3)
                                        * Referenced by: '<S176>/Gain'
                                        */
  real_T Gain1_Gain_e;                 /* Expression: 0.5
                                        * Referenced by: '<S58>/Gain1'
                                        */
  real_T Constant4_Value_lq;           /* Expression: 0.5
                                        * Referenced by: '<S58>/Constant4'
                                        */
  real_T Switch_Threshold_j;           /* Expression: 0
                                        * Referenced by: '<S173>/Switch'
                                        */
  real_T TorqueSetpoint_Time;          /* Expression: 5
                                        * Referenced by: '<Root>/Torque Setpoint'
                                        */
  real_T TorqueSetpoint_YFinal;        /* Expression: 0*bldc.T_rated
                                        * Referenced by: '<Root>/Torque Setpoint'
                                        */
  real_T Trq_Or_Spd_Threshold;         /* Expression: 1
                                        * Referenced by: '<S8>/Trq_Or_Spd'
                                        */
  real32_T Constant1_Value_c;          /* Expression: Initial.Iq
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real32_T Constant_Value_j;           /* Expression: Initial.Id
                                        * Referenced by: '<S2>/Constant'
                                        */
  real32_T Saturation2_UpperSat;     /* Computed Parameter: Saturation2_UpperSat
                                      * Referenced by: '<S173>/Saturation2'
                                      */
  real32_T Saturation2_LowerSat;     /* Computed Parameter: Saturation2_LowerSat
                                      * Referenced by: '<S173>/Saturation2'
                                      */
  real32_T Gain_Gain_i;                /* Computed Parameter: Gain_Gain_i
                                        * Referenced by: '<S173>/Gain'
                                        */
  real32_T Filter_Constant_Value;   /* Computed Parameter: Filter_Constant_Value
                                     * Referenced by: '<S188>/Filter_Constant'
                                     */
  real32_T One_Value;                  /* Computed Parameter: One_Value
                                        * Referenced by: '<S188>/One'
                                        */
  real32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S188>/Unit Delay'
                                */
  int16_T offset_Value[4];             /* Computed Parameter: offset_Value
                                        * Referenced by: '<S61>/offset'
                                        */
  uint16_T ReplaceInport_satMethod_Value;
                            /* Computed Parameter: ReplaceInport_satMethod_Value
                             * Referenced by: '<S52>/ReplaceInport_satMethod'
                             */
  uint16_T ChosenMethod_Value;         /* Computed Parameter: ChosenMethod_Value
                                        * Referenced by: '<S64>/ChosenMethod'
                                        */
  uint16_T Offset_Value;               /* Computed Parameter: Offset_Value
                                        * Referenced by: '<S172>/Offset'
                                        */
  uint16_T Switch_Threshold_c;         /* Computed Parameter: Switch_Threshold_c
                                        * Referenced by: '<S172>/Switch'
                                        */
  uint16_T Offset_Value_h;             /* Computed Parameter: Offset_Value_h
                                        * Referenced by: '<S179>/Offset'
                                        */
  uint16_T Switch_Threshold_b;         /* Computed Parameter: Switch_Threshold_b
                                        * Referenced by: '<S179>/Switch'
                                        */
  uint16_T enableInportSatMethod_Value;
                              /* Computed Parameter: enableInportSatMethod_Value
                               * Referenced by: '<S64>/enableInportSatMethod'
                               */
  uint16_T enableInportSatLim_Value;
                                 /* Computed Parameter: enableInportSatLim_Value
                                  * Referenced by: '<S64>/enableInportSatLim'
                                  */
};

/* Real-time Model Data Structure */
struct tag_RTM_SimpleFOC_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_SimpleFOC_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_SimpleFOC_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    boolean_T firstInitCondFlag;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_SimpleFOC_T SimpleFOC_P;

/* Block signals (default storage) */
extern B_SimpleFOC_T SimpleFOC_B;

/* Continuous states (default storage) */
extern X_SimpleFOC_T SimpleFOC_X;

/* Block states (default storage) */
extern DW_SimpleFOC_T SimpleFOC_DW;

/* Model entry point functions */
extern void SimpleFOC_initialize(void);
extern void SimpleFOC_step(void);
extern void SimpleFOC_terminate(void);

/* Real-time Model object */
extern RT_MODEL_SimpleFOC_T *const SimpleFOC_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Constant3' : Unused code path elimination
 * Block '<S10>/Data Type Conversion' : Unused code path elimination
 * Block '<S22>/Constant' : Unused code path elimination
 * Block '<S22>/Constant1' : Unused code path elimination
 * Block '<S22>/Constant2' : Unused code path elimination
 * Block '<S22>/Constant3' : Unused code path elimination
 * Block '<S22>/Constant4' : Unused code path elimination
 * Block '<S22>/Constant5' : Unused code path elimination
 * Block '<S22>/Logical Operator' : Unused code path elimination
 * Block '<S22>/Logical Operator1' : Unused code path elimination
 * Block '<S22>/Logical Operator2' : Unused code path elimination
 * Block '<S22>/Relational Operator1' : Unused code path elimination
 * Block '<S22>/Relational Operator2' : Unused code path elimination
 * Block '<S22>/Relational Operator3' : Unused code path elimination
 * Block '<S22>/Relational Operator4' : Unused code path elimination
 * Block '<S22>/Relational Operator5' : Unused code path elimination
 * Block '<S22>/Relational Operator6' : Unused code path elimination
 * Block '<S23>/Trigonometric Function' : Unused code path elimination
 * Block '<S23>/Trigonometric Function2' : Unused code path elimination
 * Block '<S23>/mech->elec' : Unused code path elimination
 * Block '<S23>/rad->deg' : Unused code path elimination
 * Block '<S1>/Trq_Or_Spd' : Unused code path elimination
 * Block '<S51>/Data Type Duplicate' : Unused code path elimination
 * Block '<S66>/Data Type Duplicate' : Unused code path elimination
 * Block '<S73>/Data Type Duplicate' : Unused code path elimination
 * Block '<S73>/Data Type Propagation' : Unused code path elimination
 * Block '<S74>/Data Type Duplicate' : Unused code path elimination
 * Block '<S52>/Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate2' : Unused code path elimination
 * Block '<S65>/Sqrt' : Unused code path elimination
 * Block '<S55>/Data Type Duplicate' : Unused code path elimination
 * Block '<S56>/Data Type Duplicate' : Unused code path elimination
 * Block '<S56>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate1' : Unused code path elimination
 * Block '<S61>/Data Type Duplicate' : Unused code path elimination
 * Block '<S61>/Data Type Propagation' : Unused code path elimination
 * Block '<S183>/Data Type Duplicate' : Unused code path elimination
 * Block '<S184>/Data Type Duplicate' : Unused code path elimination
 * Block '<S188>/Data Type Duplicate' : Unused code path elimination
 * Block '<S57>/Rate Transition5' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition2' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition3' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition4' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition6' : Eliminated since input and output rates are identical
 * Block '<S2>/Rate Transition7' : Eliminated since input and output rates are identical
 * Block '<S61>/Get_FractionVal' : Eliminate redundant data type conversion
 * Block '<Root>/Rate Transition1' : Eliminated since input and output rates are identical
 * Block '<Root>/Rate Transition2' : Eliminated since input and output rates are identical
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SimpleFOC'
 * '<S1>'   : 'SimpleFOC/BLDC'
 * '<S2>'   : 'SimpleFOC/FOC'
 * '<S3>'   : 'SimpleFOC/Filter'
 * '<S4>'   : 'SimpleFOC/BLDC/ElecTorque'
 * '<S5>'   : 'SimpleFOC/BLDC/Matrix_InvP'
 * '<S6>'   : 'SimpleFOC/BLDC/Matrix_P'
 * '<S7>'   : 'SimpleFOC/BLDC/MechToElec'
 * '<S8>'   : 'SimpleFOC/BLDC/Mechanical Equation'
 * '<S9>'   : 'SimpleFOC/BLDC/Motor Equation'
 * '<S10>'  : 'SimpleFOC/BLDC/MotorInfo'
 * '<S11>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta'
 * '<S12>'  : 'SimpleFOC/BLDC/Mechanical Equation/Integration1'
 * '<S13>'  : 'SimpleFOC/BLDC/Mechanical Equation/Integration2'
 * '<S14>'  : 'SimpleFOC/BLDC/Mechanical Equation/Integration1/Continuous Integration'
 * '<S15>'  : 'SimpleFOC/BLDC/Mechanical Equation/Integration2/Continuous Integration'
 * '<S16>'  : 'SimpleFOC/BLDC/Motor Equation/D-axis'
 * '<S17>'  : 'SimpleFOC/BLDC/Motor Equation/Q-axis'
 * '<S18>'  : 'SimpleFOC/BLDC/Motor Equation/D-axis/Integration'
 * '<S19>'  : 'SimpleFOC/BLDC/Motor Equation/D-axis/Integration/Continuous Integration'
 * '<S20>'  : 'SimpleFOC/BLDC/Motor Equation/Q-axis/Integration'
 * '<S21>'  : 'SimpleFOC/BLDC/Motor Equation/Q-axis/Integration/Continuous Integration'
 * '<S22>'  : 'SimpleFOC/BLDC/MotorInfo/Hall sensor'
 * '<S23>'  : 'SimpleFOC/BLDC/MotorInfo/Hall sensor/Subsystem'
 * '<S24>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a'
 * '<S25>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b'
 * '<S26>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c'
 * '<S27>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant'
 * '<S28>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant1'
 * '<S29>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant2'
 * '<S30>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant3'
 * '<S31>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant6'
 * '<S32>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant7'
 * '<S33>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant8'
 * '<S34>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-a/Compare To Constant9'
 * '<S35>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant'
 * '<S36>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant1'
 * '<S37>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant2'
 * '<S38>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant3'
 * '<S39>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant6'
 * '<S40>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant7'
 * '<S41>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant8'
 * '<S42>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-b/Compare To Constant9'
 * '<S43>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant'
 * '<S44>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant1'
 * '<S45>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant2'
 * '<S46>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant3'
 * '<S47>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant6'
 * '<S48>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant7'
 * '<S49>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant8'
 * '<S50>'  : 'SimpleFOC/BLDC/d_Psi_d_Theta/Phase-c/Compare To Constant9'
 * '<S51>'  : 'SimpleFOC/FOC/Clarke Transform'
 * '<S52>'  : 'SimpleFOC/FOC/DQ Limiter'
 * '<S53>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller'
 * '<S54>'  : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller'
 * '<S55>'  : 'SimpleFOC/FOC/Inverse Clarke Transform'
 * '<S56>'  : 'SimpleFOC/FOC/Inverse Park Transform'
 * '<S57>'  : 'SimpleFOC/FOC/Inverter'
 * '<S58>'  : 'SimpleFOC/FOC/Output Scaling'
 * '<S59>'  : 'SimpleFOC/FOC/PWM Reference Generator'
 * '<S60>'  : 'SimpleFOC/FOC/Park Transform'
 * '<S61>'  : 'SimpleFOC/FOC/Sine-Cosine Lookup'
 * '<S62>'  : 'SimpleFOC/FOC/DQ Limiter/D-Q Equivalence'
 * '<S63>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority'
 * '<S64>'  : 'SimpleFOC/FOC/DQ Limiter/Inport//Dialog Selection'
 * '<S65>'  : 'SimpleFOC/FOC/DQ Limiter/Magnitude_calc'
 * '<S66>'  : 'SimpleFOC/FOC/DQ Limiter/D-Q Equivalence/Limiter'
 * '<S67>'  : 'SimpleFOC/FOC/DQ Limiter/D-Q Equivalence/Passthrough'
 * '<S68>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/Compare To Constant'
 * '<S69>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/Compare To Constant1'
 * '<S70>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/flipInputs'
 * '<S71>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/flipInputs1'
 * '<S72>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/limiter'
 * '<S73>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/limiter/limitRef1'
 * '<S74>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/limiter/limitRef2'
 * '<S75>'  : 'SimpleFOC/FOC/DQ Limiter/D//Q Axis Priority/limiter/passThrough'
 * '<S76>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Anti-windup'
 * '<S77>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/D Gain'
 * '<S78>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Filter'
 * '<S79>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Filter ICs'
 * '<S80>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/I Gain'
 * '<S81>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Ideal P Gain'
 * '<S82>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Ideal P Gain Fdbk'
 * '<S83>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Integrator'
 * '<S84>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Integrator ICs'
 * '<S85>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/N Copy'
 * '<S86>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/N Gain'
 * '<S87>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/P Copy'
 * '<S88>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Parallel P Gain'
 * '<S89>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Reset Signal'
 * '<S90>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Saturation'
 * '<S91>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Saturation Fdbk'
 * '<S92>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Sum'
 * '<S93>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Sum Fdbk'
 * '<S94>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tracking Mode'
 * '<S95>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tracking Mode Sum'
 * '<S96>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tsamp - Integral'
 * '<S97>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tsamp - Ngain'
 * '<S98>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/postSat Signal'
 * '<S99>'  : 'SimpleFOC/FOC/Discrete Direct-Current Controller/preSat Signal'
 * '<S100>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Anti-windup/Passthrough'
 * '<S101>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/D Gain/Disabled'
 * '<S102>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Filter/Disabled'
 * '<S103>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Filter ICs/Disabled'
 * '<S104>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/I Gain/Internal Parameters'
 * '<S105>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Ideal P Gain/Passthrough'
 * '<S106>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Ideal P Gain Fdbk/Disabled'
 * '<S107>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Integrator/Continuous'
 * '<S108>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Integrator ICs/Internal IC'
 * '<S109>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/N Copy/Disabled wSignal Specification'
 * '<S110>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/N Gain/Disabled'
 * '<S111>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/P Copy/Disabled'
 * '<S112>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Parallel P Gain/Internal Parameters'
 * '<S113>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Reset Signal/Disabled'
 * '<S114>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Saturation/Passthrough'
 * '<S115>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Saturation Fdbk/Disabled'
 * '<S116>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Sum/Sum_PI'
 * '<S117>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Sum Fdbk/Disabled'
 * '<S118>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tracking Mode/Disabled'
 * '<S119>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tracking Mode Sum/Passthrough'
 * '<S120>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S121>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/Tsamp - Ngain/Passthrough'
 * '<S122>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/postSat Signal/Forward_Path'
 * '<S123>' : 'SimpleFOC/FOC/Discrete Direct-Current Controller/preSat Signal/Forward_Path'
 * '<S124>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Anti-windup'
 * '<S125>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/D Gain'
 * '<S126>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Filter'
 * '<S127>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Filter ICs'
 * '<S128>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/I Gain'
 * '<S129>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Ideal P Gain'
 * '<S130>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Ideal P Gain Fdbk'
 * '<S131>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Integrator'
 * '<S132>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Integrator ICs'
 * '<S133>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/N Copy'
 * '<S134>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/N Gain'
 * '<S135>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/P Copy'
 * '<S136>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Parallel P Gain'
 * '<S137>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Reset Signal'
 * '<S138>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Saturation'
 * '<S139>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Saturation Fdbk'
 * '<S140>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Sum'
 * '<S141>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Sum Fdbk'
 * '<S142>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tracking Mode'
 * '<S143>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tracking Mode Sum'
 * '<S144>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tsamp - Integral'
 * '<S145>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tsamp - Ngain'
 * '<S146>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/postSat Signal'
 * '<S147>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/preSat Signal'
 * '<S148>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Anti-windup/Passthrough'
 * '<S149>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/D Gain/Disabled'
 * '<S150>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Filter/Disabled'
 * '<S151>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Filter ICs/Disabled'
 * '<S152>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/I Gain/Internal Parameters'
 * '<S153>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Ideal P Gain/Passthrough'
 * '<S154>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Ideal P Gain Fdbk/Disabled'
 * '<S155>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Integrator/Continuous'
 * '<S156>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Integrator ICs/Internal IC'
 * '<S157>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/N Copy/Disabled wSignal Specification'
 * '<S158>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/N Gain/Disabled'
 * '<S159>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/P Copy/Disabled'
 * '<S160>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Parallel P Gain/Internal Parameters'
 * '<S161>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Reset Signal/Disabled'
 * '<S162>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Saturation/Passthrough'
 * '<S163>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Saturation Fdbk/Disabled'
 * '<S164>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Sum/Sum_PI'
 * '<S165>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Sum Fdbk/Disabled'
 * '<S166>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tracking Mode/Disabled'
 * '<S167>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tracking Mode Sum/Passthrough'
 * '<S168>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S169>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/Tsamp - Ngain/Passthrough'
 * '<S170>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/postSat Signal/Forward_Path'
 * '<S171>' : 'SimpleFOC/FOC/Discrete Quadrature-Current Controller/preSat Signal/Forward_Path'
 * '<S172>' : 'SimpleFOC/FOC/Inverse Park Transform/Switch_Axis'
 * '<S173>' : 'SimpleFOC/FOC/Inverter/Average-Value Inverter'
 * '<S174>' : 'SimpleFOC/FOC/PWM Reference Generator/Modulation method'
 * '<S175>' : 'SimpleFOC/FOC/PWM Reference Generator/Voltage Input'
 * '<S176>' : 'SimpleFOC/FOC/PWM Reference Generator/Modulation method/SVPWM'
 * '<S177>' : 'SimpleFOC/FOC/PWM Reference Generator/Modulation method/SVPWM/Half(Vmin+Vmax)'
 * '<S178>' : 'SimpleFOC/FOC/PWM Reference Generator/Voltage Input/Vabc'
 * '<S179>' : 'SimpleFOC/FOC/Park Transform/Switch_Axis'
 * '<S180>' : 'SimpleFOC/FOC/Sine-Cosine Lookup/Interpolation'
 * '<S181>' : 'SimpleFOC/FOC/Sine-Cosine Lookup/WrapUp'
 * '<S182>' : 'SimpleFOC/FOC/Sine-Cosine Lookup/WrapUp/Compare To Zero'
 * '<S183>' : 'SimpleFOC/FOC/Sine-Cosine Lookup/WrapUp/If Action Subsystem'
 * '<S184>' : 'SimpleFOC/FOC/Sine-Cosine Lookup/WrapUp/If Action Subsystem1'
 * '<S185>' : 'SimpleFOC/Filter/IIR Filter2'
 * '<S186>' : 'SimpleFOC/Filter/IIR Filter2/IIR Filter'
 * '<S187>' : 'SimpleFOC/Filter/IIR Filter2/IIR Filter/Low-pass'
 * '<S188>' : 'SimpleFOC/Filter/IIR Filter2/IIR Filter/Low-pass/IIR Low Pass Filter'
 */
#endif                                 /* RTW_HEADER_SimpleFOC_h_ */
