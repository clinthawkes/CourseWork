TITLE Integer Accumulator (progam3.asm)

; Author: Clinton Hawkes 
; Last Modified: May 4, 2019
; OSU email address: hawkesc@oregonstate.edu
; Course number/section: CS271-400
; Project Number: Program 3       Due Date: May 5, 2019
; Description: Program is used to gather a list of negative numbers between -100 and -1, 
; sum the numbers entered, calulate the rounded average, and then display the results to
; the user. First, the user is asked to provide their name for a personal touch. After
; the user's name is entered, they are given instructions about the numbers they are 
; allowed to enter, and how they can exit/display results by entering a non-negative 
; number. After all the numbers the user wants to enter are entered, the quantity of
; numbers entered, the sum, the rounded average, and the floating point average are 
; displayed. A final personalized farewell message is displayed to the user before the
; program terminates.

INCLUDE Irvine32.inc

LOWER_BOUND = -100				;Constant defining lower bound

.data

counter		DWORD	0			;Keeps track of the number of user entries
line		DWORD	1			;Variable used to number user input
userNum		SDWORD	0			;Storage for user input
sum			SDWORD	0			;Storage for sum of first and second numbers for output
average		SDWORD	0			;Used to store rounded average
remainder	SDWORD	0			;Used to store remainder
userName	BYTE	26 DUP(0)	;Storage for user's name
intro_1		BYTE	"Welcome to the Integer Accumulator by Clinton Hawkes", 0
prompt_1	BYTE	"What's your name? ", 0
extra1		BYTE	"** EC: Number lines during user input", 0
extra2		BYTE	"** EC: Display average as a floating point", 0
hello		BYTE	"Hello, ", 0
exclaim		BYTE	"!", 0
instruct_1	BYTE	"Please enter numbers in [-100, -1].", 0
instruct_2	BYTE	"Enter a non-negative number when you are finished to see results.", 0
number		BYTE	". Enter number: ", 0
error		BYTE	"Out of range. Enter a number in [-100, -1].", 0
validNums	BYTE	"You entered ", 0
validNums2	BYTE	" valid numbers.", 0
sumResult	BYTE	"The sum of your valid numbers is ", 0
avgResult	BYTE	"The rounded average is ", 0
void		BYTE	"I guess you don't have time right now.", 0
bye			BYTE	"Thank you for playing! It's been a pleasure meeting you, ", 0
thousand	DWORD	1000
pointA		DWORD	?			;Stores decimal portion of float
decimal		BYTE	".", 0
EC2			BYTE	"Average displayed as a float is ", 0

.code
main PROC

;Introduction:	Displays name of program and programmer's name
		mov		edx, OFFSET intro_1
		call	WriteString
		call	Crlf
		mov		edx, OFFSET extra1					;Display extra credit message notifying TA
		call	WriteString
		call	Crlf
		mov		edx, OFFSET extra2					;Display next extra credit message to TA 
		call	WriteString
		call	Crlf
		call	Crlf
		mov		edx, OFFSET prompt_1 
		call	WriteString
		mov		edx, OFFSET userName				;Retrieves name from user
		mov		ecx, SIZEOF userName
		call	ReadString
		mov		edx, OFFSET hello
		call	WriteString
		mov		edx, OFFSET userName
		call	WriteString
		call	Crlf
		call	Crlf
	
;User Instructions:	Asks user to enter numbers between -100 and -1, and to enter any non-negative number to see results
		mov		edx, OFFSET instruct_1
		call	WriteString
		call	Crlf
		mov		edx, OFFSET instruct_2
		call	WriteString
		call	Crlf
		call	Crlf
		jmp		input

;Get user data for program 
LB:
		mov		edx, OFFSET error					;Ask user to enter a number within range if prior number was not
		call	WriteString
		call	Crlf
input:
		mov		eax, line
		call	WriteDec
		mov		edx, OFFSET number					;Ask user to enter a number
		call	WriteString
		call	ReadInt
		mov		userNum, eax
		cmp		userNum, 0
		jge		pos									;If positive number entered, start calculations
		cmp		userNum, LOWER_BOUND 
		jl		LB									;If number out of bounds, re-enter the number
		push	userNum
		inc		counter
		inc		line
		jmp		input								;Jumps to revtrieve next input

;Calculates the sum, rounded average and the floating point average
pos:
		cmp		counter, 0
		je		empty
		mov		ecx, counter						;Calculate the sum
plus:
		pop		eax
		add		sum, eax
		loop	plus
		mov		eax, sum							;Calculate the rounded average
		cdq
		idiv	counter
		mov		average, eax
		mov		remainder, edx
		fild	remainder							;Calcuate the float number
		fidiv	counter
		fimul	thousand
		fchs
		fist	pointA
		jmp		result								;Jumps to display results after calculations


;Displays results of calculations
empty:			
		mov		edx, OFFSET void					;Called if no negative numbers entered by user
		call	WriteString
		jmp		farewell

result:	
		call	Crlf
		mov		edx, OFFSET validNums				;Displays number of valid inputs
		call	WriteString
		mov		eax, counter
		call	WriteDec
		mov		edx, OFFSET validNums2
		call	WriteString
		call	Crlf
		mov		edx, OFFSET sumResult				;Display sum of numbers entered
		call	WriteString
		mov		eax, sum
		call	WriteInt
		call	Crlf
		mov		edx, OFFSET avgResult				;Display rounded average of numbers entered
		call	WriteString
		mov		eax, average 
		call	WriteInt
		call	Crlf
		mov		edx, OFFSET EC2						;Display average as a floating point
		call	WriteString
		mov		eax, average
		call	WriteInt
		mov		edx, OFFSET decimal
		call	WriteString
		mov		eax, pointA
		call	WriteDec

		
;Farewell to the user: Prints a personalized farewell to user
farewell:
		call	Crlf
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
