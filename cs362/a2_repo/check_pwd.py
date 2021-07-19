import string


def check_pwd(num):
    symbols = '~`!@#$%^&*()_+-='
    all_pos = string.ascii_letters + string.digits + symbols
    if len(num) < 8 or len(num) > 20:
        return False
    if not any(char.islower() for char in num):
        return False
    if not any(char.isupper() for char in num):
        return False
    if not any(char.isdigit() for char in num):
        return False
    if not any(char in symbols for char in num):
        return False
    if any(char not in all_pos for char in num):
        return False
    return True
