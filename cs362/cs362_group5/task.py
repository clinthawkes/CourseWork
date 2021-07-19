###############################################################################
# Clinton Hawkes, Alessio Peterson, and Vincent Yasi
# Group Project
###############################################################################
# These are the three functions for Part 2 of the Group Project.
#
# The first function converts a string to a base-10 number.
#
# The second function converts seconds to a date.
#
# The third function converts an integer into hex, with a certain endian form.
#
# This file was created under a Continous Integration workflow by the three
# of us on GitHub (https://github.com/clinthawkes/cs362_group_5)
###############################################################################

# -------------------------------------------------------------------
# Function 1: String to Base 10
# -------------------------------------------------------------------
# Description: Takes in a string and converts it to a base 10 number
# -------------------------------------------------------------------


# converts hexadecimal to decimal
def convert_hex(num_str):
    result = 0
    for x, y in enumerate(num_str):
        good_char = "0123456789ABCDEF"
        value = good_char.index(y)
        power = (len(num_str) - (x + 1))
        result += (value * 16 ** power)
    return result


# converts a string to an int
def convert_int(num_str):
    result = 0
    for x, y in enumerate(num_str):
        good_char = "0123456789ABCDEF"
        value = good_char.index(y)
        result = 10 * result + value
    return result


# converts and formats a float
def format_float(num_str, decimal_index):
    result = convert_int(num_str)
    # if decimal is at beginning
    if decimal_index == 0:
        result = result / 10 ** (len(num_str))
    # if decimal is at the end
    elif decimal_index == len(num_str):
        result = result / 1
    # if the decimal is somewhere in the middle
    else:
        result = result / 10 ** (len(num_str) - decimal_index)
    return result


# converts to negative
def neg_conv(result, negative):
    if negative:
        result *= -1
    return result


# check for negative
def neg_check(num_str):
    negative = False
    if num_str[0] == '-':
        negative = True
        num_str = num_str[1:len(num_str)]
    return num_str, negative


# check for hexadecimal
def hex_check(num_str):
    valid_hex = False
    if (num_str[0:2] == '0x') or (num_str[0:3] == '-0x'):
        valid_hex = True
        num_str = num_str[2:len(num_str)]
    return num_str, valid_hex


# count and check valid decimal
def decimal_check(num_str):
    valid_decimal = False
    decimal_count = 0
    for x in num_str:
        if x == '.':
            decimal_count += 1
    if decimal_count == 1:
        valid_decimal = True
    return valid_decimal


# check for float
def float_check(num_str, valid_decimal, valid_hex):
    valid_float = False
    decimal_index = 0
    if valid_decimal and not valid_hex:
        valid_float = True
        decimal_index = num_str.index(".")
        num_str = (num_str[0:decimal_index] +
                   num_str[decimal_index + 1:len(num_str)])
    return num_str, valid_float, decimal_index


# check for out of range characters
def char_check(num_str):
    all_good = True
    num_str = num_str.upper()
    values = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              'A', 'B', 'C', 'D', 'E', 'F']
    if any(x not in values for x in num_str):
        all_good = False
    return all_good, num_str


# valid strings are converted to numbers
def compute(num_str, negative,
            valid_hex, valid_float, decimal_index):
    result = 0
    # the string is a hexadecimal number
    if valid_hex:
        result = convert_hex(num_str)
        result = neg_conv(result, negative)
        return result

    # if it isn't a hexadecimal then it shouldn't have letters
    elif num_str.isdigit():
        # the string is a float
        if valid_float:
            result = format_float(num_str, decimal_index)
        # the string is an integer
        else:
            result = convert_int(num_str)
        result = neg_conv(result, negative)
        return result


# converts a string to a base 10 number
def conv_num(num_str):

    # is is empty?
    if num_str == '':
        return None

    # is it even a string?
    valid_string = isinstance(num_str, str)
    if not valid_string:
        return None

    # is it negative?
    num_str, negative = neg_check(num_str)

    # is it in proper hexadecimal form?
    num_str, valid_hex = hex_check(num_str)

    # how many decimals are there?
    valid_decimal = decimal_check(num_str)

    # is it a float?
    num_str, valid_float, decimal_index = \
        float_check(num_str, valid_decimal, valid_hex)

    # does it have anything it shouldn't?
    all_good, num_str = char_check(num_str)

    # is it all good?
    if all_good:
        result = compute(num_str, negative, valid_hex,
                         valid_float, decimal_index)
        return result


###############################################################################
# Subfunction to Find Years from Seconds
# Takes in seconds and returns the year and remaining seconds
def find_year(inSecs):
    year = 1970

    # While there is at least one year's worth of seconds left,
    # increment year, figure out if leap year,
    # and subtract appropriate amount of seconds
    # (# secs in a normal year: 31536000)
    # (# secs in a leap year: 31622400)
    while inSecs >= 31536000:
        year = year + 1

        if year % 4 != 0:
            inSecs = inSecs - 31536000

        elif year % 100 != 0:
            inSecs = inSecs - 31622400

        elif year % 400 != 0:
            inSecs = inSecs - 31536000

        else:
            inSecs = inSecs - 31622400

    # return year and remainings seconds
    return (year, inSecs)


