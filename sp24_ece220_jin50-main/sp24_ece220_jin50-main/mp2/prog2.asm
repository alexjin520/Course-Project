; The following code computes the result of an arithmetic operation in postfix notation.
; The Stack Abstract Data Type (ADT) implementation has been used for this purpose.
; The code first takes the input from the user until user inputs "=".
; The code pushes all valid operand inputs from user (0 - 9) onto the stack.
; When an operator is detected, concerned operation is performed and result is added to the stack.
; Code detects errors such as underflow when performing operations & multiple values in stack at end.
; In case of such errors, a message is displayed on monitor indicating that expression is invalid.


; R0 - Output of PUSH/ POP subroutine -&- Input address for string to be printed
; R1 - Error Return Value (0 - success ; 1 - error; -1 - end) for EVALUATE subroutine
; R3 - Input Value provided to PRINT_HEX subroutine
; R5 - Error Return Value (0 - success ; 1 - error) for POP/ PUSH subroutine
; R6 - Error Return Value (0 - success ; 1 - error) for PRINT_HEX subroutine


.ORIG x3000

GET_CHAR
	GETC			; Take input from user
	OUT			; Print input to monitor
	AND R1, R1, #0		; Clear value stored in R1
	JSR EVALUATE		; Call sub-routine EVALUATE
	ADD R1, R1, #0		; Update CC with return value of EVALUATE subroutine
	BRz GET_CHAR		; If there are no errors, take next input from user
	BRp PRINT_INVALID	; If return value is 1, skip to display of error message		


PRINT_INVALID
	LEA R0, INVALID_EXP	; Load starting address of ASCII string with error message
	PUTS			; Print the error message on the monitor
	BRnzp DONE		; Halt the code

INVALID_EXP	.STRINGZ "Invalid Expression"	; Error message to be printed on monitor


DONE
	HALT			;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; R0 will contain the digit that will be displayed on the screen
; R1 will be the digit counter
; R2 will be bit counter used to compute hexadecimal number for corresponding 4-bits
; R3 contains the value to be printed in hexadecimal numbers on the monitor
; R4 contains decimal value corresponding to ASCII '0' or ASCII 'A'-10
; R6 - Error Return Value (0 - success ; 1 - error) for PRINT_HEX subroutine

PRINT_HEX
	ST R0, PRINTHEX_SaveR0	; Store value of R0 before executing subroutine
	ST R1, PRINTHEX_SaveR1	; Store value of R1 before executing subroutine
	ST R2, PRINTHEX_SaveR2	; Store value of R2 before executing subroutine
	ST R3, PRINTHEX_SaveR3	; Store value of R3 before executing subroutine
	ST R4, PRINTHEX_SaveR4	; Store value of R4 before executing subroutine
	ST R5, PRINTHEX_SaveR5	; Store value of R5 before executing subroutine
	ST R7, PRINTHEX_SaveR7	; Store value of R7 before executing subroutine

CHECK_STACK
	AND R6, R6, #0		; Clear value stored in R6
	LD R1, STACK_TOP	; Load address of stack pointer
	NOT R1, R1		; Compute additive inverse of stack pointer address
	ADD R1, R1, #1		; Compute additive inverse of stack pointer address
	LD R2, STACK_START	; Load starting address of stack
	ADD R1, R1, R2		; Compute difference between stack start address & pointer address
	BRz PRINT_INIT		; Print result is stack contains single value
	ADD R6, R6, #1		; If there are multiple values, return an error message
	BRnzp PRINT_HEX_DONE	; Skip to termination of subroutine

PRINT_INIT
		AND	R1, R1, #0	;Clear value stored in R1 digit counter
		ADD	R1, R1, #4	;Set digit counter to 4

NextHex		BRnz	PRINT_HEX_DONE	;Skip to end if all 4-digits are printed
		AND	R0, R0, #0	;Clear hex-digit to be printed
		AND	R2, R2, #0	;Clear value of bit counter
		ADD	R2, R2, #4	;Set bit counter to 4

ComputeHex	ADD	R0, R0, R0	;Left-shift to make space for next bit
		ADD	R3, R3, #0	;Set condition codes for value of R3
		BRzp	ZeroBit		;Skip the addition if MSB is 0
		ADD	R0, R0, #1	;Add #1 to the decimal code of hex-value to be printed
