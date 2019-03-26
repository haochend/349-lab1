    .cpu arm7tdmi
    .fpu softvfp
    .eabi_attribute 20, 1
    .eabi_attribute 21, 1
    .eabi_attribute 23, 3
    .eabi_attribute 24, 1
    .eabi_attribute 25, 1
    .eabi_attribute 26, 1
    .eabi_attribute 30, 6
    .eabi_attribute 34, 0
    .eabi_attribute 18, 4
    .file   "optimize_me.c"
    .text
    .align  2
    .global optimize_me
    .type   optimize_me, %function
optimize_me:
    @ Function supports interworking.
    @ args = 0, pretend = 0, frame = 24
    @ frame_needed = 1, uses_anonymous_args = 0
    stmfd   sp!, {r4, r5, r6, fp, lr}
    add fp, sp, #16
    sub sp, sp, #28
    add r4, r0, #2000
    
    mov r7, #0
.L7:
    mov r1, r7
    mov r8, r0
.L6:
    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4
    
    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    ldr r3, [r8]
    add r5, r3, r3, asl #4
    add r3, r0, r7, asl #2
    ldr r6, [r3] 
    mul r3, r6, r1
    add r2, r5, r3
    add r3, r2, #19
    cmp r3, #0
    addlt r3, #15
    mov r3, r3, asr #4
    str r3, [r8]
    add r1, r1, #25
    add r8, r8, #4

    cmp r8, r4
    blt .L6
    add r7, r7, #1
    cmp r7, #500
    blt .L7
    sub sp, fp, #16
    @ sp needed
    ldmfd   sp!, {r4, r5, r6, fp, lr}
    bx  lr
    .size   optimize_me, .-optimize_me
    .ident  "GCC: (GNU Tools for ARM Embedded Processors) 4.9.3 20150529 (release) [ARM/embedded-4_9-branch revision 224288]"
