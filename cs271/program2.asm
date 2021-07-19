TITLE Fibonacci Numbers (progam2.asm)

; Author: Clinton Hawkes 
; Last Modified: April 16, 2019
; OSU email address: hawkesc@oregonstate.edu
; Course number/section: CS271-400
; Project Number: Program 2       Due Date: April 21,2019
; Description: This program is used to output a user defined amount of Fibonacci numbers. First the program
;	prints out the name of the program and the name of the person who programmed it. Then the user is asked
;	to type in their name to become acquainted. Next, the user is asked how many terms of the Fibonacci
;	sequence they want printed on the screen. If the number entered is greater than 46 or less than 1, the
;	user is prompted to re-enter a number between 1 and 46. After the user enters a valid number, the program
;	prints out the Fibonacci terms neatly aligned in 5 columns. Program then prints a statement informing
;	the user who certified the results to be correct, and then prints a personalized parting message to the 
;	user.

INCLUDE Irvine32.inc

MAX_RANGE = 46					;Constant defining max number Fibonacci terms allowed

.data

counter		DWORD	0			;Keeps track of number of Fibonacci terms per line
terms		DWORD	?			;Number of Fibonacci terms user wants printed
rows		DWORD	?			;Identifies rows that need different spacing for extra credit
firstNum	DWORD	1			;Storage for first number in Fibonacci calculation
secondNum	DWORD	0			;Storage for second number in Fibonacci calculation
sum			DWORD	?			;Storage for sum of first and second numbers for output
userName	BYTE	26 DUP(0)	;Storage for user's name
intro_1		BYTE	"Fibonacci Numbers", 0
intro_2		BYTE	"Programmed by Clinton Hawkes.", 0
extraCred	BYTE	"***EC: Numbers are displayed in aligned columns.", 0
prompt_1	BYTE	"What's your name? ", 0
hello		BYTE	"Hello, ", 0
exclaim		BYTE	"!", 0
instruct_1	BYTE	"Enter the number of Fibonacci terms to be displayed.", 0
instruct_2	BYTE	"Give the number as an integer in the range [1 .. 46]", 0
prompt_2	BYTE	"How many Fibonacci terms do you want? ", 0
error		BYTE	"Out of range. Enter a number in [1 .. 46].", 0
spaces		BYTE	"     ", 0
cert		BYTE	"Results certified by Clinton Hawkes.", 0
bye			BYTE	"Nice to meet you, ", 0



.code
main PROC

;Introduction:	Displays name of program and programmer's name
		mov		edx, OFFSET intro_1
		call	WriteString
		call	Crlf
		mov		edx, OFFSET intro_2
		call	WriteString
		call	Crlf
		mov		edx, OFFSET extraCred
		call	WriteString
		call	Crlf
		call	Crlf
	
;User Instructions:	 Asks user to enter their name and then informs user what is going to happen
		mov		edx, OFFSET prompt_1
		call	WriteString
		mov		edx, OFFSET userName
		mov		ecx, SIZEOF userName
		call	ReadString
		mov		edx, OFFSET hello
		call	WriteString
		mov		edx, OFFSET	userName
		call	WriteString
		mov		edx, OFFSET exclaim
		call	WriteString
		call	Crlf
		mov		edx, OFFSET instruct_1
		call	WriteString
		call	Crlf
		mov		edx, OFFSET	instruct_2
		call	WriteString
		call	Crlf
		call	Crlf
		jmp		cont				;Jumps to next section(needed to skip error checking loop)

;Get user data:  Asks user how many Fibonacci terms they want and validates number to be 1 - 46
err:
		mov		edx, OFFSET error	;Tells user to input a correct number
		call	WriteString
		call	Crlf
cont:
    	mov		edx, OFFSET prompt_2
		call	WriteString
		call	ReadInt
		mov		terms, eax
		mov 	rows, eax
		sub		rows, 35
		mov		ebx, MAX_RANGE
		cmp		ebx, eax
		jge		nextTest			;Jumps to minimum validation if first test is passed
		jmp		err					;Jumps to err if user input was above max allowed
nextTest:
		cmp		eax, 0
		jle		err					;Jumps to err if user input is below 1
		
;Calculates and displays the fibonacci numbers
		mov		ecx, terms			;Sets the loop counter to user specified number
iterate:
		mov		eax, secondNum
		mov		sum, eax
		mov		eax, firstNum
		add		sum, eax
		mov		eax, sum
		call	WriteDec			;Prints the sum of the (current) first and second numbers
		mov		ebx, secondNum
		mov		secondNum, eax
		mov		firstNum, ebx
		mov		al, 9				;Puts tab in register
		call	WriteChar			;Prints out tab for column alignment
		cmp		ecx, rows			;Compares counter to row variable
		jg		tabs				;If counter is greater than the row variable, jumps to tabs:
fixed:
		inc		counter					
		cmp		counter, 5
		je		newLine				;If counter is 5, jump to newLine:
goBack:
		loop	iterate	
		jmp		farewell			;Jumps to farewell message after loop is done.
newLine:
		call	Crlf				;Adds a carriage return if counter is 5
		mov		counter, 0			;Resets counter to zero
		jmp		goBack
tabs:
		mov		al, 09				;Adds an additional tab to all 1 - 35 Fibonacci terms 
		call	WriteChar
		jmp		fixed

;Farewell to the user: Prints a personalized farewell to user
farewell:
		call	Crlf
		call	Crlf
		mov		edx, OFFSET cert
		call	WriteString
		call	Crlf
		mov		edx, OFFSET bye
		call	WriteString
		mov		edx, OFFSET userName
		call	WriteString
		mov		edx, OFFSET exclaim
		call	WriteString
		call	Crlf
    
     exit								;exit to operating system
main ENDP

; (insert additional procedures here)

END main
