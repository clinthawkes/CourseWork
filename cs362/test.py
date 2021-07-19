from hex import conv_endian

def numToHex(nums, endian='big'):
    temp = str(hex(nums))
    negative = False 
    
    if nums < 0:
        negative = True 
        temp = temp[1:]
    
    temp = temp[2:]

    if len(temp) % 2 != 0:
        temp = '0' + temp

    split = [temp[i:i + 2] for i in range(0, len(temp), 2)]

    if endian == 'little':
        split.reverse()



if __name__ == '__main__':

    print(conv_endian(-256))
    print(conv_endian(-256, 'little'))
    print(conv_endian(1456))
    print(conv_endian(1456, 'little'))
    print(conv_endian(-5456))
    print(conv_endian(-5456, 'little'))
    print(conv_endian(-954786))
    print(conv_endian(383825456, 'little'))
    print(conv_endian(0))
    print(conv_endian(-0, 'little'))
