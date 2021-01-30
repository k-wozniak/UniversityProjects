from PolynomialOptimisationBase import PolynomialOptimisationBase, PolynomialData
import numpy as np
from more_itertools import sort_together
from functools import reduce
from operator import add, or_
import random

# Polynomial Optimiser Ranking selective
class PolynomialOptimisationRanking(PolynomialOptimisationBase):
    def __init__(self, polynomial_data):
        super().__init__(polynomial_data)

    def evolve(self):
        # pop = population
        pop = self.population

        # Sort population by fitness
        fitenss_pop = [self.fitness(individual) for individual in pop]
        fitenss_pop, pop = sort_together([fitenss_pop, pop])
        self.keep_if_best_result(fitenss_pop[0], pop[0])

        # Generate random values in range of 0 to total sum of all weights
        ps = self.d.p_size
        count = ps * 2
        total_sum = (ps * (ps + 1)) / 2
        rand = np.random.randint(0, total_sum, count)

        # Generate new positions by cumulative addition of the weights and if
        # the random number is withing individual range, the individual is added
        # for reproduction. IMPORTANT: random numbers must be sorted 
        rand.sort() 
        reproduction = []
        cc = 0
        i = 0
        for j in range(ps):
            cc += (ps - j)

            while i < len(rand) and cc >= rand[i]:
                reproduction.append(pop[j])
                i += 1

        # Create offsprings
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
