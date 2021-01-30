from PolynomialOptimisationBase import PolynomialData
import numpy as np

# Class responsible for creating a discrit data points for different equations
class PolynomialDataFactory():

    # y = 5x
    def get_data_order_1(self):
        x = range(-100, 101, 1)
        y = lambda x : 5*x
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 1,
            v_min = 0,
            v_max = 10,
            constant = y(0))

    # y = 0.5x^2 + 2x
    def get_data_order_2(self):
        x = np.arange(-10, 5.1, 0.15)
        y = lambda x : (0.5*(x**2)) + (2*x)
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 2,
            v_min = -2.5,
            v_max = 5,
            constant = y(0))

    # y = 0.02x^3 - 0.5x^2 + 2x
    def get_data_order_3(self):
        x = np.arange(-5, 25.1, 0.3)
        y = lambda x : (0.02*(x**3)) - (0.5*(x**2)) + (2*x)
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 3,
            v_min = -1,
            v_max = 5,
            constant = y(0))

    # y = x^4 - x^3 - x^2 + x
    def get_data_order_4(self):
        x = np.arange(-2, 2.01, 0.04)
        y = lambda x : (x**4) - (x**3) - (x**2) + x
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 4,
            v_min = -5,
            v_max = 5,
            constant = y(0))
    
    # y = 3x^5 + 20x^4 - 10x^3 - 240x^2 - 250x + 200
    def get_data_order_5_type_1(self):
        # Optimal range x = [-6.2 to 3.9] y = [2000, -1500]
        x = np.arange(-6.2, 3.91, 0.102)
        y = lambda x : (3*(x**5)) + (20*(x**4)) - (10*(x**3)) - (240*(x**2)) \
            - (250*x) + 200
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 5,
            v_min = -2000,
            v_max = 2500,
            constant = y(0))
    
    # y = x^5 - 5x^4 + 5x^3 + 5x^2 - 6x - 1
    def get_data_order_5_type_2(self):
        # Optimal range x = [-1.4 to 3.4] y = [10, -10]
        x = np.arange(-1.4, 3.46, 0.049)
        y = lambda x : (x**5) - (5*(x**4)) + (5*(x**3)) + (5*(x**2)) \
            - (6*x) - 1
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 5,
            v_min = -20,
            v_max = 20,
            constant = y(0))

    # y = 3x^5 - 30x^4 + 110x^3 - 180x^2 + 135x - 56
    def get_data_order_5_type_3(self):
        # Optimal range x = [0 to 4] y = [30, -40]
        x = np.arange(0, 4.00, 0.04)
        y = lambda x : (3*(x**5)) - (30*(x**4)) + (110*(x**3)) - (180*(x**2)) \
            + (135*x) - 56
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 5,
            v_min = -70,
            v_max = 60,
            constant = y(0))

    # y = 4x^5 - 5x^4 - 20x^3 + 10x^2 + 40x + 10
    def get_data_order_5_type_4(self):
        # Optimal range x = [-2 to 2.7] y = [100, -100]
        x = np.arange(-3, 5.01, 0.08)
        y = lambda x : (4*(x**5)) - (5*(x**4)) - (20*(x**3)) + (10*(x**2)) \
            + (40*x) + 10
        xy = [[i, y(i)] for i in x]

        return PolynomialData(xy,
            eq_order = 5,
            v_min = -150,
            v_max = 150,
            constant = y(0))

    # Returns an array with every data type for testing
    def get_data_array(self):
        return [
            self.get_data_order_1(),
            self.get_data_order_2(),
            self.get_data_order_3(),
            self.get_data_order_4(),
            self.get_data_order_5_type_1(),
            self.get_data_order_5_type_2(),
            self.get_data_order_5_type_3(),
            self.get_data_order_5_type_4(),
        ]

    




