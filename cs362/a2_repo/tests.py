import unittest
from check_pwd import check_pwd


class TestPwd(unittest.TestCase):
    def test1(self):
        test_num = ''
        expected = False
        self.assertEqual(check_pwd(test_num), expected)

    def test2(self):
        test_num = '111111111111111111111'
        expected = False
        self.assertEqual(check_pwd(test_num), expected)

    def test3(self):
        test_num = '11111111'
        expected = False
        self.assertEqual(check_pwd(test_num), expected)

    def test4(self):
        test_num = 'aaaaaaaa'
        expected = False
        self.assertEqual(check_pwd(test_num), expected)

    def test5(self):
        test_num = 'AAaaaaaa'
        expected = False
        self.assertEqual(check_pwd(test_num), expected)

    def test6(self):
        test_num = 'AAaa11aa'
        expected = False
        self.assertEqual(check_pwd(test_num), expected)

    def test7(self):
        test_num = 'AAaa11!?'
        expected = False
        self.assertEqual(check_pwd(test_num), expected)


if __name__ == '__main__':
    unittest.main()
