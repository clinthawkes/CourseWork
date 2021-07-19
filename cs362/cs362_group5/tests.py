###############################################################################
# Clinton Hawkes, Alessio Peterson, and Vincent Yasi
# Group Project
###############################################################################
# The internal test suite for the group project.
# Tests are used for our own testing during the development process.
# Not the final tests the instructor will run.
###############################################################################
import unittest
from task import conv_endian
from task import my_datetime
from task import conv_num


class TestCase(unittest.TestCase):

    # ---------------------------------------------------------------
    # Function 1: conv_num
    # ---------------------------------------------------------------

    # integer: positive
    def test_conv_num_1(self):
        self.assertEqual(conv_num('12345'), 12345)

    # integer: negative
    def test_conv_num_2(self):
        self.assertEqual(conv_num('-12345'), -12345)

    # float: positive
    # decimal: middle
    def test_conv_num_3(self):
        self.assertEqual(conv_num('123.45'), 123.45)

    # float: negative
    # decimal: middle
    def test_conv_num_4(self):
        self.assertEqual(conv_num('-123.45'), -123.45)

    # float: positive
    # decimal: start
    def test_conv_num_5(self):
        self.assertEqual(conv_num('.45'), 0.45)

    # float: negative
    # decimal: start
    def test_conv_num_6(self):
        self.assertEqual(conv_num('-.45'), -0.45)

    # float: positive
    # decimal: end
    def test_conv_num_7(self):
        self.assertEqual(conv_num('123.'), 123.0)

    # float: negative
    # decimal: end
    def test_conv_num_8(self):
        self.assertEqual(conv_num('-123.'), -123.0)

    # hexadecimal: positive
    # valid prefix: yes
    # valid characters: yes
    def test_conv_num_9(self):
        self.assertEqual(conv_num('0xAD4'), 2772)

    # hexadecimal: negative
    # valid prefix: yes
    # valid characters: yes
    def test_conv_num_10(self):
        self.assertEqual(conv_num('-0xAD4'), -2772)

    # hexadecimal: positive
    # valid prefix: yes
    # valid characters: no
    def test_conv_num_11(self):
        self.assertEqual(conv_num('0xAZ4'), None)

    # hexadecimal: negative
    # valid prefix: yes
    # valid characters: no
    def test_conv_num_12(self):
        self.assertEqual(conv_num('-0xAZ4'), None)

    # hexadecimal: positive
    # valid prefix: no
    # valid characters: yes
    def test_conv_num_13(self):
        self.assertEqual(conv_num('12345A'), None)

    # hexadecimal: negative
    # valid prefix: no
    # valid characters: yes
    def test_conv_num_14(self):
        self.assertEqual(conv_num('-12345A'), None)

    # multiple decimals
    def test_conv_num_15(self):
        self.assertEqual(conv_num('12.3.45'), None)

    # negative with multiple decimals
    def test_conv_num_16(self):
        self.assertEqual(conv_num('-12.3.45'), None)

    # float: positive
    # decimal: middle
    def test_conv_num_17(self):
        self.assertEqual(conv_num('12345.6789'), 12345.6789)

    # float: negative
    # decimal: middle
    def test_conv_num_18(self):
        self.assertEqual(conv_num('-12345.6789'), -12345.6789)

    # float: positive
    # decimal: middle
    def test_conv_num_19(self):
        self.assertEqual(conv_num('0.000004'), 0.000004)

    # float: negative
    # decimal: middle
    def test_conv_num_20(self):
        self.assertEqual(conv_num('-0.000004'), -0.000004)

    # hexadecimal: negative
    # valid prefix: yes
    # valid characters: yes
    # case: lower and upper
    def test_conv_num_21(self):
        self.assertEqual(conv_num('0xaD4'), 2772)

    # hexadecimal: negative
    # valid prefix: yes
    # valid characters: yes
    # case:lower and upper
    def test_conv_num_22(self):
        self.assertEqual(conv_num('-0xaD4'), -2772)

    # hexadecimal: no '0x' prefix
    # valid prefix: no
    # valid characters: yes
    # case: upper
    def test_conv_num_23(self):
        self.assertEqual(conv_num('BB8'), None)

    # empty string
    def test_conv_num_24(self):
        self.assertEqual(conv_num(''), None)

    # non-number string
    def test_conv_num_25(self):
        self.assertEqual(conv_num('Software'), None)

    def test_conv_num_26(self):
        self.assertEqual(conv_num('12.3.45.'), None)

    #######################
    # my conv_endian() Tests #
    #######################

    # test for num = 0 and no endian
    def testHex0(self):
        expected = None 
        self.assertEqual(conv_endian(), expected)

    # test for num = 0 and no endian
    def testHex1(self):
        num = 0
        endian = 'big'
        expected = '00'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 0 and little endian
    def testHex2(self):
        num = 0
        endian = 'little'
        expected = '00'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -0 and no endian
    def testHex3(self):
        num = -0
        endian = 'big'
        expected = '00'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -0 and little endian
    def testHex4(self):
        num = -0
        endian = 'little'
        expected = '00'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 0 and invalid endian
    def testHex5(self):
        num = 0
        endian = 'me'
        expected = None
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 1 and no endian
    def testHex6(self):
        num = 1
        endian = 'big'
        expected = '01'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -1 and no endian
    def testHex7(self):
        num = -1
        endian = 'big'
        expected = '-01'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -1 and little endian
    def testHex8(self):
        num = -1
        endian = 'little'
        expected = '-01'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 17 and big endian
    def testHex9(self):
        num = 17
        endian = 'big'
        expected = '11'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 17 and little endian
    def testHex10(self):
        num = 17
        endian = 'little'
        expected = '11'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 273 and big endian
    def testHex11(self):
        num = 273
        endian = 'big'
        expected = '01 11'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 273 and little endian
    def testHex12(self):
        num = 273
        endian = 'little'
        expected = '11 01'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -273 and big endian
    def testHex13(self):
        num = -273
        endian = 'big'
        expected = '-01 11'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -273 and little endian
    def testHex14(self):
        num = -273
        endian = 'little'
        expected = '-11 01'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -273 and BIG endian
    def testHex15(self):
        num = -273
        endian = 'BIG'
        expected = None
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -273 and LITTLE endian
    def testHex16(self):
        num = -273
        endian = 'LITTLE'
        expected = None
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 913355 and big endian
    def testHex17(self):
        num = 913355
        endian = 'big'
        expected = '0D EF CB'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = 913355 and little endian
    def testHex18(self):
        num = 913355
        endian = 'little'
        expected = 'CB EF 0D'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -913355 and big endian
    def testHex19(self):
        num = -913355
        endian = 'big'
        expected = '-0D EF CB'
        self.assertEqual(conv_endian(num, endian), expected)

    # test for num = -913355 and little endian
    def testHex20(self):
        num = -913355
        endian = 'little'
        expected = '-CB EF 0D'
        self.assertEqual(conv_endian(num, endian), expected)

    #######################
    # my_datetime() Tests #
    #######################
    # Test for correct convert from seconds to date
    def testDate1(self):
        testDate = "07-12-1989"
        self.assertEqual(my_datetime(616249602), testDate)

    # Test for correct convert from seconds to date
    def testDate2(self):
        testDate = "11-18-2009"
        self.assertEqual(my_datetime(1258547202), testDate)

    # Test for correct convert for future date
    def testDate3(self):
        testDate = "08-21-3010"
        self.assertEqual(my_datetime(32839302402), testDate)

    # Test for correct convert for far future date
    def testDate4(self):
        testDate = "08-21-9220"
        self.assertEqual(my_datetime(228808067202), testDate)

    # Test for correct convert for 0 seconds
    def testDate5(self):
        testDate = "01-01-1970"
        self.assertEqual(my_datetime(0), testDate)

    # Test for correct convert for leap year
    def testDate6(self):
        testDate = "02-29-2000"
        self.assertEqual(my_datetime(951827202), testDate)

    # Test for correct convert for non-leap year leap year
    # A seconds value which would convert to Feb 29th if
    # 2001 were a leap year
    def testDate7(self):
        testDate = "03-01-2001"
        self.assertEqual(my_datetime(983449602), testDate)

    # Test for non-leap year century
    # Year divisible by 4, but not 400
    def testDate8(self):
        testDate = "06-23-6100"
        self.assertEqual(my_datetime(130345261629), testDate)

    # Test for one second after epoch
    def testDate9(self):
        testDate = "01-01-1970"
        self.assertEqual(my_datetime(1), testDate)

    # Test for one day after start of year
    def testDate10(self):
        testDate = "01-02-1978"
        self.assertEqual(my_datetime(252583200), testDate)

    # Test for one second before midnight at end of year
    def testDate11(self):
        testDate = "12-31-1992"
        self.assertEqual(my_datetime(725846399), testDate)

    # Test for Christmas becuase of good will to all
    # Also a leap year
    def testDate12(self):
        testDate = "12-25-2010"
        self.assertEqual(my_datetime(1293310740), testDate)


if __name__ == '__main__':
    unittest.main()
