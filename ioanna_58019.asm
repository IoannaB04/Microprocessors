.global _start

// time in seconds

// payment(plate_number, now_time)

_start:
	
	ldr r0, =0x0FFFF000 // plate_number
	ldr r1, =0xBF2		// entry_time	3058
	str r1, [r0]
	ldr r1, =0x17C9		// now_time		6089
	
	//--------------------------------------------
	// r0 --> plate_number
	// r1 --> now_time in sec
	movs r11, #16	// address to save euros
	movs r12, #20	// address to save cents
	
	movs r6, #60
	mul r6, r6, r6 	// r6 = 3600 --> sec in 1 h
	adds r7, r6, #0	// r7 = 3600
	
	
	ldr r2, [r0]	// r2 --> entry_time_in_parking (sec)
	
	subs r2, r1, r2	// now - entry (sec)
	
	cmp r2, r7		// 3600 sec == 1 h
	bhi c2
	movs r3, #0		// euros
	movs r4, #50	// cents
	str r3, [r11]
	str r4, [r12]
	bx lr
	
c2: add r7, r7, r6	// r7 = 7200  
	cmp r2, r7		// 7200 sec == 2 h
	bhi c3
	movs r3, #0		// euros
	movs r4, #95	// cents
	str r3, [r11]
	str r4, [r12]
	bx lr

c3: add r7, r7, r6	// r7 = 10800
	cmp r2, r7		// 10800 sec == 3 h
	bhi c4
	movs r3, #1		// euros
	movs r4, #70	// cents
	str r3, [r11]
	str r4, [r12]
	bx lr
	
c4: add r7, r7, r6	// r7 = 14400
	cmp r2, r7		// 14400 sec == 4 h
	bhi c5
	movs r3, #2		// euros
	movs r4, #60	// cents
	str r3, [r11]
	str r4, [r12]
	bx lr

c5: movs r3, #3 	// euros
	movs r4, #50	// cents
	str r3, [r11]
	str r4, [r12]
	bx lr