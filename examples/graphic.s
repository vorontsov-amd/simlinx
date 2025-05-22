	.file	"graphic.c"
	.text
	.globl	main                            ; -- Begin function main
	.type	main,@function
main:                                   ; @main
; %bb.0:                                ; %entry
	MOVli r2 0
	STORE r2 r1 104
	MOVli r4 1280
	STORE r4 r1 100
	MOVli r4 720
	STORE r4 r1 96
	MOVli r4 500
	STORE r4 r1 92
	MOVli r4 299
	STORE r4 r1 88
	MOVli r4 1
	STORE r4 r1 84
	STORE r4 r1 80
	MOVli r4 8
	STORE r4 r1 76
	MOVli r4 255
	STORE r4 r1 44
	MOVli r4 65535
	STORE r4 r1 48
	MOVli r4 65280
	STORE r4 r1 52
	MOVhi r4 255
	ORi r9 r4 255
	STORE r9 r1 56
	ORi r9 r4 32512
	STORE r9 r1 60
	MOVhi r9 127
	ORi r9 r9 255
	STORE r9 r1 64
	STORE r4 r1 68
	ORi r4 r4 65280
	STORE r4 r1 72
	LOAD r4 r1 44
	STORE r4 r1 40
	STORE r2 r1 36
	STORE r2 r1 32
	MOVli r4 200
	STORE r4 r1 28
	STORE r4 r1 24
	MOVli r4 5
	STORE r4 r1 20
	STORE r4 r1 16
	STORE r2 r1 12
	STORE r2 r1 8
	B .LBB0_1
.LBB0_1:                                ; %while.body
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_22 Depth 2
                                        ;       Child Loop BB0_24 Depth 3
	LOAD r4 r1 28
	MOVli r2 0
	B.GT r2 r4 .LBB0_3
	B .LBB0_2
.LBB0_2:                                ; %lor.lhs.false
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 28
	MOVli r4 500
	ADD r4 r2 r4
	MOVli r2 1280
	B.GT r2 r4 .LBB0_11
	B .LBB0_3
.LBB0_3:                                ; %if.then
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 28
	MOVhi r4 65535
	ORi r4 r4 65535
	B.GT r2 r4 .LBB0_5
	B .LBB0_4
.LBB0_4:                                ; %if.then11
                                        ;   in Loop: Header=BB0_1 Depth=1
	MOVli r2 0
	STORE r2 r1 28
	B .LBB0_5
.LBB0_5:                                ; %if.end
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r4 r1 28
	MOVli r2 780
	B.GT r2 r4 .LBB0_7
	B .LBB0_6
.LBB0_6:                                ; %if.then13
                                        ;   in Loop: Header=BB0_1 Depth=1
	MOVli r2 779
	STORE r2 r1 28
	B .LBB0_7
.LBB0_7:                                ; %if.end14
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r4 r1 20
	MOVli r2 0
	SUB r2 r2 r4
	STORE r2 r1 20
	LOAD r2 r1 36
	MOVli r4 1
	ADD r2 r2 r4
	MOVli r4 7
	B.GT r2 r4 .LBB0_9
	B .LBB0_8
.LBB0_8:                                ; %if.then17
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 36
	MOVli r4 1
	ADD r2 r2 r4
	STORE r2 r1 36
	B .LBB0_10
.LBB0_9:                                ; %if.else
                                        ;   in Loop: Header=BB0_1 Depth=1
	MOVli r2 0
	STORE r2 r1 36
	B .LBB0_10
.LBB0_10:                               ; %if.end19
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 36
	STORE r2 r1 32
	LOAD r2 r1 32
	SHL r4, r2, 2
	ADD r2 r1 44
	ADD r2 r2 r4
	LOAD r2 r2 0
	STORE r2 r1 40
	B .LBB0_11
.LBB0_11:                               ; %if.end21
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r4 r1 24
	MOVli r2 0
	B.GT r2 r4 .LBB0_13
	B .LBB0_12
.LBB0_12:                               ; %lor.lhs.false23
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 24
	MOVli r4 299
	ADD r4 r2 r4
	MOVli r2 720
	B.GT r2 r4 .LBB0_21
	B .LBB0_13
.LBB0_13:                               ; %if.then26
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 24
	MOVhi r4 65535
	ORi r4 r4 65535
	B.GT r2 r4 .LBB0_15
	B .LBB0_14
