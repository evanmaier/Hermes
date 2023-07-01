/*
 * SimpleFOC_types.h
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

#ifndef RTW_HEADER_SimpleFOC_types_h_
#define RTW_HEADER_SimpleFOC_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_J7t6RGObaCo2oYnr7cGuTF_
#define DEFINED_TYPEDEF_FOR_struct_J7t6RGObaCo2oYnr7cGuTF_

typedef struct {
  real_T ILd;
  real_T ILq;
  real_T ITheta;
} struct_J7t6RGObaCo2oYnr7cGuTF;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_maxBupWeQJ2AuQC08ctECC_
#define DEFINED_TYPEDEF_FOR_struct_maxBupWeQJ2AuQC08ctECC_

typedef struct {
  struct_J7t6RGObaCo2oYnr7cGuTF bldc;
  real_T Speed;
  real_T Torque;
  real_T Id;
  real_T Iq;
  real_T InverterVoltage;
} struct_maxBupWeQJ2AuQC08ctECC;

#endif

/* Parameters (default storage) */
typedef struct P_SimpleFOC_T_ P_SimpleFOC_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_SimpleFOC_T RT_MODEL_SimpleFOC_T;

#endif                                 /* RTW_HEADER_SimpleFOC_types_h_ */
