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
/* Generated on Sun Jul 12 06:37:33 EDT 2009 */

#include "../../codelet-dft.h"

#ifdef HAVE_FMA

/* Generated by: ../../../genfft/gen_twiddle -fma -reorder-insns -schedule-for-pipeline -compact -variables 4 -pipeline-latency 4 -n 7 -name t1_7 -include t.h */

/*
 * This function contains 72 FP additions, 66 FP multiplications,
 * (or, 18 additions, 12 multiplications, 54 fused multiply/add),
 * 66 stack variables, 6 constants, and 28 memory accesses
 */
#include "../t.h"

static void t1_7(float *ri, float *ii, const float *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP974927912, +0.974927912181823607018131682993931217232785801);
     DK(KP801937735, +0.801937735804838252472204639014890102331838324);
     DK(KP900968867, +0.900968867902419126236102319507445051165919162);
     DK(KP692021471, +0.692021471630095869627814897002069140197260599);
     DK(KP554958132, +0.554958132087371191422194871006410481067288862);
     DK(KP356895867, +0.356895867892209443894399510021300583399127187);
     INT m;
     for (m = mb, W = W + (mb * 12); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 12, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1c, T19, T1i, T18, T16, T1q, T1t, T1r, T1u, T1s;
	  {
	       E T1, TR, T1h, Te, Tt, Tw, T1a, TM, T1g, Tr, Tu, TS, Tz, TC, Ty;
	       E Tv, TB;
	       T1 = ri[0];
	       T1c = ii[0];
	       {
		    E T9, Tc, TP, Ta, Tb, TO, T7;
		    {
			 E T3, T6, T8, TN, T4, T2, T5;
			 T3 = ri[WS(rs, 1)];
			 T6 = ii[WS(rs, 1)];
			 T2 = W[0];
			 T9 = ri[WS(rs, 6)];
			 Tc = ii[WS(rs, 6)];
			 T8 = W[10];
			 TN = T2 * T6;
			 T4 = T2 * T3;
			 T5 = W[1];
			 TP = T8 * Tc;
			 Ta = T8 * T9;
			 Tb = W[11];
			 TO = FNMS(T5, T3, TN);
			 T7 = FMA(T5, T6, T4);
		    }
		    {
			 E Tg, Tj, Th, TI, Tm, Tp, Tl, Ti, To, TQ, Td, Tf;
			 Tg = ri[WS(rs, 2)];
			 TQ = FNMS(Tb, T9, TP);
			 Td = FMA(Tb, Tc, Ta);
			 Tj = ii[WS(rs, 2)];
			 Tf = W[2];
			 T19 = TO + TQ;
			 TR = TO - TQ;
			 T1h = Td - T7;
			 Te = T7 + Td;
			 Th = Tf * Tg;
			 TI = Tf * Tj;
			 Tm = ri[WS(rs, 5)];
			 Tp = ii[WS(rs, 5)];
			 Tl = W[8];
			 Ti = W[3];
			 To = W[9];
			 {
			      E TJ, Tk, TL, Tq, TK, Tn, Ts;
			      Tt = ri[WS(rs, 3)];
			      TK = Tl * Tp;
			      Tn = Tl * Tm;
			      TJ = FNMS(Ti, Tg, TI);
			      Tk = FMA(Ti, Tj, Th);
			      TL = FNMS(To, Tm, TK);
			      Tq = FMA(To, Tp, Tn);
			      Tw = ii[WS(rs, 3)];
			      Ts = W[4];
			      T1a = TJ + TL;
			      TM = TJ - TL;
			      T1g = Tq - Tk;
			      Tr = Tk + Tq;
			      Tu = Ts * Tt;
			      TS = Ts * Tw;
			 }
			 Tz = ri[WS(rs, 4)];
			 TC = ii[WS(rs, 4)];
			 Ty = W[6];
			 Tv = W[5];
			 TB = W[7];
		    }
	       }
	       {
		    E TF, TT, Tx, TV, TD, T1d, TU, TA;
		    TF = FNMS(KP356895867, Tr, Te);
		    TU = Ty * TC;
		    TA = Ty * Tz;
		    TT = FNMS(Tv, Tt, TS);
		    Tx = FMA(Tv, Tw, Tu);
		    TV = FNMS(TB, Tz, TU);
		    TD = FMA(TB, TC, TA);
		    T1d = FNMS(KP356895867, T1a, T19);
		    {
			 E T1b, T15, T17, TW;
			 T17 = FNMS(KP554958132, TR, TM);
			 T1b = TT + TV;
			 TW = TT - TV;
			 {
			      E TE, T1l, T1e, T12;
			      T1i = TD - Tx;
			      TE = Tx + TD;
			      T1l = FNMS(KP356895867, T19, T1b);
			      T1e = FNMS(KP692021471, T1d, T1b);
			      ii[0] = T19 + T1a + T1b + T1c;
			      T12 = FMA(KP554958132, TM, TW);
			      {
				   E TX, T1o, T1j, T14;
				   TX = FMA(KP554958132, TW, TR);
				   T1o = FMA(KP554958132, T1g, T1i);
				   T1j = FMA(KP554958132, T1i, T1h);
				   T14 = FNMS(KP356895867, TE, Tr);
				   {
					E TZ, TG, T1m, T1f;
					TZ = FNMS(KP356895867, Te, TE);
					TG = FNMS(KP692021471, TF, TE);
					ri[0] = T1 + Te + Tr + TE;
					T1m = FNMS(KP692021471, T1l, T1a);
					T1f = FNMS(KP900968867, T1e, T1c);
					{
					     E T13, TY, T1p, T1k;
					     T13 = FNMS(KP801937735, T12, TR);
					     TY = FMA(KP801937735, TX, TM);
					     T1p = FNMS(KP801937735, T1o, T1h);
					     T1k = FMA(KP801937735, T1j, T1g);
					     T15 = FNMS(KP692021471, T14, Te);
					     {
						  E T10, TH, T1n, T11;
						  T10 = FNMS(KP692021471, TZ, Tr);
						  TH = FNMS(KP900968867, TG, T1);
						  T1n = FNMS(KP900968867, T1m, T1c);
						  ii[WS(rs, 6)] = FNMS(KP974927912, T1k, T1f);
						  ii[WS(rs, 1)] = FMA(KP974927912, T1k, T1f);
						  T11 = FNMS(KP900968867, T10, T1);
						  ri[WS(rs, 1)] = FMA(KP974927912, TY, TH);
						  ri[WS(rs, 6)] = FNMS(KP974927912, TY, TH);
						  ii[WS(rs, 5)] = FNMS(KP974927912, T1p, T1n);
						  ii[WS(rs, 2)] = FMA(KP974927912, T1p, T1n);
						  ri[WS(rs, 2)] = FMA(KP974927912, T13, T11);
						  ri[WS(rs, 5)] = FNMS(KP974927912, T13, T11);
						  T18 = FNMS(KP801937735, T17, TW);
					     }
					}
				   }
			      }
			 }
			 T16 = FNMS(KP900968867, T15, T1);
			 T1q = FNMS(KP356895867, T1b, T1a);
			 T1t = FNMS(KP554958132, T1h, T1g);
		    }
	       }
	  }
	  ri[WS(rs, 3)] = FMA(KP974927912, T18, T16);
	  ri[WS(rs, 4)] = FNMS(KP974927912, T18, T16);
	  T1r = FNMS(KP692021471, T1q, T19);
	  T1u = FNMS(KP801937735, T1t, T1i);
	  T1s = FNMS(KP900968867, T1r, T1c);
	  ii[WS(rs, 4)] = FNMS(KP974927912, T1u, T1s);
	  ii[WS(rs, 3)] = FMA(KP974927912, T1u, T1s);
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 7},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 7, "t1_7", twinstr, &fftwf_dft_t_genus, {18, 12, 54, 0}, 0, 0, 0 };