# Subfunctions to Find Month from Seconds
# Takes in seconds and year and subtracts seconds until find month
# Unfortunately, no real pattern to month length,
# so need to check and subtract each one by one
# Broken into two parts as flake8 claimed too complex
def check_month(inSecs, inMonth):
    if inSecs <= inMonth:
        return True
    else:
        return False


def find_month(inSecs, year):
    # number of seconds in each month based on length
    month30 = 2592000
    month31 = 2678400
    month28 = 2419200
    month29 = 2505600

    # hold number of month
    month = 0

    # array with order of month lengths
    # two arrays for leap vs regular
    reg_lengths = [month31, month28, month31, month30, month31, month30,
                   month31, month31, month30, month31, month30, month31]
    leap_lengths = [month31, month29, month31, month30, month31, month30,
                    month31, month31, month30, month31, month30, month31]

    # loop regulating variable
    found = False

    # array iterator
    i = 0

    # leap variable
    leap = False

    # determine if year is leap year
    if year % 4 != 0:
        leap = False

    elif year % 100 != 0:
        leap = True

    elif year % 400 != 0:
        leap = False

    else:
        leap = True

    # check each month to see if it is the one (two versions based on leap)
    # if so, mark month
    # if not, subtract that month's seconds and move to next
    if leap is True:
        while found is False:
            found = check_month(inSecs, leap_lengths[i])
            if found is True:
                month = i + 1
                inSecs = inSecs + 86400
            else:
                inSecs = inSecs - leap_lengths[i]
                i = i + 1

    elif leap is False:
        while found is False:
            found = check_month(inSecs, reg_lengths[i])
            if found is True:
                month = i + 1
            else:
                inSecs = inSecs - reg_lengths[i]
                i = i + 1

    return (month, inSecs)


# Function 2 -Seconds to Date-
# Uses two subfunctions to take the seconds since Epoch
# and converts it into MM-DD-YYYY format of date
def my_datetime(num_sec):
    ###########################
    # Get The Year of The Date
    ###########################

    year, secs = find_year(num_sec)

    ########################
    # Get Month of The Date
    ########################

    month, secs = find_month(secs, year)

    if month < 10:
        month = '0' + str(month)

    else:
        month = str(month)

    ######################
    # Get Day of The Date
    ######################

    # As we have stripped away year and month seconds,
    # we just need to subtract days until we have less than one day left
    # (86400 seconds in a day)

    day = 1

    while secs > 86400:
        secs = secs - 86400
        day = day + 1

    # save as string
    # see if '0' needs to be added to front
    if day < 10:
        day = '0' + str(day)

    else:
        day = str(day)

    ###################################
    # Build Date String and Return It
    ###################################
    date = month + "-" + day + "-" + str(year)

    return date
###############################################################################


# Function 3 -Integer to Hexadecimal-
def conv_endian(num, endian='big'):
    # returns None for incorrect endian values
    if endian != 'little' and endian != 'big':
        return None

    if num == 0:
        return '00'

    # hash table of the dec to hex values for quick lookup
    hexNums = {0: '0', 1: '1', 2: '2', 3: '3',
               4: '4', 5: '5', 6: '6', 7: '7',
               8: '8', 9: '9', 10: 'A', 11: 'B',
               12: 'C', 13: 'D', 14: 'E', 15: 'F'}

    # bool will determine whether to add '-' to the hex string later on
    negative = False

    # sets bool for negative and turns negative input to positive
    # value for easy conversion to hex
    if num < 0:
        negative = True
        num *= -1

    # start building hex string with empty string
    hexBuild = ''

    # takes the input number and converts it to hex using the process found
    # in the provided assignment resources
    while num > 0:
        hexBuild = hexNums[num % 16] + hexBuild
        num //= 16

    # hex string must be returned with 2 chars per byte, so this ensures
    # there are an even number of chars
    if len(hexBuild) % 2 != 0:
        hexBuild = '0' + hexBuild

    # bytes in hex string are separated by a space. Breaking the string into
    # a list makes the process much easier. It also allows the hex string to
    # be reversed if the endian requested is 'little'. This breaks the
    # string into a list of 2 char strings
    split = [hexBuild[index:index + 2] for index in range(0, len(hexBuild), 2)]

    # reverses the list created above if the endian requested is 'little'
    if endian == 'little':
        split.reverse()

    # reset hexBuild so we can start concatenating all the strings in the list
    hexBuild = ''

    # builds the hex string from the list of 2 char strings created above. The
    # mini strings are separated by a space
    for part in split:
        hexBuild += part
        hexBuild += ' '

    # strips off the trailing space
    hexBuild = hexBuild.rstrip(' ')

    # if the negative bool was set in the beginning, a '-' is appended to the
    # front of the hex string
    if negative:
        hexBuild = '-' + hexBuild

    return hexBuild
