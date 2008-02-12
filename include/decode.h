/****************************************************************************
*
*						Realmode X86 Emulator Library
*
*            	Copyright (C) 1996-1999 SciTech Software, Inc.
* 				     Copyright (C) David Mosberger-Tang
* 					   Copyright (C) 1999 Egbert Eich
*
*  ========================================================================
*
*  Permission to use, copy, modify, distribute, and sell this software and
*  its documentation for any purpose is hereby granted without fee,
*  provided that the above copyright notice appear in all copies and that
*  both that copyright notice and this permission notice appear in
*  supporting documentation, and that the name of the authors not be used
*  in advertising or publicity pertaining to distribution of the software
*  without specific, written prior permission.  The authors makes no
*  representations about the suitability of this software for any purpose.
*  It is provided "as is" without express or implied warranty.
*
*  THE AUTHORS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
*  INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
*  EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
*  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
*  USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
*  OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
*  PERFORMANCE OF THIS SOFTWARE.
*
*  ========================================================================
*
* Language:		ANSI C
* Environment:	Any
* Developer:    Kendall Bennett
*
* Description:  Header file for instruction decoding logic.
*
****************************************************************************/

#ifndef __X86EMU_DECODE_H
#define __X86EMU_DECODE_H

/*---------------------- Macros and type definitions ----------------------*/

/* Instruction Decoding Stuff */

#define FETCH_DECODE_MODRM(mod,rh,rl) 	fetch_decode_modrm(&mod,&rh,&rl)
#define DECODE_RM_BYTE_REGISTER(r)    	decode_rm_byte_register(r)
#define DECODE_RM_WORD_REGISTER(r)    	decode_rm_word_register(r)
#define DECODE_RM_LONG_REGISTER(r)    	decode_rm_long_register(r)
#define DECODE_CLEAR_SEGOVR()

#define OP_DECODE(a) \
  memcpy(M.x86.disasm_ptr, a, sizeof a - 1), \
  M.x86.disasm_ptr += sizeof a - 1

#define SEGPREF_DECODE \
  memcpy(M.x86.disasm_ptr, M.x86.decode_seg, 4), \
  M.x86.disasm_ptr += M.x86.default_seg ? 4 : 1

/*-------------------------- Function Prototypes --------------------------*/

#ifdef  __cplusplus
extern "C" {            			/* Use "C" linkage when in C++ mode */
#endif

void 	x86emu_intr_raise (u8 type);
void    fetch_decode_modrm (int *mod,int *regh,int *regl);
u8      fetch_byte_imm (void);
u16     fetch_word_imm (void);
u32     fetch_long_imm (void);
u8      fetch_data_byte (uint offset);
u8      fetch_data_byte_abs (uint segment, uint offset);
u16     fetch_data_word (uint offset);
u16     fetch_data_word_abs (uint segment, uint offset);
u32     fetch_data_long (uint offset);
u32     fetch_data_long_abs (uint segment, uint offset);
void    store_data_byte (uint offset, u8 val);
void    store_data_byte_abs (uint segment, uint offset, u8 val);
void    store_data_word (uint offset, u16 val);
void    store_data_word_abs (uint segment, uint offset, u16 val);
void    store_data_long (uint offset, u32 val);
void    store_data_long_abs (uint segment, uint offset, u32 val);
u8* 	decode_rm_byte_register(int reg);
u16* 	decode_rm_word_register(int reg);
u32* 	decode_rm_long_register(int reg);
u16* 	decode_rm_seg_register(int reg);
sel_t *decode_rm_seg_register2(int reg);
u32	decode_rm00_address(int rm);
u32	decode_rm01_address(int rm);
u32	decode_rm10_address(int rm);
u32	decode_sib_address(int sib, int mod);
u32     decode_rm_address(int mod, int rl);

void decode_hex2(u32 ofs);
void decode_hex4(u32 ofs);
void decode_hex8(u32 ofs);
void decode_hex2s(s32 ofs);
void decode_hex4s(s32 ofs);
void decode_hex8s(s32 ofs);

void decode_set_seg_register(sel_t *sel, u16 val);


#ifdef  __cplusplus
}                       			/* End of "C" linkage for C++   	*/
#endif

#endif /* __X86EMU_DECODE_H */