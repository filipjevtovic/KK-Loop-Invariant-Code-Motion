; ModuleID = '2.in.ll'
source_filename = "2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [7 x i8] c"%d %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @foo(i32 noundef %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %2, align 4
  store i32 5, ptr %3, align 4
  store i32 0, ptr %4, align 4
  store i32 0, ptr %5, align 4
  %6 = load i32, ptr %2, align 4
  %7 = load i32, ptr %3, align 4
  %8 = mul nsw i32 %7, 10
  br label %9

9:                                                ; preds = %19, %1
  %10 = load i32, ptr %5, align 4
  %11 = icmp slt i32 %10, %6
  br i1 %11, label %12, label %22

12:                                               ; preds = %9
  %13 = load i32, ptr %5, align 4
  %14 = load i32, ptr %5, align 4
  %15 = mul nsw i32 %13, %14
  %16 = sub nsw i32 %15, %8
  %17 = load i32, ptr %4, align 4
  %18 = add nsw i32 %17, %16
  store i32 %18, ptr %4, align 4
  br label %19

19:                                               ; preds = %12
  %20 = load i32, ptr %5, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, ptr %5, align 4
  br label %9, !llvm.loop !6

22:                                               ; preds = %9
  %23 = load i32, ptr %4, align 4
  ret i32 %23
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 10, ptr %3, align 4
  store i32 10, ptr %4, align 4
  %5 = load i32, ptr %3, align 4
  %6 = and i32 %5, 1
  br label %7

7:                                                ; preds = %15, %0
  %8 = load i32, ptr %4, align 4
  %9 = icmp sge i32 %8, 0
  br i1 %9, label %10, label %18

10:                                               ; preds = %7
  store i32 %6, ptr %2, align 4
  %11 = load i32, ptr %2, align 4
  %12 = load i32, ptr %4, align 4
  %13 = call i32 @foo(i32 noundef %12)
  %14 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %11, i32 noundef %13)
  br label %15

15:                                               ; preds = %10
  %16 = load i32, ptr %4, align 4
  %17 = add nsw i32 %16, -1
  store i32 %17, ptr %4, align 4
  br label %7, !llvm.loop !8

18:                                               ; preds = %7
  %19 = load i32, ptr %1, align 4
  ret i32 %19
}

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.0 (https://github.com/filipjevtovic/KK-Loop-Invariant-Code-Motion.git 278898160ec63a956d7f6ad3062d6c7b2132ae31)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
