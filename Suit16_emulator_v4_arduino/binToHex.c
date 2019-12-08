#include <stdio.h>

static void CreateHex(void);

int main(void) {
int newChar = 0;;
int counter = 0;

	while (	(newChar != EOF)
			&& (counter < 53)
	) {
		if (newChar == '-') {
			counter++;
		} else {
			counter = 0;
		}
		newChar = getchar();
	}

	// found line of '-------'
	if (counter == 53) {
		// make array of found hex data
		CreateHex();
	}
	printf(":00000001FF\n");

	return 0;
}


static void CreateHex(void) {
	unsigned int hexdata;
	int retValue = 1;
	int column;
	int counter = 0;
	unsigned int checksum;
	unsigned int prevAddr = 0;

	// start of array

	while (retValue > 0) {
		checksum = 0;
		column = 0;
		retValue = scanf("%x", &hexdata); // first read address at beginning of line
	
		if (hexdata < prevAddr) {
			return;
		}
		prevAddr = hexdata;
	
		printf(":10"); // always 16 bits
		checksum += 0x10;
		
		if (hexdata > 0) {
			hexdata /=2;
		}
		checksum += (hexdata >> 8) & 0xFF;
		checksum += (hexdata & 0x00FF);
		
		if (hexdata <= 0xFFF) {
			printf("0");
		}
		printf("%X",hexdata); 
		printf("00"); // type
		while (	(retValue > 0)
				&&	(column < 16)
		) {
			retValue = scanf("%x", &hexdata); //read byte
			
			checksum += hexdata;
			
			column += 1;
			if (hexdata <= 0xF) {
				printf("0");
			}
			printf("%X", hexdata);
			if (	(column > 0)
				&& ((column % 16) == 0)
			) {
				checksum &= 0xFF;
				
				unsigned char val;
				val = ~checksum + 1;
				
				if (val <= 0x0F) {
					printf("0");
				}
				printf("%X", val);
				printf("\n");

				counter++;
			}
	 	 }
	}
}

