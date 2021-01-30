# Example usage
from genetic import *
from statistics import median

# Constants for entire testing
p_count = 200
i_length = 10
target = 500
i_min = 0
i_max = 1000

# Number of generations p_count
number_of_p = []
for i in range(50, 1000, 50):
    print(i)
    v = []
    for _ in range(20):
        G = Genetic(target, i, i_length, i_min, i_max)
        G.train(2000)
        v.append(len(G.get_fitness_history()))

    number_of_p.append([i, median(v)])

print(number_of_p)


# i_length
number_of_p = []
for i in range(1, 16, 1):
    print(i)
    v = []
    for _ in range(50):
        i_length = i
        G = Genetic(target, p_count, i_length, i_min, i_max)
        G.train(500)
        v.append( len(G.get_fitness_history()))

    number_of_p.append([i, median(v)])

print(number_of_p)


# Random Select rate 0 -> 1, step 0.01
data = []
for i in np.arange(0.66, 0.75, 0.01):
    print(i)
    v = []
    for _ in range(11):
        G = Genetic(target, p_count, i_length, i_min, i_max, 0.2, i)
        G.train(1000)
        v.append( len(G.get_fitness_history()))

    data.append([i, median(v)])

print(data)

# Retain rate 0 -> 1, step 0.01
data = []
for i in np.arange(0.61, 1, 0.01):
    print(i)
    v = []
    for _ in range(11):
        G = Genetic(target, p_count, i_length, i_min, i_max, i)
        G.train(1000)
        v.append(len(G.get_fitness_history()))

    data.append([i, median(v)])

print(data)

# mutate select 0 -> 1, step 0.01
data = []
for i in np.arange(0.15, 0.45, 0.01):
    print(i)
    v = []
    for _ in range(11):
        G = Genetic(target, p_count, i_length, i_min, i_max, 0.2, 0.05, i)
        G.train(1000)
        v.append( len(G.get_fitness_history()))

    data.append([i, median(v)])

print(data)
