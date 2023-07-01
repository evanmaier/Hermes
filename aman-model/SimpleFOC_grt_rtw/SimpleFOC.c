/*
 * SimpleFOC.c
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

#include "SimpleFOC.h"
#include "rtwtypes.h"
#include "SimpleFOC_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <float.h>
#include <string.h>

/* Block signals (default storage) */
B_SimpleFOC_T SimpleFOC_B;

/* Continuous states */
X_SimpleFOC_T SimpleFOC_X;

/* Block states (default storage) */
DW_SimpleFOC_T SimpleFOC_DW;

/* Real-time model */
static RT_MODEL_SimpleFOC_T SimpleFOC_M_;
RT_MODEL_SimpleFOC_T *const SimpleFOC_M = &SimpleFOC_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  SimpleFOC_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  SimpleFOC_step();
  SimpleFOC_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  SimpleFOC_step();
  SimpleFOC_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      real_T q;
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Model step function */
void SimpleFOC_step(void)
{
  real_T Bias;
  real_T cosOut;
  real_T cosOut_tmp;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  real_T tmp_3;
  real_T tmp_4;
  real_T *tmp_5;
  int32_T i;
  real32_T u0;
  uint32_T Sum_l;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* set solver stop time */
    if (!(SimpleFOC_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&SimpleFOC_M->solverInfo,
                            ((SimpleFOC_M->Timing.clockTickH0 + 1) *
        SimpleFOC_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&SimpleFOC_M->solverInfo,
                            ((SimpleFOC_M->Timing.clockTick0 + 1) *
        SimpleFOC_M->Timing.stepSize0 + SimpleFOC_M->Timing.clockTickH0 *
        SimpleFOC_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(SimpleFOC_M)) {
    SimpleFOC_M->Timing.t[0] = rtsiGetT(&SimpleFOC_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Constant: '<S8>/Pos0' */
    SimpleFOC_B.Pos0 = SimpleFOC_P.Initial.bldc.ITheta;
  }

  /* Integrator: '<S15>/Integrator' */
  if (SimpleFOC_DW.Integrator_IWORK != 0) {
    SimpleFOC_X.Integrator_CSTATE = SimpleFOC_B.Pos0;
  }

  /* Integrator: '<S15>/Integrator' */
  SimpleFOC_B.Integrator = SimpleFOC_X.Integrator_CSTATE;

  /* Gain: '<S7>/pole-pair1' */
  SimpleFOC_B.polepair1 = SimpleFOC_P.BLDC_p * SimpleFOC_B.Integrator;

  /* Math: '<S7>/Mod' incorporates:
   *  Constant: '<S7>/Constant'
   */
  SimpleFOC_B.Mod = rt_modd_snf(SimpleFOC_B.polepair1,
    SimpleFOC_P.Constant_Value_k);

  /* Trigonometry: '<S5>/SinCos' incorporates:
   *  Trigonometry: '<S6>/SinCos'
   */
  cosOut = SimpleFOC_B.Mod;
  Bias = sin(cosOut);
  cosOut_tmp = cos(cosOut);
  cosOut = cosOut_tmp;

  /* Trigonometry: '<S5>/SinCos' */
  SimpleFOC_B.SinCos_o1 = Bias;

  /* Trigonometry: '<S5>/SinCos' */
  SimpleFOC_B.SinCos_o2 = cosOut;

  /* SignalConversion generated from: '<S5>/MatrixMultiply' */
  SimpleFOC_B.TmpSignalConversionAtMatrixMult[0] = SimpleFOC_B.SinCos_o1;
  SimpleFOC_B.TmpSignalConversionAtMatrixMult[1] = SimpleFOC_B.SinCos_o2;

  /* Product: '<S5>/MatrixMultiply' incorporates:
   *  Constant: '<S5>/Minus120'
   */
  cosOut = SimpleFOC_P.Minus120_Value[0];
  tmp_3 = SimpleFOC_P.Minus120_Value[1];
  tmp_1 = SimpleFOC_P.Minus120_Value[2];
  tmp_4 = SimpleFOC_P.Minus120_Value[3];
  tmp_0 = SimpleFOC_B.TmpSignalConversionAtMatrixMult[0];
  tmp_2 = SimpleFOC_B.TmpSignalConversionAtMatrixMult[1];
  tmp = cosOut * tmp_0;
  tmp += tmp_1 * tmp_2;

  /* Product: '<S5>/MatrixMultiply' */
  SimpleFOC_B.MatrixMultiply[0] = tmp;

  /* Product: '<S5>/MatrixMultiply' */
  tmp = tmp_3 * tmp_0;
  tmp += tmp_4 * tmp_2;

  /* Product: '<S5>/MatrixMultiply' */
  SimpleFOC_B.MatrixMultiply[1] = tmp;

  /* Product: '<S5>/MatrixMultiply1' incorporates:
   *  Constant: '<S5>/Plus120'
   */
  cosOut = SimpleFOC_P.Plus120_Value[0];
  tmp_3 = SimpleFOC_P.Plus120_Value[1];
  tmp_1 = SimpleFOC_P.Plus120_Value[2];
  tmp_4 = SimpleFOC_P.Plus120_Value[3];
  tmp_0 = SimpleFOC_B.TmpSignalConversionAtMatrixMult[0];
  tmp_2 = SimpleFOC_B.TmpSignalConversionAtMatrixMult[1];
  tmp = cosOut * tmp_0;
  tmp += tmp_1 * tmp_2;

  /* Product: '<S5>/MatrixMultiply1' */
  SimpleFOC_B.MatrixMultiply1[0] = tmp;

  /* Product: '<S5>/MatrixMultiply1' */
  tmp = tmp_3 * tmp_0;
  tmp += tmp_4 * tmp_2;

  /* Product: '<S5>/MatrixMultiply1' */
  SimpleFOC_B.MatrixMultiply1[1] = tmp;

  /* SignalConversion generated from: '<S5>/Matrix Concatenate1' incorporates:
   *  Concatenate: '<S5>/Matrix Concatenate1'
   */
  SimpleFOC_B.MatrixConcatenate1[0] = SimpleFOC_B.SinCos_o2;
  SimpleFOC_B.MatrixConcatenate1[1] = SimpleFOC_B.MatrixMultiply[1];
  SimpleFOC_B.MatrixConcatenate1[2] = SimpleFOC_B.MatrixMultiply1[1];

  /* Gain: '<S5>/Gain2' incorporates:
   *  Concatenate: '<S5>/Matrix Concatenate1'
   */
  SimpleFOC_B.MatrixConcatenate1[3] = SimpleFOC_P.Gain2_Gain_n *
    SimpleFOC_B.SinCos_o1;
  SimpleFOC_B.MatrixConcatenate1[4] = SimpleFOC_P.Gain2_Gain_n *
    SimpleFOC_B.MatrixMultiply[0];
  SimpleFOC_B.MatrixConcatenate1[5] = SimpleFOC_P.Gain2_Gain_n *
    SimpleFOC_B.MatrixMultiply1[0];

  /* SignalConversion generated from: '<S5>/Matrix Concatenate1' incorporates:
   *  Concatenate: '<S5>/Matrix Concatenate1'
   *  Constant: '<S5>/Constant2'
   */
  SimpleFOC_B.MatrixConcatenate1[6] = SimpleFOC_P.Constant2_Value;
  SimpleFOC_B.MatrixConcatenate1[7] = SimpleFOC_P.Constant2_Value;
  SimpleFOC_B.MatrixConcatenate1[8] = SimpleFOC_P.Constant2_Value;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Constant: '<S16>/Id_0' */
    SimpleFOC_B.Id_0 = SimpleFOC_P.Initial.bldc.ILd;
  }

  /* Integrator: '<S19>/Integrator' */
  if (SimpleFOC_DW.Integrator_IWORK_n != 0) {
    SimpleFOC_X.Integrator_CSTATE_l = SimpleFOC_B.Id_0;
  }

  /* Integrator: '<S19>/Integrator' */
  SimpleFOC_B.Integrator_d = SimpleFOC_X.Integrator_CSTATE_l;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Constant: '<S17>/Id_0' */
    SimpleFOC_B.Id_0_e = SimpleFOC_P.Initial.bldc.ILq;
  }

  /* Integrator: '<S21>/Integrator' */
  if (SimpleFOC_DW.Integrator_IWORK_o != 0) {
    SimpleFOC_X.Integrator_CSTATE_g = SimpleFOC_B.Id_0_e;
  }

  /* Integrator: '<S21>/Integrator' */
  SimpleFOC_B.Integrator_a = SimpleFOC_X.Integrator_CSTATE_g;

  /* SignalConversion generated from: '<S4>/MatrixMultiply2' incorporates:
   *  Constant: '<S9>/Constant'
   */
  SimpleFOC_B.TmpSignalConversionAtMatrixMu_m[0] = SimpleFOC_B.Integrator_d;
  SimpleFOC_B.TmpSignalConversionAtMatrixMu_m[1] = SimpleFOC_B.Integrator_a;
  SimpleFOC_B.TmpSignalConversionAtMatrixMu_m[2] = SimpleFOC_P.Constant_Value_mp;

  /* Product: '<S4>/MatrixMultiply2' incorporates:
   *  Concatenate: '<S5>/Matrix Concatenate1'
   *  Product: '<S1>/MatrixMultiply'
   */
  tmp_5 = &SimpleFOC_B.MatrixConcatenate1[0];
  cosOut = SimpleFOC_B.TmpSignalConversionAtMatrixMu_m[0];
  tmp_3 = SimpleFOC_B.TmpSignalConversionAtMatrixMu_m[1];
  tmp_1 = SimpleFOC_B.TmpSignalConversionAtMatrixMu_m[2];
  for (i = 0; i < 3; i++) {
    tmp = tmp_5[i] * cosOut;
    tmp += tmp_5[i + 3] * tmp_3;
    tmp += tmp_5[i + 6] * tmp_1;

    /* Product: '<S4>/MatrixMultiply2' */
    SimpleFOC_B.MatrixMultiply2[i] = tmp;
  }

  /* Bias: '<S24>/Bias3' */
  SimpleFOC_B.Bias3 = SimpleFOC_B.Mod + SimpleFOC_P.Bias3_Bias;

  /* Math: '<S24>/Mod' incorporates:
   *  Constant: '<S24>/Constant7'
   */
  SimpleFOC_B.Mod_i = rt_modd_snf(SimpleFOC_B.Bias3, SimpleFOC_P.Constant7_Value);

  /* RelationalOperator: '<S27>/Compare' incorporates:
   *  Constant: '<S27>/Constant'
   */
  SimpleFOC_B.Compare = (SimpleFOC_B.Mod_i <=
    SimpleFOC_P.CompareToConstant_const);

  /* Switch: '<S24>/Switch' */
  if (SimpleFOC_B.Compare) {
    /* Gain: '<S24>/Gain' */
    SimpleFOC_B.Gain_n = SimpleFOC_P.Gain_Gain * SimpleFOC_B.Mod_i;

    /* Bias: '<S24>/Bias1' */
    SimpleFOC_B.Bias1_m = SimpleFOC_B.Gain_n + SimpleFOC_P.Bias1_Bias;

    /* Switch: '<S24>/Switch' */
    SimpleFOC_B.Switch = SimpleFOC_B.Bias1_m;
  } else {
    /* Switch: '<S24>/Switch' incorporates:
     *  Constant: '<S24>/Constant8'
     */
    SimpleFOC_B.Switch = SimpleFOC_P.Constant8_Value;
  }

  /* End of Switch: '<S24>/Switch' */

  /* RelationalOperator: '<S28>/Compare' incorporates:
   *  Constant: '<S28>/Constant'
   */
  SimpleFOC_B.Compare_n = (SimpleFOC_B.Mod_i >
    SimpleFOC_P.CompareToConstant1_const);

  /* RelationalOperator: '<S29>/Compare' incorporates:
   *  Constant: '<S29>/Constant'
   */
  SimpleFOC_B.Compare_k = (SimpleFOC_B.Mod_i <=
    SimpleFOC_P.CompareToConstant2_const);

  /* Logic: '<S24>/AND' */
  SimpleFOC_B.AND = (SimpleFOC_B.Compare_n && SimpleFOC_B.Compare_k);

  /* Switch: '<S24>/Switch1' */
  if (SimpleFOC_B.AND) {
    /* Switch: '<S24>/Switch1' incorporates:
     *  Constant: '<S24>/Constant1'
     */
    SimpleFOC_B.Switch1 = SimpleFOC_P.Constant1_Value;
  } else {
    /* Switch: '<S24>/Switch1' incorporates:
     *  Constant: '<S24>/Constant3'
     */
    SimpleFOC_B.Switch1 = SimpleFOC_P.Constant3_Value_l;
  }

  /* End of Switch: '<S24>/Switch1' */

  /* RelationalOperator: '<S30>/Compare' incorporates:
   *  Constant: '<S30>/Constant'
   */
  SimpleFOC_B.Compare_p = (SimpleFOC_B.Mod_i >
    SimpleFOC_P.CompareToConstant3_const);

  /* RelationalOperator: '<S31>/Compare' incorporates:
   *  Constant: '<S31>/Constant'
   */
  SimpleFOC_B.Compare_c = (SimpleFOC_B.Mod_i <=
    SimpleFOC_P.CompareToConstant6_const);

  /* Logic: '<S24>/AND1' */
  SimpleFOC_B.AND1 = (SimpleFOC_B.Compare_p && SimpleFOC_B.Compare_c);

  /* Switch: '<S24>/Switch2' */
  if (SimpleFOC_B.AND1) {
    /* Gain: '<S24>/Gain1' */
    SimpleFOC_B.Gain1_k = SimpleFOC_P.Gain1_Gain * SimpleFOC_B.Mod_i;

    /* Bias: '<S24>/Bias' */
    SimpleFOC_B.Bias_k = SimpleFOC_B.Gain1_k + SimpleFOC_P.Bias_Bias;

    /* Switch: '<S24>/Switch2' */
    SimpleFOC_B.Switch2 = SimpleFOC_B.Bias_k;
  } else {
    /* Switch: '<S24>/Switch2' incorporates:
     *  Constant: '<S24>/Constant2'
     */
    SimpleFOC_B.Switch2 = SimpleFOC_P.Constant2_Value_i;
  }

  /* End of Switch: '<S24>/Switch2' */

  /* RelationalOperator: '<S32>/Compare' incorporates:
   *  Constant: '<S32>/Constant'
   */
  SimpleFOC_B.Compare_m = (SimpleFOC_B.Mod_i >
    SimpleFOC_P.CompareToConstant7_const);

  /* RelationalOperator: '<S33>/Compare' incorporates:
   *  Constant: '<S33>/Constant'
   */
  SimpleFOC_B.Compare_h = (SimpleFOC_B.Mod_i <=
    SimpleFOC_P.CompareToConstant8_const);

  /* Logic: '<S24>/AND3' */
  SimpleFOC_B.AND3 = (SimpleFOC_B.Compare_m && SimpleFOC_B.Compare_h);

  /* Switch: '<S24>/Switch3' */
  if (SimpleFOC_B.AND3) {
    /* Switch: '<S24>/Switch3' incorporates:
     *  Constant: '<S24>/Constant4'
     */
    SimpleFOC_B.Switch3 = SimpleFOC_P.Constant4_Value;
  } else {
    /* Switch: '<S24>/Switch3' incorporates:
     *  Constant: '<S24>/Constant5'
     */
    SimpleFOC_B.Switch3 = SimpleFOC_P.Constant5_Value;
  }

  /* End of Switch: '<S24>/Switch3' */

  /* RelationalOperator: '<S34>/Compare' incorporates:
   *  Constant: '<S34>/Constant'
   */
  SimpleFOC_B.Compare_h4 = (SimpleFOC_B.Mod_i >
    SimpleFOC_P.CompareToConstant9_const);

  /* Switch: '<S24>/Switch4' */
  if (SimpleFOC_B.Compare_h4) {
    /* Gain: '<S24>/Gain2' */
    SimpleFOC_B.Gain2_ng = SimpleFOC_P.Gain2_Gain * SimpleFOC_B.Mod_i;

    /* Bias: '<S24>/Bias2' */
    SimpleFOC_B.Bias2_b = SimpleFOC_B.Gain2_ng + SimpleFOC_P.Bias2_Bias;

    /* Switch: '<S24>/Switch4' */
    SimpleFOC_B.Switch4 = SimpleFOC_B.Bias2_b;
  } else {
    /* Switch: '<S24>/Switch4' incorporates:
     *  Constant: '<S24>/Constant6'
     */
    SimpleFOC_B.Switch4 = SimpleFOC_P.Constant6_Value;
  }

  /* End of Switch: '<S24>/Switch4' */

  /* Sum: '<S24>/Add' */
  SimpleFOC_B.Add = (((SimpleFOC_B.Switch + SimpleFOC_B.Switch1) +
                      SimpleFOC_B.Switch2) + SimpleFOC_B.Switch3) +
    SimpleFOC_B.Switch4;

  /* Bias: '<S25>/Bias3' */
  SimpleFOC_B.Bias3_c = SimpleFOC_B.Mod + SimpleFOC_P.Bias3_Bias_g;

  /* Math: '<S25>/Mod' incorporates:
   *  Constant: '<S25>/Constant7'
   */
  SimpleFOC_B.Mod_f = rt_modd_snf(SimpleFOC_B.Bias3_c,
    SimpleFOC_P.Constant7_Value_n);

  /* RelationalOperator: '<S35>/Compare' incorporates:
   *  Constant: '<S35>/Constant'
   */
  SimpleFOC_B.Compare_cg = (SimpleFOC_B.Mod_f <=
    SimpleFOC_P.CompareToConstant_const_f);

  /* Switch: '<S25>/Switch' */
  if (SimpleFOC_B.Compare_cg) {
    /* Gain: '<S25>/Gain' */
    SimpleFOC_B.Gain_h = SimpleFOC_P.Gain_Gain_c * SimpleFOC_B.Mod_f;

    /* Bias: '<S25>/Bias1' */
    SimpleFOC_B.Bias1_p = SimpleFOC_B.Gain_h + SimpleFOC_P.Bias1_Bias_a;

    /* Switch: '<S25>/Switch' */
    SimpleFOC_B.Switch_d = SimpleFOC_B.Bias1_p;
  } else {
    /* Switch: '<S25>/Switch' incorporates:
     *  Constant: '<S25>/Constant8'
     */
    SimpleFOC_B.Switch_d = SimpleFOC_P.Constant8_Value_h;
  }

  /* End of Switch: '<S25>/Switch' */

  /* RelationalOperator: '<S36>/Compare' incorporates:
   *  Constant: '<S36>/Constant'
   */
  SimpleFOC_B.Compare_i = (SimpleFOC_B.Mod_f >
    SimpleFOC_P.CompareToConstant1_const_l);

  /* RelationalOperator: '<S37>/Compare' incorporates:
   *  Constant: '<S37>/Constant'
   */
  SimpleFOC_B.Compare_nw = (SimpleFOC_B.Mod_f <=
    SimpleFOC_P.CompareToConstant2_const_f);

  /* Logic: '<S25>/AND' */
  SimpleFOC_B.AND_n = (SimpleFOC_B.Compare_i && SimpleFOC_B.Compare_nw);

  /* Switch: '<S25>/Switch1' */
  if (SimpleFOC_B.AND_n) {
    /* Switch: '<S25>/Switch1' incorporates:
     *  Constant: '<S25>/Constant1'
     */
    SimpleFOC_B.Switch1_k = SimpleFOC_P.Constant1_Value_d;
  } else {
    /* Switch: '<S25>/Switch1' incorporates:
     *  Constant: '<S25>/Constant3'
     */
    SimpleFOC_B.Switch1_k = SimpleFOC_P.Constant3_Value_l3;
  }

  /* End of Switch: '<S25>/Switch1' */

  /* RelationalOperator: '<S38>/Compare' incorporates:
   *  Constant: '<S38>/Constant'
   */
  SimpleFOC_B.Compare_hx = (SimpleFOC_B.Mod_f >
    SimpleFOC_P.CompareToConstant3_const_b);

  /* RelationalOperator: '<S39>/Compare' incorporates:
   *  Constant: '<S39>/Constant'
   */
  SimpleFOC_B.Compare_cy = (SimpleFOC_B.Mod_f <=
    SimpleFOC_P.CompareToConstant6_const_k);

  /* Logic: '<S25>/AND1' */
  SimpleFOC_B.AND1_j = (SimpleFOC_B.Compare_hx && SimpleFOC_B.Compare_cy);

  /* Switch: '<S25>/Switch2' */
  if (SimpleFOC_B.AND1_j) {
    /* Gain: '<S25>/Gain1' */
    SimpleFOC_B.Gain1_l = SimpleFOC_P.Gain1_Gain_l * SimpleFOC_B.Mod_f;

    /* Bias: '<S25>/Bias' */
    SimpleFOC_B.Bias_o = SimpleFOC_B.Gain1_l + SimpleFOC_P.Bias_Bias_a;

    /* Switch: '<S25>/Switch2' */
    SimpleFOC_B.Switch2_j = SimpleFOC_B.Bias_o;
  } else {
    /* Switch: '<S25>/Switch2' incorporates:
     *  Constant: '<S25>/Constant2'
     */
    SimpleFOC_B.Switch2_j = SimpleFOC_P.Constant2_Value_l;
  }

  /* End of Switch: '<S25>/Switch2' */

  /* RelationalOperator: '<S40>/Compare' incorporates:
   *  Constant: '<S40>/Constant'
   */
  SimpleFOC_B.Compare_l = (SimpleFOC_B.Mod_f >
    SimpleFOC_P.CompareToConstant7_const_o);

  /* RelationalOperator: '<S41>/Compare' incorporates:
   *  Constant: '<S41>/Constant'
   */
  SimpleFOC_B.Compare_b = (SimpleFOC_B.Mod_f <=
    SimpleFOC_P.CompareToConstant8_const_l);

  /* Logic: '<S25>/AND3' */
  SimpleFOC_B.AND3_p = (SimpleFOC_B.Compare_l && SimpleFOC_B.Compare_b);

  /* Switch: '<S25>/Switch3' */
  if (SimpleFOC_B.AND3_p) {
    /* Switch: '<S25>/Switch3' incorporates:
     *  Constant: '<S25>/Constant4'
     */
    SimpleFOC_B.Switch3_j = SimpleFOC_P.Constant4_Value_k;
  } else {
    /* Switch: '<S25>/Switch3' incorporates:
     *  Constant: '<S25>/Constant5'
     */
    SimpleFOC_B.Switch3_j = SimpleFOC_P.Constant5_Value_a;
  }

  /* End of Switch: '<S25>/Switch3' */

  /* RelationalOperator: '<S42>/Compare' incorporates:
   *  Constant: '<S42>/Constant'
   */
  SimpleFOC_B.Compare_hm = (SimpleFOC_B.Mod_f >
    SimpleFOC_P.CompareToConstant9_const_c);

  /* Switch: '<S25>/Switch4' */
  if (SimpleFOC_B.Compare_hm) {
    /* Gain: '<S25>/Gain2' */
    SimpleFOC_B.Gain2_e = SimpleFOC_P.Gain2_Gain_b * SimpleFOC_B.Mod_f;

    /* Bias: '<S25>/Bias2' */
    SimpleFOC_B.Bias2_k = SimpleFOC_B.Gain2_e + SimpleFOC_P.Bias2_Bias_j;

    /* Switch: '<S25>/Switch4' */
    SimpleFOC_B.Switch4_g = SimpleFOC_B.Bias2_k;
  } else {
    /* Switch: '<S25>/Switch4' incorporates:
     *  Constant: '<S25>/Constant6'
     */
    SimpleFOC_B.Switch4_g = SimpleFOC_P.Constant6_Value_h;
  }

  /* End of Switch: '<S25>/Switch4' */

  /* Sum: '<S25>/Add' */
  SimpleFOC_B.Add_h = (((SimpleFOC_B.Switch_d + SimpleFOC_B.Switch1_k) +
                        SimpleFOC_B.Switch2_j) + SimpleFOC_B.Switch3_j) +
    SimpleFOC_B.Switch4_g;

  /* Bias: '<S26>/Bias3' */
  SimpleFOC_B.Bias3_n = SimpleFOC_B.Mod + SimpleFOC_P.Bias3_Bias_f;

  /* Math: '<S26>/Mod' incorporates:
   *  Constant: '<S26>/Constant7'
   */
  SimpleFOC_B.Mod_a = rt_modd_snf(SimpleFOC_B.Bias3_n,
    SimpleFOC_P.Constant7_Value_k);

  /* RelationalOperator: '<S43>/Compare' incorporates:
   *  Constant: '<S43>/Constant'
   */
  SimpleFOC_B.Compare_mi = (SimpleFOC_B.Mod_a <=
    SimpleFOC_P.CompareToConstant_const_b);

  /* Switch: '<S26>/Switch' */
  if (SimpleFOC_B.Compare_mi) {
    /* Gain: '<S26>/Gain' */
    SimpleFOC_B.Gain_g = SimpleFOC_P.Gain_Gain_o * SimpleFOC_B.Mod_a;

    /* Bias: '<S26>/Bias1' */
    SimpleFOC_B.Bias1 = SimpleFOC_B.Gain_g + SimpleFOC_P.Bias1_Bias_h;

    /* Switch: '<S26>/Switch' */
    SimpleFOC_B.Switch_g = SimpleFOC_B.Bias1;
  } else {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S26>/Constant8'
     */
    SimpleFOC_B.Switch_g = SimpleFOC_P.Constant8_Value_g;
  }

  /* End of Switch: '<S26>/Switch' */

  /* RelationalOperator: '<S44>/Compare' incorporates:
   *  Constant: '<S44>/Constant'
   */
  SimpleFOC_B.Compare_he = (SimpleFOC_B.Mod_a >
    SimpleFOC_P.CompareToConstant1_const_lf);

  /* RelationalOperator: '<S45>/Compare' incorporates:
   *  Constant: '<S45>/Constant'
   */
  SimpleFOC_B.Compare_hr = (SimpleFOC_B.Mod_a <=
    SimpleFOC_P.CompareToConstant2_const_c);

  /* Logic: '<S26>/AND' */
  SimpleFOC_B.AND_nc = (SimpleFOC_B.Compare_he && SimpleFOC_B.Compare_hr);

  /* Switch: '<S26>/Switch1' */
  if (SimpleFOC_B.AND_nc) {
    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant1'
     */
    SimpleFOC_B.Switch1_j = SimpleFOC_P.Constant1_Value_j;
  } else {
    /* Switch: '<S26>/Switch1' incorporates:
     *  Constant: '<S26>/Constant3'
     */
    SimpleFOC_B.Switch1_j = SimpleFOC_P.Constant3_Value_o;
  }

  /* End of Switch: '<S26>/Switch1' */

  /* RelationalOperator: '<S46>/Compare' incorporates:
   *  Constant: '<S46>/Constant'
   */
  SimpleFOC_B.Compare_g = (SimpleFOC_B.Mod_a >
    SimpleFOC_P.CompareToConstant3_const_k);

  /* RelationalOperator: '<S47>/Compare' incorporates:
   *  Constant: '<S47>/Constant'
   */
  SimpleFOC_B.Compare_pv = (SimpleFOC_B.Mod_a <=
    SimpleFOC_P.CompareToConstant6_const_f);

  /* Logic: '<S26>/AND1' */
  SimpleFOC_B.AND1_i = (SimpleFOC_B.Compare_g && SimpleFOC_B.Compare_pv);

  /* Switch: '<S26>/Switch2' */
  if (SimpleFOC_B.AND1_i) {
    /* Gain: '<S26>/Gain1' */
    SimpleFOC_B.Gain1_e = SimpleFOC_P.Gain1_Gain_f * SimpleFOC_B.Mod_a;

    /* Bias: '<S26>/Bias' */
    SimpleFOC_B.Bias = SimpleFOC_B.Gain1_e + SimpleFOC_P.Bias_Bias_h;

    /* Switch: '<S26>/Switch2' */
    SimpleFOC_B.Switch2_g = SimpleFOC_B.Bias;
  } else {
    /* Switch: '<S26>/Switch2' incorporates:
     *  Constant: '<S26>/Constant2'
     */
    SimpleFOC_B.Switch2_g = SimpleFOC_P.Constant2_Value_c;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* RelationalOperator: '<S48>/Compare' incorporates:
   *  Constant: '<S48>/Constant'
   */
  SimpleFOC_B.Compare_bo = (SimpleFOC_B.Mod_a >
    SimpleFOC_P.CompareToConstant7_const_b);

  /* RelationalOperator: '<S49>/Compare' incorporates:
   *  Constant: '<S49>/Constant'
   */
  SimpleFOC_B.Compare_ka = (SimpleFOC_B.Mod_a <=
    SimpleFOC_P.CompareToConstant8_const_b);

  /* Logic: '<S26>/AND3' */
  SimpleFOC_B.AND3_a = (SimpleFOC_B.Compare_bo && SimpleFOC_B.Compare_ka);

  /* Switch: '<S26>/Switch3' */
  if (SimpleFOC_B.AND3_a) {
    /* Switch: '<S26>/Switch3' incorporates:
     *  Constant: '<S26>/Constant4'
     */
    SimpleFOC_B.Switch3_k = SimpleFOC_P.Constant4_Value_l;
  } else {
    /* Switch: '<S26>/Switch3' incorporates:
     *  Constant: '<S26>/Constant5'
     */
    SimpleFOC_B.Switch3_k = SimpleFOC_P.Constant5_Value_ay;
  }

  /* End of Switch: '<S26>/Switch3' */

  /* RelationalOperator: '<S50>/Compare' incorporates:
   *  Constant: '<S50>/Constant'
   */
  SimpleFOC_B.Compare_f = (SimpleFOC_B.Mod_a >
    SimpleFOC_P.CompareToConstant9_const_g);

  /* Switch: '<S26>/Switch4' */
  if (SimpleFOC_B.Compare_f) {
    /* Gain: '<S26>/Gain2' */
    SimpleFOC_B.Gain2_n = SimpleFOC_P.Gain2_Gain_p * SimpleFOC_B.Mod_a;

    /* Bias: '<S26>/Bias2' */
    SimpleFOC_B.Bias2 = SimpleFOC_B.Gain2_n + SimpleFOC_P.Bias2_Bias_c;

    /* Switch: '<S26>/Switch4' */
    SimpleFOC_B.Switch4_h = SimpleFOC_B.Bias2;
  } else {
    /* Switch: '<S26>/Switch4' incorporates:
     *  Constant: '<S26>/Constant6'
     */
    SimpleFOC_B.Switch4_h = SimpleFOC_P.Constant6_Value_b;
  }

  /* End of Switch: '<S26>/Switch4' */

  /* Sum: '<S26>/Add' */
  SimpleFOC_B.Add_l = (((SimpleFOC_B.Switch_g + SimpleFOC_B.Switch1_j) +
                        SimpleFOC_B.Switch2_g) + SimpleFOC_B.Switch3_k) +
    SimpleFOC_B.Switch4_h;

  /* Gain: '<S11>/Max_Lampda_PM_rate' */
  cosOut = 2.0 * SimpleFOC_P.BLDC_Lambda / 2.617993877991494;

  /* Gain: '<S11>/Max_Lampda_PM_rate' */
  SimpleFOC_B.Max_Lampda_PM_rate[0] = cosOut * SimpleFOC_B.Add;
  SimpleFOC_B.Max_Lampda_PM_rate[1] = cosOut * SimpleFOC_B.Add_h;
  SimpleFOC_B.Max_Lampda_PM_rate[2] = cosOut * SimpleFOC_B.Add_l;

  /* Product: '<S4>/Product2' */
  SimpleFOC_B.Product2[0] = SimpleFOC_B.MatrixMultiply2[0] *
    SimpleFOC_B.Max_Lampda_PM_rate[0];
  SimpleFOC_B.Product2[1] = SimpleFOC_B.MatrixMultiply2[1] *
    SimpleFOC_B.Max_Lampda_PM_rate[1];
  SimpleFOC_B.Product2[2] = SimpleFOC_B.MatrixMultiply2[2] *
    SimpleFOC_B.Max_Lampda_PM_rate[2];

  /* Sum: '<S4>/Sum of Elements' */
  cosOut = SimpleFOC_B.Product2[0];
  cosOut += SimpleFOC_B.Product2[1];
  cosOut += SimpleFOC_B.Product2[2];

  /* Sum: '<S4>/Sum of Elements' */
  SimpleFOC_B.SumofElements = cosOut;

  /* Gain: '<S4>/Gain1' */
  SimpleFOC_B.Gain1 = SimpleFOC_P.BLDC_p * SimpleFOC_B.SumofElements;

  /* Product: '<S4>/Product' */
  SimpleFOC_B.Product = SimpleFOC_B.Integrator_d * SimpleFOC_B.Integrator_a;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Sum: '<S4>/Subtract2' incorporates:
     *  Constant: '<S4>/Ld'
     *  Constant: '<S4>/Lq'
     */
    SimpleFOC_B.Subtract2 = SimpleFOC_P.BLDC_Ld - SimpleFOC_P.BLDC_Lq;
  }

  /* Product: '<S4>/Product1' */
  SimpleFOC_B.Product1 = SimpleFOC_B.Product * SimpleFOC_B.Subtract2;

  /* Gain: '<S4>/Gain3' */
  cosOut = 3.0 * SimpleFOC_P.BLDC_p / 2.0;

  /* Gain: '<S4>/Gain3' */
  SimpleFOC_B.Gain3 = cosOut * SimpleFOC_B.Product1;

  /* Sum: '<S4>/Add' */
  SimpleFOC_B.Add_i = SimpleFOC_B.Gain1 + SimpleFOC_B.Gain3;

  /* Trigonometry: '<S6>/SinCos' */
  cosOut = cosOut_tmp;

  /* Trigonometry: '<S6>/SinCos' */
  SimpleFOC_B.SinCos_o1_p = Bias;

  /* Trigonometry: '<S6>/SinCos' */
  SimpleFOC_B.SinCos_o2_j = cosOut;

  /* Gain: '<S6>/Gain' */
  SimpleFOC_B.Gain = SimpleFOC_P.Gain_Gain_pp * SimpleFOC_B.SinCos_o1_p;

  /* SignalConversion generated from: '<S6>/Matrix Concatenate1' incorporates:
   *  Concatenate: '<S6>/Matrix Concatenate1'
   *  Constant: '<S6>/Constant2'
   */
  SimpleFOC_B.MatrixConcatenate1_h[0] = SimpleFOC_B.SinCos_o2_j;
  SimpleFOC_B.MatrixConcatenate1_h[1] = SimpleFOC_B.Gain;
  SimpleFOC_B.MatrixConcatenate1_h[2] = SimpleFOC_P.Constant2_Value_h;

  /* SignalConversion generated from: '<S6>/MatrixMultiply' */
  SimpleFOC_B.TmpSignalConversionAtMatrixMu_a[0] = SimpleFOC_B.SinCos_o1_p;
  SimpleFOC_B.TmpSignalConversionAtMatrixMu_a[1] = SimpleFOC_B.SinCos_o2_j;

  /* Product: '<S6>/MatrixMultiply' incorporates:
   *  Constant: '<S6>/Minus120'
   */
  cosOut = SimpleFOC_P.Minus120_Value_i[0];
  tmp_3 = SimpleFOC_P.Minus120_Value_i[1];
  tmp_1 = SimpleFOC_P.Minus120_Value_i[2];
  tmp_4 = SimpleFOC_P.Minus120_Value_i[3];
  tmp_0 = SimpleFOC_B.TmpSignalConversionAtMatrixMu_a[0];
  tmp_2 = SimpleFOC_B.TmpSignalConversionAtMatrixMu_a[1];
  tmp = cosOut * tmp_0;
  tmp += tmp_1 * tmp_2;

  /* Product: '<S6>/MatrixMultiply' */
  SimpleFOC_B.MatrixMultiply_c[0] = tmp;

  /* Product: '<S6>/MatrixMultiply' */
  tmp = tmp_3 * tmp_0;
  tmp += tmp_4 * tmp_2;

  /* Product: '<S6>/MatrixMultiply' */
  SimpleFOC_B.MatrixMultiply_c[1] = tmp;

  /* Gain: '<S6>/Gain2' */
  SimpleFOC_B.Gain2 = SimpleFOC_P.Gain2_Gain_bt * SimpleFOC_B.MatrixMultiply_c[0];

  /* SignalConversion generated from: '<S6>/Matrix Concatenate1' incorporates:
   *  Concatenate: '<S6>/Matrix Concatenate1'
   *  Constant: '<S6>/Constant2'
   */
  SimpleFOC_B.MatrixConcatenate1_h[3] = SimpleFOC_B.MatrixMultiply_c[1];
  SimpleFOC_B.MatrixConcatenate1_h[4] = SimpleFOC_B.Gain2;
  SimpleFOC_B.MatrixConcatenate1_h[5] = SimpleFOC_P.Constant2_Value_h;

  /* Product: '<S6>/MatrixMultiply1' incorporates:
   *  Constant: '<S6>/Plus120'
   */
  cosOut = SimpleFOC_P.Plus120_Value_j[0];
  tmp_3 = SimpleFOC_P.Plus120_Value_j[1];
  tmp_1 = SimpleFOC_P.Plus120_Value_j[2];
  tmp_4 = SimpleFOC_P.Plus120_Value_j[3];
  tmp_0 = SimpleFOC_B.TmpSignalConversionAtMatrixMu_a[0];
  tmp_2 = SimpleFOC_B.TmpSignalConversionAtMatrixMu_a[1];
  tmp = cosOut * tmp_0;
  tmp += tmp_1 * tmp_2;

  /* Product: '<S6>/MatrixMultiply1' */
  SimpleFOC_B.MatrixMultiply1_c[0] = tmp;

  /* Product: '<S6>/MatrixMultiply1' */
  tmp = tmp_3 * tmp_0;
  tmp += tmp_4 * tmp_2;

  /* Product: '<S6>/MatrixMultiply1' */
  SimpleFOC_B.MatrixMultiply1_c[1] = tmp;

  /* Gain: '<S6>/Gain3' */
  SimpleFOC_B.Gain3_m = SimpleFOC_P.Gain3_Gain * SimpleFOC_B.MatrixMultiply1_c[0];

  /* SignalConversion generated from: '<S6>/Matrix Concatenate1' incorporates:
   *  Concatenate: '<S6>/Matrix Concatenate1'
   *  Constant: '<S6>/Constant2'
   */
  SimpleFOC_B.MatrixConcatenate1_h[6] = SimpleFOC_B.MatrixMultiply1_c[1];
  SimpleFOC_B.MatrixConcatenate1_h[7] = SimpleFOC_B.Gain3_m;
  SimpleFOC_B.MatrixConcatenate1_h[8] = SimpleFOC_P.Constant2_Value_h;
  for (i = 0; i < 9; i++) {
    /* Gain: '<S6>/Gain1' incorporates:
     *  Concatenate: '<S6>/Matrix Concatenate1'
     */
    SimpleFOC_B.Gain1_i[i] = SimpleFOC_P.Gain1_Gain_o *
      SimpleFOC_B.MatrixConcatenate1_h[i];
  }

  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Switch: '<S64>/Switch1' incorporates:
     *  Constant: '<S64>/enableInportSatMethod'
     */
    if (SimpleFOC_P.enableInportSatMethod_Value != 0) {
      /* Switch: '<S64>/Switch1' incorporates:
       *  Constant: '<S52>/ReplaceInport_satMethod'
       */
      SimpleFOC_B.Switch1_o = SimpleFOC_P.ReplaceInport_satMethod_Value;
    } else {
      /* Switch: '<S64>/Switch1' incorporates:
       *  Constant: '<S64>/ChosenMethod'
       */
      SimpleFOC_B.Switch1_o = SimpleFOC_P.ChosenMethod_Value;
    }

    /* End of Switch: '<S64>/Switch1' */

    /* Constant: '<S2>/Constant1' */
    SimpleFOC_B.SPQC = SimpleFOC_P.Constant1_Value_c;

    /* UnitDelay generated from: '<Root>/Unit Delay' */
    SimpleFOC_B.IaStator = SimpleFOC_DW.UnitDelay_1_DSTATE;

    /* UnitDelay generated from: '<Root>/Unit Delay' */
    SimpleFOC_B.IbStator = SimpleFOC_DW.UnitDelay_2_DSTATE;

    /* Outputs for Atomic SubSystem: '<S2>/Clarke Transform' */
    /* Sum: '<S51>/a_plus_2b' */
    SimpleFOC_B.a_plus_2b = (SimpleFOC_B.IaStator + SimpleFOC_B.IbStator) +
      SimpleFOC_B.IbStator;

    /* Gain: '<S51>/one_by_sqrt3' */
    SimpleFOC_B.one_by_sqrt3 = SimpleFOC_P.one_by_sqrt3_Gain *
      SimpleFOC_B.a_plus_2b;

    /* AlgorithmDescriptorDelegate generated from: '<S51>/a16' */
    SimpleFOC_B.algDD_o1_e = SimpleFOC_B.IaStator;

    /* AlgorithmDescriptorDelegate generated from: '<S51>/a16' */
    SimpleFOC_B.algDD_o2_h = SimpleFOC_B.one_by_sqrt3;

    /* End of Outputs for SubSystem: '<S2>/Clarke Transform' */

    /* UnitDelay generated from: '<Root>/Unit Delay' */
    SimpleFOC_B.MtrPos = SimpleFOC_DW.UnitDelay_9_DSTATE;

    /* Gain: '<S181>/convert_pu' */
    SimpleFOC_B.convert_pu = SimpleFOC_P.convert_pu_Gain * SimpleFOC_B.MtrPos;

    /* RelationalOperator: '<S182>/Compare' incorporates:
     *  Constant: '<S182>/Constant'
     */
    SimpleFOC_B.Compare_pg = (SimpleFOC_B.convert_pu <
      SimpleFOC_P.Constant_Value_h);

    /* DataTypeConversion: '<S181>/Data Type Conversion' */
    SimpleFOC_B.DataTypeConversion = SimpleFOC_B.Compare_pg;
  }

  /* If: '<S181>/If' */
  if (rtsiIsModeUpdateTimeStep(&SimpleFOC_M->solverInfo)) {
    rtAction = (int8_T)(SimpleFOC_B.DataTypeConversion <= 0);
    SimpleFOC_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = SimpleFOC_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S181>/If Action Subsystem' incorporates:
     *  ActionPort: '<S183>/Action Port'
     */
    /* DataTypeConversion: '<S183>/Convert_uint16' */
    tmp = floor(SimpleFOC_B.convert_pu);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    /* DataTypeConversion: '<S183>/Convert_uint16' */
    SimpleFOC_B.Convert_uint16_n = (int16_T)(tmp < 0.0 ? (int32_T)(int16_T)
      -(int16_T)(uint16_T)-tmp : (int32_T)(int16_T)(uint16_T)tmp);

    /* DataTypeConversion: '<S183>/Convert_back' */
    SimpleFOC_B.Convert_back_k = SimpleFOC_B.Convert_uint16_n;

    /* Merge: '<S181>/Merge' incorporates:
     *  Sum: '<S183>/Sum'
     */
    SimpleFOC_B.Merge = SimpleFOC_B.convert_pu - SimpleFOC_B.Convert_back_k;

    /* End of Outputs for SubSystem: '<S181>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S181>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S184>/Action Port'
     */
    /* DataTypeConversion: '<S184>/Convert_uint16' */
    tmp = trunc(SimpleFOC_B.convert_pu);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    /* DataTypeConversion: '<S184>/Convert_uint16' */
    SimpleFOC_B.Convert_uint16 = (int16_T)(tmp < 0.0 ? (int32_T)(int16_T)
      -(int16_T)(uint16_T)-tmp : (int32_T)(int16_T)(uint16_T)tmp);

    /* DataTypeConversion: '<S184>/Convert_back' */
    SimpleFOC_B.Convert_back = SimpleFOC_B.Convert_uint16;

    /* Merge: '<S181>/Merge' incorporates:
     *  Sum: '<S184>/Sum'
     */
    SimpleFOC_B.Merge = SimpleFOC_B.convert_pu - SimpleFOC_B.Convert_back;

    /* End of Outputs for SubSystem: '<S181>/If Action Subsystem1' */
  }

  /* End of If: '<S181>/If' */

  /* Gain: '<S61>/indexing' */
  SimpleFOC_B.indexing = SimpleFOC_P.indexing_Gain * SimpleFOC_B.Merge;

  /* DataTypeConversion: '<S61>/Get_Integer' */
  tmp = trunc(SimpleFOC_B.indexing);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  /* DataTypeConversion: '<S61>/Get_Integer' */
  SimpleFOC_B.Get_Integer = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Sum: '<S61>/Sum' incorporates:
     *  Constant: '<S61>/offset'
     */
    Sum_l = (uint32_T)SimpleFOC_P.offset_Value[0] + SimpleFOC_B.Get_Integer;
    SimpleFOC_B.Sum_l[0] = Sum_l;

    /* Selector: '<S61>/Lookup' incorporates:
     *  Constant: '<S61>/sine_table_values'
     */
    SimpleFOC_B.Lookup[0] = SimpleFOC_P.sine_table_values_Value[(int32_T)Sum_l];

    /* Sum: '<S61>/Sum' incorporates:
     *  Constant: '<S61>/offset'
     */
    Sum_l = (uint32_T)SimpleFOC_P.offset_Value[1] + SimpleFOC_B.Get_Integer;
    SimpleFOC_B.Sum_l[1] = Sum_l;

    /* Selector: '<S61>/Lookup' incorporates:
     *  Constant: '<S61>/sine_table_values'
     */
    SimpleFOC_B.Lookup[1] = SimpleFOC_P.sine_table_values_Value[(int32_T)Sum_l];

    /* Sum: '<S61>/Sum' incorporates:
     *  Constant: '<S61>/offset'
     */
    Sum_l = (uint32_T)SimpleFOC_P.offset_Value[2] + SimpleFOC_B.Get_Integer;
    SimpleFOC_B.Sum_l[2] = Sum_l;

    /* Selector: '<S61>/Lookup' incorporates:
     *  Constant: '<S61>/sine_table_values'
     */
    SimpleFOC_B.Lookup[2] = SimpleFOC_P.sine_table_values_Value[(int32_T)Sum_l];

    /* Sum: '<S61>/Sum' incorporates:
     *  Constant: '<S61>/offset'
     */
    Sum_l = (uint32_T)SimpleFOC_P.offset_Value[3] + SimpleFOC_B.Get_Integer;
    SimpleFOC_B.Sum_l[3] = Sum_l;

    /* Selector: '<S61>/Lookup' incorporates:
     *  Constant: '<S61>/sine_table_values'
     */
    SimpleFOC_B.Lookup[3] = SimpleFOC_P.sine_table_values_Value[(int32_T)Sum_l];

    /* Sum: '<S180>/Sum3' */
    SimpleFOC_B.Sum3 = SimpleFOC_B.Lookup[0] - SimpleFOC_B.Lookup[1];
  }

  /* DataTypeConversion: '<S61>/Data Type Conversion1' */
  SimpleFOC_B.DataTypeConversion1 = SimpleFOC_B.Get_Integer;

  /* Sum: '<S61>/Sum2' */
  SimpleFOC_B.Sum2 = SimpleFOC_B.indexing - SimpleFOC_B.DataTypeConversion1;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Product: '<S180>/Product' */
    SimpleFOC_B.Product_d = SimpleFOC_B.Sum3 * SimpleFOC_B.Sum2;

    /* Sum: '<S180>/Sum4' */
    SimpleFOC_B.Sum4 = SimpleFOC_B.Product_d + SimpleFOC_B.Lookup[1];

    /* Sum: '<S180>/Sum5' */
    SimpleFOC_B.Sum5 = SimpleFOC_B.Lookup[2] - SimpleFOC_B.Lookup[3];

    /* Product: '<S180>/Product1' */
    SimpleFOC_B.Product1_i = SimpleFOC_B.Sum5 * SimpleFOC_B.Sum2;

    /* Sum: '<S180>/Sum6' */
    SimpleFOC_B.Sum6 = SimpleFOC_B.Product1_i + SimpleFOC_B.Lookup[3];

    /* Outputs for Atomic SubSystem: '<S2>/Park Transform' */
    /* Product: '<S60>/bcos' */
    SimpleFOC_B.bcos = SimpleFOC_B.algDD_o2_h * SimpleFOC_B.Sum6;

    /* Product: '<S60>/asin' */
    SimpleFOC_B.asin_d = SimpleFOC_B.algDD_o1_e * SimpleFOC_B.Sum4;

    /* Sum: '<S60>/sum_Qs' */
    SimpleFOC_B.sum_Qs = SimpleFOC_B.bcos - SimpleFOC_B.asin_d;

    /* Product: '<S60>/acos' */
    SimpleFOC_B.acos_f = SimpleFOC_B.algDD_o1_e * SimpleFOC_B.Sum6;

    /* Product: '<S60>/bsin' */
    SimpleFOC_B.bsin = SimpleFOC_B.algDD_o2_h * SimpleFOC_B.Sum4;

    /* Sum: '<S60>/sum_Ds' */
    SimpleFOC_B.sum_Ds = SimpleFOC_B.acos_f + SimpleFOC_B.bsin;

    /* Switch: '<S179>/Switch' incorporates:
     *  Constant: '<S179>/Offset'
     */
    if (SimpleFOC_P.Offset_Value_h > SimpleFOC_P.Switch_Threshold_b) {
      /* UnaryMinus: '<S179>/Unary_Minus' */
      SimpleFOC_B.Unary_Minus = -SimpleFOC_B.sum_Qs;

      /* Switch: '<S179>/Switch' */
      SimpleFOC_B.Switch_a[0] = SimpleFOC_B.Unary_Minus;
      SimpleFOC_B.Switch_a[1] = SimpleFOC_B.sum_Ds;
    } else {
      /* Switch: '<S179>/Switch' */
      SimpleFOC_B.Switch_a[0] = SimpleFOC_B.sum_Ds;
      SimpleFOC_B.Switch_a[1] = SimpleFOC_B.sum_Qs;
    }

    /* End of Switch: '<S179>/Switch' */

    /* AlgorithmDescriptorDelegate generated from: '<S60>/a16' */
    SimpleFOC_B.algDD_o1 = SimpleFOC_B.Switch_a[0];

    /* AlgorithmDescriptorDelegate generated from: '<S60>/a16' */
    SimpleFOC_B.algDD_o2 = SimpleFOC_B.Switch_a[1];

    /* End of Outputs for SubSystem: '<S2>/Park Transform' */

    /* Sum: '<S2>/Sum2' */
    SimpleFOC_B.ErrorQC = SimpleFOC_B.SPQC - SimpleFOC_B.algDD_o2;

    /* Gain: '<S160>/Proportional Gain' */
    SimpleFOC_B.ProportionalGain = SimpleFOC_P.Kp_iq * SimpleFOC_B.ErrorQC;

    /* Constant: '<S2>/Constant' */
    SimpleFOC_B.SPDC = SimpleFOC_P.Constant_Value_j;

    /* Sum: '<S2>/Sum1' */
    SimpleFOC_B.ErrorDC = SimpleFOC_B.SPDC - SimpleFOC_B.algDD_o1;

    /* Gain: '<S112>/Proportional Gain' */
    SimpleFOC_B.ProportionalGain_j = SimpleFOC_P.Kp_id * SimpleFOC_B.ErrorDC;
  }

  /* Integrator: '<S155>/Integrator' */
  SimpleFOC_B.Integrator_l = SimpleFOC_X.Integrator_CSTATE_lo;

  /* Sum: '<S164>/Sum' */
  SimpleFOC_B.Sum = SimpleFOC_B.ProportionalGain + SimpleFOC_B.Integrator_l;

  /* Integrator: '<S107>/Integrator' */
  SimpleFOC_B.Integrator_g = SimpleFOC_X.Integrator_CSTATE_p;

  /* Sum: '<S116>/Sum' */
  SimpleFOC_B.Sum_d = SimpleFOC_B.ProportionalGain_j + SimpleFOC_B.Integrator_g;

  /* Product: '<S65>/Product' */
  SimpleFOC_B.Product_b = SimpleFOC_B.Sum_d * SimpleFOC_B.Sum_d;

  /* Product: '<S65>/Product1' */
  SimpleFOC_B.Product1_h = SimpleFOC_B.Sum * SimpleFOC_B.Sum;

  /* Sum: '<S65>/Sum1' */
  SimpleFOC_B.Sum1 = SimpleFOC_B.Product_b + SimpleFOC_B.Product1_h;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Switch: '<S64>/Switch' incorporates:
     *  Constant: '<S64>/enableInportSatLim'
     */
    if (SimpleFOC_P.enableInportSatLim_Value != 0) {
      /* Switch: '<S64>/Switch' incorporates:
       *  Constant: '<S52>/ReplaceInport_satLim'
       */
      SimpleFOC_B.Switch_i = SimpleFOC_P.ReplaceInport_satLim_Value;
    } else {
      /* Switch: '<S64>/Switch' incorporates:
       *  Constant: '<S64>/Constant3'
       */
      SimpleFOC_B.Switch_i = SimpleFOC_P.Constant3_Value;
    }

    /* End of Switch: '<S64>/Switch' */

    /* Product: '<S64>/Product' */
    SimpleFOC_B.Product_dk = SimpleFOC_B.Switch_i * SimpleFOC_B.Switch_i;

    /* If: '<S52>/If' */
    if (rtsiIsModeUpdateTimeStep(&SimpleFOC_M->solverInfo)) {
      rtAction = (int8_T)((SimpleFOC_B.Switch1_o != 1) && (SimpleFOC_B.Switch1_o
        != 2));
      SimpleFOC_DW.If_ActiveSubsystem_p = rtAction;
    } else {
      rtAction = SimpleFOC_DW.If_ActiveSubsystem_p;
    }

    if (rtAction == 0) {
      /* Outputs for IfAction SubSystem: '<S52>/D//Q Axis Priority' incorporates:
       *  ActionPort: '<S63>/Action Port'
       */
      /* RelationalOperator: '<S68>/Compare' incorporates:
       *  Constant: '<S68>/Constant'
       */
      SimpleFOC_B.Compare_o = (SimpleFOC_B.Switch1_o ==
        SimpleFOC_P.CompareToConstant_const_j);

      /* RelationalOperator: '<S69>/Compare' incorporates:
       *  Constant: '<S69>/Constant'
       */
      SimpleFOC_B.Compare_c0 = (SimpleFOC_B.Switch1_o ==
        SimpleFOC_P.CompareToConstant1_const_a);

      /* Switch: '<S63>/Switch' */
      if (SimpleFOC_B.Compare_o) {
        /* Switch: '<S63>/Switch' */
        SimpleFOC_B.Switch_az[0] = SimpleFOC_B.Sum_d;
        SimpleFOC_B.Switch_az[1] = SimpleFOC_B.Sum;
      } else {
        /* Switch: '<S63>/Switch' */
        SimpleFOC_B.Switch_az[0] = SimpleFOC_B.Sum;
        SimpleFOC_B.Switch_az[1] = SimpleFOC_B.Sum_d;
      }

      /* End of Switch: '<S63>/Switch' */

      /* RelationalOperator: '<S73>/LowerRelop1' */
      SimpleFOC_B.LowerRelop1 = (SimpleFOC_B.Switch_az[0] > SimpleFOC_B.Switch_i);

      /* Switch: '<S73>/Switch2' */
      if (SimpleFOC_B.LowerRelop1) {
        /* Switch: '<S73>/Switch2' */
        SimpleFOC_B.Switch2_h = SimpleFOC_B.Switch_i;
      } else {
        /* Gain: '<S72>/Gain' */
        SimpleFOC_B.Gain_e = SimpleFOC_P.Gain_Gain_k * SimpleFOC_B.Switch_i;

        /* RelationalOperator: '<S73>/UpperRelop' */
        SimpleFOC_B.UpperRelop = (SimpleFOC_B.Switch_az[0] < SimpleFOC_B.Gain_e);

        /* Switch: '<S73>/Switch' */
        if (SimpleFOC_B.UpperRelop) {
          /* Switch: '<S73>/Switch' */
          SimpleFOC_B.Switch_l = SimpleFOC_B.Gain_e;
        } else {
          /* Switch: '<S73>/Switch' */
          SimpleFOC_B.Switch_l = SimpleFOC_B.Switch_az[0];
        }

        /* End of Switch: '<S73>/Switch' */

        /* Switch: '<S73>/Switch2' */
        SimpleFOC_B.Switch2_h = SimpleFOC_B.Switch_l;
      }

      /* End of Switch: '<S73>/Switch2' */

      /* Product: '<S72>/Product' */
      SimpleFOC_B.Product_p = SimpleFOC_B.Switch2_h * SimpleFOC_B.Switch2_h;

      /* Sum: '<S72>/Sum' */
      SimpleFOC_B.Sum_m = SimpleFOC_B.Product_dk - SimpleFOC_B.Product_p;

      /* Product: '<S72>/Product2' */
      SimpleFOC_B.Product2_l = SimpleFOC_B.Switch_az[1] * SimpleFOC_B.Switch_az
        [1];

      /* RelationalOperator: '<S72>/Relational Operator' */
      SimpleFOC_B.RelationalOperator_g = (SimpleFOC_B.Sum_m >=
        SimpleFOC_B.Product2_l);

      /* DataTypeConversion: '<S72>/Data Type Conversion' */
      SimpleFOC_B.DataTypeConversion_j = SimpleFOC_B.RelationalOperator_g;

      /* If: '<S72>/If' incorporates:
       *  Switch: '<S74>/Switch1'
       */
      if (SimpleFOC_B.DataTypeConversion_j != 0) {
        /* Outputs for IfAction SubSystem: '<S72>/passThrough' incorporates:
         *  ActionPort: '<S75>/Action Port'
         */
        /* Merge: '<S72>/Merge' incorporates:
         *  SignalConversion generated from: '<S75>/ref2'
         */
        SimpleFOC_B.Merge_o = SimpleFOC_B.Switch_az[1];

        /* End of Outputs for SubSystem: '<S72>/passThrough' */
      } else {
        /* Outputs for IfAction SubSystem: '<S72>/limitRef2' incorporates:
         *  ActionPort: '<S74>/Action Port'
         */
        if (SimpleFOC_B.Sum_m > SimpleFOC_P.Switch1_Threshold) {
          /* Switch: '<S74>/Switch1' */
          SimpleFOC_B.Switch1_d = SimpleFOC_B.Sum_m;
        } else {
          /* Switch: '<S74>/Switch1' incorporates:
           *  Constant: '<S74>/Constant'
           */
          SimpleFOC_B.Switch1_d = SimpleFOC_P.Constant_Value;
        }

        /* Sqrt: '<S74>/Sqrt' */
        SimpleFOC_B.Sqrt = sqrt(SimpleFOC_B.Switch1_d);

        /* Switch: '<S74>/Switch' */
        if (SimpleFOC_B.Switch_az[1] >= SimpleFOC_P.Switch_Threshold) {
          /* Merge: '<S72>/Merge' */
          SimpleFOC_B.Merge_o = SimpleFOC_B.Sqrt;
        } else {
          /* Gain: '<S74>/Gain' */
          SimpleFOC_B.Gain_m = SimpleFOC_P.Gain_Gain_p * SimpleFOC_B.Sqrt;

          /* Merge: '<S72>/Merge' */
          SimpleFOC_B.Merge_o = SimpleFOC_B.Gain_m;
        }

        /* End of Switch: '<S74>/Switch' */
        /* End of Outputs for SubSystem: '<S72>/limitRef2' */
      }

      /* End of If: '<S72>/If' */

      /* Switch: '<S63>/Switch1' */
      if (SimpleFOC_B.Compare_c0) {
        /* Merge: '<S52>/Merge' */
        SimpleFOC_B.Merge_e[0] = SimpleFOC_B.Switch2_h;
        SimpleFOC_B.Merge_e[1] = SimpleFOC_B.Merge_o;
      } else {
        /* Merge: '<S52>/Merge' */
        SimpleFOC_B.Merge_e[0] = SimpleFOC_B.Merge_o;
        SimpleFOC_B.Merge_e[1] = SimpleFOC_B.Switch2_h;
      }

      /* End of Switch: '<S63>/Switch1' */
      /* End of Outputs for SubSystem: '<S52>/D//Q Axis Priority' */
    } else {
      /* Outputs for IfAction SubSystem: '<S52>/D-Q Equivalence' incorporates:
       *  ActionPort: '<S62>/Action Port'
       */
      /* RelationalOperator: '<S62>/Relational Operator' */
      SimpleFOC_B.RelationalOperator = (SimpleFOC_B.Sum1 >
        SimpleFOC_B.Product_dk);

      /* DataTypeConversion: '<S62>/Data Type Conversion' */
      SimpleFOC_B.DataTypeConversion_d = SimpleFOC_B.RelationalOperator;

      /* If: '<S62>/If' */
      if (SimpleFOC_B.DataTypeConversion_d != 0) {
        /* Outputs for IfAction SubSystem: '<S62>/Limiter' incorporates:
         *  ActionPort: '<S66>/Action Port'
         */
        /* Product: '<S66>/Product' */
        SimpleFOC_B.Product_b2[0] = SimpleFOC_B.Sum_d * SimpleFOC_B.Switch_i;
        SimpleFOC_B.Product_b2[1] = SimpleFOC_B.Sum * SimpleFOC_B.Switch_i;

        /* Sqrt: '<S66>/Square Root' */
        SimpleFOC_B.SquareRoot = sqrt(SimpleFOC_B.Sum1);

        /* Switch: '<S66>/Switch' */
        if (SimpleFOC_B.SquareRoot != 0.0) {
          /* Switch: '<S66>/Switch' */
          SimpleFOC_B.Switch_h = SimpleFOC_B.SquareRoot;
        } else {
          /* Switch: '<S66>/Switch' incorporates:
           *  Constant: '<S66>/Constant'
           */
          SimpleFOC_B.Switch_h = SimpleFOC_P.Constant_Value_o;
        }

        /* End of Switch: '<S66>/Switch' */

        /* Product: '<S66>/Reciprocal' */
        SimpleFOC_B.Reciprocal = 1.0 / SimpleFOC_B.Switch_h;

        /* Merge: '<S52>/Merge' incorporates:
         *  Product: '<S66>/Product1'
         */
        SimpleFOC_B.Merge_e[0] = SimpleFOC_B.Product_b2[0] *
          SimpleFOC_B.Reciprocal;
        SimpleFOC_B.Merge_e[1] = SimpleFOC_B.Product_b2[1] *
          SimpleFOC_B.Reciprocal;

        /* End of Outputs for SubSystem: '<S62>/Limiter' */
      } else {
        /* Outputs for IfAction SubSystem: '<S62>/Passthrough' incorporates:
         *  ActionPort: '<S67>/Action Port'
         */
        /* Merge: '<S52>/Merge' incorporates:
         *  SignalConversion generated from: '<S67>/dqRef'
         */
        SimpleFOC_B.Merge_e[0] = SimpleFOC_B.Sum_d;
        SimpleFOC_B.Merge_e[1] = SimpleFOC_B.Sum;

        /* End of Outputs for SubSystem: '<S62>/Passthrough' */
      }

      /* End of If: '<S62>/If' */
      /* End of Outputs for SubSystem: '<S52>/D-Q Equivalence' */
    }

    /* End of If: '<S52>/If' */

    /* Outputs for Atomic SubSystem: '<S2>/Inverse Park Transform' */
    /* Product: '<S56>/qcos' */
    SimpleFOC_B.qcos = SimpleFOC_B.Merge_e[1] * SimpleFOC_B.Sum6;

    /* Product: '<S56>/dsin' */
    SimpleFOC_B.dsin = SimpleFOC_B.Merge_e[0] * SimpleFOC_B.Sum4;

    /* Sum: '<S56>/sum_beta' */
    SimpleFOC_B.sum_beta = SimpleFOC_B.qcos + SimpleFOC_B.dsin;

    /* Product: '<S56>/dcos' */
    SimpleFOC_B.dcos = SimpleFOC_B.Merge_e[0] * SimpleFOC_B.Sum6;

    /* Product: '<S56>/qsin' */
    SimpleFOC_B.qsin = SimpleFOC_B.Merge_e[1] * SimpleFOC_B.Sum4;

    /* Sum: '<S56>/sum_alpha' */
    SimpleFOC_B.sum_alpha = SimpleFOC_B.dcos - SimpleFOC_B.qsin;

    /* Switch: '<S172>/Switch' incorporates:
     *  Constant: '<S172>/Offset'
     */
    if (SimpleFOC_P.Offset_Value > SimpleFOC_P.Switch_Threshold_c) {
      /* UnaryMinus: '<S172>/Unary_Minus' */
      SimpleFOC_B.Unary_Minus_a = -SimpleFOC_B.sum_alpha;

      /* Switch: '<S172>/Switch' */
      SimpleFOC_B.Switch_m[0] = SimpleFOC_B.sum_beta;
      SimpleFOC_B.Switch_m[1] = SimpleFOC_B.Unary_Minus_a;
    } else {
      /* Switch: '<S172>/Switch' */
      SimpleFOC_B.Switch_m[0] = SimpleFOC_B.sum_alpha;
      SimpleFOC_B.Switch_m[1] = SimpleFOC_B.sum_beta;
    }

    /* End of Switch: '<S172>/Switch' */

    /* AlgorithmDescriptorDelegate generated from: '<S56>/a16' */
    SimpleFOC_B.algDD_o1_c = SimpleFOC_B.Switch_m[0];

    /* AlgorithmDescriptorDelegate generated from: '<S56>/a16' */
    SimpleFOC_B.algDD_o2_d = SimpleFOC_B.Switch_m[1];

    /* End of Outputs for SubSystem: '<S2>/Inverse Park Transform' */

    /* Gain: '<S55>/one_by_two' */
    SimpleFOC_B.one_by_two = SimpleFOC_P.one_by_two_Gain *
      SimpleFOC_B.algDD_o1_c;

    /* Gain: '<S55>/sqrt3_by_two' */
    SimpleFOC_B.sqrt3_by_two = SimpleFOC_P.sqrt3_by_two_Gain *
      SimpleFOC_B.algDD_o2_d;

    /* Sum: '<S55>/add_b' */
    SimpleFOC_B.add_b = SimpleFOC_B.sqrt3_by_two - SimpleFOC_B.one_by_two;

    /* Sum: '<S55>/add_c' */
    SimpleFOC_B.add_c = (0.0 - SimpleFOC_B.one_by_two) -
      SimpleFOC_B.sqrt3_by_two;

    /* MinMax: '<S177>/Max' */
    Bias = fmax(SimpleFOC_B.algDD_o1_c, SimpleFOC_B.add_b);
    Bias = fmax(Bias, SimpleFOC_B.add_c);

    /* MinMax: '<S177>/Max' */
    SimpleFOC_B.Max = Bias;

    /* MinMax: '<S177>/Min' */
    Bias = fmin(SimpleFOC_B.algDD_o1_c, SimpleFOC_B.add_b);
    Bias = fmin(Bias, SimpleFOC_B.add_c);

    /* MinMax: '<S177>/Min' */
    SimpleFOC_B.Min = Bias;

    /* Sum: '<S177>/Add' */
    SimpleFOC_B.Add_k = SimpleFOC_B.Max + SimpleFOC_B.Min;

    /* Gain: '<S177>/one_by_two' */
    SimpleFOC_B.one_by_two_d = SimpleFOC_P.one_by_two_Gain_o * SimpleFOC_B.Add_k;

    /* Sum: '<S176>/Add3' */
    SimpleFOC_B.Add3 = SimpleFOC_B.algDD_o1_c + SimpleFOC_B.one_by_two_d;

    /* Sum: '<S176>/Add1' */
    SimpleFOC_B.Add1 = SimpleFOC_B.add_b + SimpleFOC_B.one_by_two_d;

    /* Sum: '<S176>/Add2' */
    SimpleFOC_B.Add2 = SimpleFOC_B.one_by_two_d + SimpleFOC_B.add_c;

    /* Gain: '<S176>/Gain' */
    SimpleFOC_B.Gain_a[0] = SimpleFOC_P.Gain_Gain_e * SimpleFOC_B.Add3;
    SimpleFOC_B.Gain_a[1] = SimpleFOC_P.Gain_Gain_e * SimpleFOC_B.Add1;
    SimpleFOC_B.Gain_a[2] = SimpleFOC_P.Gain_Gain_e * SimpleFOC_B.Add2;

    /* Gain: '<S58>/Gain1' */
    Bias = SimpleFOC_P.Gain1_Gain_e * SimpleFOC_B.Gain_a[0];
    SimpleFOC_B.Gain1_d[0] = Bias;

    /* Sum: '<S58>/Sum' incorporates:
     *  Constant: '<S58>/Constant4'
     */
    Bias += SimpleFOC_P.Constant4_Value_lq;
    SimpleFOC_B.PWM_Duty_Cycles[0] = Bias;

    /* DataTypeConversion: '<S57>/Data Type Conversion1' */
    SimpleFOC_B.DataTypeConversion1_h[0] = (real32_T)Bias;

    /* Saturate: '<S173>/Saturation2' */
    u0 = SimpleFOC_B.DataTypeConversion1_h[0];
    if (u0 > SimpleFOC_P.Saturation2_UpperSat) {
      u0 = SimpleFOC_P.Saturation2_UpperSat;
    } else if (u0 < SimpleFOC_P.Saturation2_LowerSat) {
      u0 = SimpleFOC_P.Saturation2_LowerSat;
    }

    /* Saturate: '<S173>/Saturation2' */
    SimpleFOC_B.Saturation2[0] = u0;

    /* Gain: '<S58>/Gain1' */
    Bias = SimpleFOC_P.Gain1_Gain_e * SimpleFOC_B.Gain_a[1];
    SimpleFOC_B.Gain1_d[1] = Bias;

    /* Sum: '<S58>/Sum' incorporates:
     *  Constant: '<S58>/Constant4'
     */
    Bias += SimpleFOC_P.Constant4_Value_lq;
    SimpleFOC_B.PWM_Duty_Cycles[1] = Bias;

    /* DataTypeConversion: '<S57>/Data Type Conversion1' */
    SimpleFOC_B.DataTypeConversion1_h[1] = (real32_T)Bias;

    /* Saturate: '<S173>/Saturation2' */
    u0 = SimpleFOC_B.DataTypeConversion1_h[1];
    if (u0 > SimpleFOC_P.Saturation2_UpperSat) {
      u0 = SimpleFOC_P.Saturation2_UpperSat;
    } else if (u0 < SimpleFOC_P.Saturation2_LowerSat) {
      u0 = SimpleFOC_P.Saturation2_LowerSat;
    }

    /* Saturate: '<S173>/Saturation2' */
    SimpleFOC_B.Saturation2[1] = u0;

    /* Gain: '<S58>/Gain1' */
    Bias = SimpleFOC_P.Gain1_Gain_e * SimpleFOC_B.Gain_a[2];
    SimpleFOC_B.Gain1_d[2] = Bias;

    /* Sum: '<S58>/Sum' incorporates:
     *  Constant: '<S58>/Constant4'
     */
    Bias += SimpleFOC_P.Constant4_Value_lq;
    SimpleFOC_B.PWM_Duty_Cycles[2] = Bias;

    /* DataTypeConversion: '<S57>/Data Type Conversion1' */
    SimpleFOC_B.DataTypeConversion1_h[2] = (real32_T)Bias;

    /* Saturate: '<S173>/Saturation2' */
    u0 = SimpleFOC_B.DataTypeConversion1_h[2];
    if (u0 > SimpleFOC_P.Saturation2_UpperSat) {
      u0 = SimpleFOC_P.Saturation2_UpperSat;
    } else if (u0 < SimpleFOC_P.Saturation2_LowerSat) {
      u0 = SimpleFOC_P.Saturation2_LowerSat;
    }

    /* Saturate: '<S173>/Saturation2' */
    SimpleFOC_B.Saturation2[2] = u0;

    /* Sum: '<S173>/Sum' */
    SimpleFOC_B.Sum_f = (SimpleFOC_B.Saturation2[1] + SimpleFOC_B.Saturation2[2])
      + SimpleFOC_B.Saturation2[0];

    /* Gain: '<S173>/Gain' */
    SimpleFOC_B.Gain_i = SimpleFOC_P.Gain_Gain_i * SimpleFOC_B.Sum_f;

    /* Sum: '<S173>/Sum1' */
    SimpleFOC_B.Sum1_l = SimpleFOC_B.Saturation2[0] - SimpleFOC_B.Gain_i;

    /* Sum: '<S173>/Sum2' */
    SimpleFOC_B.Sum2_f = SimpleFOC_B.Saturation2[1] - SimpleFOC_B.Gain_i;

    /* Sum: '<S173>/Sum3' */
    SimpleFOC_B.Sum3_c = SimpleFOC_B.Saturation2[2] - SimpleFOC_B.Gain_i;

    /* Switch: '<S173>/Switch' incorporates:
     *  Constant: '<S2>/12V'
     */
    if (SimpleFOC_P.Initial.InverterVoltage >= SimpleFOC_P.Switch_Threshold_j) {
      /* Switch: '<S173>/Switch' */
      SimpleFOC_B.Switch_k = SimpleFOC_P.Initial.InverterVoltage;
    } else {
      /* Switch: '<S173>/Switch' incorporates:
       *  Constant: '<S173>/Constant'
       */
      SimpleFOC_B.Switch_k = SimpleFOC_P.Constant_Value_m;
    }

    /* End of Switch: '<S173>/Switch' */

    /* Product: '<S173>/Product' */
    SimpleFOC_B.Product_l[0] = SimpleFOC_B.Sum1_l * SimpleFOC_B.Switch_k;
    SimpleFOC_B.Product_l[1] = SimpleFOC_B.Sum2_f * SimpleFOC_B.Switch_k;
    SimpleFOC_B.Product_l[2] = SimpleFOC_B.Sum3_c * SimpleFOC_B.Switch_k;
  }

  /* Gain: '<S1>/Rs' */
  Bias = SimpleFOC_P.BLDC_Rs * SimpleFOC_B.MatrixMultiply2[0];
  SimpleFOC_B.Rs[0] = Bias;

  /* Sum: '<S1>/Subtract' */
  SimpleFOC_B.Subtract[0] = SimpleFOC_B.Product_l[0] - Bias;

  /* Gain: '<S1>/Rs' */
  Bias = SimpleFOC_P.BLDC_Rs * SimpleFOC_B.MatrixMultiply2[1];
  SimpleFOC_B.Rs[1] = Bias;

  /* Sum: '<S1>/Subtract' */
  SimpleFOC_B.Subtract[1] = SimpleFOC_B.Product_l[1] - Bias;

  /* Gain: '<S1>/Rs' */
  Bias = SimpleFOC_P.BLDC_Rs * SimpleFOC_B.MatrixMultiply2[2];
  SimpleFOC_B.Rs[2] = Bias;

  /* Sum: '<S1>/Subtract' */
  SimpleFOC_B.Subtract[2] = SimpleFOC_B.Product_l[2] - Bias;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Step: '<Root>/Torque Setpoint' */
    Bias = (((SimpleFOC_M->Timing.clockTick1+SimpleFOC_M->Timing.clockTickH1*
              4294967296.0)) * 2.5E-6);
    if (Bias < SimpleFOC_P.TorqueSetpoint_Time) {
      /* Step: '<Root>/Torque Setpoint' */
      SimpleFOC_B.TorqueSetpoint = SimpleFOC_P.Initial.Torque;
    } else {
      /* Step: '<Root>/Torque Setpoint' */
      SimpleFOC_B.TorqueSetpoint = SimpleFOC_P.TorqueSetpoint_YFinal;
    }

    /* End of Step: '<Root>/Torque Setpoint' */

    /* DataTypeConversion: '<S3>/Data Type Conversion2' */
    SimpleFOC_B.DataTypeConversion2 = (real32_T)SimpleFOC_B.TorqueSetpoint;

    /* Product: '<S188>/Product' incorporates:
     *  Constant: '<S188>/Filter_Constant'
     */
    SimpleFOC_B.Product_h = SimpleFOC_B.DataTypeConversion2 *
      SimpleFOC_P.Filter_Constant_Value;

    /* UnitDelay: '<S188>/Unit Delay' */
    SimpleFOC_B.UnitDelay = SimpleFOC_DW.UnitDelay_DSTATE;

    /* Product: '<S188>/Product1' incorporates:
     *  Constant: '<S188>/One'
     */
    SimpleFOC_B.Product1_b = SimpleFOC_P.One_Value * SimpleFOC_B.UnitDelay;

    /* Sum: '<S188>/Add1' */
    SimpleFOC_B.Add1_n = SimpleFOC_B.Product_h + SimpleFOC_B.Product1_b;

    /* Constant: '<S8>/Speed0' */
    SimpleFOC_B.Speed0 = SimpleFOC_P.BLDC_Omega_init;
  }

  /* Integrator: '<S14>/Integrator' */
  if (SimpleFOC_DW.Integrator_IWORK_a != 0) {
    SimpleFOC_X.Integrator_CSTATE_c = SimpleFOC_B.Speed0;
  }

  /* Integrator: '<S14>/Integrator' */
  SimpleFOC_B.Integrator_h = SimpleFOC_X.Integrator_CSTATE_c;

  /* Switch: '<S8>/Trq_Or_Spd' incorporates:
   *  Constant: '<S8>/Constant3'
   */
  if (SimpleFOC_P.BLDC_MechInput > SimpleFOC_P.Trq_Or_Spd_Threshold) {
    /* Switch: '<S8>/Trq_Or_Spd' */
    SimpleFOC_B.Trq_Or_Spd = SimpleFOC_B.Add1_n;
  } else {
    /* Switch: '<S8>/Trq_Or_Spd' */
    SimpleFOC_B.Trq_Or_Spd = SimpleFOC_B.Integrator_h;
  }

  /* End of Switch: '<S8>/Trq_Or_Spd' */

  /* Gain: '<S1>/pole-pair' */
  SimpleFOC_B.polepair = SimpleFOC_P.BLDC_p * SimpleFOC_B.Trq_Or_Spd;

  /* Product: '<S1>/Product' */
  Bias = SimpleFOC_B.Max_Lampda_PM_rate[0] * SimpleFOC_B.polepair;
  SimpleFOC_B.Product_m[0] = Bias;

  /* Sum: '<S1>/Subtract1' */
  SimpleFOC_B.Subtract1[0] = SimpleFOC_B.Subtract[0] - Bias;

  /* Product: '<S1>/Product' */
  Bias = SimpleFOC_B.Max_Lampda_PM_rate[1] * SimpleFOC_B.polepair;
  SimpleFOC_B.Product_m[1] = Bias;

  /* Sum: '<S1>/Subtract1' */
  SimpleFOC_B.Subtract1[1] = SimpleFOC_B.Subtract[1] - Bias;

  /* Product: '<S1>/Product' */
  Bias = SimpleFOC_B.Max_Lampda_PM_rate[2] * SimpleFOC_B.polepair;
  SimpleFOC_B.Product_m[2] = Bias;

  /* Sum: '<S1>/Subtract1' */
  SimpleFOC_B.Subtract1[2] = SimpleFOC_B.Subtract[2] - Bias;

  /* Product: '<S1>/MatrixMultiply' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Product: '<S4>/MatrixMultiply2'
   */
  tmp_5 = &SimpleFOC_B.Gain1_i[0];
  cosOut = SimpleFOC_B.Subtract1[0];
  tmp_3 = SimpleFOC_B.Subtract1[1];
  tmp_1 = SimpleFOC_B.Subtract1[2];
  for (i = 0; i < 3; i++) {
    tmp = tmp_5[i] * cosOut;
    tmp += tmp_5[i + 3] * tmp_3;
    tmp += tmp_5[i + 6] * tmp_1;

    /* Product: '<S1>/MatrixMultiply' */
    SimpleFOC_B.MatrixMultiply_g[i] = tmp;
  }

  /* Product: '<S8>/Product' incorporates:
   *  Constant: '<S8>/Viscous'
   */
  SimpleFOC_B.Product_j = SimpleFOC_P.BLDC_B * SimpleFOC_B.Trq_Or_Spd;

  /* Sum: '<S8>/Subtract' incorporates:
   *  Constant: '<S8>/FrictionT'
   */
  SimpleFOC_B.Subtract_k = ((SimpleFOC_B.Add_i - SimpleFOC_B.Add1_n) -
    SimpleFOC_P.BLDC_F) - SimpleFOC_B.Product_j;

  /* Gain: '<S8>/1//J' */
  cosOut = 1.0 / SimpleFOC_P.BLDC_J;

  /* Gain: '<S8>/1//J' */
  SimpleFOC_B.uJ = cosOut * SimpleFOC_B.Subtract_k;

  /* Product: '<S16>/Divide1' incorporates:
   *  Constant: '<S16>/Ld'
   */
  SimpleFOC_B.Divide1 = SimpleFOC_B.MatrixMultiply_g[0] / SimpleFOC_P.BLDC_Ld;

  /* Product: '<S16>/Divide2' incorporates:
   *  Constant: '<S16>/Ld'
   */
  SimpleFOC_B.Divide2 = SimpleFOC_B.polepair / SimpleFOC_P.BLDC_Ld;

  /* Product: '<S16>/Product1' incorporates:
   *  Constant: '<S16>/Lq'
   */
  SimpleFOC_B.Product1_g = SimpleFOC_P.BLDC_Lq * SimpleFOC_B.Integrator_a;

  /* Product: '<S16>/Product2' */
  SimpleFOC_B.Product2_a = SimpleFOC_B.Divide2 * SimpleFOC_B.Product1_g;

  /* Sum: '<S16>/Add' */
  SimpleFOC_B.Add_j = SimpleFOC_B.Divide1 + SimpleFOC_B.Product2_a;

  /* Product: '<S17>/Divide1' incorporates:
   *  Constant: '<S17>/Lq'
   */
  SimpleFOC_B.Divide1_a = SimpleFOC_B.MatrixMultiply_g[1] / SimpleFOC_P.BLDC_Lq;

  /* Product: '<S17>/Divide2' incorporates:
   *  Constant: '<S17>/Lq'
   */
  SimpleFOC_B.Divide2_e = SimpleFOC_B.polepair / SimpleFOC_P.BLDC_Lq;

  /* Product: '<S17>/Product1' incorporates:
   *  Constant: '<S17>/Ld'
   */
  SimpleFOC_B.Product1_l = SimpleFOC_P.BLDC_Ld * SimpleFOC_B.Integrator_d;

  /* Product: '<S17>/Product2' */
  SimpleFOC_B.Product2_m = SimpleFOC_B.Divide2_e * SimpleFOC_B.Product1_l;

  /* Sum: '<S17>/Add' */
  SimpleFOC_B.Add_c = SimpleFOC_B.Divide1_a - SimpleFOC_B.Product2_m;
  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Gain: '<S104>/Integral Gain' */
    SimpleFOC_B.IntegralGain = SimpleFOC_P.Ki_id * SimpleFOC_B.ErrorDC;

    /* Gain: '<S152>/Integral Gain' */
    SimpleFOC_B.IntegralGain_b = SimpleFOC_P.Ki_iq * SimpleFOC_B.ErrorQC;
  }

  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(SimpleFOC_M->rtwLogInfo, (SimpleFOC_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* Update for Integrator: '<S15>/Integrator' */
    SimpleFOC_DW.Integrator_IWORK = 0;

    /* Update for Integrator: '<S19>/Integrator' */
    SimpleFOC_DW.Integrator_IWORK_n = 0;

    /* Update for Integrator: '<S21>/Integrator' */
    SimpleFOC_DW.Integrator_IWORK_o = 0;
    if (rtmIsMajorTimeStep(SimpleFOC_M)) {
      /* Update for UnitDelay generated from: '<Root>/Unit Delay' */
      SimpleFOC_DW.UnitDelay_1_DSTATE = SimpleFOC_B.MatrixMultiply2[0];

      /* Update for UnitDelay generated from: '<Root>/Unit Delay' */
      SimpleFOC_DW.UnitDelay_2_DSTATE = SimpleFOC_B.MatrixMultiply2[1];

      /* Update for UnitDelay generated from: '<Root>/Unit Delay' */
      SimpleFOC_DW.UnitDelay_9_DSTATE = SimpleFOC_B.Integrator;

      /* Update for UnitDelay: '<S188>/Unit Delay' */
      SimpleFOC_DW.UnitDelay_DSTATE = SimpleFOC_B.Add1_n;
    }

    /* Update for Integrator: '<S14>/Integrator' */
    SimpleFOC_DW.Integrator_IWORK_a = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(SimpleFOC_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(SimpleFOC_M)!=-1) &&
          !((rtmGetTFinal(SimpleFOC_M)-(((SimpleFOC_M->Timing.clockTick1+
               SimpleFOC_M->Timing.clockTickH1* 4294967296.0)) * 2.5E-6)) >
            (((SimpleFOC_M->Timing.clockTick1+SimpleFOC_M->Timing.clockTickH1*
               4294967296.0)) * 2.5E-6) * (DBL_EPSILON))) {
        rtmSetErrorStatus(SimpleFOC_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&SimpleFOC_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++SimpleFOC_M->Timing.clockTick0)) {
      ++SimpleFOC_M->Timing.clockTickH0;
    }

    SimpleFOC_M->Timing.t[0] = rtsiGetSolverStopTime(&SimpleFOC_M->solverInfo);

    {
      /* Update absolute timer for sample time: [2.5E-6s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 2.5E-6, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      SimpleFOC_M->Timing.clockTick1++;
      if (!SimpleFOC_M->Timing.clockTick1) {
        SimpleFOC_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void SimpleFOC_derivatives(void)
{
  XDot_SimpleFOC_T *_rtXdot;
  _rtXdot = ((XDot_SimpleFOC_T *) SimpleFOC_M->derivs);

  /* Derivatives for Integrator: '<S15>/Integrator' */
  _rtXdot->Integrator_CSTATE = SimpleFOC_B.Trq_Or_Spd;

  /* Derivatives for Integrator: '<S19>/Integrator' */
  _rtXdot->Integrator_CSTATE_l = SimpleFOC_B.Add_j;

  /* Derivatives for Integrator: '<S21>/Integrator' */
  _rtXdot->Integrator_CSTATE_g = SimpleFOC_B.Add_c;

  /* Derivatives for Integrator: '<S155>/Integrator' */
  _rtXdot->Integrator_CSTATE_lo = SimpleFOC_B.IntegralGain_b;

  /* Derivatives for Integrator: '<S107>/Integrator' */
  _rtXdot->Integrator_CSTATE_p = SimpleFOC_B.IntegralGain;

  /* Derivatives for Integrator: '<S14>/Integrator' */
  _rtXdot->Integrator_CSTATE_c = SimpleFOC_B.uJ;
}

/* Model initialize function */
void SimpleFOC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)SimpleFOC_M, 0,
                sizeof(RT_MODEL_SimpleFOC_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&SimpleFOC_M->solverInfo,
                          &SimpleFOC_M->Timing.simTimeStep);
    rtsiSetTPtr(&SimpleFOC_M->solverInfo, &rtmGetTPtr(SimpleFOC_M));
    rtsiSetStepSizePtr(&SimpleFOC_M->solverInfo, &SimpleFOC_M->Timing.stepSize0);
    rtsiSetdXPtr(&SimpleFOC_M->solverInfo, &SimpleFOC_M->derivs);
    rtsiSetContStatesPtr(&SimpleFOC_M->solverInfo, (real_T **)
                         &SimpleFOC_M->contStates);
    rtsiSetNumContStatesPtr(&SimpleFOC_M->solverInfo,
      &SimpleFOC_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&SimpleFOC_M->solverInfo,
      &SimpleFOC_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&SimpleFOC_M->solverInfo,
      &SimpleFOC_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&SimpleFOC_M->solverInfo,
      &SimpleFOC_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&SimpleFOC_M->solverInfo, (&rtmGetErrorStatus
      (SimpleFOC_M)));
    rtsiSetRTModelPtr(&SimpleFOC_M->solverInfo, SimpleFOC_M);
  }

  rtsiSetSimTimeStep(&SimpleFOC_M->solverInfo, MAJOR_TIME_STEP);
  SimpleFOC_M->intgData.y = SimpleFOC_M->odeY;
  SimpleFOC_M->intgData.f[0] = SimpleFOC_M->odeF[0];
  SimpleFOC_M->intgData.f[1] = SimpleFOC_M->odeF[1];
  SimpleFOC_M->intgData.f[2] = SimpleFOC_M->odeF[2];
  SimpleFOC_M->contStates = ((X_SimpleFOC_T *) &SimpleFOC_X);
  rtsiSetSolverData(&SimpleFOC_M->solverInfo, (void *)&SimpleFOC_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&SimpleFOC_M->solverInfo, false);
  rtsiSetSolverName(&SimpleFOC_M->solverInfo,"ode3");
  rtmSetTPtr(SimpleFOC_M, &SimpleFOC_M->Timing.tArray[0]);
  rtmSetTFinal(SimpleFOC_M, 3.0000000000000004);
  SimpleFOC_M->Timing.stepSize0 = 2.5E-6;
  rtmSetFirstInitCond(SimpleFOC_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    SimpleFOC_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(SimpleFOC_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(SimpleFOC_M->rtwLogInfo, (NULL));
    rtliSetLogT(SimpleFOC_M->rtwLogInfo, "tout");
    rtliSetLogX(SimpleFOC_M->rtwLogInfo, "");
    rtliSetLogXFinal(SimpleFOC_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(SimpleFOC_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(SimpleFOC_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(SimpleFOC_M->rtwLogInfo, 0);
    rtliSetLogDecimation(SimpleFOC_M->rtwLogInfo, 1);
    rtliSetLogY(SimpleFOC_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(SimpleFOC_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(SimpleFOC_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &SimpleFOC_B), 0,
                sizeof(B_SimpleFOC_T));

  /* states (continuous) */
  {
    (void) memset((void *)&SimpleFOC_X, 0,
                  sizeof(X_SimpleFOC_T));
  }

  /* states (dwork) */
  (void) memset((void *)&SimpleFOC_DW, 0,
                sizeof(DW_SimpleFOC_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(SimpleFOC_M->rtwLogInfo, 0.0, rtmGetTFinal
    (SimpleFOC_M), SimpleFOC_M->Timing.stepSize0, (&rtmGetErrorStatus
    (SimpleFOC_M)));

  /* Start for Constant: '<S8>/Pos0' */
  SimpleFOC_B.Pos0 = SimpleFOC_P.Initial.bldc.ITheta;

  /* Start for Constant: '<S16>/Id_0' */
  SimpleFOC_B.Id_0 = SimpleFOC_P.Initial.bldc.ILd;

  /* Start for Constant: '<S17>/Id_0' */
  SimpleFOC_B.Id_0_e = SimpleFOC_P.Initial.bldc.ILq;

  /* Start for If: '<S181>/If' */
  SimpleFOC_DW.If_ActiveSubsystem = -1;

  /* Start for If: '<S52>/If' */
  SimpleFOC_DW.If_ActiveSubsystem_p = -1;

  /* Start for Constant: '<S8>/Speed0' */
  SimpleFOC_B.Speed0 = SimpleFOC_P.BLDC_Omega_init;

  /* InitializeConditions for Integrator: '<S15>/Integrator' incorporates:
   *  Integrator: '<S19>/Integrator'
   */
  if (rtmIsFirstInitCond(SimpleFOC_M)) {
    SimpleFOC_X.Integrator_CSTATE = 0.0;
    SimpleFOC_X.Integrator_CSTATE_l = 0.0;
  }

  SimpleFOC_DW.Integrator_IWORK = 1;

  /* End of InitializeConditions for Integrator: '<S15>/Integrator' */

  /* InitializeConditions for Integrator: '<S19>/Integrator' */
  SimpleFOC_DW.Integrator_IWORK_n = 1;

  /* InitializeConditions for Integrator: '<S21>/Integrator' incorporates:
   *  Integrator: '<S14>/Integrator'
   */
  if (rtmIsFirstInitCond(SimpleFOC_M)) {
    SimpleFOC_X.Integrator_CSTATE_g = 0.0;
    SimpleFOC_X.Integrator_CSTATE_c = 20.0;
  }

  SimpleFOC_DW.Integrator_IWORK_o = 1;

  /* End of InitializeConditions for Integrator: '<S21>/Integrator' */

  /* InitializeConditions for UnitDelay generated from: '<Root>/Unit Delay' */
  SimpleFOC_DW.UnitDelay_1_DSTATE = SimpleFOC_P.UnitDelay_1_InitialCondition;

  /* InitializeConditions for UnitDelay generated from: '<Root>/Unit Delay' */
  SimpleFOC_DW.UnitDelay_2_DSTATE = SimpleFOC_P.UnitDelay_2_InitialCondition;

  /* InitializeConditions for UnitDelay generated from: '<Root>/Unit Delay' */
  SimpleFOC_DW.UnitDelay_9_DSTATE = SimpleFOC_P.UnitDelay_9_InitialCondition;

  /* InitializeConditions for Integrator: '<S155>/Integrator' */
  SimpleFOC_X.Integrator_CSTATE_lo = SimpleFOC_P.DiscreteQuadratureCurrentContro;

  /* InitializeConditions for Integrator: '<S107>/Integrator' */
  SimpleFOC_X.Integrator_CSTATE_p = SimpleFOC_P.DiscreteDirectCurrentController;

  /* InitializeConditions for UnitDelay: '<S188>/Unit Delay' */
  SimpleFOC_DW.UnitDelay_DSTATE = SimpleFOC_P.UnitDelay_InitialCondition;

  /* InitializeConditions for Integrator: '<S14>/Integrator' */
  SimpleFOC_DW.Integrator_IWORK_a = 1;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(SimpleFOC_M)) {
    rtmSetFirstInitCond(SimpleFOC_M, 0);
  }
}

/* Model terminate function */
void SimpleFOC_terminate(void)
{
  /* (no terminate code required) */
}