.LBB0_14:                               ; %if.then28
                                        ;   in Loop: Header=BB0_1 Depth=1
	MOVli r2 0
	STORE r2 r1 24
	B .LBB0_15
.LBB0_15:                               ; %if.end29
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r4 r1 24
	MOVli r2 421
	B.GT r2 r4 .LBB0_17
	B .LBB0_16
.LBB0_16:                               ; %if.then31
                                        ;   in Loop: Header=BB0_1 Depth=1
	MOVli r2 420
	STORE r2 r1 24
	B .LBB0_17
.LBB0_17:                               ; %if.end32
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r4 r1 16
	MOVli r2 0
	SUB r2 r2 r4
	STORE r2 r1 16
	LOAD r2 r1 36
	MOVli r4 1
	ADD r2 r2 r4
	MOVli r4 7
	B.GT r2 r4 .LBB0_19
	B .LBB0_18
.LBB0_18:                               ; %if.then36
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 36
	MOVli r4 1
	ADD r2 r2 r4
	STORE r2 r1 36
	B .LBB0_20
.LBB0_19:                               ; %if.else38
                                        ;   in Loop: Header=BB0_1 Depth=1
	MOVli r2 0
	STORE r2 r1 36
	B .LBB0_20
.LBB0_20:                               ; %if.end39
                                        ;   in Loop: Header=BB0_1 Depth=1
	LOAD r2 r1 36
	STORE r2 r1 32
	LOAD r2 r1 32
	SHL r4, r2, 2
	ADD r2 r1 44
	ADD r2 r2 r4
	LOAD r2 r2 0
	STORE r2 r1 40
	B .LBB0_21
.LBB0_21:                               ; %if.end41
                                        ;   in Loop: Header=BB0_1 Depth=1
	CLEAR
	MOVli r2 0
	STORE r2 r1 4
	B .LBB0_22
.LBB0_22:                               ; %for.cond
                                        ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_24 Depth 3
	LOAD r2 r1 4
	MOVli r4 499
	B.GT r2 r4 .LBB0_29
	B .LBB0_23
.LBB0_23:                               ; %for.body
                                        ;   in Loop: Header=BB0_22 Depth=2
	MOVli r2 0
	STORE r2 r1 0
	B .LBB0_24
.LBB0_24:                               ; %for.cond43
                                        ;   Parent Loop BB0_1 Depth=1
                                        ;     Parent Loop BB0_22 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	LOAD r2 r1 0
	MOVli r4 298
	B.GT r2 r4 .LBB0_27
	B .LBB0_25
.LBB0_25:                               ; %for.body45
                                        ;   in Loop: Header=BB0_24 Depth=3
	LOAD r2 r1 28
	LOAD r4 r1 4
	ADD r2 r2 r4
	STORE r2 r1 12
	LOAD r2 r1 24
	LOAD r4 r1 0
	ADD r2 r2 r4
	STORE r2 r1 8
	LOAD r2 r1 12
	LOAD r4 r1 8
	LOAD r9 r1 40
	PUTPIXEL r2 r4 r9
	B .LBB0_26
.LBB0_26:                               ; %for.inc
                                        ;   in Loop: Header=BB0_24 Depth=3
	LOAD r2 r1 0
	MOVli r4 1
	ADD r2 r2 r4
	STORE r2 r1 0
	B .LBB0_24
.LBB0_27:                               ; %for.end
                                        ;   in Loop: Header=BB0_22 Depth=2
	B .LBB0_28
.LBB0_28:                               ; %for.inc48
                                        ;   in Loop: Header=BB0_22 Depth=2
	LOAD r2 r1 4
	MOVli r4 1
	ADD r2 r2 r4
	STORE r2 r1 4
	B .LBB0_22
.LBB0_29:                               ; %for.end50
                                        ;   in Loop: Header=BB0_1 Depth=1
	FLUSH
	LOAD r2 r1 28
	LOAD r4 r1 20
	ADD r2 r2 r4
	STORE r2 r1 28
	LOAD r2 r1 24
	LOAD r4 r1 16
	ADD r2 r2 r4
	STORE r2 r1 24
	B .LBB0_1
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        ; -- End function
	.ident	"clang version 20.1.4 (git@github.com:vorontsov-amd/llvm-project.git 28e76154f5210ef5349c658947d2672f83539519)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
