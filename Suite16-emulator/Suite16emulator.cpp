// Suite16emulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>


//#define __DEBUG__
#define MEMSIZE		(1024)


uint16_t M[MEMSIZE] = {
	0x0F00,
	0x1000,
	0x003E,
	0x0C00,
	0x0D00,
	0x1100,
	0x0200,
	0x4100,
	0x0C00,
	0xE100,
	0x0107,
	0x0044,
	0x0F00,
	0x0F00,
	0x0F00,
	0x0F00,
	0x1200,
	0x0000,
	0x1300,
	0x0030,
	0x0216,
	0x001C,
	0x1100,
	0x7530,
	0xB100,
	0xE200,
	0xE200,
	0xE200,
	0x1100,
	0x2710,
	0x0834,
	0x1100,
	0x03E8,
	0x0834,
	0x1100,
	0x0064,
	0x0834,
	0x1100,
	0x000A,
	0x0834,
	0xA300,
	0x0C00,
	0xB400,
	0x1000,
	0x000A,
	0x0C00,
	0x1000,
	0x000D,
	0x0C00,
	0x0000,
	0x0F00,
	0x0F00,
	0xB100,
	0x0238,
	0xE200,
	0x0034,
	0x3400,
	0x2200,
	0xA300,
	0x0C00,
	0x2400,
	0xA100,
	0x1200,
	0x0000,
	0x0900,
	0x0F00,
	0x0F00,
	0x0F00,
	0x1100,
	0x0200,
	0x1700,
	0x0000,
	0x4100,
	0x3400,
	0xE100,
	0x4100,
	0x0B30,
	0x0258,
	0x0B17,
	0x0358,
	0x085B,
	0xA700,
	0xA000,
	0xA000,
	0xA000,
	0xA000,
	0x3700,
	0x0048,
	0x085B,
	0xA700,
	0x0010,
	0x2400,
	0x0B40,
	0x0260,
	0x0A09,
	0x0062,
	0x2400,
	0x0B30,
	0x0900,
	0x0F00,
	0x0F00,
	0x0F00,
	0x0F00,
	0x0F00,
};

uint32_t count = 0;
uint16_t PC = 0;
uint16_t IR = 0;
int16_t A = 0;
uint16_t i = 0;

// Zero the Registers, Set the top of the return stack at 0x0200
uint16_t R[16] = { 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0x200 };

static void fetch(void);
static void execute(void);

int main(void) {
	while (1) {
		fetch();
		execute();
	}
}

void fetch(void) {
	IR = M[PC];
	PC++;
	PC &= (MEMSIZE - 1);
}

void execute() {
	// Instruction Decoder
	uint8_t op = (uint8_t)(IR >> 12);			// op = IR 15:12      Opcode
	uint8_t n = (uint8_t)((IR & 0xF00) >> 8);	// n = IR 11:8        Register or Condition
	uint8_t addr = (uint8_t)(IR & 0x0FF);	    // addr = IR 7:0      Address or Displacement

#ifdef __DEBUG__
	printf("curr PC = %d\t", PC - 1);
	printf("PC=%x, IR=%x, op=%d, n=%d, addr = %x\t", PC, IR, op, n, addr);
	printf("next PC = %d\t", PC);
#endif // __DEBUG__

	// Opcode Execute */
	switch (op) {
	case 0x0:   break;
	case 0x1:   R[n] = M[PC]; PC++; break;  /* SET */
	case 0x2:   R[0] = R[n]; break;  /* LD */
	case 0x3:   R[n] = R[0]; break;  /* ST */
	case 0x4:   R[0] = M[R[n]]; break;  /* LD@ */
	case 0x5:   M[R[n]] = R[0]; break;  /* ST@ */
	case 0x6:   R[0] = M[R[n]]; R[n] = R[n] + 1;  break; /* POP with post-increment of pointer Rn  */
	case 0x7:   R[n] = R[n] - 1; M[R[n]] = R[0];  break; /* PSH with pre-decrement of pointer Rn */
	case 0x8:   R[0] &= R[n]; break;  /* AND */
	case 0x9:   R[0] |= R[n]; break;  /* OR  */
	case 0xA:   R[0] += R[n]; break;  /* ADD */
	case 0xB:   R[0] -= R[n]; break;  /* SUB */
	case 0xC:   R[n] = ~R[n]; break;  /* INV */
	case 0xD:   R[n] = R[n] - 1; break;  /* DEC */
	case 0xE:   R[n] = R[n] + 1; break;  /* INC */
	case 0xF:   R[0] ^= R[n]; break;  /* XOR */
	default: break;
	}

	// Conditional Branches and I/O Group

#ifdef __DEBUG__
	printf("A=%d, A=%x, R[0]=%d, R[0]=%x\t", A, A, R[0], R[0]);
	printf("R[1]=%x, R[2]=%x, R[3]=%x, R[4]=%x, R[5]=%x, R[6]=%x, R[7]=%x\n", R[1], R[2], R[3], R[4], R[5], R[6], R[7]);
#endif // __DEBUG__

	A = (int16_t)R[0];

	if (op == 0) { // do an unconditional jump back to enclosed address

		switch (n) {
		case 0x0:  PC = addr;              break;   // BRA Branch Always
		case 0x1:  if (A>0) { PC = addr; } break;   // BGT Branch if Greater
		case 0x2:  if (A<0) { PC = addr; } break;   // BLT Branch if Less Than
		case 0x3:  if (A >= 0) { PC = addr; } break;   // BGE Branch if Greater or Equal
		case 0x4:  if (A <= 0) { PC = addr; } break;   // BLE Branch if Less Than or Equal
		case 0x5:  if (A != 0) { PC = addr; } break;   // BNE Branch if Not Equal to zero
		case 0x6:  if (A == 0) { PC = addr; } break;   // BEQ Branch if Equal to zero
		case 0x7:  PC = M[PC]; break;  // 16-bit JMP
		case 0x8:  R[15] = R[15] - 1; M[R[15]] = PC; PC = addr; break;   // CALL (zero page) use R15 as Return Stack Pointer
		case 0x9:  PC = M[R[15]]; R[15] = R[15] + 1; break;        // RET
		case 0xA:  R[0] = R[0] + addr; break;        // ADI add the immediate 8-bit contained in the address field
		case 0xB:  R[0] = R[0] - addr; break;        // SBI subtract the immediate 8-bit contained in the address field											
		case 0xC:  printf("%c", (uint8_t)R[0]);  break; // OUT  - output a character to the Serial port
		case 0xD:  i = 0; while (i < (63)) {          // GETCHAR - get '0' terminated character string into buffer													  
			int ch = getchar();
			if (ch == '\r' || ch == '\n') break;
			if (ch >= ' ' && ch <= '~') { M[512 + i] = (uint8_t)ch;  i++; }
		}
			M[512 + i] = '\n'; M[512 + 1 + i] = 0; // Terminate the buffer with zero
			break;
		case 0xE:  PC = R[0]; R[0] = M[PC]; break;  // JMP @R0   - useful for indexing and table look-up ( curious but useful pipeline effect here)
		case 0xF:  break; R[0] &= R[0];             // NOP   AND accumulator with itself
		default: break;
		}
	}
	count++ ;    // Increment the instruction count
}

