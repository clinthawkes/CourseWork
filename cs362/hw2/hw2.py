import unittest
from contrived_func import contrived_func


class TestConditions(unittest.TestCase):
    def test_condition1(self):
        self.assertTrue(contrived_func(125),
                        msg='first statement should be true')

    def test_condition2(self):
        self.assertFalse(contrived_func(6),
                         msg='second statement should be false')

    def test_condition3(self):
        self.assertTrue(contrived_func(7),
                        msg='second statement should be true')

    def test_condition4(self):
        self.assertFalse(contrived_func(72),
                         msg='third statement should be false')

    def test_condition5(self):
        self.assertTrue(contrived_func(80),
                        msg='third statement should be true')

    def test_condition6(self):
        self.assertTrue(contrived_func(60),
                        msg='third statment should be true')

    def test_condition7(self):
        self.assertFalse(contrived_func(151),
                         msg='all statements should be false')


if __name__ == '__main__':
    unittest.main()
