import numpy as np
from functools import reduce
from operator import add
from GeneticPolynomialFinder import *
import unittest

data_points = [
    [-10, -10], [-9, -9], [-8, -8], [-7, -7], [-6, -6], [-5, -5], [-4, -4], [-3, -3], [-2, -2], [-1, -1],
    [0, 0],
    [1, 1], [2, 2], [3, 3], [4, 4], [5, 5], [6, 6], [7, 7], [8, 8], [9, 9], [10, 10],
]


#G.train(500, 1)

#[ print(datum) for datum in G.get_fitness_history() ]

#G.sort_population_by_grade()
#print(G.population[0])

    
# Equations
# y = 3x^5 + 20x^4 - 10x^3 - 240x^2 - 250x + 200
# Optimal range x = [-6.2 to 3.9] y = [2000, -1500]
x1 = np.arange(-6.2, 3.91, 0.102)
y1 = lambda x : (3*(x**5)) + (20*(x**4)) - (10*(x**3)) - (240*(x**2)) - (250*x) + 200

# y = x^5 - 5x^4 + 5x^3 + 5x^2 - 6x - 1
# Optimal range x = [-1.4 to 3.4] y = [10, -10]
x2 = np.arange(-1.4, 3.46, 0.049)
y2 = lambda x : (x**5) - (5*(x**4)) + (5*(x**3)) + (5*(x**2)) - (6*x) - 1

# y = 3x^5 - 30x^4 + 110x^3 - 180x^2 + 135x - 56
# Optimal range x = [0 to 4] y = [30, -40]
x3 = np.arange(0, 4.00, 0.04)
y3 = lambda x : (3*(x**5)) - (30*(x**4)) + (110*(x**3)) - (180*(x**2)) + (135*x) - 56

# y = 4x^5 - 5x^4 - 20x^3 + 10x^2 + 40x + 10
# Optimal range x = [-2 to 2.7] y = [100, -100]
x4 = np.arange(-2, 2.700, 0.047)
y4 = lambda x : (4*(x**5)) - (5*(x**4)) - (20*(x**3)) + (10*(x**2)) + (40*x) + 10

xy = [[x, y2(x)] for x in x2]
c = y2(0)

min_max = [-10, 10]
equation_order = 5
population_size = 100

G = GeneticPolynomialFinder(xy, equation_order, min_max, population_size, c)
G.train(500, 1)

[ print(datum) for datum in G.get_fitness_history() ]
print(G.best_fit)

