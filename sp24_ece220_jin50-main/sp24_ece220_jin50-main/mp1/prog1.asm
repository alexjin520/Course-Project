;partners: jin50, jaypark3
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; R0: Printed Letter
; R1: Original Bit
; R2: Holds the Extracted Value
; R3: The bit counter, in the most inner loop
; R4: The Memory Address of Letter in the Histogram
; R5: Shows the Current Letter
; R6: Counter for digit, in the second most inner loop

; This program is for counting the number of letters and non-letters 
; and printing a histogram to the screen in the hexadecimal form. 
; It first prints all of the histogram bin labels, spaces,  
; and newlines, and it does the loop for each bin. 
; Then it prints a hexadecimal number from a register. This program uses 3 loops. 
; The first loop is for looping all 27 bins. Then, the second loop is supposed to loop 4 group of 4 bits, 
; and the third loop is looping through each loop in each group.

AND R4, R4, #0 ; Initialize the memory address
AND R5, R5, #0 ; Initialize the current letter 
AND R6, R6, #0 ; Initiliaze the counter for the bins

LD R4, HIST_ADDR ; Loads Histogram to R4
LETTLOOP LDR R1, R4, #0 ; Load the content of the first bin to R1
LD R0, FIRLET ; load @
ADD R0, R0, R5; move to the current letter
OUT ; Prints the current letter
AND R0, R0, #0 ; reset R
LD R0, SP ; load space
OUT ; Print Space

AND R6, R6, #0 ; digit outer
ADD R6, R6, #4 ; digit outer

OUTELOOP

; Lab 1 code
AND R2, R2, #0 ; Initialize R2 to 0
AND R3, R3, #0 ; Initialize R3 to 0
ADD R3, R3, #4 ; Add 4 to R3



LOOP
ADD R2, R2, R2 ; Left shifting R2 with 1 bit
ADD R1, R1, #0 ; Observe the highest bit of R1
BRzp SHIFT ; If the hightest bit of R1 is 0, we skip adding 1 to R2
ADD R2, R2, #1 ; Add 1 to R2

SHIFT
ADD R1, R1, R1 ; Left shifting R1 with 1 bit
ADD R3, R3, #-1 ; Decrease R3 by 1
BRp LOOP ; if there are still more bits, go back to LOOP

ADD R0, R2, #-9 ; R0 stores the result of R2-9
BRnz PRINT ; if R0 is negative or zero, load R0 with '0'
LD R0,A ; Load R0 with 'A'
ADD R0, R0, R2
ADD R0, R0, #-10 ;Decrease R0 by 10
BRnzp DONE1 ; Print

PRINT
LD R0, ZERO ; Load R0 with '0'
ADD R0, R0, R2 ; R0 stores the result of R0 + R2


DONE1 OUT

ADD R6, R6, #-1 ; Decrease R6 by 1
BRp OUTELOOP ; outer loop condition

AND R0, R0, #0 ; reset r0;
LD R0, NEWLINE ; loads new line
OUT ; Prints new line

ADD R4, R4, #1 ; moves to the next memory address
ADD R5, R5, #1 ; moves to next letter

AND R0, R0, #0 ; Initialize R0 to 0
ADD R0, R0, #-13 ; Decrease R0 by 13
ADD R0, R0, #-14 ;Decrease R0 by 14
ADD R0, R0, R5 ; Add R5 to R0
BRn LETTLOOP ; if R0 is negative, loop back 

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address


NEWLINE .FILL x000A
FIRLET .FILL x0040
SP .FILL x0020

A .FILL x0041
ZERO .FILL x0030


; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
