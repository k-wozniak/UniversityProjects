import numpy as np

class Perceptron:
    weights = [1.0, 1.0] # Default value
    bias = -1
    def __init__(self, w, b):
        self.weights = w
        self.bias = b

    def Compute(self, inputs_list):
        inputs = np.array(inputs_list)
        weights = np.array(self.weights)
        
        summed = np.dot(inputs, weights)
        summed = summed + self.bias 

        return (1 if summed > 0 else 0)


p_AND = Perceptron([1, 1], -1.5) # AND gate
p_OR = Perceptron([2, 2], -1) # OR gate
p_NAND = Perceptron([-1, -1], 1.5) # NAND gate
p_NOR = Perceptron([-1, -1], 1) # NOR gate

# XOR gate - not possible with current activation function
# p_XOR = Perceptron([0.5, 0.5], 0)

# Simulate all possible inputs
for perceptron in [p_AND, p_OR, p_NAND, p_NOR]:
    for x in range(2):
        for y in range(2):
            inputs = [x, y]
            perceptron.Compute(inputs)
            print("Result for [", x, " ", y, "]: ", perceptron.Compute(inputs))
