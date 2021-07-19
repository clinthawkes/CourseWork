import unittest
from check_pwd import check_pwd


class PwdCheck(unittest.TestCase):
    def test_empty(self):
        input = '' 
        expected = false
import unittest
from check_pwd import check_pwd


class PwdCheck(unittest.TestCase):
    def test_empty(self):
        input = '' 
        expected = false
        self.assertEqual(check_pwd(input), expected)

if __name___ == '__main__':
    allowed = {'~', '\'', '!', '@', '#', '$', '%', '^', '&',
                               '*', '(', ')', '_', '+', '-', '='}
                    if allowed.issuperset(num):
