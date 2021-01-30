import numpy as np
from operator import add
from random import randint, random, uniform
from functools import reduce

class GeneticPolynomialFinder:
    def __init__(self, data_points, eq_order = 5, min_max = [-100, 100], population_size = 100, constant = 0):
        self.data_points = data_points
        self.data_points_count = len(data_points)
        self.eq_order = eq_order
        self.min_max = min_max
        self.population_size = population_size
        self.fitness_history = []
        self.cons = constant

        self.constants = dict()
        self.population = self.generate_population()

        self.best_fit = [self.fitness(self.population[0]), self.population[0].copy()]   

    def generate_power_array(self, number):
        return [number**i for i in range(1, self.eq_order + 1)]

    def get_power(self, number, power):
        if number in self.constants:
            return self.constants[number][power-1]

        else:
            self.constants[number] = self.generate_power_array(number)

        return self.constants[number][power-1]

    def generate_individual(self):
        return [ uniform(self.min_max[0], self.min_max[1]) for i in range(self.eq_order) ]

    def generate_population(self):
        return [ self.generate_individual() for i in range(self.population_size)]

    def fitness_at_pos(self, x_y, individual):
        sum = self.cons
     
        for i in range(self.eq_order):           
            sum += (individual[i] * self.get_power(x_y[0], i+1)) 

        return (sum - x_y[1]) ** 2

    def fitness(self, individual):
        return reduce(add, (self.fitness_at_pos(x, individual) for x in self.data_points))

    def population_fitness(self):
        summed = reduce(add, (self.fitness(x) for x in self.population))
        return summed / (self.population_size * 1.0)

    def sort_population_by_grade(self):
        fitenss_population = [ (self.fitness(individual), individual) for individual in self.population]
        sorted_fitenss_population = sorted(fitenss_population)
        
        # keep the best result if better than any other
        if sorted_fitenss_population[0][0] < self.best_fit[0]:
            self.best_fit[0] = sorted_fitenss_population[0][0]
            self.best_fit[1] = sorted_fitenss_population[0][1].copy()

        self.population = [ x[1] for x in sorted_fitenss_population]

    def get_new_parents(self, retain = 0.2, random_select = 0.05):
        retain_index = int(self.data_points_count*retain)

        # Get top parents
        parents = self.population[ :retain_index ]

        # Get random parents
        random_parents = []
        for individual in self.population[retain_index:]:
            if random_select > random():  # random float number between 0.0 to 1.0
                random_parents.append(individual)

        # Return list
        return [*parents, *random_parents]

    def mutate_population(self, population, mutate_rate):
        for individual in population:
            if mutate_rate > random(): # random number between 0.0 to 1.0
                pos_to_mutate = randint(0, len(individual)-1)
                individual[pos_to_mutate] = uniform(self.min_max[0], self.min_max[1])

        return population

    def generate_children(self, parents, count):
        children = []
        parents_length = len(parents)

        while len(children) < count:
            # Select parents
            p1 = randint(0, parents_length-1)
            p2 = randint(0, parents_length-1)

            if p1 != p2: # merge if parents are different
                p1 = parents[p1]
                p2 = parents[p2]

                child = (np.array(p1) + np.array(p2)) / 2 
                children.append(child.tolist())                  

        return children

    def evolve(self, retain = 0.10, random_select = 0.01, mutate = 0.05):
        self.sort_population_by_grade()

        parents = self.get_new_parents(retain, random_select)
        parents = self.mutate_population(parents, mutate)

        children = self.generate_children(parents, (self.population_size - len(parents)))

        self.population = [*parents, *children]

    def train(self, max_iterations, fitness_threshold):
        for _ in range(max_iterations):
            self.evolve()

            fitness = self.population_fitness()
            self.fitness_history.append(fitness)

            if fitness < fitness_threshold: 
                break

    def get_fitness_history(self):
        return self.fitness_history