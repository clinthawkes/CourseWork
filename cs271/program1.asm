TITLE Program 1 (progam1.asm)

; Author: Clinton Hawkes 
; Last Modified: April 11, 2019
; OSU email address: hawkesc@oregonstate.edu
; Course number/section: CS271-400
; Project Number: Program 1       Due Date: April 14,2019
; Description: This program is used to perform elementary arithmetic operations on two numbers that are supplied
;	by the user. First an introduction and instructions are displayed and then the user is prompted to enter two numbers for the
;	calculations. After two valid numbers are entered, the program calculates the sum, difference, multiplication and integer
;	division of the numbers. The results of the calculations are displayed to the console and the user has the option to 
;	quit or repeat the program.

INCLUDE Irvine32.inc

;Include any constants here

.data

firstNum       DWORD     ?				;First number entered by user
secondNum      DWORD     ?				;Second number entered by user
addition       DWORD     ?				;Result of addition calculation
subtraction    DWORD     ?				;Result of difference calculation
multiply       DWORD     ?				;Result of multiplication calculation
quotient       DWORD     ?				;Result of quotient calculation
remainder      DWORD     ?				;Result of remainder calculation
answer         DWORD     ?				;Holds user's answer if they want to quit or continue
intro_1        BYTE      "         Elementary Arithmetic   by Clinton Hawkes", 0
instruction    BYTE      "Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder.", 0
firstNumPrpt   BYTE      "First number: ", 0
secNumPrpt     BYTE      "Second number: ", 0
goodBye        BYTE      "Impressed? Bye!", 0
plus           BYTE      " + ", 0
minus          BYTE      " - ", 0
times          BYTE      " * ", 0
divide         BYTE      " / ", 0
remain         BYTE      " remainder ", 0
equal          BYTE      " = ", 0
quit           BYTE      "Press 1 to repeat this program and start over. Press any other key to quit: ", 0
extraCredit    BYTE      "**EC: Program repeats until user chooses to quit.", 0
extraCredit2   BYTE      "**EC: Program checks if first number is larger than the second number.", 0
numProb	       BYTE	 "The first number must be larger than the second number."

.code
main PROC

;Introduction:	Displays the programmer's name and then instructs user to input two numbers 
     mov       edx, OFFSET intro_1
     call      WriteString
     call      CrLf
     mov       edx, OFFSET extraCredit
     call      WriteString
     call      CrLf
     mov       edx, OFFSET extraCredit2
     call      WriteString
     call      CrLf
J1:						;Jump location if user chooses to repeat program
     call      CrLf
     mov       edx, OFFSET instruction
     call      WriteString
     call      CrLf
     call      CrLf
  
;Get the first and second numbers from the user
J2:						;Jump location if first number is not larger than the second
     mov       edx, OFFSET firstNumPrpt
     call      WriteString
     call      ReadInt
     mov       firstNum, eax
     mov       edx, OFFSET secNumPrpt
     call      WriteString
     call      Readint
     mov       secondNum, eax
     call      CrLf

;Check if first number is larger than the second number
     mov       eax, firstNum
     cmp       secondNum, eax
     jle       Yes				;Jumps if no issues with user's input
     mov       edx, OFFSET numProb
     call      WriteString
     call      CrLf
     call      CrLf
     jmp       J2						

;Calculates the sum, difference, product, quotient and remainder  
Yes:						;Jump location if first number is larger than the second
     mov       eax, firstNum			;Beginning of sum calculation
     add       eax, secondNum
     mov       addition, eax
     mov       eax, firstNum			;Beginning of difference calculation
     sub       eax, secondNum
     mov       subtraction, eax
     mov       eax, firstNum			;Beginning of multiplication calculation
     mov       ebx, secondNum
     mul       ebx
     mov       multiply, eax
     mov       eax, firstNum			;Beginning of quotient and remainder calculation
     cdq
     mov       ebx, secondNum
     div       ebx
     mov       quotient, eax
     mov       remainder, edx

;Report results of calculations performed on the first and second numbers
     mov       eax, firstNum			;Beginning of the addition problem printing to console
     call      WriteDec
     mov       edx, OFFSET plus
     call      WriteString
     mov       eax, secondNum
     call      WriteDec
     mov       edx, OFFSET equal
     call      WriteString
     mov       eax, addition
     call      WriteDec
     call      CrLf						
     mov       eax, firstNum			;Beginning of the subtraction problem printing to console
     call      WriteDec
     mov       edx, OFFSET minus
     call      WriteString
     mov       eax, secondNum
     call      WriteDec
     mov       edx, OFFSET equal
     call      WriteString
     mov       eax, subtraction
     call      WriteDec
     call      CrLf						
     mov       eax, firstNum			;Beginning of the multiplication problem printing to console
     call      WriteDec
     mov       edx, OFFSET times
     call      WriteString
     mov       eax, secondNum
     call      WriteDec
     mov       edx, OFFSET equal
     call      WriteString
     mov       eax, multiply
     call      WriteDec
     call      CrLf					
     mov       eax, firstNum			;Beginning of the quotient/remainder problem printing to console
     call      WriteDec
     mov       edx, OFFSET divide
     call      WriteString
     mov       eax, secondNum
     call      WriteDec
     mov       edx, OFFSET equal
     call      WriteString
     mov       eax, quotient
     call      WriteDec
     mov       edx, OFFSET remain
     call      WriteString
     mov       eax, remainder
     call      WriteDec
     call      CrLf
     call      CrLf						

;Continue or quit
     mov       edx, OFFSET quit
     call      WriteString
     call      ReadInt
     cmp       eax, 1
     je        J1				;Jumps up to J1 to repeat the program if user chooses to 


;Say "Good-bye"
     call      CrLf
     mov       edx, OFFSET goodBye
     call      WriteString
    
     exit                                       ;exit to operating system
main ENDP

; (insert additional procedures here)

END main
