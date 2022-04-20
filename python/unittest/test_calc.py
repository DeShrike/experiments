import unittest
import calc

class TestCalc(unittest.TestCase):


    @classmethod
    def setUpClass(cls):
        print("setupClass")

    @classmethod
    def tearDownClass(cls):
        print("TeardownClass")

    def setUp(self):
        print("Setup")

    def tearDown(self):
        print("Teardown")

    def test_subtract(self):
        result = calc.subtract(100, 50)
        self.assertEqual(result, 50)

    def test_divide(self):
        self.assertEqual(calc.divide(10, 5), 2)
        self.assertEqual(calc.divide(10, 1), 10)
        self.assertEqual(calc.divide(100, -5), -20)
        self.assertEqual(calc.divide(1000, 5), 200)
        self.assertRaises(ValueError, calc.divide, 20, 0)

        with self.assertRaises(ValueError):
            calc.divide(100, 0)

    def test_add(self):
        """
        assertEqual
        assertNotEqual
        assertTrue
        assertFalse
        assertIs
        assertIsNot
        assertIsNone
        assertIsNotNone
        assertIn
        assertNotIn
        assertIsInstance
        assertNotIsInstance
        """
        result = calc.add(10,5)
        self.assertEqual(result, 15)

"""
python -m unittest test_calc.py

"""

if __name__ == "__main__":
    unittest.main()
