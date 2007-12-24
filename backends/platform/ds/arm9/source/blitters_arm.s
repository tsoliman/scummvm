@ ScummVM Scumm Interpreter
@ Copyright (C) 2007 The ScummVM project
@
@ This program is free software@ you can redistribute it and/or
@ modify it under the terms of the GNU General Public License
@ as published by the Free Software Foundation@ either version 2
@ of the License, or (at your option) any later version.
@
@ This program is distributed in the hope that it will be useful,
@ but WITHOUT ANY WARRANTY; without even the implied warranty of
@ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
@ GNU General Public License for more details.
@
@ You should have received a copy of the GNU General Public License
@ along with this program@ if not, write to the Free Software
@ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
@
@ $URL:  $
@ $Id:  $
@
@ @author Robin Watts (robin@wss.co.uk)

	.global	asmDrawStripToScreen
	.global	asmCopy8Col
	.global	Rescale_320x256xPAL8_To_256x256x1555
	.global	Rescale_320x256x1555_To_256x256x1555
	.section .itcm,"ax", %progbits
	.align 2
	.code 32

	@ ARM implementation of asmDrawStripToScreen.
	@
	@ C prototype would be:
	@
	@ extern "C" void asmDrawStripToScreen(int         height,
	@                                      int         width,
	@                                      byte const *text,
	@                                      byte const *src,
	@                                      byte       *dst,
	@                                      int         vsPitch,
	@                                      int         vsScreenWidth,
	@                                      int         textSurfacePitch);
	@
	@ In addition, we assume that text, src and dst are all word (4 byte)
	@ aligned. This is the same assumption that the old 'inline' version
	@ made.
asmDrawStripToScreen:
	@ r0 = height
	@ r1 = width
	@ r2 = text
	@ r3 = src
	MOV	r12,r13
	STMFD	r13!,{r4-r7,r9-r11,R14}
	LDMIA	r12,{r4,r5,r6,r7}
	@ r4 = dst
	@ r5 = vsPitch
	@ r6 = vmScreenWidth
	@ r7 = textSurfacePitch

	CMP	r0,#0			@ If height<=0
	MOVLE	r0,#1			@    height=1
	CMP	r1,#4			@ If width<4
	BLT	end			@    return

	@ Width &= ~4 ? What's that about then? Width &= ~3 I could have
	@ understood...
	BIC	r1,r1,#4

	SUB	r5,r5,r1		@ vsPitch          -= width
	SUB	r6,r6,r1		@ vmScreenWidth    -= width
	SUB	r7,r7,r1		@ textSurfacePitch -= width
	MOV	r10,#253
	ORR	r10,r10,r10,LSL #8
	ORR	r10,r10,r10,LSL #16	@ r10 = mask
yLoop:
	MOV	r14,r1			@ r14 = width
xLoop:
	LDR	r12,[r2],#4		@ r12 = [text]
	LDR	r11,[r3],#4		@ r11 = [src]
	CMP	r12,r10
	BNE	singleByteCompare
	SUBS	r14,r14,#4
	STR	r11,[r4], #4		@ r4 = [dst]
	BGT	xLoop

	ADD	r2,r2,r7		@ text += textSurfacePitch
	ADD	r3,r3,r5		@ src  += vsPitch
	ADD	r4,r4,r6		@ dst  += vmScreenWidth
	SUBS	r0,r0,#1
	BGT	yLoop
	LDMFD	r13!,{r4-r7,r9-r11,PC}

