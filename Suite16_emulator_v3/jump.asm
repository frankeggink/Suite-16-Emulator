
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
	
.org $7000
block5:
	CALL CRLF
	SET R1, HELP_MSG_5
next5:	
	LD R0, @R1
	OUT
	INC R1
	BGT next5
	CALL CRLF
	CALL CRLF
	JMP $0
	
.org $7F00
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

.end	
