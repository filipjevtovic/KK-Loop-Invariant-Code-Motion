; ModuleID = '3.c'
source_filename = "3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [7 x i8] c"%d%d%d\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4    ;x
  %3 = alloca i32, align 4    ;y
  %4 = alloca i32, align 4    ;z
  %5 = alloca i32, align 4    ;n
  %6 = alloca i32, align 4    ;s
  %7 = alloca i32, align 4    ;t
  %8 = alloca i32, align 4    ;i
  %9 = alloca i32, align 4    ;j
  store i32 0, ptr %1, align 4
  store i32 1000, ptr %5, align 4
  %10 = call i32 (ptr, ...) @__isoc99_scanf(ptr noundef @.str, ptr noundef %2, ptr noundef %3, ptr noundef %4)
  store i32 0, ptr %8, align 4
  br label %11

11:                                               ; preds = %36, %0
  %12 = load i32, ptr %8, align 4
  %13 = load i32, ptr %5, align 4
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %15, label %39

15:                                               ; preds = %11
  %16 = load i32, ptr %2, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, ptr %2, align 4
  %18 = load i32, ptr %2, align 4
  %19 = load i32, ptr %4, align 4
  %20 = mul nsw i32 %18, %19
  store i32 %20, ptr %3, align 4
  %21 = load i32, ptr %5, align 4
  %22 = sub nsw i32 %21, 42
  store i32 %22, ptr %4, align 4
  store i32 -1, ptr %9, align 4
  br label %23

23:                                               ; preds = %32, %15
  %24 = load i32, ptr %9, align 4
  %25 = load i32, ptr %5, align 4
  %26 = icmp slt i32 %24, %25
  br i1 %26, label %27, label %35

27:                                               ; preds = %23
  store i32 5, ptr %2, align 4
  %28 = load i32, ptr %9, align 4
  %29 = mul nsw i32 7, %28
  store i32 %29, ptr %6, align 4
  %30 = load i32, ptr %5, align 4
  %31 = and i32 %30, 1
  store i32 %31, ptr %7, align 4
  br label %32

32:                                               ; preds = %27
  %33 = load i32, ptr %9, align 4
  %34 = add nsw i32 %33, 1
  store i32 %34, ptr %9, align 4
  br label %23, !llvm.loop !6

35:                                               ; preds = %23
  br label %36

36:                                               ; preds = %35
  %37 = load i32, ptr %8, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, ptr %8, align 4
  br label %11, !llvm.loop !8

39:                                               ; preds = %11
  ret i32 0
}

declare i32 @__isoc99_scanf(ptr noundef, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.0 (https://github.com/filipjevtovic/KK-Loop-Invariant-Code-Motion.git 9556a5dd7e7c216852f4f16e9685235229829ac5)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