ZeroBit		ADD	R3, R3, R3	;Left-shift given value to update MSB
		ADD	R2, R2, #-1	;Decrement bit-counter
		BRp	ComputeHex	;Check for single hexadecimal digit completion
		
		ADD	R2, R0, #-9	;Set condition codes for value of R0 to be printed
		BRnz	AddZero		;Skip addition of #55 if value of R0 is ess than 9
		LD	R4, Alphabet	;Store decimal value corresponding to ASCII 'A'-10					
		BRnzp	PrintHex	;Skip to printing of hexadecimal digit
AddZero		LD	R4, Number	;Store decimal value corresponding to ASCII '0'

PrintHex	ADD	R0, R0, R4	;Compute decimal value of ASCII character to be printed	
		OUT			;Display the computed hexadecimal digit
		ADD	R1, R1, #-1	;Decrement digit counter by 1
		BRnzp	NextHex		;Skip to computation of next hexadecimal digit

PRINT_HEX_DONE
	LD R0, PRINTHEX_SaveR0	; Reload the initial value of R0 in main code
	LD R1, PRINTHEX_SaveR1	; Reload the initial value of R1 in main code	
	LD R2, PRINTHEX_SaveR2	; Reload the initial value of R2 in main code
	LD R3, PRINTHEX_SaveR3	; Reload the initial value of R3 in main code
	LD R4, PRINTHEX_SaveR4	; Reload the initial value of R4 in main code
	LD R5, PRINTHEX_SaveR5	; Reload the initial value of R5 in main code
	LD R7, PRINTHEX_SaveR7	; Reload the initial value of R7 in main code
	RET

PRINTHEX_SaveR0	.BLKW #1	; Location where R0 is stored before execution
PRINTHEX_SaveR1	.BLKW #1	; Location where R1 is stored before execution
PRINTHEX_SaveR2	.BLKW #1	; Location where R2 is stored before execution
PRINTHEX_SaveR3	.BLKW #1	; Location where R3 is stored before execution
PRINTHEX_SaveR4	.BLKW #1	; Location where R4 is stored before execution
PRINTHEX_SaveR5	.BLKW #1	; Location where R5 is stored before execution
PRINTHEX_SaveR7	.BLKW #1	; Location where R7 is stored before execution

Number		.FILL 	x0030		;Decimal value corresponding to ASCII '0'
Alphabet	.FILL	x0037		;Decimal value corresponding to ASCII 'A'-10


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; R0 - Character input from keyboard
; R1 - Error Return Value (0 - success ; 1 - error; -1 - end) for EVALUATE subroutine
; R2 - Temporary register to check for valid operand & operator
; R5 - Error Return Value (0 - success ; 1 - error) for POP/ PUSH subroutine 

EVALUATE
	ST R0, EVALUATE_SaveR0	; Store value of R0 before executing subroutine	
	ST R2, EVALUATE_SaveR2	; Store value of R2 before executing subroutine
	ST R3, EVALUATE_SaveR3	; Store value of R3 before executing subroutine
	ST R4, EVALUATE_SaveR4	; Store value of R4 before executing subroutine
	ST R5, EVALUATE_SaveR5	; Store value of R5 before executing subroutine
	ST R6, EVALUATE_SaveR6	; Store value of R6 before executing subroutine
	ST R7, EVALUATE_SaveR7	; Store value of R7 before executing subroutine
	
	LD R2, EQUAL_SIGN	; Check if the input character is "="
	ADD R2, R2, R0		;
	BRz EVAL_EQUAL		;
	
	LD R2, SPACE_CHAR	; Check if the input character is ASCII SPACE
	ADD R2, R2, R0		;
	BRz EVAL_DONE		;
	
	LD R2, ZERO_CHAR	; Check if the input character is "0"
	ADD R2, R2, R0		;
	BRz ACCEPT_CHAR		; Accept character if it is "0"
	BRn CHECK_OPERATOR	; If ASCII value less than "0", check for operator
	LD R2, NINE_CHAR	; Check if the input character is between "0" & "9"
	ADD R2, R2, R0		;
	BRnz ACCEPT_CHAR	; Accept character if it is between "0" to "9"

