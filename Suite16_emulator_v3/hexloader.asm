;
; Constant definitions
;
loader_start	.equ	$0			; hexloader starts here
program_start	.equ	$0300		; hexloader jumps to here when done loading
eos				.equ	$0000		; end of string

.org	loader_start

starting_addr:
; Print a welcome message
	SET R1, hello_msg
	CALL puts
	CALL crlf
	SET R0, 62				; > cursor
	OUT						; Print cursor
	
get_colon:	
	; zero checksum
	SET R14, 0				; used to hold checksum
	; get first character 
	IN						; getchar
	SET R1, 512
	LD R0, @R1				; get character
	
	
	SET R1, 58				; ':' char
	SUB R1
	BNE get_colon

	; READ LENGTH
	call getbyte
	; value is in R7
	LD R0, R7
	ST R10, R0				; store in R[10]
	
	; READ ADDRESS
	call getword
	; value is in R7
	LD R0, R7
	ST R11, R0				; store in R[11]
	
	; CALCULATE ADDRESS IN WORDS (16-bit)
	LD R0, R11				; put address in R0
	CALL divide_by_two
	; value is in R2
	LD R0, R2
	ST R12, R0				; divided value in R[12]
	
	; READ RECORD TYPE
	call getbyte
	; value is in R7
	LD R0, R7
	ST R13, R0;				; store in R[13]
	
	; R[10] = length in bytes
	; R[11] = address
	; R[12] = address in words 
	; R[13] = record type 
	
	SET R1, 1				; record type 01
	ST R7, R0				; store for later
	SUB R1					; check if type is 01
	BEQ endload				; record type is 01 (EOF), we are done_msg
	LD R0, R7				; get value back
	BGT invalid				; check if greater than zero (and not 01)

read_data:	
	; this is a data byte
msb_part:
	call getbyte
	; value is in R7
	LD R0, R7				; get byte in R0
	ADD R0					; shift
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ST @R12, R0				; store at memory address
	
lsb_part:
	call getbyte
	; value is in R7
	LD R0, @R12				; get what is in memory
	OR R7					; OR lsb into it
	ST @R12, R0				; store at memory address
	
	INC R12					; next memory address
	
	;decrement 2x
	DEC R10					; decrement 
	DEC R10					; decrement 
	
	LD R0, R10				; get length
	BGT read_data			; 
	
	; GET LAST BYTE
	call getbyte			; get checksum byte
	
	; CHECK CHECKSUM
	LD R0, R14				; get checksum byte
	SET R1, $00FF
	AND R1
	BNE checksum_error
	
	call crlf
	SET R0, 62				; > cursor
	OUT						; Print cursor
	BRA get_colon
	
	JMP loop				 ; TODO check
	
invalid:
	call crlf
	SET R1, invalid_msg
	call puts
	call crlf
	BRA starting_addr
	
endload:
	call getbyte			; get last checksum byte

	LD R0, R14				; get checksum byte
	SET R1, $00FF
	AND R1
	BNE checksum_error
	call crlf
	SET R1, done_msg
	call puts
	call crlf
	call crlf

	; jump to fixed memory location (loaded program)
	; loader program has to start at location "program_start" for now
	JMP program_start
	
checksum_error:
	call crlf
	SET R1, error_msg
	call puts
	call crlf
	BRA starting_addr

divide_by_two:
	; R0 should contain value to divide
big_address:
	SET R2, 0 ; clear result
	BGE small_address
	; signed to unsigned trick
	SET R1, $8000
	SET R2, $4000
	SUB R1
; normal part	
small_address	
	SET R1, 2
divide_more	
	SUB R1
	BLT divide_done
	INC R2
	BRA divide_more
divide_done:
	RET
	
	; program should never get here !!!
loop:
	BRA loop
;
; Message definitions
;
.MSFIRST
hello_msg		.WORD	"Suite16 Hex Loader", eos
error_msg		.WORD	"Checksum error", eos
invalid_msg		.WORD	"Invalid record type", eos
done_msg		.WORD	"Done loading", eos

;
; 
;
getnibble:
	IN				; read char from serial in
	SET R1, 512
	LD R0, @R1		; get character
	SBI $30		
	ST R2, R0		; save temporary
	SBI 10
	BLT decimal
	LD R0, R2		; restore value
	SBI 7
	BRA hexadecimal
decimal:	
	LD R0, R2		; restore value
hexadecimal:	
	ST R7, R0		; value is stored in R7
	RET
	
;
;
;
getbyte:
	call getnibble
	LD R0, R7
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ST R8, R0		; temporary store msb 
	call getnibble
	LD R0, R7		; get back lsb
	OR R8			; create word value
	ST R7, R0		; value is stored in R7
	
	; store byte for checksum
	LD R0, R14		; load checksum
	ADD R7			; add byte to checksum
	ST R14, R0
	
	RET

getword:
	call getbyte
	LD R0, R7
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ADD R0
	ST R9, R0		; CHECK IF NEEDED
	call getbyte
	LD R0, R7		; get back lsb ???
	OR R9
	ST R7, R0
	RET
	
;
; Send a string to the serial line, HL contains the pointer to the string:
;
puts:
	CALL putc
	INC R1
	BGT puts
	RET

; Send a CR/LF pair:
;
crlf:
	SET R1, cr
	call    putc
	SET R1, lf
	call    putc
	ret

;
; Send a single character to the serial line (a contains the character):
;
putc:
	LD R0, @R1;
	OUT
	RET


.MSFIRST
cr				.WORD $0d	; carriage return
lf				.WORD $0a	; line feed
space			.WORD $20	; space

.end