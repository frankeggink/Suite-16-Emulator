
#include <stdint.h>

//#define __DEBUG__         // NOTE: can't use __DEBUG__ at the moment with arduino (printf statements need to be changed)
#define MEMSIZE    (65536) // you need a arduino compatible with > 64K (like a Nucleo-144 STM32F767)
unsigned int M[MEMSIZE] = { // hexloader_new is placed in memory
  0x1100,
  0x0071,
  0x0800,
  0x00E5,
  0x0800,
  0x00EA,
  0x1000,
  0x003E,
  0x0C00,
  0x1E00,
  0x0000,
  0x0D00,
  0x1100,
  0x0200,
  0x4100,
  0x1100,
  0x003A,
  0xB100,
  0x0509,
  0x0800,
  0x00C2,
  0x2700,
  0x3A00,
  0x0800,
  0x00D3,
  0x2700,
  0x3B00,
  0x0800,
  0x00C2,
  0x2700,
  0x3D00,
  0x1100,
  0x0001,
  0x3700,
  0xB100,
  0x0654,
  0x2700,
  0x014B,
  0x0800,
  0x00C2,
  0x2700,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0x5B00,
  0x0800,
  0x00C2,
  0x4B00,
  0x9700,
  0x5B00,
  0xEB00,
  0xDA00,
  0xDA00,
  0x2A00,
  0x0126,
  0x0800,
  0x00C2,
  0x2E00,
  0x1100,
  0x00FF,
  0x8100,
  0x0567,
  0x0800,
  0x00EA,
  0x1000,
  0x003E,
  0x0C00,
  0x0009,
  0x0700,
  0x0070,
  0x0800,
  0x00EA,
  0x1100,
  0x0093,
  0x0800,
  0x00E5,
  0x0800,
  0x00EA,
  0x0000,
  0x0800,
  0x00C2,
  0x2E00,
  0x1100,
  0x00FF,
  0x8100,
  0x0567,
  0x0800,
  0x00EA,
  0x1100,
  0x00A7,
  0x0800,
  0x00E5,
  0x0800,
  0x00EA,
  0x0800,
  0x00EA,
  0x0700,
  0x0300,
  0x0800,
  0x00EA,
  0x1100,
  0x0084,
  0x0800,
  0x00E5,
  0x0800,
  0x00EA,
  0x0000,
  0x0070,
  0x0053,
  0x0075,
  0x0069,
  0x0074,
  0x0065,
  0x0031,
  0x0036,
  0x0020,
  0x0048,
  0x0065,
  0x0078,
  0x0020,
  0x004C,
  0x006F,
  0x0061,
  0x0064,
  0x0065,
  0x0072,
  0x0000,
  0x0043,
  0x0068,
  0x0065,
  0x0063,
  0x006B,
  0x0073,
  0x0075,
  0x006D,
  0x0020,
  0x0065,
  0x0072,
  0x0072,
  0x006F,
  0x0072,
  0x0000,
  0x0049,
  0x006E,
  0x0076,
  0x0061,
  0x006C,
  0x0069,
  0x0064,
  0x0020,
  0x0072,
  0x0065,
  0x0063,
  0x006F,
  0x0072,
  0x0064,
  0x0020,
  0x0074,
  0x0079,
  0x0070,
  0x0065,
  0x0000,
  0x0044,
  0x006F,
  0x006E,
  0x0065,
  0x0020,
  0x006C,
  0x006F,
  0x0061,
  0x0064,
  0x0069,
  0x006E,
  0x0067,
  0x0000,
  0x0D00,
  0x1100,
  0x0200,
  0x4100,
  0x0B30,
  0x3200,
  0x0B0A,
  0x02BF,
  0x2200,
  0x0B07,
  0x00C0,
  0x2200,
  0x3700,
  0x0900,
  0x0800,
  0x00B4,
  0x2700,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0x3800,
  0x0800,
  0x00B4,
  0x2700,
  0x9800,
  0x3700,
  0x2E00,
  0xA700,
  0x3E00,
  0x0900,
  0x0800,
  0x00C2,
  0x2700,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0xA000,
  0x3900,
  0x0800,
  0x00C2,
  0x2700,
  0x9900,
  0x3700,
  0x0900,
  0x0800,
  0x00F3,
  0xE100,
  0x01E5,
  0x0900,
  0x1100,
  0x00F6,
  0x0800,
  0x00F3,
  0x1100,
  0x00F7,
  0x0800,
  0x00F3,
  0x0900,
  0x4100,
  0x0C00,
  0x0900,
  0x000D,
  0x000A,
  0x0020,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
  0x0000,
};
uint32_t count = 0;
uint16_t PC = 0;
uint16_t PCM = 0;
uint16_t IR = 0;
int16_t A = 0;
uint16_t i = 0;

