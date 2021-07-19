TITLE Sorting Random Integers (program5.asm)

; Author: Clinton Hawkes 
; Last Modified: May 17, 2019
; OSU email address: hawkesc@oregonstate.edu
; Course number/section: CS271-400
; Project Number: Program 5       Due Date: May 26, 2019
; Description: Program is used to display a user specified quantity of composite numbers to the console.

INCLUDE Irvine32.inc

;Constants
	
MIN = 10				;Minimum quantity of numbers to be generated
MAX = 200				;Maximum quantity of numbers to be generated
LO = 100				;Lower bound of random range
HI = 999				;Upper bound of random range

.data

request		DWORD	?			;Storage for user input
intro		BYTE	"Sorting Random Integers             Programmed by Clinton Hawkes", 0
instruct_1	BYTE	"This program generates random numbers in the range [", 0
instruct_2	BYTE	"displays the original list, sorts the list, and calculates the", 0
instruct_3	BYTE	"median value. Finally, it displays the list sorted in descending order.", 0
prompt_1	BYTE	"Enter the number of integers to be generated. [", 0
dots		BYTE	" .. ", 0
bracket_1	BYTE	"]: ", 0
bracket_2	BYTE	"], ", 0
error		BYTE	"Out of range. Try again.  ", 0
list_prior	BYTE	"The unsorted random numbers:", 0
median		BYTE	"The median is ", 0
list_after	BYTE	"The sorted list:", 0
array		DWORD	MAX DUP(?)	
col			DWORD	10			;Number of columns per row

.code
main PROC
	call	Randomize

	push	OFFSET intro
	push	OFFSET instruct_1
	push	OFFSET dots
	push	OFFSET bracket_2
	push	OFFSET instruct_2
	push	OFFSET instruct_3
	call	introduction	

	push	OFFSET request
	push	OFFSET prompt_1
	push	OFFSET dots
	push	OFFSET bracket_1
	push	OFFSET error
	call	getData

	push	request
	push	OFFSET array
	call	fillArray

	push	col
	push	OFFSET array
	push	request
	push	OFFSET list_prior
	call	displayList

	push	request
	push	OFFSET array
	call	sortList
	
	push	OFFSET median
	push	request	
	push	OFFSET array
	call	displayMedian
	
	push	col
	push	OFFSET array
	push	request
	push	OFFSET list_after
	call	displayList

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
	push	ebp
	mov		ebp, esp
	mov		edx, [ebp+28]
	call	WriteString
	call	CrLf
	call	CrLf
	mov		edx, [ebp+24]
	call	WriteString
	mov		eax, LO
	call	WriteDec
	mov		edx, [ebp+20]
	call	WriteString
	mov		eax, HI
	call	WriteDec
	mov		edx, [ebp+16]
	call	WriteString
	call	CrLf
	mov		edx, [ebp+12]
	call	WriteString
	call	CrLf
	mov		edx, [ebp+8]
	call	WriteString
	call	CrLf
	call	CrLf
	pop		ebp

	ret 24

introduction ENDP

;***********************************************************************************************
;Procedure:	Asks user to enter a number within the specified range. Validation procedure is 
;	then called to ensure the value is within range. 
;Receives:  prompt is a global veriable 
;Returns:  userNum is returned with a valid value 
;Preconditions:  none
;Registers changed: edx
;***********************************************************************************************
getData	PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 4
	mov		edx, [ebp+20]
	call	WriteString
	mov		eax, MIN
	call	WriteDec
	mov		edx, [ebp+16]
	call	WriteString
	mov		eax, MAX
	call	WriteDec
	mov		edx, [ebp+12]
	call	WriteString
	call	ReadDec
	mov		[ebp-4], eax
	call	validation
	mov		esp, ebp
	pop		ebp
		
	ret	20	

getData ENDP

;***********************************************************************************************
;Procedure: Validates that user input is within the specified range (1-10000). If the input is	
;Receives: userNum and error are global variables. UPPER_LIMIT is a global constant 
;Returns:  validCode as a 0 or 1. 1 = valid / 0 = invalid input 
;Preconditions:  none
;Registers changed: edx
;***********************************************************************************************
validation PROC
again:
	mov		eax, [ebp-4]
	cmp		eax, MIN
	jl		wrong
	cmp		eax, MAX
	jg		wrong
	mov		ebx, [ebp+24]
	mov		ecx, [ebp-4]
	mov		[ebx], ecx
	jmp		good
	
