from textwrap import wrap


def conv_endian(num, endian = 'big'):
    if endian != 'big' and endian != 'little':
        return None

    if num == 0:
        return '00'

    hexNums = {0:'0', 1:'1', 2:'2', 3:'3',
               4:'4', 5:'5', 6:'6', 7:'7',
               8:'8', 9:'9', 10:'A', 11:'B',
               12:'C', 13:'D', 14:'E', 15:'F'}

    negative = False

    if num < 0:
        negative = True
        num *= -1

    hexBuild = ''

    while num > 0:
        hexBuild = hexNums[num % 16] + hexBuild
        num //= 16

    if len(hexBuild) % 2 != 0:
        hexBuild = '0' + hexBuild

    split = wrap(hexBuild, 2)

    if endian == 'little':
        split.reverse()

    hexBuild = ''
    
    for part in split:
        hexBuild += part
        hexBuild += ' '

    hexBuild.rstrip()

    if negative:
        hexBuild = '-' + hexBuild

    return hexBuild
