
EOS:         .EQU    $0000            	;End of string

.org $300
block1:
	CALL CRLF
	SET R1, HELP_MSG_1
next:	
	LD R0, @R1
	OUT
	INC R1
	BGT next	
	JMP block2
	
.org $1000
block2:
	CALL CRLF
	SET R1, HELP_MSG_2
next2:	
	LD R0, @R1
	OUT
	INC R1
	BGT next2
	JMP block3
	
.org $2000
block3:
	CALL CRLF
	SET R1, HELP_MSG_3
next3:	
	LD R0, @R1
	OUT
	INC R1
	BGT next3
	JMP block4
	
.org $3000
block4:
	CALL CRLF
	SET R1, HELP_MSG_4
next4:	
	LD R0, @R1
	OUT
	INC R1
	BGT next4
	JMP block5
	
.org $A000
block5:
	CALL CRLF
	SET R1, HELP_MSG_5
next5:	
	LD R0, @R1
	OUT
	INC R1
	BGT next5
	JMP block6

.org $B000
block6:
	CALL CRLF
	SET R1, HELP_MSG_6
next6:	
	LD R0, @R1
	OUT
	INC R1
	BGT next6
	JMP block7

.org $C000
block7:
	CALL CRLF
	SET R1, HELP_MSG_7
next7:	
	LD R0, @R1
	OUT
	INC R1
	BGT next7
	JMP block8

.org $D000
block8:
	CALL CRLF
	SET R1, HELP_MSG_8
next8:	
	LD R0, @R1
	OUT
	INC R1
	BGT next8
	JMP block9

.org $E000
block9:
	CALL CRLF
	SET R1, HELP_MSG_9
next9:	
	LD R0, @R1
	OUT
	INC R1
	BGT next9
	JMP block10

.org $F000
block10:
	CALL CRLF
	SET R1, HELP_MSG_10
next10:	
	LD R0, @R1
	OUT
	INC R1
	BGT next10
	CALL CRLF
	CALL CRLF
	JMP $0
	
	
.org $FF00
; Send a CR/LF pair:
;
CRLF:
	SET R1, CR
	CALL PUTC
	SET R1, LF
	CALL PUTC
	ret
	
;
; Send a single character to the serial line (a contains the character):
;
PUTC:
	LD R0, @R1;
	OUT
	RET

	
.MSFIRST
CR				.WORD $0d	; carriage return
LF				.WORD $0a	; line feed

HELP_MSG_1: .WORD "BLOCK1",EOS
HELP_MSG_2: .WORD "BLOCK2",EOS
HELP_MSG_3: .WORD "BLOCK3",EOS
HELP_MSG_4: .WORD "BLOCK4",EOS
HELP_MSG_5: .WORD "BLOCK5",EOS
HELP_MSG_6: .WORD "BLOCK6",EOS
HELP_MSG_7: .WORD "BLOCK7",EOS
HELP_MSG_8: .WORD "BLOCK8",EOS
HELP_MSG_9: .WORD "BLOCK9",EOS
HELP_MSG_10: .WORD "BLOCK10",EOS

.end	
