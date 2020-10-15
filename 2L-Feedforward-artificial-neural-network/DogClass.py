# Class template for a dog object
class Dog:
    def __init__(self, name, hungerLevel):
        self.name = name
        self.hungerLevel = hungerLevel

    def status(self):
        print("Dog is called ", self.name)
        print("Dog hunger level is ", self.hungerLevel)
        pass

    def setHungerLevel(self, hungerLevel):
        self.hungerLevel = hungerLevel
        pass

    def bark(self):
        print("Woff!")
        pass

# Create dogs
lassie = Dog("Lassie", "Mild")
yoda = Dog("Yoda", "Ravenous")

# Check on Yoda & Lassie
yoda.status()
lassie.status()

# Get Lassie to bark
lassie.bark()

# Feed Yoda
yoda.setHungerLevel("Full")
yoda.status()