CHECK_OPERATOR
	JSR POP			; Check if stack has at least 1 operand
	ADD R5, R5, #0		;
	BRp INVALID_CHAR_CHECK	; If there is underflow, skip to display of error message
	ADD R4, R0, #0		;
	
	JSR POP			; Check if stack has at least 2 operands
	ADD R5, R5, #0		;
	BRp INVALID_CHAR_CHECK	; If there is underflow, skip to display of error message
	ADD R3, R0, #0		;

	LD R0, EVALUATE_SaveR0	; Load input value from user in R0
	
	LD R2, PLUS_CHAR	; Check if input character is "+"
	ADD R2, R2, R0		;
	BRz EVAL_PLUS		;
	
	LD R2, MINUS_CHAR	; Check if input character is "-"
	ADD R2, R2, R0		;
	BRz EVAL_MIN		;

	LD R2, MUL_CHAR		; Check if input character is "*"
	ADD R2, R2, R0		;
	BRz EVAL_MUL		;

	LD R2, DIV_CHAR		; Check if input character is "/"
	ADD R2, R2, R0		;
	BRz EVAL_DIV		;

	LD R2, EXP_CHAR		; Check if input character is "^"
	ADD R2, R2, R0		;
	BRz EVAL_EXP		;

INVALID_CHAR_CHECK
	ADD R1, R1, #1		; Load R1 with error return value of 1
	BRnzp EVAL_DONE		; Exit subroutine

ACCEPT_CHAR
	LD R2, ZERO_CHAR	; Compute decimal value of input operand
	ADD R0, R0, R2		;
	JSR PUSH		; Add the operand to the stack
	BRnzp EVAL_DONE		; Exit subroutine

EVAL_PLUS
	AND R0, R0, #0		; Reset output register of PLUS subroutine
	JSR PLUS		; Compute addition of concerned operands
	JSR PUSH		; Push the result to the stack
	BRnzp EVAL_DONE		;

EVAL_MIN
	AND R0, R0, #0		; Reset output register of MINUS subroutine
	JSR MIN			; Compute the difference between concerned operands
	JSR PUSH		; Push the result to the stack
	BRnzp EVAL_DONE		;

EVAL_MUL
	AND R0, R0, #0		; Reset output register of MUL subroutine
	JSR MUL			; Compute product of concerned operands
	JSR PUSH		; Push result to the stack
	BRnzp EVAL_DONE		;

EVAL_DIV
	AND R0, R0, #0		; Reset output register of DIV subroutine
	JSR DIV			; Compute the quotient obtained from division of operands
	JSR PUSH		; Push result to the stack
	BRnzp EVAL_DONE		;

EVAL_EXP
	AND R0, R0, #0		; Reset output register of EXP subroutine
	JSR EXP			; Compute the concerned exponent
	JSR PUSH		; Push the result to the stack
	BRnzp EVAL_DONE		;

EVAL_EQUAL
	ADD R1, R1, #-1		; Return code end value of -1

EVAL_DONE
	LD R0, EVALUATE_SaveR0	; Reload the initial value of R0 in main code	
	LD R2, EVALUATE_SaveR2	; Reload the initial value of R2 in main code
	LD R3, EVALUATE_SaveR3	; Reload the initial value of R3 in main code
	LD R4, EVALUATE_SaveR4	; Reload the initial value of R4 in main code
	LD R5, EVALUATE_SaveR5	; Reload the initial value of R5 in main code
	LD R6, EVALUATE_SaveR6	; Reload the initial value of R6 in main code
	LD R7, EVALUATE_SaveR7	; Reload the initial value of R7 in main code
	RET			; Return back to main code

EVALUATE_SaveR0	.BLKW #1	; Location where R0 is stored before execution
EVALUATE_SaveR2	.BLKW #1	; Location where R2 is stored before execution
EVALUATE_SaveR3	.BLKW #1	; Location where R3 is stored before execution
EVALUATE_SaveR4	.BLKW #1	; Location where R4 is stored before execution
EVALUATE_SaveR5	.BLKW #1	; Location where R5 is stored before execution
EVALUATE_SaveR6	.BLKW #1	; Location where R6 is stored before execution
EVALUATE_SaveR7	.BLKW #1	; Location where R7 is stored before execution

EQUAL_SIGN	.FILL xFFC3	; Additive inverse of ASCII "="
SPACE_CHAR	.FILL xFFE0	; Additive inverse of ASCII SPACE
ZERO_CHAR	.FILL xFFD0	; Additive inverse of ASCII "0"
NINE_CHAR	.FILL xFFC7	; Additive inverse of ASCII "9"
PLUS_CHAR	.FILL xFFD5	; Additive inverse of ASCII "+"
MINUS_CHAR	.FILL xFFD3	; Additive inverse of ASCII "-"
MUL_CHAR	.FILL xFFD6	; Additive inverse of ASCII "*"
DIV_CHAR	.FILL xFFD1	; Additive inverse of ASCII "/"
EXP_CHAR	.FILL xFFA2	; Additive inverse of ASCII "^"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Input - R3, R4
; Out - R0

