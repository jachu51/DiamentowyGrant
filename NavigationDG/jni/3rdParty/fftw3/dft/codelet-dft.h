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


/*
 * This header file must include every file or define every
 * type or macro which is required to compile a codelet.
 */

#ifndef __DFT_CODELET_H__
#define __DFT_CODELET_H__

#include "../kernel/ifftw.h"

/**************************************************************
 * types of codelets
 **************************************************************/

/* DFT codelets */
typedef struct kdft_desc_s kdft_desc;

typedef struct {
     int (*okp)(
	  const kdft_desc *desc,
	  const float *ri, const float *ii, const float *ro, const float *io,
	  INT is, INT os, INT vl, INT ivs, INT ovs,
	  const planner *plnr);
     INT vl;
} kdft_genus;

struct kdft_desc_s {
     INT sz;    /* size of transform computed */
     const char *nam;
     opcnt ops;
     const kdft_genus *genus;
     INT is;
     INT os;
     INT ivs;
     INT ovs;
};

typedef void (*kdft) (const float *ri, const float *ii, float *ro, float *io,
                      stride is, stride os, INT vl, INT ivs, INT ovs);
void fftwf_kdft_register(planner *p, kdft codelet, const kdft_desc *desc);


typedef struct ct_desc_s ct_desc;

typedef struct {
     int (*okp)(
	  const struct ct_desc_s *desc,
	  const float *rio, const float *iio,
	  INT rs, INT vs, INT m, INT mb, INT me, INT ms,
	  const planner *plnr);
     INT vl;
} ct_genus;

struct ct_desc_s {
     INT radix;
     const char *nam;
     const tw_instr *tw;
     const ct_genus *genus;
     opcnt ops;
     INT rs;
     INT vs;
     INT ms;
};

typedef void (*kdftw) (float *rioarray, float *iioarray, const float *W,
		       stride ios, INT mb, INT me, INT ms);
void fftwf_kdft_dit_register(planner *p, kdftw codelet, const ct_desc *desc);
void fftwf_kdft_dif_register(planner *p, kdftw codelet, const ct_desc *desc);


typedef void (*kdftwsq) (float *rioarray, float *iioarray,
			 const float *W, stride is, stride vs,
			 INT mb, INT me, INT ms);
void fftwf_kdft_difsq_register(planner *p, kdftwsq codelet, const ct_desc *desc);


extern const solvtab fftwf_solvtab_dft_standard;

#if HAVE_SIMD
extern const solvtab fftwf_solvtab_dft_simd;
#endif

#endif				/* __DFT_CODELET_H__ */
