from PolynomialOptimisationBase import PolynomialOptimisationBase, PolynomialData
import numpy as np
from more_itertools import sort_together
from functools import reduce
from operator import add, or_
import random

# Polynomial Optimiser Roulete Wheel selective
class PolynomialOptimisationRouleteWheel(PolynomialOptimisationBase):
    def __init__(self, polynomial_data):
        super().__init__(polynomial_data)

    def evolve(self):
        population = self.population
        count = self.d.p_size * 2

        # Sort the population by fitness
        fitenss_population = [self.fitness(individual) for individual in population]
        fitenss_population, population = sort_together([fitenss_population, population])
        self.keep_if_best_result(fitenss_population[0], population[0])

        # Find the max fitness and invert all values to find percentages
        max_value = fitenss_population[-1]
        fitenss_population = [(max_value + 1 - v) for v in fitenss_population]

        # Generate new positions
        rand = np.random.uniform(0, sum(fitenss_population), count)
        rand.sort() 

        # Generate new positions by cumulative addition of the weights and if
        # the random number is withing individual range, the individual is added
        # for reproduction. IMPORTANT: random numbers must be sorted 
        reproduction = []
        cc = 0
        i = 0
        for j in range(len(fitenss_population)):
            cc += fitenss_population[j]

            while i < len(rand) and cc >= rand[i]:
                reproduction.append(population[j])
                i += 1

        # Create new generation from new parents
        random.shuffle(reproduction)
        new_population = []
        for i in range(0, count, 2):
            male = reproduction[i]
            female = reproduction[i+1]

            child = []
            for i in range(len(male)):
                min_ = min([male[i], female[i]])
                max_ = max([female[i], male[i]])

                v = np.random.uniform(min_, max_)
                child.append(v)

            new_population.append(child)

        # Mutate
        new_population = self.mutate_population(new_population, self.d.mutate,
            self.d.v_min, self.d.v_max)

        self.population = new_population
