b reset
b reset
b reset
b reset
b reset
b reset
b reset
b reset

reset:
    bl gpio_output
    bl led2_on
    mov r0,r1
    mov r1,r2
    mov r2,r3
    mov r3,r4
    mov r4,r5
1:
    b 1b @跳到前面的1标号 1f的话是跳到后面的1标号

gpio_output:
	ldr	r11, =0xE0200280
	ldr	r12, =0x00001111
	str r12, [r11]
	ldr	r11, =0xE0200284
	ldr	r12, =0xF
	str	r12, [r11]
	mov	pc, lr