singleByteCompare:
	MOV	r9,r12,LSR #24		@ r9 = 1st byte of [text]
	CMP	r9,r10,LSR #24		@ if (r9 == mask)
	MOVEQ	r9,r11,LSR #24		@     r9 = 1st byte of [src]
	ORR	r12,r9,r12,LSL #8	@ r12 = combine r9 and r12

	MOV	r9,r12,LSR #24		@ r9 = 1st byte of [text]
	CMP	r9,r10,LSR #24		@ if (r9 == mask)
	MOVEQ	r9,r11,LSR #24		@     r9 = 1st byte of [src]
	ORR	r12,r9,r12,LSL #8	@ r12 = combine r9 and r12

	MOV	r9,r12,LSR #24		@ r9 = 1st byte of [text]
	CMP	r9,r10,LSR #24		@ if (r9 == mask)
	MOVEQ	r9,r11,LSR #24		@     r9 = 1st byte of [src]
	ORR	r12,r9,r12,LSL #8	@ r12 = combine r9 and r12

	MOV	r9,r12,LSR #24		@ r9 = 1st byte of [text]
	CMP	r9,r10,LSR #24		@ if (r9 == mask)
	MOVEQ	r9,r11,LSR #24		@     r9 = 1st byte of [src]
	ORR	r12,r9,r12,LSL #8	@ r12 = combine r9 and r12

	STR	r12,[r4],#4
	SUBS	r14,r14,#4
	BGT	xLoop

	ADD	r2,r2,r7		@ text += textSurfacePitch
	ADD	r3,r3,r5		@ src  += vsPitch
	ADD	r4,r4,r6		@ dst  += vmScreenWidth
	SUBS	r0,r0,#1
	BGT	yLoop
end:
	LDMFD	r13!,{r4-r7,r9-r11,PC}


	@ ARM implementation of asmCopy8Col
	@
	@ C prototype would be:
	@
	@ extern "C" void asmCopy8Col(byte       *dst,
	@                             int         dstPitch,
	@                             const byte *src,
	@                             int         height);
	@
	@ In addition, we assume that src and dst are both word (4 byte)
	@ aligned. This is the same assumption that the old 'inline' version
	@ made.
asmCopy8Col:
	@ r0 = dst
	@ r1 = dstPitch
	@ r2 = src
	@ r3 = height
	STMFD	r13!,{r14}
	SUB	r1,r1,#4

	TST	r3,#1
	ADDNE   r3,r3,#1
	BNE	roll2
yLoop2:
	LDR	r12,[r2],#4
	LDR	r14,[r2],r1
	STR	r12,[r0],#4
	STR	r14,[r0],r1
roll2:
	LDR	r12,[r2],#4
	LDR	r14,[r2],r1
	SUBS	r3,r3,#2
	STR	r12,[r0],#4
	STR	r14,[r0],r1
	BNE	yLoop2

	LDMFD	r13!,{PC}


	@ ARM implementation of Rescale_320x256x1555_To_256x256x1555
	@
	@ C prototype would be:
	@
	@ extern "C" void Rescale_320x256x1555_To_256x256x1555(
	@                                      u16        *dst,
	@                                      const u16  *src,
	@                                      int         dstStride,
	@                                      int         srcStride);
Rescale_320x256x1555_To_256x256x1555:
	@ r0 = dst
	@ r1 = src
	@ r2 = dstStride
	@ r3 = srcStride
	STMFD	r13!,{r4-r6,r8-r11,r14}

	SUB	r2,r2,#64*4		@ srcStride -= line length
	SUB	r3,r3,#64*5		@ dstStride -= line length

	MOV	r8,    #0x0000001F
	ORR	r8, r8,#0x00007C00
	ORR	r8, r8,#0x03E00000	@ r8 = mask
	MOV	r6, #0x8000
	ORR	r6, r6, r6, LSL #16
	MOV	r5, #200		@ r5 = y
yLoop3:
	MOV	r4, #64			@ r4 = x
