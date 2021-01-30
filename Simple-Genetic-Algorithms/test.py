import numpy as np
from functools import reduce
from operator import add
from GeneticPolynomialFinder import *
import unittest

class TestingGeneticPolynomialFinder(unittest.TestCase):

    def __init__(self, *args, **kwargs):
        super(TestingGeneticPolynomialFinder, self).__init__(*args, **kwargs)

        self.data_points = [
            [-10, -10], [-9, -9], [-8, -8], [-7, -7], [-6, -6], [-5, -5], [-4, -4], [-3, -3], [-2, -2], [-1, -1],
            [0, 0],
            [1, 1], [2, 2], [3, 3], [4, 4], [5, 5], [6, 6], [7, 7], [8, 8], [9, 9], [10, 10],
        ]

    def test_init(self):
        G = GeneticPolynomialFinder(self.data_points, 2, [-10, 10], 10)
        self.assertEqual(G.data_points_count, 21)
        self.assertEqual(G.range, [-10, 10])
        self.assertEqual(G.offset, 10)

    def test_fitnes_at_pos(self):
        G = GeneticPolynomialFinder(self.data_points, 2, [-10, 10], 10)
        self.assertEqual(G.fitness_at_pos([1, 1], [0.5, 5]), 20.25)

    def test_fitness(self):
        G = GeneticPolynomialFinder(self.data_points, 2, [-10, 10], 10)
        self.assertEqual(G.fitness([1, 0]), 0)
        self.assertEqual(G.fitness([1, 1]), 50666)

    def test_grade_and_sort(self):
        G = GeneticPolynomialFinder(self.data_points, 2, [-10, 10], 4)
        G.population = [ [2, 2], [1, 0], [1, 1], [0, 1] ] # Stage population
        G.sort_population_by_grade()

        expected_population = [ [1, 0], [1, 1], [0, 1], [2, 2] ]

        self.assertEqual(G.population, expected_population)

    def test_mutate_population(self):
        G = GeneticPolynomialFinder(self.data_points, 2, [1, 2], 4)

        new_population = G.mutate_population([[0,0,0,0,0,0,0,0,0,0,0]], 1.1)

        self.assertNotEqual([[0,0,0,0,0,0,0,0,0,0,0]], new_population)

unittest.main()


