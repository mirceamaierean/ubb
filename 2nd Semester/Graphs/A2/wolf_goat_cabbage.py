class wolf_goat_cabbage:
    incompatibilities = [
        ['c', 'g', 'w'],
        ['g', 'w'],
        ['c', 'g']
    ]

    def __init__(self, left_side=['c', 'g', 'w'], right_side=[], boat_side=False, children=[]):
        self.left_side = left_side
        self.right_side = right_side
        self.boat_side = boat_side
        self.children = children

    def __str__(self):
        return str(str(self.left_side) + " " + str(self.right_side) + " The man is on the " + ("left" if not self.boat_side else "right") + " side")

    def generate_children(self, previous_states, dad_map):
        children = []
        if not self.boat_side:
            for i in self.left_side:
                new_left = self.left_side[:]
                new_left.remove(i)
                new_right = self.right_side[:]
                new_right.append(i)
                if sorted(new_left) not in wolf_goat_cabbage.incompatibilities and not wolf_goat_cabbage.state_in_previous(previous_states, new_left, new_right, not self.boat_side):
                    child = wolf_goat_cabbage(
                        new_left, new_right, not self.boat_side, [])
                    children.append(child)
                    dad_map[child] = self
            if sorted(self.left_side) not in wolf_goat_cabbage.incompatibilities and not wolf_goat_cabbage.state_in_previous(previous_states, self.left_side[:], self.right_side[:], not self.boat_side):
                child = wolf_goat_cabbage(
                    self.left_side[:], self.right_side[:], not self.boat_side, [])
                children.append(child)
                dad_map[child] = self
        else:
            for i in self.right_side:
                new_left = self.left_side[:]
                new_left.append(i)
                new_right = self.right_side[:]
                new_right.remove(i)
                if sorted(new_right) not in wolf_goat_cabbage.incompatibilities and not wolf_goat_cabbage.state_in_previous(previous_states, new_left, new_right, not self.boat_side):
                    child = wolf_goat_cabbage(new_left, new_right,
                                              not self.boat_side, [])
                    children.append(child)
                    dad_map[child] = self
            if sorted(self.right_side) not in wolf_goat_cabbage.incompatibilities and not wolf_goat_cabbage.state_in_previous(previous_states, self.left_side[:], self.right_side[:], not self.boat_side):
                child = wolf_goat_cabbage(
                    self.left_side[:], self.right_side[:], not self.boat_side, [])
                children.append(child)
                dad_map[child] = self
        self.children = children

    @staticmethod
    def state_in_previous(previous_states, left_side, right_side, boat_side):
        return any(
            sorted(left_side) == sorted(i.left_side) and
            sorted(right_side) == sorted(i.right_side) and
            boat_side == i.boat_side
            for i in previous_states
        )