void fftwf_codelet_t1_7 (planner *p) {
     fftwf_kdft_dit_register (p, t1_7, &desc);
}
#else				/* HAVE_FMA */

/* Generated by: ../../../genfft/gen_twiddle -compact -variables 4 -pipeline-latency 4 -n 7 -name t1_7 -include t.h */

/*
 * This function contains 72 FP additions, 60 FP multiplications,
 * (or, 36 additions, 24 multiplications, 36 fused multiply/add),
 * 29 stack variables, 6 constants, and 28 memory accesses
 */
#include "../t.h"

static void t1_7(float *ri, float *ii, const float *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP222520933, +0.222520933956314404288902564496794759466355569);
     DK(KP900968867, +0.900968867902419126236102319507445051165919162);
     DK(KP623489801, +0.623489801858733530525004884004239810632274731);
     DK(KP433883739, +0.433883739117558120475768332848358754609990728);
     DK(KP781831482, +0.781831482468029808708444526674057750232334519);
     DK(KP974927912, +0.974927912181823607018131682993931217232785801);
     INT m;
     for (m = mb, W = W + (mb * 12); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 12, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1, TR, Tc, TS, TC, TO, Tn, TT, TI, TP, Ty, TU, TF, TQ;
	  T1 = ri[0];
	  TR = ii[0];
	  {
	       E T6, TA, Tb, TB;
	       {
		    E T3, T5, T2, T4;
		    T3 = ri[WS(rs, 1)];
		    T5 = ii[WS(rs, 1)];
		    T2 = W[0];
		    T4 = W[1];
		    T6 = FMA(T2, T3, T4 * T5);
		    TA = FNMS(T4, T3, T2 * T5);
	       }
	       {
		    E T8, Ta, T7, T9;
		    T8 = ri[WS(rs, 6)];
		    Ta = ii[WS(rs, 6)];
		    T7 = W[10];
		    T9 = W[11];
		    Tb = FMA(T7, T8, T9 * Ta);
		    TB = FNMS(T9, T8, T7 * Ta);
	       }
	       Tc = T6 + Tb;
	       TS = Tb - T6;
	       TC = TA - TB;
	       TO = TA + TB;
	  }
	  {
	       E Th, TG, Tm, TH;
	       {
		    E Te, Tg, Td, Tf;
		    Te = ri[WS(rs, 2)];
		    Tg = ii[WS(rs, 2)];
		    Td = W[2];
		    Tf = W[3];
		    Th = FMA(Td, Te, Tf * Tg);
		    TG = FNMS(Tf, Te, Td * Tg);
	       }
	       {
		    E Tj, Tl, Ti, Tk;
		    Tj = ri[WS(rs, 5)];
		    Tl = ii[WS(rs, 5)];
		    Ti = W[8];
		    Tk = W[9];
		    Tm = FMA(Ti, Tj, Tk * Tl);
		    TH = FNMS(Tk, Tj, Ti * Tl);
	       }
	       Tn = Th + Tm;
	       TT = Tm - Th;
	       TI = TG - TH;
	       TP = TG + TH;
	  }
	  {
	       E Ts, TD, Tx, TE;
	       {
		    E Tp, Tr, To, Tq;
		    Tp = ri[WS(rs, 3)];
		    Tr = ii[WS(rs, 3)];
		    To = W[4];
		    Tq = W[5];
		    Ts = FMA(To, Tp, Tq * Tr);
		    TD = FNMS(Tq, Tp, To * Tr);
	       }
	       {
		    E Tu, Tw, Tt, Tv;
		    Tu = ri[WS(rs, 4)];
		    Tw = ii[WS(rs, 4)];
		    Tt = W[6];
		    Tv = W[7];
		    Tx = FMA(Tt, Tu, Tv * Tw);
		    TE = FNMS(Tv, Tu, Tt * Tw);
	       }
	       Ty = Ts + Tx;
	       TU = Tx - Ts;
	       TF = TD - TE;
	       TQ = TD + TE;
	  }
	  ri[0] = T1 + Tc + Tn + Ty;
	  ii[0] = TO + TP + TQ + TR;
	  {
	       E TJ, Tz, TX, TY;
	       TJ = FNMS(KP781831482, TF, KP974927912 * TC) - (KP433883739 * TI);
	       Tz = FMA(KP623489801, Ty, T1) + FNMA(KP900968867, Tn, KP222520933 * Tc);
	       ri[WS(rs, 5)] = Tz - TJ;
	       ri[WS(rs, 2)] = Tz + TJ;
	       TX = FNMS(KP781831482, TU, KP974927912 * TS) - (KP433883739 * TT);
	       TY = FMA(KP623489801, TQ, TR) + FNMA(KP900968867, TP, KP222520933 * TO);
	       ii[WS(rs, 2)] = TX + TY;
	       ii[WS(rs, 5)] = TY - TX;
	  }
	  {
	       E TL, TK, TV, TW;
	       TL = FMA(KP781831482, TC, KP974927912 * TI) + (KP433883739 * TF);
	       TK = FMA(KP623489801, Tc, T1) + FNMA(KP900968867, Ty, KP222520933 * Tn);
	       ri[WS(rs, 6)] = TK - TL;
	       ri[WS(rs, 1)] = TK + TL;
	       TV = FMA(KP781831482, TS, KP974927912 * TT) + (KP433883739 * TU);
	       TW = FMA(KP623489801, TO, TR) + FNMA(KP900968867, TQ, KP222520933 * TP);
	       ii[WS(rs, 1)] = TV + TW;
	       ii[WS(rs, 6)] = TW - TV;
	  }
	  {
	       E TN, TM, TZ, T10;
	       TN = FMA(KP433883739, TC, KP974927912 * TF) - (KP781831482 * TI);
	       TM = FMA(KP623489801, Tn, T1) + FNMA(KP222520933, Ty, KP900968867 * Tc);
	       ri[WS(rs, 4)] = TM - TN;
	       ri[WS(rs, 3)] = TM + TN;
	       TZ = FMA(KP433883739, TS, KP974927912 * TU) - (KP781831482 * TT);
	       T10 = FMA(KP623489801, TP, TR) + FNMA(KP222520933, TQ, KP900968867 * TO);
	       ii[WS(rs, 3)] = TZ + T10;
	       ii[WS(rs, 4)] = T10 - TZ;
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 7},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 7, "t1_7", twinstr, &fftwf_dft_t_genus, {36, 24, 36, 0}, 0, 0, 0 };

void fftwf_codelet_t1_7 (planner *p) {
     fftwf_kdft_dit_register (p, t1_7, &desc);
}
#endif				/* HAVE_FMA */