PLUS	
	ADD R0, R3, R4		; Add the two operands
	RET			; Exit subroutine
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Input R3, R4
; Out R0

MIN	
	ST R4, MIN_SaveR4	; Store the value of R4 before execution
	NOT R4, R4		; Compute additive inverse of second operand
	ADD R4, R4, #1		; Compute additive inverse of second operand
	ADD R0, R3, R4		; Compute difference between the operands
	LD R4, MIN_SaveR4	; Reload the initial value of R4 in main code
	RET			; Exit subroutine

MIN_SaveR4	.BLKW #1	; Location where R4 value is stored
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Input R3, R4
; Output R0
; R4 - Multiplication counter

MUL	
	ST R4, MUL_SaveR4	; Store the value of R4 before execution
	ADD R4, R4, #0		; Update CC with value of multiplication counter
	BRzp MUL_LOOP		; Flip the signs of both operands if counter operand is negative
	NOT R3, R3		; 
	NOT R4, R4		;
	ADD R3, R3, #1		;
	ADD R4, R4, #1		;
MUL_LOOP	
	ADD R4, R4, #-1		; Decrement multiplication counter
	BRn MUL_DONE		; Check for completion of operation
	ADD R0, R3, R0		; Update output by adding value of first operand to result
	BRnzp MUL_LOOP		; Repeat the multiplication loop until completion
MUL_DONE	
	LD R4, MUL_SaveR4	; Reload the initial value of R4 in main code
	RET			; Exit subroutine

MUL_SaveR4	.BLKW #1	; Location where R4 value is stored
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Input R3, R4
; Output R0

DIV	
	ST R3, DIV_SaveR3	; Store the value of R3 before execution
	ST R4, DIV_SaveR4	; Store the value of R4 before execution
	NOT R4, R4		; Compute additive inverse of divisor operand
	ADD R4, R4, #1		;
DIV_LOOP		
	ADD R3, R3, R4		; Subtract divisor from dividend
	BRn DIV_DONE		; Check for completion of division
	ADD R0, R0, #1		; Increment quotient by 1
	BRnzp DIV_LOOP		; Repeat division loop until completion
DIV_DONE
	LD R3, DIV_SaveR3	; Reload the value of R3 in main code
	LD R4, DIV_SaveR4	; Reload the value of R4 in main code
	RET			;	

DIV_SaveR3	.BLKW #1	; Location where R3 value is stored
DIV_SaveR4	.BLKW #1	; Location where R4 value is stored
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Input R3, R4
; Output R0
; R5 - exponent counter
; R7 - stores program counter of main code

EXP
	ST R3, EXP_SaveR3	; Store the value of R3 before execution
	ST R4, EXP_SaveR4	; Store the value of R4 before execution
	ST R5, EXP_SaveR5	; Store the value of R5 before execution
	ST R7, EXP_SaveR7	; Store the value of R7 before execution
EXP_CHECK
	ADD R5, R4, #0		; Load exponent counter with exponent operand
	BRp EXP_INIT		; Initialise exponent loop is exponent is positive
	ADD R0, R0, #1		; Return Output = 1 if exponent operand is 0
	BRnzp EXP_DONE		; Terminate subroutine
EXP_INIT
	ADD R0, R3, #0		; Add base operand to result
EXP_LOOP
	ADD R5, R5, #-1		; Decrement exponent counter
	BRz EXP_DONE		; Check for completion of operation
	ADD R4, R0, #0		; Load second input operand of multiplication with result
	AND R0, R0, #0		; Clear existing value of result
	JSR MUL			; Call MUL subroutine
	BRnzp EXP_LOOP		; Repeat exponent loop until completion
EXP_DONE
	LD R3, EXP_SaveR3	; Reload the initial value of R3 in main code
	LD R4, EXP_SaveR4	; Reload the initial value of R4 in main code
	LD R5, EXP_SaveR5	; Reload the initial value of R5 in main code
	LD R7, EXP_SaveR7	; Reload the initial value of R7 in main code
	RET			; Exit subroutine
		
EXP_SaveR3	.BLKW #1	; Location where R3 value is stored
EXP_SaveR4	.BLKW #1	; Location where R4 value is stored
EXP_SaveR5	.BLKW #1	; Location where R5 value is stored
EXP_SaveR7	.BLKW #1	; Location where R7 value is stored
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END

