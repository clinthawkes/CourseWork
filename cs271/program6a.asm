TITLE Sorting Random Integers (program5.asm)

; Author: Clinton Hawkes 
; Last Modified: May 24, 2019
; OSU email address: hawkesc@oregonstate.edu
; Course number/section: CS271-400
; Project Number: Program 5       Due Date: May 26, 2019
; Description: Program is used to generate a user specified quantity of random numbers between
; a minimum and maximum value, store the random numbers in an array, print the unsorted array, 
; sort the array in descending order, calculate and print the median, and finally print the 
; sorted array. User input is validated to fall withing the given range of values to generate.
; Range of numbers that can be generated: 10 - 200
; Range of values the random numbers can take: 100 - 999

INCLUDE Irvine32.inc

;Global Constants go here
	
NUM_OF_INPUT = 10

;Macros go here

getString MACRO inString, sizeNum	
	push	ecx
	push	edx
	mov		edx, inString
	mov		ecx, sizeNum
	call	ReadString
	pop		edx
	pop		ecx
ENDM

displayString MACRO outString
	push	edx
	mov		edx, outString
	call	WriteString
	pop		edx
ENDM


.data

intro		BYTE	"Programming Assignment 6A             Programmed by Clinton Hawkes", 0
instruct_1	BYTE	"Please provide 10 unsigned decimal numbers.", 0
instruct_2	BYTE	"Each number needs to be small enough to fit inside a 32 bit register.", 0
instruct_3	BYTE	"After you have finished inputting the raw numbers, I will display the list", 0
instruct_4	BYTE	"of the integers, their sum, and their average value.", 0
prompt		BYTE	"Please enter an unsigned number: ", 0
error		BYTE	"ERROR: Number needs to be an unsigned integer or it was too big.", 0
try_again	BYTE	"Please try again:", 0
num_list	BYTE	"You entered the following numbers:", 0
sum			BYTE	"The sum of these numbers is: ", 0
median		BYTE	"The average is: ", 0
farewell	BYTE	"Thank you playing!", 0
array		DWORD	10 DUP(0)	
numVal		DWORD	0
strVal		BYTE	15 DUP(0)
sumVal		DWORD	?
average		DWORD	?

.code
main PROC
	push	OFFSET intro
	push	OFFSET instruct_1
	push	OFFSET instruct_2
	push	OFFSET instruct_3
	push	OFFSET instruct_4
	call	introduction

	push	OFFSET array
	push	OFFSET numVal
	push	OFFSET strVal
	push	SIZEOF strVal
	push	OFFSET try_again
	push	OFFSET error
	push	OFFSET prompt
	call	getData

	push	OFFSET numVal
	push	OFFSET strVal
	push	OFFSET num_list
	push	OFFSET array
	push	LENGTHOF array
	call	displayList

	push	OFFSET strVal
	push	OFFSET sumVal
	push	OFFSET array
	push	LENGTHOF array
	push	OFFSET sum
	call	displaySum



     exit								;exit to operating system
main ENDP

;***********************************************************************************************
;Procedure:	Displays name of program and programmer's name and instructions for user
;Receives:  offset of all strings to print intro, LO and HI global constants
;Returns:  nothing
;Preconditions: arguments must be pushed on stack prior 
;Registers changed: ebp, eax, edx
;***********************************************************************************************
introduction PROC
	push	ebp
	push	edx
	mov		ebp, esp
	displayString	[ebp+28]
	call	CrLf
	call	CrLf
	displayString	[ebp+24]
	call	CrLf
	displayString	[ebp+20]
	call	CrLf
	displayString	[ebp+16]
	call	CrLf
	displayString	[ebp+12]
	call	CrLf
	call	CrLf
	pop		edx
	pop		ebp
	ret 20
introduction ENDP

;***********************************************************************************************
;Procedure:	Asks user to enter a number within the specified range. Validation procedure is 
;	then called to ensure the value is within range. 
;Receives: request offset, prompt_1 offset, dots offset, brackets_1 offset, MIN and MAX constants
;Returns:  request variable with valid number
;Preconditions: arguments must be put on stack prior 
;Registers changed: ebp, esp, eax, edx 
;***********************************************************************************************
getData	PROC
	pushad
	mov		ebp, esp
	mov		ecx, NUM_OF_INPUT				;global constant for number of user inputs
	mov		edi, [ebp+60]					;array offset moved to edi
gather:
	call	ReadVal							;calls macro to get number from user
	mov		ebx, [ebp+56]					;move address of numVal to ebx
	mov		eax, [ebx]						;move value of numVal to eax
	mov		[edi], eax						;put numVal in array
	add		edi, 4							;focus edi on next array element
	mov		eax, 0							
	mov		[ebx], eax						;resets numVal for next user input
	loop	gather

	popad
	ret 28

getData ENDP







readVal PROC
	pushad
	mov		ebp, esp
	sub		esp, 4							;create local variable
	displayString	[ebp+72]				;print prompt for user input

redo:
	getString		[ebp+88], [ebp+84]		;passes strVal and numVal offset to macro
	cmp		eax, 9							;only allows 9 digit numbers
	jg		err
	mov		ecx, eax						;sets loop counter to quantity of numbers
	mov		esi, [ebp+88]					;offset of strVal 
	mov		edi, [ebp+92]					;offset of numVal
	mov		ebx, 10							;used to multiply for conversion

