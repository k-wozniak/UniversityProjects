from PolynomialOptimisationBase import PolynomialOptimisationBase, PolynomialData
from PolynomialDataFactory import PolynomialDataFactory
from RouleteWheel import PolynomialOptimisationRouleteWheel
from Elitism import PolynomialOptimisationElitism
from Ranking import PolynomialOptimisationRanking
from SteadyState import PolynomialOptimisationSteadyState

from more_itertools import sort_together
import sys
import numpy as np

# returns a new instance of the selected algorithm
def getAlgorithm(name, data):
    return {
        'elit': PolynomialOptimisationElitism(data),
        'rank': PolynomialOptimisationRanking(data),
        'whel': PolynomialOptimisationRouleteWheel(data),
        'stat': PolynomialOptimisationSteadyState(data),
    }.get(name)

# performs training on the data with a selected repeats number and chooses
# best fit outcomes
def train(name, data_array, a_type, repeats):
    print(name)
    
    for d in data_array:
        stat = [sys.maxsize, []]

        for _ in range(repeats):
            algorithm = getAlgorithm(a_type, d)
            algorithm.train()
            
            if stat[0] > algorithm.best_fit[0]:
                stat[0] = algorithm.best_fit[0]
                stat[1] = algorithm.best_fit[1].copy()

        print(stat)

# Init values
data_factory = PolynomialDataFactory()
data_array = data_factory.get_data_array()

data_array = [
    data_factory.get_data_order_5_type_3(),
]

collected_data = []
repeats = 50

# training on each type of implemented algorithm
train('Elitism', data_array, 'elit' , repeats)
train('Ranking', data_array, 'rank' , repeats)
train('RouleteWheel', data_array, 'whel' , repeats)
train('SteadyState', data_array, 'stat' , repeats)