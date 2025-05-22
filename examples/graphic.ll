; ModuleID = 'graphic.c'
source_filename = "graphic.c"
target datalayout = "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32"
target triple = "mozartVM"

; Function Attrs: mustprogress noinline norecurse nounwind optnone
define dso_local noundef i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %window_width = alloca i32, align 4
  %window_height = alloca i32, align 4
  %image_width = alloca i32, align 4
  %image_height = alloca i32, align 4
  %dy = alloca i32, align 4
  %dx = alloca i32, align 4
  %color_count = alloca i32, align 4
  %colors = alloca [8 x i32], align 4
  %image_color = alloca i32, align 4
  %current_color = alloca i32, align 4
  %next_color = alloca i32, align 4
  %image_x = alloca i32, align 4
  %image_y = alloca i32, align 4
  %speed_x = alloca i32, align 4
  %speed_y = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  store i32 1920, ptr %window_width, align 4
  store i32 1080, ptr %window_height, align 4
  store i32 500, ptr %image_width, align 4
  store i32 299, ptr %image_height, align 4
  store i32 1, ptr %dy, align 4
  store i32 1, ptr %dx, align 4
  store i32 8, ptr %color_count, align 4
  %arrayidx = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 0
  store i32 255, ptr %arrayidx, align 4
  %arrayidx1 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 1
  store i32 65535, ptr %arrayidx1, align 4
  %arrayidx2 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 2
  store i32 65280, ptr %arrayidx2, align 4
  %arrayidx3 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 3
  store i32 16711935, ptr %arrayidx3, align 4
  %arrayidx4 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 4
  store i32 16744192, ptr %arrayidx4, align 4
  %arrayidx5 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 5
  store i32 8323327, ptr %arrayidx5, align 4
  %arrayidx6 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 6
  store i32 16711680, ptr %arrayidx6, align 4
  %arrayidx7 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 7
  store i32 16776960, ptr %arrayidx7, align 4
  %arrayidx8 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 0
  %0 = load i32, ptr %arrayidx8, align 4
  store i32 %0, ptr %image_color, align 4
  store i32 0, ptr %current_color, align 4
  store i32 0, ptr %next_color, align 4
  store i32 600, ptr %image_x, align 4
  store i32 600, ptr %image_y, align 4
  store i32 5, ptr %speed_x, align 4
  store i32 5, ptr %speed_y, align 4
  store i32 0, ptr %x, align 4
  store i32 0, ptr %y, align 4
  br label %while.body

while.body:                                       ; preds = %entry, %for.end50
  %1 = load i32, ptr %image_x, align 4
  %cmp = icmp sgt i32 0, %1
  br i1 %cmp, label %if.then, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %while.body
  %2 = load i32, ptr %image_x, align 4
  %add = add nsw i32 %2, 500
  %cmp9 = icmp sge i32 %add, 1920
  br i1 %cmp9, label %if.then, label %if.end21

if.then:                                          ; preds = %lor.lhs.false, %while.body
  %3 = load i32, ptr %image_x, align 4
  %cmp10 = icmp slt i32 %3, 0
  br i1 %cmp10, label %if.then11, label %if.end

if.then11:                                        ; preds = %if.then
  store i32 0, ptr %image_x, align 4
  br label %if.end

if.end:                                           ; preds = %if.then11, %if.then
  %4 = load i32, ptr %image_x, align 4
  %cmp12 = icmp sgt i32 %4, 1419
  br i1 %cmp12, label %if.then13, label %if.end14

if.then13:                                        ; preds = %if.end
  store i32 1419, ptr %image_x, align 4
  br label %if.end14

if.end14:                                         ; preds = %if.then13, %if.end
  %5 = load i32, ptr %image_x, align 4
  store i32 %5, ptr %image_x, align 4
  %6 = load i32, ptr %speed_x, align 4
  %sub = sub nsw i32 0, %6
  store i32 %sub, ptr %speed_x, align 4
  %7 = load i32, ptr %current_color, align 4
  %add15 = add nsw i32 %7, 1
  %cmp16 = icmp slt i32 %add15, 8
  br i1 %cmp16, label %if.then17, label %if.else

if.then17:                                        ; preds = %if.end14
  %8 = load i32, ptr %current_color, align 4
  %add18 = add nsw i32 %8, 1
  store i32 %add18, ptr %current_color, align 4
  br label %if.end19

if.else:                                          ; preds = %if.end14
  store i32 0, ptr %current_color, align 4
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.then17
  %9 = load i32, ptr %current_color, align 4
  store i32 %9, ptr %next_color, align 4
  %10 = load i32, ptr %next_color, align 4
  %arrayidx20 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 %10
  %11 = load i32, ptr %arrayidx20, align 4
  store i32 %11, ptr %image_color, align 4
  br label %if.end21

if.end21:                                         ; preds = %if.end19, %lor.lhs.false
  %12 = load i32, ptr %image_y, align 4
  %cmp22 = icmp sgt i32 0, %12
  br i1 %cmp22, label %if.then26, label %lor.lhs.false23

lor.lhs.false23:                                  ; preds = %if.end21
  %13 = load i32, ptr %image_y, align 4
  %add24 = add nsw i32 %13, 299
  %cmp25 = icmp sge i32 %add24, 1080
  br i1 %cmp25, label %if.then26, label %if.end41

