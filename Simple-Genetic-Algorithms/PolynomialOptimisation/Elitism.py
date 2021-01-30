from PolynomialOptimisationBase import PolynomialOptimisationBase, PolynomialData
import numpy as np
from more_itertools import sort_together
from functools import reduce
from operator import add, or_
import random

# Polynomial Optimiser Elitism selective
class PolynomialOptimisationElitism(PolynomialOptimisationBase):
    def __init__(self, polynomial_data):
        super().__init__(polynomial_data)

    def evolve(self):
        # pop = population
        pop = self.population

        # Population ranking 
        fitenss_pop = [self.fitness(individual) for individual in pop]
        fitenss_pop, pop = sort_together([fitenss_pop, pop])
        self.keep_if_best_result(fitenss_pop[0], pop[0])

        # Get top half of the population to go to the next generation
        old_count = int(self.d.p_size/2)
        new_pop = [v for v in pop[0:old_count]]

        # Generate second half of the populaiton by combining parents next to 
        # each other
        for i in range(0, self.d.p_size, 2):
            male = pop[i]
            female = pop[i+1]

            child = []
            for i in range(len(male)):
                min_ = min([male[i], female[i]])
                max_ = max([female[i], male[i]])

                v = np.random.uniform(min_, max_)
                child.append(v)

            new_pop.append(child)

        new_pop = self.mutate_population(new_pop, self.d.mutate, 
            self.d.v_min, self.d.v_max)
        
        self.population = new_pop
