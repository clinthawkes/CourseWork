import random
import unittest
from credit_card_validator import credit_card_validator


class TestRandomly(unittest.TestCase):
    def test_all(self):
        for i in range(0, 10000):
            odds = random.randint(1, 5)
            if odds == 1:
                val = random.randint(1000000000000000, 5700000000000000)
            elif odds == 2:
                val = random.randint(300000000000000, 1000000000000000)
            else:
                val = random.randint(300000000000000, 6000000000000000)
            credit_card_validator(val)

    def test_visa(self):
        for i in range(0, 40000):
            odds = random.randint(1, 10)
            if odds == 1 or 3:
                val = random.randint(3900000000000000, 4100000000000000)
            elif odds == 2:
                val = random.randint(4900000000000000, 5100000000000000)
            else:
                val = random.randint(3900000000000000, 5100000000000000)
            credit_card_validator(val)

    def test_master(self):
        for i in range(0, 20000):
            val = random.randint(5000000000000000, 5700000000000000)
            credit_card_validator(val)

    def test_master2(self):
        for i in range(0, 20000):
            val = random.randint(2220000000000000, 2722000000000000)
            credit_card_validator(val)

    def test_amex(self):
        for i in range(0, 20000):
            val = random.randint(330000000000000, 360000000000000)
            credit_card_validator(val)

    def test_amex2(self):
        for i in range(0, 20000):
            val = random.randint(360000000000000, 390000000000000)
            credit_card_validator(val)


if __name__ == '__main__':
    unittest.main()