calc:
	lodsb
	movzx	edx, al							;loads character into edx
	mov		[ebp-4], edx					;stores character in local variable
	cmp		al, 48							;character must be at least 48 (the number 0)
	jl		err
	cmp		al, 57							;character must be at most 57 (the number 9)
	jg		err
	mov		eax, [edi]						;move value of numVal into eax for multiplication
	mul		ebx								;multiplies by 10
	add		eax, [ebp-4]					;adds current working character to numVal
	sub		eax, 48							;sub 48 to convert from char to int
	mov		[edi], eax						;store working number in numVal
	loop	calc
	jmp		done

err:
	displayString	[ebp+76]				;display error message
	call	CrLf
	displayString	[ebp+80]				;display "please try again"
	jmp		redo

done:
	mov		esp, ebp
	popad
	ret	

readVal ENDP

;;***********************************************************************************************
;;Procedure:	Populates an array with random numbers that are with the range of LO - HI
;;Receives: array offset, request value, LO and HI global constants
;;Returns:  nothing - prints all info to the console
;;Preconditions:  arguments must be pushed to stack prior
;;Registers changed: ebp, esp, esi, eax, ecx
;;***********************************************************************************************
displayList PROC
	pushad
	mov		ebp, esp
	mov		ecx, [ebp+36]				;move length of array into counter
	mov		esi, [ebp+40]
	mov		ebx, [ebp+52]				;set offset of array to source
	call	CrLf
	displayString [ebp+44]				;num_list is printed out
	call	crlf
cir:
	mov		eax, [esi]					;array element moved to eax
	mov		[ebx], eax
	push	[ebp+52]					;push the offset of numVal to be printed
	push	[ebp+48]					;push the offset of strVal to assist printing
	call	writeVal
	mov		al, 9						;print tab between numbers 
	call	writechar
	add		esi, 4						;next element in array	
	loop	cir

	call	CrLf
	popad
	ret	20

displayList ENDP



;;***********************************************************************************************
;;Procedure:	Prints the lists of random numbers to the console, 10 numbers per line, a tab
;;			between each number.	
;;Receives: col value, array offset, request value and list_after offset 
;;Returns:  N/A Just displays array values and string to console
;;Preconditions: Need to push offset of numVal and strVal just prior to calling. Order of call matters
;;Registers changed: ebp, esp, esi, eax, ebx, ecx, edx, al 
;;***********************************************************************************************

writeVal PROC
	pushad
	mov		ebp, esp			
	mov		esi, [ebp+40]				;move offset of numVal to source
	mov		edi, [ebp+36]				;move offset of strVal to destination
	mov		ecx, 0						;set loop counter to 0

again:
	mov		eax, [esi]					;move value of numVal to eax
	mov		ebx, 10						;always divide by 10 for converting number to string
	cdq
	div		ebx
	mov		[esi], eax					;move the dividend to numVal
	mov		eax, edx					;move remainder to eax for manipulation		
	add		eax, 48						;convert number to character
	push	eax							;push to stack for later
	inc		ecx							;increase counter for later when adding all the characters to strVal
	mov		eax, [esi]					;moves dividend back to  eax for comparison	
	cmp		eax, 0							
	je		store						;if there is nothing left to divide, move on to adding chars to strVal
	jmp		again						;repeat if we can still divide

store:
	mov		ebx, ecx
next:
	pop		eax							;pop the most recent character into eax
	stosb								;move the character to strVal. When we divide by 10 to convert numbers to characters, the 
	loop	next						;characters are in reverse, so we had to push to the stack and then pop off for correct result

finish:
	displayString [ebp+36]				;call macro to print the string we just created from the number
	mov		ecx, 10						;preparing to clear the 10 bytes in strVal
	mov		eax, 0
	dec		ebx							
	sub		edi, ebx					;returns the stosb incrementer to the beginning of the string

clean:
	stosb								;fills the current byte with 0
	loop	clean						;repeats 10 times

	popad
	ret 8

writeVal ENDP

;;***********************************************************************************************
;;Procedure:	Prints the lists of random numbers to the console, 10 numbers per line, a tab
;;			between each number.	
;;Receives: col value, array offset, request value and list_after offset 
;;Returns:  N/A Just displays array values and string to console
;;Preconditions: Need to push offset of variable holding number and strVal just prior to calling. 
;;     Order of call matters
;;Registers changed: ebp, esp, esi, eax, ebx, ecx, edx, al 
;;***********************************************************************************************
displaySum PROC
	pushad
	mov		ebp, esp
	mov		ecx, [ebp+40]				;populate counter with array length	
	mov		esi, [ebp+44]				;move array offset to source
	mov		edi, [ebp+48]				;move sumVal offset to desination
	call	CrLf
	displayString	[ebp+36]			;print message "The sum of these numbers is"

plus:
	mov		eax, [esi]					;move value of current array element to eax
	add		[edi], eax					;add the value to the running sum
	add		esi, 4						;focus on the next element
	loop	plus
	
	push	[ebp+48]					;push offset of sumVal to be printed
	push	[ebp+52]					;push offset of strVal to assist in the printing
	call	writeVal
	popad
	ret 16

displaySum ENDP
;
;;***********************************************************************************************
;;Procedure:	Prints the lists of random numbers to the console, 10 numbers per line, a tab
;;			between each number.	
;;Receives: col value, array offset, request value and list_after offset 
;;Returns:  N/A Just displays array values and string to console
;;Preconditions:	Arguments received need to be pushed to the stack prior 
;;Registers changed: ebp, esp, esi, eax, ebx, ecx, edx, al 
;;***********************************************************************************************
;farewell PROC
;
;
;farewell ENDP
;
END main