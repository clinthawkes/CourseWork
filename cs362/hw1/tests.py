import unittest
from credit_card_validator import credit_card_validator

"""
TestCase Methodology:
I started this assignment by first splitting up the requirements that
needed to be tested. I came up with string length, string prefix, and
check digit.

Length: I generated a valid credit card number for each of the different
        prefixes and then change the length of each string to be one
        less than required, and one more than required.

Prefix: For visa and amex, I generated a valid cc number for their
        prefixes and then changed the prefix to one value below and for
        one value above the valid prefix. I tested that the valid prefix
        would return true, and that the prefix that was less or more
        would return false For mastercard, I took the two end points of
        the range and generated a valid cc number for the end points. I
        then changed the prefix for each end point to be one more and
        one less. I tested the endpoint values and the values that were
        one within the ranges to return true. I then tested the cc
        number that was not included in the range to return false.

Check Digit:    I generated a valid cc number for each of the valid
                prefixes and then changed the check digit to make it
                incorrect. I tested these cases to verify they returned
                false.
"""


class TestCardNumber(unittest.TestCase):
    def test_empty_string(self):
        self.assertFalse(credit_card_validator(''),
                         msg='String containing card number was empty')

    def test_visa_min_length(self):
        self.assertFalse(credit_card_validator('453627182908352'),
                         msg='Visa length 15 passed validator')

    def test_visa_max_length(self):
        self.assertFalse(credit_card_validator('45362718290835218'),
                         msg='Visa length 17 passed validator')

    def test_master_min_length(self):
        self.assertFalse(credit_card_validator('542402917672282'),
                         msg='Master length 15 passed validator')

    def test_master_max_length(self):
        self.assertFalse(credit_card_validator('54240291767228390'),
                         msg='Master length 17 passed validator')

    def test_master2_min_length(self):
        self.assertFalse(credit_card_validator('222105659845126'),
                         msg='Master length 15 passed validator')

    def test_master2_max_length(self):
        self.assertFalse(credit_card_validator('22210565984512865'),
                         msg='Master length 17 passed validator')

    def test_amex_min_length(self):
        self.assertFalse(credit_card_validator('37954708874628'),
                         msg='AE length 14 passed validator')

    def test_amex_max_length(self):
        self.assertFalse(credit_card_validator('3795470887462388'),
                         msg='AE length 16 passed validator')

    def test_amex_first_min_length(self):
        self.assertFalse(credit_card_validator('34263042254320'),
                         msg='AE length 14 passed validator')

    def test_amex_first_max_length(self):
        self.assertFalse(credit_card_validator('3426304225432810'),
                         msg='AE length 16 passed validator')

    def test_amex_lower_prefix(self):
        self.assertFalse(credit_card_validator('332349981520703'),
                         msg='AE 33 prefix was valid')

    def test_amex_valid_low_prefix(self):
        self.assertTrue(credit_card_validator('349567524879374'),
                        msg='AE 34 prefix was not valid')

    def test_amex_invalid1_prefix(self):
        self.assertFalse(credit_card_validator('352349981520708'),
                         msg='AE 35 prefix was valid')

    def test_amex_invalid2_prefix(self):
        self.assertFalse(credit_card_validator('362349981520706'),
                         msg='AE 36 prefix was valid')

    def test_amex_upper_prefix(self):
        self.assertTrue(credit_card_validator('373814410559267'),
                        msg='AE 37 prefix was not valid')

    def test_amex_high_prefix(self):
        self.assertFalse(credit_card_validator('382349981520702'),
                         msg='AE 38 prefix valid')

    def test_visa_low_prefix(self):
        self.assertFalse(credit_card_validator('3911466542547216'),
                         msg='Visa 3 prefix was valid')

    def test_visa_valid_prefix(self):
        self.assertTrue(credit_card_validator('4996144052211756'),
                        msg='Visa 4 prefix was not valid')

    def test_visa_high_prefix(self):
        self.assertFalse(credit_card_validator('5911466542547211'),
                         msg='Visa 5 prefix was valid')

    def test_master_low_prefix(self):
        self.assertFalse(credit_card_validator('5008056598451287'),
                         msg='Master 50 prefix was valid')

    def test_master_low_mid2_prefix(self):
        self.assertTrue(credit_card_validator('5129776823917364'),
                        msg='Master 51 prefix was not valid')

    def test_master_low_mid_prefix(self):
        self.assertTrue(credit_card_validator('5273703735000232'),
                        msg='Master 52 prefix was not valid')

    def test_master_high_mid_prefix(self):
        self.assertTrue(credit_card_validator('5467019050345680'),
                        msg='Master 54 prefix was not valid')

    def test_master_high_mid2_prefix(self):
        self.assertTrue(credit_card_validator('5558035661389156'),
                        msg='Master 55 prefix was not valid')

    def test_master_low_high_prefix(self):
        self.assertFalse(credit_card_validator('5608056598451281'),
                         msg='Master 56 prefix was valid')

    def test_master_too_low_prefix(self):
        self.assertFalse(credit_card_validator('2220056598451286'),
                         msg='Master 2220 prefix was valid')

    def test_master_lower_bound_prefix(self):
        self.assertTrue(credit_card_validator('2221567576575762'),
                        msg='Master 2221 prefix was not valid')

    def test_master_middle_lower_bound_prefix(self):
        self.assertTrue(credit_card_validator('2222567576575761'),
                        msg='Master 2222 prefix was not valid')

    def test_master_middle_upper_bound_prefix(self):
        self.assertTrue(credit_card_validator('2719576757675761'),
                        msg='Master 2719 prefix was not valid')

    def test_master_upper_bound_prefix(self):
        self.assertTrue(credit_card_validator('2720576757675768'),
                        msg='Master 2720 prefix was not valid')

    def test_master_high_prefix(self):
        self.assertFalse(credit_card_validator('2721056598451280'),
                         msg='Master 2721 prefix was valid')

    def test_visa_low_check(self):
        self.assertFalse(credit_card_validator('4170130969508746'),
                         msg='Low visa check number(6 instead of 7)')

    def test_visa_high_check(self):
        self.assertFalse(credit_card_validator('4170130969508748'),
                         msg='High visa check number(8 instead of 7)')

    def test_master_low_check(self):
        self.assertFalse(credit_card_validator('5197658404207892'),
                         msg='Low master check number(2 instead of 3)')

    def test_master_high_check(self):
        self.assertFalse(credit_card_validator('5197658404207894'),
                         msg='High master check number(4 instead of 3)')

    def test_master_second_low_check(self):
        self.assertFalse(credit_card_validator('2720576757675767'),
                         msg='Low master check number(7 instead of 8)')

    def test_master_second_high_check(self):
        self.assertFalse(credit_card_validator('2720576757675769'),
                         msg='High master check number(9 instead of 8)')

    def test_amex_low_check(self):
        self.assertFalse(credit_card_validator('378944764980894'),
                         msg='Low ae check number(4 instead of 5)')

    def test_amex_high_check(self):
        self.assertFalse(credit_card_validator('378944764980896'),
                         msg='High ae check number(6 instead of 5)')


if __name__ == '__main__':
    unittest.main()
