// Ergasia Omadas 33
// Ioanna Bourcha A.M. 58019

// time is declared in seconds

#include <MKL25Z4.H>

__asm void payment(int plate_number, int now_time){

// r0 --> plate_number 	r1 --> now_time in seconds

	ldr r11, =0xFFFFFD50	// default address to save euros
							// default address to save cents 0xFFFFFD54
	
	movs r6, #60
	mul  r6, r6, r6 	// r6 = 3600 --> sec in 1 h
	adds r7, r6, #0		// r7 = 3600

		
	ldr r2, [r0]		// r2 --> entry_time_in_parking (sec)
	
	subs r2, r1, r2		// diff = now - entry (sec)

	cmp r2, r7			// 3600 sec == 1 h
	bhi c2
	movs r3, #0			// euros
	movs r4, #50	    // cents
	str r3, [r11]
	str r4, [r11, #4]
	bx lr
		
c2: add r7, r7, r6		// r7 = 7200  
	cmp r2, r7			// 7200 sec == 2 h
	bhi c3
	movs r3, #0			// euros
	movs r4, #95		// cents
	str r3, [r11]
	str r4, [r11, #4]
	bx lr

c3: add r7, r7, r6		// r7 = 10800
	cmp r2, r7			// 10800 sec == 3 h
	bhi c4
	movs r3, #1			// euros
	movs r4, #70		// cents
	str r3, [r11]
	str r4, [r11, #4]
	bx lr
		
c4: add r7, r7, r6		// r7 = 14400
	cmp r2, r7			// 14400 sec == 4 h
	bhi c5
	movs r3, #2			// euros
	movs r4, #60		// cents
	str r3, [r11]
	str r4, [r11, #412]
	bx lr

c5: movs r3, #3 		// euros
	movs r4, #50		// cents
	str r3, [r11]
	str r4, [r11, #4]
	bx lr
}

__asm void store_entry(int plate_number, int entry_time){	str r1, [r0]	}

int main(void)
{
	int plate_number = 0x0FFFF000;
	int entry_time = 3058;	// time in seconds
	int now_time   = 6089;	// time in seconds
	
	store_entry(plate_number, entry_time);
	
	payment(plate_number, now_time);
}

// Ergasia Omadas 33

