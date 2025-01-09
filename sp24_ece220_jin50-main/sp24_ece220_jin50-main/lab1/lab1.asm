;partners: jin50, jaypark3
; R0: Printed Letter
; R1: Original Bit
; R2: Holds the Extracted Value
; R3: The digit counter
; R4: The Memory Address of Letter in the Histogram
; R5: Shows the Current Letter
; R6: Counter for how many Letters for each bin

.ORIG x3000

AND R4, R4, #0 ; Initialize the memory address
AND R5, R5, #0 ; Initialize the current letter 
AND R6, R6, #0 ; Initiliaze the counter for the bins

LD R4, HIST_ADDR ; Loads Histogram to R4
LETTLOOP LDR R1, R5, #0 ; 
LD R0, FIRLET ; load @
ADD R0, R0, R5; move to the current letter
OUT ; Prints the current letter
AND R0, R0, #0 ; reset R
LD R0, SP ; load space
OUT ; Print Space



; Lab 1 code
AND R2, R2, #0
AND R3, R3, #0
ADD R3, R3, #4


LOOP
ADD R2, R2, R2
ADD R1, R1, #0
BRzp SHIFT
ADD R2, R2, #1

SHIFT
ADD R1, R1, R1
ADD R3, R3, #-1
BRp LOOP

ADD R0, R2, #-9
BRnz PRINT
LD R0,A
ADD R0, R0, R2
ADD R0, R0, #-10
BRnzp DONE1

PRINT
LD R0, ZERO
ADD R0, R0, R2

DONE1 OUT


AND R0, R0, #0 ; reset r0;
LD R0, NEWLINE ; loads new line
OUT ; Prints new line

ADD R4, R4, #1 ; moves to the next memory address
ADD R5, R5, #1 ; moves to next letter

AND R0, R0, #0;
ADD R0, R0, #-13;
ADD R0, R0, #-14;
ADD R0, R0, R5;
BRp LETTLOOP

HALT

NEWLINE .FILL x000A
FIRLET .FILL x0040
SP .FILL x0020

A .FILL x0041
ZERO .FILL x0030

.END
