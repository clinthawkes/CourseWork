TITLE Composite Numbers (program4.asm)

; Author: Clinton Hawkes 
; Last Modified: May 7, 2019
; OSU email address: hawkesc@oregonstate.edu
; Course number/section: CS271-400
; Project Number: Program 4       Due Date: May 12, 2019
; Description: Program is used to display a user specified quantity of composite numbers to the console.
; First, the user is greeted and informed what the program is going to do. Then the user is asked to 
; specify how many composite numbers they would like printed to the console. Current range for the 
; user input is 1 - 10000. If the user enters a number outside this range, an error message will print
; and the user will be asked to enter a number within range. After a valid number is entered, the list
; of composite numbers will print to the console with 10 numbers per column and 25 rows per page.
; After all the composite numbers have been displayed, a farewell message is printed and the program ends.

INCLUDE Irvine32.inc

UPPER_LIMIT = 10000				;Constant defining upper range limit

.data

counter		DWORD	0			;Keeps track of the number of composite numbers
userNum		DWORD	0			;Storage for user input
validCode	DWORD	?			;1 = valid user input / 0 = invalid input
intro		BYTE	"Composite Numbers        Programmed by Clinton Hawkes", 0
extra1		BYTE	"** EC: Align the output columns", 0
extra2		BYTE	"** EC: Display more composites, but show them one page at a time", 0
extra3		BYTE	"** EC: Use an array of primes for better efficiency.", 0
instruct_1	BYTE	"Enter the number of composite numbers you would like to see.", 0
instruct_2	BYTE	"I'll accept orders for up to 10,000 composites.", 0
prompt		BYTE	"Enter the number of composites to display [1 .. 10000]: ", 0
error		BYTE	"Out of range. Try again.", 0
bye			BYTE	"Results certified by Clinton Hawkes. See ya later.", 0
primeNums	DWORD	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 0
testing		DWORD	4			;Stores current number being tested. Begins with first composite number, 4
column		DWORD	0			;Keeps count of current column being populated
row			DWORD	0			;Keeps count of current row being populated

.code
main PROC
	call	introduction				
	call	getUserData
	call	showComposites
	call	farewell

     exit								;exit to operating system
main ENDP

;***********************************************************************************************
;Procedure:	Displays name of program and programmer's name and instructions for user
;Receives:  intro, extra1, extra2, instruct_1, and instruct_2 are all global variables
;Returns:  nothing
;Preconditions: none 
;Registers changed: edx
;***********************************************************************************************
introduction PROC
	mov		edx, OFFSET intro			;prints title and name of programmer
	call	WriteString
	call	Crlf
	mov		edx, OFFSET extra1			;prints first extra credit message
	call	WriteString
	call	Crlf
	mov		edx, OFFSET extra2			;prints second extra credit message
	call	WriteString
	call	Crlf
	mov		edx, OFFSET extra3			;prints third extra credit message
	call	WriteString
	call	Crlf
	call	Crlf
	mov		edx, OFFSET instruct_1		;prints instructions for user
	call	WriteString
	call	Crlf
	mov		edx, OFFSET instruct_2		;specifies the max number user can enter
	call	WriteString
	call	Crlf
	call	Crlf	
	ret

introduction ENDP

;***********************************************************************************************
;Procedure:	Asks user to enter a number within the specified range. Validation procedure is 
;	then called to ensure the value is within range. 
;Receives:  prompt is a global veriable 
;Returns:  userNum is returned with a valid value 
;Preconditions:  none
;Registers changed: edx
;***********************************************************************************************
getUserData	PROC
retrieve:
	mov		edx, OFFSET prompt			;asks user to enter a number from 1 - 10000
	call	WriteString
	call	ReadDec						
	mov		userNum, eax				;stores user input in userNum variable
	call	validation					;validation procedure called to ensure number is in range
	cmp		validCode, 1					
	je		finish						;if validCode is 1, number is valid. Program continues
	jmp		retrieve					;user is asked to enter another number if validCode = 0
finish:
	ret	

getUserData ENDP

