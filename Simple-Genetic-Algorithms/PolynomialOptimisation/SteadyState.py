from PolynomialOptimisationBase import PolynomialOptimisationBase, PolynomialData
import numpy as np
from more_itertools import sort_together
from functools import reduce
from operator import add, or_
import random

# Polynomial Optimiser Steady State selective
class PolynomialOptimisationSteadyState(PolynomialOptimisationBase):
    def __init__(self, polynomial_data):
        super().__init__(polynomial_data)

    # Sorts the population by grade 
    def sort_population_by_grade(self):
        fitenss_population = [ self.fitness(individual) for 
            individual in self.population]
        fitenss_population, population = sort_together([fitenss_population,
            self.population])
        
        self.keep_if_best_result(fitenss_population[0], population[0])
        self.population = population
    
    # Returns new paretns
    def get_new_parents(self, retain, random_select):
        # Number of top fitness parents to select
        retain_index = int(self.d.p_size*retain)

        # Get top parents
        parents = self.population[ :retain_index ]

        # Get random parents bast on random_select rate
        random_parents = []
        for individual in self.population[retain_index:]:
            if random_select > random.random():
                random_parents.append(individual)

        # Return list
        return [*parents, *random_parents]

    # Retruns children based on parents provided
    def generate_children(self, parents, count):
        children = []
        parents_length = len(parents)

        while len(children) < count:
            # Select two random parents
            p1 = random.randint(0, parents_length-1)
            p2 = random.randint(0, parents_length-1)

            if p1 != p2: # merge if parents are different
                p1 = parents[p1]
                p2 = parents[p2]

                child = (np.array(p1) + np.array(p2)) / 2 
                children.append(child.tolist())                  

        return children

    def evolve(self):
        self.sort_population_by_grade()

        parents = self.get_new_parents(self.d.retain, self.d.random_select)
        children = self.generate_children(parents, (self.d.p_size - len(parents)))

        self.population = self.mutate_population([*parents, *children],
            self.d.mutate, self.d.v_min, self.d.v_max)