xLoop3:
	LDRH	r9, [r1],#2		@ r9 = src0
	LDRH	r10,[r1],#2		@ r10= src1
	LDRH	r11,[r1],#2		@ r11= src2
	LDRH	r12,[r1],#2		@ r12= src3
	LDRH	r14,[r1],#2		@ r14= src4

	ORR	r9, r9, r9, LSL #16	@ r9 = src0 | src0
	ORR	r10,r10,r10,LSL #16	@ r10= src1 | src1
	ORR	r11,r11,r11,LSL #16	@ r11= src2 | src2
	ORR	r12,r12,r12,LSL #16	@ r12= src3 | src3
	ORR	r14,r14,r14,LSL #16	@ r13= src4 | src4

	AND	r9, r9, r8		@ r9 = 0 | G0 | 0 | B0 | 0 | R0
	AND	r10,r10,r8		@ r10= 0 | G1 | 0 | B1 | 0 | R1
	AND	r11,r11,r8		@ r11= 0 | G2 | 0 | B2 | 0 | R2
	AND	r12,r12,r8		@ r12= 0 | G3 | 0 | B3 | 0 | R3
	AND	r14,r14,r8		@ r14= 0 | G4 | 0 | B4 | 0 | R4

	ADD	r9, r9, r9, LSL #1	@ r9 = 3*src0
	ADD	r9, r9, r10		@ r9 = dst0<<2
	ADD	r10,r10,r11		@ r10= dst1
	ADD	r11,r11,r12		@ r11= dst2
	ADD	r12,r12,r14		@ r12= src3 + src4
	ADD	r12,r12,r14,LSL #1	@ r12= src3 + src4*3 = dst3<<2

	AND	r9, r8, r9, LSR #2	@ r9 = dst0 (split)
	AND	r10,r8, r10,LSR #1	@ r10= dst1 (split)
	AND	r11,r8, r11,LSR #1	@ r11= dst2 (split)
	AND	r12,r8, r12,LSR #2	@ r12= dst3 (split)

	ORR	r9, r9, r9, ROR #16	@ r9 = dst0
	ORR	r10,r10,r10,ROR #16	@ r10= dst1
	ORR	r11,r11,r11,ROR #16	@ r11= dst2
	ORR	r12,r12,r12,ROR #16	@ r12= dst3

	ORR	r10,r6, r10,LSL #16
	ORR	r9, r10,r9, LSR #16
	ORR	r12,r6, r12,LSL #16
	ORR	r11,r12,r11,LSR #16
	STMIA	r0!,{r9,r11}

	SUBS	r4,r4,#1
	BGT	xLoop3

	ADD	r0,r0,r2,LSL #1
	ADD	r1,r1,r3,LSL #1
	SUBS	r5,r5,#1
	BGT	yLoop3

	LDMFD	r13!,{r4-r6,r8-r11,PC}

	@ ARM implementation of Rescale_320x256xPAL8_To_256x256x1555
	@
	@ C prototype would be:
	@
	@ extern "C" void Rescale_320x256xPAL8_To_256x256x1555(
	@                                      u16        *dst,
	@                                      const u8   *src,
	@                                      int         dstStride,
	@                                      int         srcStride,
	@                                      const u16  *pal);
	@