;***********************************************************************************************
;Procedure: Validates that user input is within the specified range (1-10000). If the input is	
;Receives: userNum and error are global variables. UPPER_LIMIT is a global constant 
;Returns:  validCode as a 0 or 1. 1 = valid / 0 = invalid input 
;Preconditions:  none
;Registers changed: edx
;***********************************************************************************************
validation PROC
	cmp		userNum, UPPER_LIMIT			
	jg		redo						;if user input is greater than UPPER_LIMIT, the user receives an error and validCode = 0
	cmp		userNum, 1
	jl		redo						;if user input is below 1, the user receives an error and a validCode = 0
	mov		validCode, 1
	jmp		validated					;if user input is in range, validCode = 1
redo:
	mov		edx, OFFSET error			;error message prints out telling user input is invalid
	call	WriteString
	call	Crlf
	mov		validCode, 0
validated:
	ret

validation ENDP

;***********************************************************************************************
;Procedure:	Displays the specified quantity of composite numbers for the user. Controls the 
; spacing and calls upon the isComposite procedure to print each composite number.
;Receives:  userNum, column, row are all global variables
;Returns:  nothing - prints all info to the console
;Preconditions:  userNum must be 1 - 10000
;Registers changed: eax and ecx
;***********************************************************************************************
showComposites PROC
	mov		ecx, userNum				;ecx (loop counter) is set to the number the user specified
L1:
	mov		eax, column
	cmp		eax, 10
	je		newLine						;if current column being populated is 10, a new line is inserted using newLine procedure
	mov		eax, row
	cmp		eax, 25						;if current row being populated is 25, a new page is created using newPage procedure
	je		newPage
	call	isComposite	
	loop	L1							;loop runs until the number of composites shown equals the user's entered number 
	jmp		next
newLine:
	call	Crlf
	mov		column, 0					;column is reset to 0 when a new line is entered
	inc		row							;since a new line is being populated, the row variable has increase
	jmp		L1	
newPage:
	call	WaitMsg						;pauses the console
	call	Clrscr						;clears the console screen
	mov		row, 0						;row variable is reset to 0 when a new page is created
	jmp		L1
next:
	ret

showComposites ENDP

;***********************************************************************************************
;Procedure:	Determines if the test number is a composite or prime. Prints the composite
;	and skips over the primes
;Receives: primeNums, testing 
;Returns:  counter and column and testing, all global variables
;Preconditions:  none
;Registers changed: eax, ebx, edx, esi, al 
;***********************************************************************************************
isComposite PROC
start:
	mov		esi, OFFSET primeNums		;moves starting address of primeNums array to esi
evaluate:
	mov		eax, testing
	cmp		eax, [esi]					
	jle		prime						;if testing is <= the prime divisor, no even division has occurred and the number is a prime
	mov		ebx, [esi]
	cmp		ebx, 0
	je		prime						;if the prime divisor is 0, we are at the end of the array and no even division has occured. Prime.
	mov		edx, 0
	mov		ebx, [esi]
	div		ebx
	cmp		edx, 0
	je		comp						;if edx is 0, testing was evenly divided by a prime in the array and testing is a composite
	add		esi, 4						;if no prime or composite were found with the current prime, the next prime in the array becomes the divisor
	jmp		evaluate
prime:
	inc		testing						;if a prime was found, testing is incremented so we can begin the process again to find a composite
	jmp		start
comp:
	mov		eax, testing					
	call	WriteDec					;the found composite number is printed to the console
	mov		al, 9
	call	WriteChar					;tab is printed to evenly space out the columns
	inc		testing						;number after the found composite is the next number to be tested 
	inc		counter						;number of composites found has increased
	inc		column
finished:
	ret	

isComposite ENDP

;***********************************************************************************************
;Introduction:  Prints a message stating results were certified by Clint(me). Says bye.
;Receives: bye is a global variable
;Returns:  nothing
;Preconditions:  none
;Registers changed: edx
;***********************************************************************************************
farewell PROC
	call	Crlf
	call	Crlf
	mov		edx, OFFSET bye
	call	WriteString					;parting message is printed to the console
	call	Crlf
	ret

farewell ENDP

END main
