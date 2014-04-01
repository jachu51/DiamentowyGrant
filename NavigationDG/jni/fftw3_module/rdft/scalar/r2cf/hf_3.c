/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sun Jul 12 06:43:45 EDT 2009 */

#include "../../codelet-rdft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_hc2hc -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 3 -dit -name hf_3 -include hf.h */

/*
 * This function contains 16 FP additions, 14 FP multiplications,
 * (or, 6 additions, 4 multiplications, 10 fused multiply/add),
 * 21 stack variables, 2 constants, and 12 memory accesses
 */
#include "../hf.h"

static void hf_3(float *cr, float *ci, const float *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, Tl, T9, Tc, Tb, Th, T7, Ti, Ta, Tj, Td;
	  T1 = cr[0];
	  Tl = ci[0];
	  {
	       E T3, T6, T2, T5, Tg, T4, T8;
	       T3 = cr[WS(rs, 1)];
	       T6 = ci[WS(rs, 1)];
	       T2 = W[0];
	       T5 = W[1];
	       T9 = cr[WS(rs, 2)];
	       Tc = ci[WS(rs, 2)];
	       Tg = T2 * T6;
	       T4 = T2 * T3;
	       T8 = W[2];
	       Tb = W[3];
	       Th = FNMS(T5, T3, Tg);
	       T7 = FMA(T5, T6, T4);
	       Ti = T8 * Tc;
	       Ta = T8 * T9;
	  }
	  Tj = FNMS(Tb, T9, Ti);
	  Td = FMA(Tb, Tc, Ta);
	  {
	       E Tk, Te, To, Tn, Tm, Tf;
	       Tk = Th - Tj;
	       Tm = Th + Tj;
	       Te = T7 + Td;
	       To = Td - T7;
	       ci[WS(rs, 2)] = Tm + Tl;
	       Tn = FNMS(KP500000000, Tm, Tl);
	       cr[0] = T1 + Te;
	       Tf = FNMS(KP500000000, Te, T1);
	       ci[WS(rs, 1)] = FMA(KP866025403, To, Tn);
	       cr[WS(rs, 2)] = FMS(KP866025403, To, Tn);
	       cr[WS(rs, 1)] = FMA(KP866025403, Tk, Tf);
	       ci[0] = FNMS(KP866025403, Tk, Tf);
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 3},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 3, "hf_3", twinstr, &fftwf_rdft_hf_genus, {6, 4, 10, 0} };

void fftwf_codelet_hf_3 (planner *p) {
     fftwf_khc2hc_register (p, hf_3, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_hc2hc -compact -variables 4 -pipeline-latency 4 -n 3 -dit -name hf_3 -include hf.h */

/*
 * This function contains 16 FP additions, 12 FP multiplications,
 * (or, 10 additions, 6 multiplications, 6 fused multiply/add),
 * 15 stack variables, 2 constants, and 12 memory accesses
 */
#include "../hf.h"

static void hf_3(float *cr, float *ci, const float *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 4); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, Ti, T6, Te, Tb, Tf, Tc, Tj;
	  T1 = cr[0];
	  Ti = ci[0];
	  {
	       E T3, T5, T2, T4;
	       T3 = cr[WS(rs, 1)];
	       T5 = ci[WS(rs, 1)];
	       T2 = W[0];
	       T4 = W[1];
	       T6 = FMA(T2, T3, T4 * T5);
	       Te = FNMS(T4, T3, T2 * T5);
	  }
	  {
	       E T8, Ta, T7, T9;
	       T8 = cr[WS(rs, 2)];
	       Ta = ci[WS(rs, 2)];
	       T7 = W[2];
	       T9 = W[3];
	       Tb = FMA(T7, T8, T9 * Ta);
	       Tf = FNMS(T9, T8, T7 * Ta);
	  }
	  Tc = T6 + Tb;
	  Tj = Te + Tf;
	  {
	       E Td, Tg, Th, Tk;
	       cr[0] = T1 + Tc;
	       Td = FNMS(KP500000000, Tc, T1);
	       Tg = KP866025403 * (Te - Tf);
	       ci[0] = Td - Tg;
	       cr[WS(rs, 1)] = Td + Tg;
	       ci[WS(rs, 2)] = Tj + Ti;
	       Th = KP866025403 * (Tb - T6);
	       Tk = FNMS(KP500000000, Tj, Ti);
	       cr[WS(rs, 2)] = Th - Tk;
	       ci[WS(rs, 1)] = Th + Tk;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 3},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 3, "hf_3", twinstr, &fftwf_rdft_hf_genus, {10, 6, 6, 0} };

void fftwf_codelet_hf_3 (planner *p) {
     fftwf_khc2hc_register (p, hf_3, &desc);
}
#endif				/* HAVE_FMA */
