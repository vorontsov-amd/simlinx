	.file	"simple.c"
	.text
	.globl	_Z3appv                         ; -- Begin function _Z3appv
	.type	_Z3appv,@function
_Z3appv:                                ; @_Z3appv
; %bb.0:                                ; %entry
	B .LBB0_1
.LBB0_1:                                ; %while.body
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_2 Depth 2
                                        ;       Child Loop BB0_4 Depth 3
	MOVli r2 0
	STORE r2 r1 4
	B .LBB0_2
.LBB0_2:                                ; %for.cond
                                        ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_4 Depth 3
	LOAD r2 r1 4
	MOVli r4 999
	B.GT r2 r4 .LBB0_9
	B .LBB0_3
.LBB0_3:                                ; %for.body
                                        ;   in Loop: Header=BB0_2 Depth=2
	MOVli r2 0
	STORE r2 r1 0
	B .LBB0_4
.LBB0_4:                                ; %for.cond1
                                        ;   Parent Loop BB0_1 Depth=1
                                        ;     Parent Loop BB0_2 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	LOAD r2 r1 0
	MOVli r4 999
	B.GT r2 r4 .LBB0_7
	B .LBB0_5
.LBB0_5:                                ; %for.body3
                                        ;   in Loop: Header=BB0_4 Depth=3
	LOAD r2 r1 0
	LOAD r4 r1 4
	ADD r9 r2 r4
	MOVli r10 255
	ADD r9 r9 r10
	PUTPIXEL r2 r4 r9
	B .LBB0_6
.LBB0_6:                                ; %for.inc
                                        ;   in Loop: Header=BB0_4 Depth=3
	LOAD r2 r1 0
	MOVli r4 1
	ADD r2 r2 r4
	STORE r2 r1 0
	B .LBB0_4
.LBB0_7:                                ; %for.end
                                        ;   in Loop: Header=BB0_2 Depth=2
	B .LBB0_8
.LBB0_8:                                ; %for.inc5
                                        ;   in Loop: Header=BB0_2 Depth=2
	LOAD r2 r1 4
	MOVli r4 1
	ADD r2 r2 r4
	STORE r2 r1 4
	B .LBB0_2
.LBB0_9:                                ; %for.end7
                                        ;   in Loop: Header=BB0_1 Depth=1
	FLUSH
	B .LBB0_1
.Lfunc_end0:
	.size	_Z3appv, .Lfunc_end0-_Z3appv
                                        ; -- End function
	.ident	"clang version 20.1.4 (git@github.com:vorontsov-amd/llvm-project.git 28e76154f5210ef5349c658947d2672f83539519)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