if.then26:                                        ; preds = %lor.lhs.false23, %if.end21
  %14 = load i32, ptr %image_y, align 4
  %cmp27 = icmp slt i32 %14, 0
  br i1 %cmp27, label %if.then28, label %if.end29

if.then28:                                        ; preds = %if.then26
  store i32 0, ptr %image_y, align 4
  br label %if.end29

if.end29:                                         ; preds = %if.then28, %if.then26
  %15 = load i32, ptr %image_y, align 4
  %cmp30 = icmp sgt i32 %15, 780
  br i1 %cmp30, label %if.then31, label %if.end32

if.then31:                                        ; preds = %if.end29
  store i32 780, ptr %image_y, align 4
  br label %if.end32

if.end32:                                         ; preds = %if.then31, %if.end29
  %16 = load i32, ptr %image_y, align 4
  store i32 %16, ptr %image_y, align 4
  %17 = load i32, ptr %speed_y, align 4
  %sub33 = sub nsw i32 0, %17
  store i32 %sub33, ptr %speed_y, align 4
  %18 = load i32, ptr %current_color, align 4
  %add34 = add nsw i32 %18, 1
  %cmp35 = icmp slt i32 %add34, 8
  br i1 %cmp35, label %if.then36, label %if.else38

if.then36:                                        ; preds = %if.end32
  %19 = load i32, ptr %current_color, align 4
  %add37 = add nsw i32 %19, 1
  store i32 %add37, ptr %current_color, align 4
  br label %if.end39

if.else38:                                        ; preds = %if.end32
  store i32 0, ptr %current_color, align 4
  br label %if.end39

if.end39:                                         ; preds = %if.else38, %if.then36
  %20 = load i32, ptr %current_color, align 4
  store i32 %20, ptr %next_color, align 4
  %21 = load i32, ptr %next_color, align 4
  %arrayidx40 = getelementptr inbounds [8 x i32], ptr %colors, i32 0, i32 %21
  %22 = load i32, ptr %arrayidx40, align 4
  store i32 %22, ptr %image_color, align 4
  br label %if.end41

if.end41:                                         ; preds = %if.end39, %lor.lhs.false23
  call void @llvm.mozartVM.clearwindow()
  store i32 0, ptr %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc48, %if.end41
  %23 = load i32, ptr %i, align 4
  %cmp42 = icmp slt i32 %23, 500
  br i1 %cmp42, label %for.body, label %for.end50

for.body:                                         ; preds = %for.cond
  store i32 0, ptr %j, align 4
  br label %for.cond43

for.cond43:                                       ; preds = %for.inc, %for.body
  %24 = load i32, ptr %j, align 4
  %cmp44 = icmp slt i32 %24, 299
  br i1 %cmp44, label %for.body45, label %for.end

for.body45:                                       ; preds = %for.cond43
  %25 = load i32, ptr %image_x, align 4
  %26 = load i32, ptr %i, align 4
  %add46 = add nsw i32 %25, %26
  store i32 %add46, ptr %x, align 4
  %27 = load i32, ptr %image_y, align 4
  %28 = load i32, ptr %j, align 4
  %add47 = add nsw i32 %27, %28
  store i32 %add47, ptr %y, align 4
  %29 = load i32, ptr %x, align 4
  %30 = load i32, ptr %y, align 4
  %31 = load i32, ptr %image_color, align 4
  call void @llvm.mozartVM.putpixel(i32 %29, i32 %30, i32 %31)
  br label %for.inc

for.inc:                                          ; preds = %for.body45
  %32 = load i32, ptr %j, align 4
  %inc = add nsw i32 %32, 1
  store i32 %inc, ptr %j, align 4
  br label %for.cond43, !llvm.loop !3

for.end:                                          ; preds = %for.cond43
  br label %for.inc48

for.inc48:                                        ; preds = %for.end
  %33 = load i32, ptr %i, align 4
  %inc49 = add nsw i32 %33, 1
  store i32 %inc49, ptr %i, align 4
  br label %for.cond, !llvm.loop !5

for.end50:                                        ; preds = %for.cond
  call void @llvm.mozartVM.flush()
  %34 = load i32, ptr %image_x, align 4
  %35 = load i32, ptr %speed_x, align 4
  %mul = mul nsw i32 %35, 1
  %add51 = add nsw i32 %34, %mul
  store i32 %add51, ptr %image_x, align 4
  %36 = load i32, ptr %image_y, align 4
  %37 = load i32, ptr %speed_y, align 4
  %mul52 = mul nsw i32 %37, 1
  %add53 = add nsw i32 %36, %mul52
  store i32 %add53, ptr %image_y, align 4
  br label %while.body, !llvm.loop !6
}

; Function Attrs: nounwind
declare void @llvm.mozartVM.clearwindow() #1

; Function Attrs: nounwind
declare void @llvm.mozartVM.putpixel(i32, i32, i32) #1

; Function Attrs: nounwind
declare void @llvm.mozartVM.flush() #1

attributes #0 = { mustprogress noinline norecurse nounwind optnone "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #1 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 1}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{!"clang version 20.1.4 (git@github.com:vorontsov-amd/llvm-project.git 28e76154f5210ef5349c658947d2672f83539519)"}
!3 = distinct !{!3, !4}
!4 = !{!"llvm.loop.mustprogress"}
!5 = distinct !{!5, !4}
!6 = distinct !{!6, !4}
