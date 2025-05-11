import random

class Node:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level):
        self.max_level = max_level
        self.header = Node(None, self.max_level)
        self.level = 0

    def random_level(self):
        level = 0
        while random.random() < 0.5 and level < self.max_level:
            level += 1
        return level

    def insert(self, value):
        current = self.header
        update = [None] * (self.max_level + 1)

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current

        current = current.forward[0]
        if current is None or current.value != value:
            new_level = self.random_level()
            if new_level > self.level:
                for i in range(self.level + 1, new_level + 1):
                    update[i] = self.header
                self.level = new_level

            new_node = Node(value, new_level)
            for i in range(new_level + 1):
                new_node.forward[i] = update[i].forward[i]
                update[i].forward[i] = new_node

    def search(self, value):
        current = self.header
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
        current = current.forward[0]
        return current.value if current and current.value == value else None

    def closest(self, value):
        current = self.header
        closest_value = None

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
        
        if current and current.value is not None:
            closest_value = current.value
        
        if current.forward[0]:
            if closest_value is None or abs(current.forward[0].value - value) < abs(closest_value - value):
                closest_value = current.forward[0].value

        return closest_value

# Example usage
if __name__ == "__main__":
    skip_list = SkipList(max_level=3)
    
    elements = [3, 6, 7, 9, 12, 19, 17, 26, 21, 25]
    for elem in elements:
        skip_list.insert(elem)

    print("Searching for 19:", skip_list.search(19))  # Output: 19
    print("Searching for 15:", skip_list.search(15))  # Output: None

    value_to_find = 20
    closest = skip_list.closest(value_to_find)
    print(f"The closest value to {value_to_find} is {closest}.")  # Output: The closest value to 20 is 21.