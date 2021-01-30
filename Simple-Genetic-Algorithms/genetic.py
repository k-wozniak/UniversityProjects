from random import randint, random
from operator import add, or_
from functools import reduce
from statistics import mean
import numpy as np

class Genetic:
    def __init__(self, target, p_count, i_length, i_min, i_max, retain=0.2, random_select=0.05, mutate=0.01):
        self.target = target
        self.p_count = p_count
        self.i_length = i_length
        self.i_min = i_min
        self.i_max = i_max
        self.retain = retain
        self.random_select = random_select
        self.mutate = mutate

        self.p = self.__population()
        self.fitness_history = [self.grade(self.p, self.target)]

        self.best_individual = self.p[0]
        self.best_individual_fitness = self.fitness(self.best_individual, self.target)

    'Creates a member of the population.'
    def __individual(self):
        return [ randint(self.i_min, self.i_max) for x in range(self.i_length) ]

    'Create a number of individuals (i.e. a population).'
    def __population(self):
        return [ self.__individual() for x in range(self.p_count) ]

    'Determine the fitness of an individual. Higher is better.'
    def fitness(self, individual, target):
        newArr = []
        for v in individual:
            newArr.append(abs(target - v))

        mm = mean(newArr)
        return mm

    def grade(self, pop, target):
        'Find average fitness for a population.'
        summed = reduce(add, (self.fitness(x, target) for x in pop))
        return summed / (len(pop) * 1.0)

    def evolve(self, pop, target):
        graded = [ (self.fitness(x, target), x) for x in pop]

        graded = sorted(graded)
        # New Best individual check
        if self.best_individual_fitness > graded[0][0]:
            self.best_individual_fitness = graded[0][0]
            self.best_individual = graded[0][1]

        graded = [ x[1] for x in sorted(graded)]
        retain_length = int(len(graded)*self.retain)
        parents = graded[:retain_length]
        
        # randomly add other individuals to
        # promote genetic diversity
        for individual in graded[retain_length:]:
            if self.random_select > random():
                parents.append(individual)
        
        # mutate some individuals
        for individual in parents:
            if self.mutate > random(): # random number between 0.0 to 1.0
                pos_to_mutate = randint(0, len(individual)-1)
                individual[pos_to_mutate] = randint(self.i_min, self.i_max)

        # crossover parents to create children
        parents_length = len(parents)
        desired_length = len(pop) - parents_length
        children = []
        while len(children) < desired_length:
            male = randint(0, parents_length-1)
            female = randint(0, parents_length-1)
            if male != female:
                male = parents[male]
                female = parents[female]

                child = []
                for i in range(len(male)):
                    min_ = min([male[i], female[i]])
                    max_ = max([female[i], male[i]])

                    v = randint(min_, max_)
                    child.append(v)

                children.append(child)  
                

        parents.extend(children)
        return parents 

    def train(self, max_iterations, optimal_individual = 0.01, population_optimal = 0.1, population_stagnation = 10):
        for _ in range(max_iterations):
            print(self.p[0])
            self.p = self.evolve(self.p, self.target)
            
            fitness = self.grade(self.p, self.target)
            self.fitness_history.append(fitness)

            if len(self.fitness_history[-population_stagnation:]) == population_stagnation:
                is_lower = reduce(or_, (x > self.fitness_history[-1] for x in self.fitness_history[-population_stagnation:]))
                if is_lower != True:
                    print("Population Stagnation Found.")
                    break

            if self.best_individual_fitness <= optimal_individual:
                print("Optimal Individual Found.")
                break

            if fitness <= population_optimal:
                print("Population Optimal Found.")
                break

    def get_fitness_history(self):
        return self.fitness_history