Rescale_320x256xPAL8_To_256x256x1555:
	@ r0 = dst
	@ r1 = src
	@ r2 = dstStride
	@ r3 = srcStride
	STMFD	r13!,{r4-r11,r14}
	MOV	r8,    #0x0000001F
	ORR	r8, r8,#0x0000FC00
	ORR	r8, r8,#0x03E00000	@ r8 = mask
	LDR	r9, [r13,#9*4]		@ r9 = palette

	SUB	r13,r13,#256*4		@ r13 = 1K of space on the stack.
	MOV	r5, r13			@ r5 points to this space
	MOV	r14,#256
palLoop:
	LDRH	r10,[r9],#2		@ r10 = palette entry
	SUBS	r14,r14,#1
	ORR	r10,r10,r10,LSL #16
	AND	r10,r10,r8		@ r10 = separated palette entry
	ORR	r10,r10,#0x00008000
	STR	r10,[r5], #4
	BGT	palLoop

	SUB	r2,r2,#64*4		@ srcStride -= line length
	SUB	r3,r3,#64*5		@ dstStride -= line length

	MOV	r14,#0xFF		@ r14= 255
	MOV	r5,#200			@ r5 = y
yLoop4:
	MOV	r4,#16			@ r4 = x
xLoop4:
	LDMIA	r1!,{r10,r11,r12}
	AND	r6, r14,r10		@ r6 = src0
	LDR	r6, [r13,r6, LSL #2]	@ r6 = pal[src0]
	AND	r7, r14,r10,LSR #8	@ r7 = src1
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src1]
	ADD	r6, r6, r6, LSL #1	@ r6 = 3*pal[src0]
	AND	r9, r14,r10,LSR #16	@ r9 = src2
	LDR	r9, [r13,r9, LSL #2]	@ r9 = pal[src2]
 	MOV	r10,r10,LSR #24		@ r10= src3
	LDR	r10,[r13,r10,LSL #2]	@ r10= pal[src3]
	ADD	r6, r6, r7		@ r6 = dst0<<2
	AND	r6, r8, r6, LSR #2	@ r6 = dst0 (split)
	ORR	r6, r6, r6, ROR #16	@ r6 = dst0 (in both halves)
	ADD	r7, r7, r9		@ r7 = dst1<<1
	AND	r7, r8, r7, LSR #1	@ r7 = dst1 (split)
	ORR	r7, r7, r7, ROR #16	@ r7 = dst1 (in both halves)
	MOV	r7, r7, LSL #16		@ r7 = dst1<<16
	ORR	r6, r7, r6, LSR #16	@ r6 = dst0 | dst1<<16
	AND	r7, r14,r11		@ r7 = src4
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src4]
	ADD	r9, r9, r10		@ r9 = dst2<<1
	AND	r9, r8, r9, LSR #1	@ r9 = dst2 (split)
	ORR	r9, r9, r9, ROR #16	@ r9 = dst2 (in both halves)
	ADD	r10,r10,r7		@ r7 = pal[src3]+pal[src4]
	ADD	r10,r10,r7, LSL #1	@ r10= dst3<<2
	AND	r10,r8, r10,LSR #2	@ r10= dst3 (split)
	ORR	r10,r10,r10,ROR #16	@ r10= dst3 (in both halves)
	MOV	r7, r9, LSR #16
	ORR	r7, r7, r10, LSL #16	@ r7 = dst2 | dst3<<16
	STMIA	r0!,{r6,r7}

	AND	r6, r14,r11,LSR #8	@ r6 = src5
	LDR	r6, [r13,r6, LSL #2]	@ r6 = pal[src5]
	AND	r7, r14,r11,LSR #16	@ r7 = src6
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src6]
	ADD	r6, r6, r6, LSL #1	@ r6 = 3*pal[src5]
	MOV	r9, r11,LSR #24		@ r9 = src7
	LDR	r9, [r13,r9, LSL #2]	@ r9 = pal[src7]
 	AND	r10,r14,r12		@ r10= src8
	LDR	r10,[r13,r10,LSL #2]	@ r10= pal[src8]
	ADD	r6, r6, r7		@ r6 = dst4<<2
	AND	r6, r8, r6, LSR #2	@ r6 = dst4 (split)
	ORR	r6, r6, r6, ROR #16	@ r6 = dst4 (in both halves)
	ADD	r7, r7, r9		@ r7 = dst5<<1
	AND	r7, r8, r7, LSR #1	@ r7 = dst5 (split)
	ORR	r7, r7, r7, ROR #16	@ r7 = dst5 (in both halves)
	MOV	r7, r7, LSL #16		@ r7 = dst5<<16
	ORR	r6, r7, r6, LSR #16	@ r6 = dst4 | dst5<<16
	AND	r7, r14,r12,LSR #8	@ r7 = src9
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src9]
	ADD	r9, r9, r10		@ r9 = dst6<<1
	AND	r9, r8, r9, LSR #1	@ r9 = dst6 (split)
	ORR	r9, r9, r9, ROR #16	@ r9 = dst6 (in both halves)
	ADD	r10,r10,r7		@ r10= pal[src8]+pal[src9]
	ADD	r10,r10,r7, LSL #1	@ r10= dst7<<2
	AND	r10,r8, r10,LSR #2	@ r10= dst7 (split)
	ORR	r10,r10,r10,ROR #16	@ r10= dst7 (in both halves)
	MOV	r7, r9, LSR #16
	ORR	r7, r7, r10, LSL #16	@ r7 = dst6 | dst7<<16
	LDMIA	r1!,{r10,r11}
	SUBS	r4,r4,#1
	STMIA	r0!,{r6,r7}

	AND	r6, r14,r12,LSR #16	@ r6 = src10
	LDR	r6, [r13,r6, LSL #2]	@ r6 = pal[src10]
	MOV	r7, r12,LSR #24		@ r7 = src11
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src11]
	ADD	r6, r6, r6, LSL #1	@ r6 = 3*pal[src10]
	AND	r9, r14,r10		@ r9 = src12
	LDR	r9, [r13,r9, LSL #2]	@ r9 = pal[src12]
 	AND	r12,r14,r10,LSR #8	@ r11= src13
	LDR	r12,[r13,r12,LSL #2]	@ r11= pal[src13]
	ADD	r6, r6, r7		@ r6 = dst8<<2
	AND	r6, r8, r6, LSR #2	@ r6 = dst8 (split)
	ORR	r6, r6, r6, ROR #16	@ r6 = dst8 (in both halves)
	ADD	r7, r7, r9		@ r7 = dst9<<1
	AND	r7, r8, r7, LSR #1	@ r7 = dst9 (split)
	ORR	r7, r7, r7, ROR #16	@ r7 = dst9 (in both halves)
	MOV	r7, r7, LSL #16		@ r7 = dst9<<16
	ORR	r6, r7, r6, LSR #16	@ r6 = dst8 | dst9<<16
	AND	r7, r14,r10,LSR #16	@ r7 = src14
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src14]
	ADD	r9, r9, r12		@ r9 = dst10<<1
	AND	r9, r8, r9, LSR #1	@ r9 = dst10 (split)
	ORR	r9, r9, r9, ROR #16	@ r9 = dst10 (in both halves)
	ADD	r12,r12,r7		@ r12= pal[src13]+pal[src14]
	ADD	r12,r12,r7, LSL #1	@ r12= dst11<<2
	AND	r12,r8, r12,LSR #2	@ r12= dst11 (split)
	ORR	r12,r12,r12,ROR #16	@ r12= dst11 (in both halves)
	MOV	r7, r9, LSR #16
	ORR	r7, r7, r12, LSL #16	@ r7 = dst10 | dst11<<16
	STMIA	r0!,{r6,r7}

	MOV	r6, r10,LSR #24		@ r6 = src15
	LDR	r6, [r13,r6, LSL #2]	@ r6 = pal[src15]
	AND	r7, r14,r11		@ r7 = src16
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src16]
	ADD	r6, r6, r6, LSL #1	@ r6 = 3*pal[src15]
	AND	r9, r14,r11,LSR #8	@ r9 = src17
	LDR	r9, [r13,r9, LSL #2]	@ r9 = pal[src17]
 	AND	r12,r14,r11,LSR #16	@ r11= src18
	LDR	r12,[r13,r12,LSL #2]	@ r11= pal[src18]
	ADD	r6, r6, r7		@ r6 = dst12<<2
	AND	r6, r8, r6, LSR #2	@ r6 = dst12 (split)
	ORR	r6, r6, r6, ROR #16	@ r6 = dst12 (in both halves)
	ADD	r7, r7, r9		@ r7 = dst13<<1
	AND	r7, r8, r7, LSR #1	@ r7 = dst13 (split)
	ORR	r7, r7, r7, ROR #16	@ r7 = dst13 (in both halves)
	MOV	r7, r7, LSL #16		@ r7 = dst13<<16
	ORR	r6, r7, r6, LSR #16	@ r6 = dst12 | dst13<<16
	MOV	r7, r11,LSR #24		@ r7 = src19
	LDR	r7, [r13,r7, LSL #2]	@ r7 = pal[src19]
	ADD	r9, r9, r12		@ r9 = dst14<<1
	AND	r9, r8, r9, LSR #1	@ r9 = dst14 (split)
	ORR	r9, r9, r9, ROR #16	@ r9 = dst14 (in both halves)
	ADD	r12,r12,r7		@ r12= pal[src18]+pal[src19]
	ADD	r12,r12,r7, LSL #1	@ r12= dst15<<2
	AND	r12,r8, r12,LSR #2	@ r12= dst15 (split)
	ORR	r12,r12,r12,ROR #16	@ r12= dst15 (in both halves)
	MOV	r7, r9, LSR #16
	ORR	r7, r7, r12, LSL #16	@ r7 = dst14 | dst15<<16
	STMIA	r0!,{r6,r7}

	BGT	xLoop4

	ADD	r0,r0,r2,LSL #1
	ADD	r1,r1,r3
	SUBS	r5,r5,#1
	BGT	yLoop4

	ADD	r13,r13,#256*4

	LDMFD	r13!,{r4-r11,PC}