wrong:
	mov		edx, [ebp+8]
	call	WriteString
	call	ReadDec
	mov		[ebp-4], eax
	jmp		again

good:
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
fillArray PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 4
	mov		eax, HI
	sub		eax, LO
	inc		eax
	mov		DWORD PTR [ebp-4], eax
	mov		ecx, [ebp+12]
	mov		esi, [ebp+8]

fill:
	mov		eax, [ebp-4]
	call	RandomRange
	add		eax, LO
	mov		[esi], eax
	add		esi, 4
	loop	fill

	mov		esp, ebp
	pop		ebp

	ret 8

fillArray ENDP

;***********************************************************************************************
;Procedure:	Determines if the test number is a composite or prime. Prints the composite
;	and skips over the primes
;Receives: primeNums, testing 
;Returns:  counter and column and testing, all global variables
;Preconditions:  none
;Registers changed: eax, ebx, edx, esi, al 
;***********************************************************************************************

;BubbleSort taken from the textbook. Pg. 375 Slight modification to make the list descending

sortList PROC
	push	ebp
	mov		ebp, esp
	mov		ecx, [ebp+12]
	dec		ecx
outer:
	push	ecx
	mov		esi, [ebp+8]
inner:
	mov		eax, [esi]
	add		esi, 4
	cmp		[esi], eax
	jl		higher
	xchg	eax, [esi]
	sub		esi, 4
	mov		[esi], eax
	add		esi, 4
higher:
	;add		esi, 4
	loop	inner
	pop		ecx
	loop	outer

	pop		ebp
	ret	8

sortList ENDP

;***********************************************************************************************
;Procedure:	Determines if the test number is a composite or prime. Prints the composite
;	and skips over the primes
;Receives: primeNums, testing 
;Returns:  counter and column and testing, all global variables
;Preconditions:  none
;Registers changed: eax, ebx, edx, esi, al 
;***********************************************************************************************
displayMedian PROC
	push	ebp
	mov		ebp, esp
	mov		edx, [ebp+16]				;Prints out the corresponding title
	call	CrLf
	call	WriteString
	mov		esi, [ebp+8]				;Loads array address into esi
	mov		edx, 0						;Checking to see if "request" is even or odd
	mov		eax, [ebp+12]
	mov		ebx, 2
	div		ebx
	cmp		edx, 0
	je		evenNum						;Jump down if "request" is even
	mov		ebx, 4
	mul		ebx	
	add		esi, eax
	mov		eax, [esi]
	jmp		done
evenNum:
	mov		ebx, 4
	mul		ebx	
	add		esi, eax
	mov		eax, [esi]
	sub		esi, 4
	add		eax, [esi]
	mov		ebx, 2
	div		ebx
done:
	call	WriteDec
	call	CrLf

	pop		ebp
	ret	12

displayMedian ENDP

;***********************************************************************************************
;Procedure:	Determines if the test number is a composite or prime. Prints the composite
;	and skips over the primes
;Receives: primeNums, testing 
;Returns:  counter and column and testing, all global variables
;Preconditions:  none
;Registers changed: eax, ebx, edx, esi, al 
;***********************************************************************************************
displayList PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 8
	mov		edx, [ebp+8]
	call	CrLf
	call	WriteString
	call	CrLf
	mov		ebx, 0					;Keeps count of columns used in the row
	mov		ecx, [ebp+12]
	mov		esi, [ebp+16]

print:
	mov		eax, [esi]
	call	WriteDec
	mov		al, 9
	call	WriteChar
	add		esi, 4
	inc		ebx
	cmp		ebx, [ebp+20]
	jge		newLine

back:
	loop	print
	jmp		done

newLine:
	call	CrLf
	mov		ebx, 0
	jmp		back

done:
	call	CrLf
	mov		esp, ebp
	pop		ebp

	ret	16

displayList ENDP

END main