// Zero the Registers, Set the top of the return stack at 0x0200
uint16_t R[16] = { 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0x200 };


void fetch(void);
void execute(void);


void setup() {  
  Serial.begin(115200); 
}

void loop() { 
  fetch(); 
  execute(); 
}


void fetch(void) {
  IR = M[PC];
  PC++;
  PC &= (MEMSIZE - 1);
}

void execute() {
  // Instruction Decoder
  uint8_t op = (uint8_t)(IR >> 12);     // op = IR 15:12      Opcode
  uint8_t n = (uint8_t)((IR & 0xF00) >> 8); // n = IR 11:8        Register or Condition
  uint8_t addr = (uint8_t)(IR & 0x0FF);     // addr = IR 7:0      Address or Displacement

  // calculate modified PC (used for conditional branching within 256-byte page)
  PCM = PC & 0xFF00;  // keep MSB of PC
  PCM |= addr;    // add LSB (addr) to it

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
  printf("R[1]=%x, R[2]=%x, R[3]=%x, R[4]=%x, R[5]=%x, R[6]=%x, R[7]=%x, R[8]=%x, R[9]=%x, R[10]=%x, R[11]=%x, R[12]=%x, R[13]=%x, R[14]=%x, R[15]=%x\n", R[1], R[2], R[3], R[4], R[5], R[6], R[7], R[8], R[9], R[10], R[11], R[12], R[13], R[14], R[15]);
#endif // __DEBUG__

  A = (int16_t)R[0];

  if (op == 0) { // do an unconditional jump back to enclosed address

    switch (n) {
    case 0x0:  PC = PCM;         break;   // BRA Branch Always
    case 0x1:  if (A > 0) { PC = PCM; } break;   // BGT Branch if Greater
    case 0x2:  if (A < 0) { PC = PCM; } break;   // BLT Branch if Less Than
    case 0x3:  if (A >= 0) { PC = PCM; } break;   // BGE Branch if Greater or Equal
    case 0x4:  if (A <= 0) { PC = PCM; } break;   // BLE Branch if Less Than or Equal
    case 0x5:  if (A != 0) { PC = PCM; } break;   // BNE Branch if Not Equal to zero
    case 0x6:  if (A == 0) { PC = PCM; } break;   // BEQ Branch if Equal to zero
    case 0x7:  PC = M[PC]; break; // 16-bit JMP
    case 0x8:  R[15] = R[15] - 1; M[R[15]] = PC+1; PC = M[PC]; break;   // CALL (16-bit) use R15 as Return Stack Pointer
    case 0x9:  PC = M[R[15]]; R[15] = R[15] + 1; break;        // RET
    case 0xA:  R[0] = R[0] + addr; break;        // ADI add the immediate 8-bit contained in the address field
    case 0xB:  R[0] = R[0] - addr; break;        // SBI subtract the immediate 8-bit contained in the address field                     
    case 0xC:  Serial.write((uint8_t)R[0]);  break; // OUT  - output a character to the Serial port
    case 0xD: 
    {
        while (!Serial.available()) {
          ; // wait
        }
        char ch = Serial.read();
        Serial.write(ch);
    M[512] = (uint8_t)ch;
    break;
    }
    case 0xE:  PC = R[0]; R[0] = M[PC]; break;  // JMP @R0   - useful for indexing and table look-up ( curious but useful pipeline effect here)
    case 0xF:  break; R[0] &= R[0];             // NOP   AND accumulator with itself
    default: break;
    }
  }

  count++ ;    // Increment the instruction count
}



