from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import List, Any
from random import randint, random, uniform
from functools import reduce
from operator import add, or_

# Solver Base
# Contains functionality for each genetic algorithm to use
class PolynomialOptimisationBase(ABC):
    def __init__(self, polynomial_data):
        self.d = polynomial_data
        
        self.constants = dict()
        self.population = self.generate_population()

        self.fitness_history = []
        self.best_fit = [self.fitness(self.population[0]), self.population[0].copy()]   
        
        super().__init__()

    # Abstract class required to be implemented in child class
    @abstractmethod
    def evolve(self):
        pass

    # Generates an array of powers of a given number up to the eq_order
    def generate_power_array(self, number: int):
        return [number**i for i in range(1, self.d.eq_order + 1)]

    # To decrease computation time, powers are calculated once and stored in 
    # a list
    def get_power(self, number: int, power: int):
        if number in self.constants:
            return self.constants[number][power-1]
        else:
            self.constants[number] = self.generate_power_array(number)

        return self.constants[number][power-1]

    # Generates random individual within the provided boundries
    def generate_individual(self):
        return [ uniform(self.d.v_min, self.d.v_max) for i in range(self.d.eq_order) ]

    # Generates the population of p_size size
    def generate_population(self):
        return [ self.generate_individual() for i in range(self.d.p_size)]

    # Fitness at the given x,y position of the individual
    # Metric used: sum of the variation squared 
    def fitness_at_pos(self, x, y, individual):
        sum = self.d.constant
     
        for i in range(self.d.eq_order):           
            sum += (individual[i] * self.get_power(x, i+1)) 

        return (sum - y) ** 2

    # Finds the fitness of the given individual
    def fitness(self, individual):
        return reduce(add, (self.fitness_at_pos(xy[0], xy[1], individual) for xy in self.d.data_points))

    # Finds the mean population fitness
    def mean_population_fitness(self):
        summed = reduce(add, (self.fitness(x) for x in self.population))
        return summed / (self.d.p_size * 1.0)

    # Performs training to find the optimal solution
    # Stops if certain params are met
    def train(self):
        for _ in range(self.d.max_iterations):
            self.evolve()

            fitness = self.mean_population_fitness()
            self.fitness_history.append(fitness)

            last_values = self.fitness_history[-self.d.population_stagnation:]
            if len(last_values) == self.d.population_stagnation:
                is_lower = reduce(or_, (x > self.fitness_history[-1] for x in last_values))
                if not is_lower:
                    #print("Population Stagnation. Abort.")
                    break

            if self.best_fit[0] <= self.d.optimal_individual:
                #print("Optimal Individual Found.")
                break

            if fitness <= self.d.optimal_population:
                #print("Population Optimal Found.")
                break
    
    # Returns the fitness histor of the algorithm
    def get_fitness_history(self):
        return self.fitness_history

    # Mutates the population
    def mutate_population(self, population, mutate_rate, v_min, v_max):
        for individual in population:
            if mutate_rate > random(): # random number between 0.0 to 1.0
                pos_to_mutate = randint(0, len(individual)-1)
                individual[pos_to_mutate] = uniform(v_min, v_max)

        return population

    # Checks if the individual has best fitness if true, replaces the stored
    # indiviual
    def keep_if_best_result(self, fitness, individual):
        # keep the best result if better than any other
        if fitness < self.best_fit[0]:
            self.best_fit[0] = fitness
            self.best_fit[1] = individual.copy()


# Class for storage of data
@dataclass
class PolynomialData():
    data_points: List

    eq_order: int = 5
    p_size: int = 500
    v_min: int = -100
    v_max: int = 100
    constant: float = 0.0

    retain: float = 0.50
    mutate: float = 0.05
    random_select: float = 0.01

    max_iterations: int = 1500
    optimal_individual: float = 0.01
    optimal_population: float = 0.1
    population_stagnation: int = 50
