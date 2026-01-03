from Tree import Tree

class Grammar:
    def __init__(self, N, sigma, P, S):
        self.N = N  # Non-terminals
        self.Sigma = sigma  # Terminals
        self.P = P  # Productions (dictionary: key -> list of productions)
        self.S = S  # Start symbol
        self.action_table, self.goto_table = self.build_parsing_table()

    def get_N(self):
        return self.N

    def get_Sigma(self):
        return self.Sigma

    def get_P(self):
        return self.P

    def get_S(self):
        return self.S

    def check_is_valid(self):
        self.check_is_CFG()
        for key in self.P.keys():
            for production in self.P[key]:
                self.check_is_valid_production(production)

    def check_is_CFG(self):
        for key in self.P.keys():
            if key not in self.N:
                raise ValueError(f"Key {key} is not in N")

    def check_is_valid_production(self, production):
        production = production.split(" ")
        for symbol in production:
            # Check if symbol is in N or Sigma or is epsilon
            if symbol not in self.N and symbol not in self.Sigma and symbol != "":
                raise ValueError(f"Symbol {symbol} is not in N or Sigma")

    def get_productions_for_non_terminal(self, non_terminal):
        if non_terminal not in self.P:
            raise ValueError(f"Non-terminal {non_terminal} is not in P")
        return self.P[non_terminal]

    def print_grammar(self):
        print("N, set of non terminals = ", self.N)
        print("Sigma, set of terminals = ", self.Sigma)
        print("S, initial state = ", self.S)
        print("P, set of productions = ", self.P)

    def closure(self, items):
        closure_list = list(items)
        added = True

        while added:
            added = False
            new_items = []
            for item in closure_list:
                _, body, dot_index = item
                # If the dot is before a non-terminal, expand the closure
                if dot_index < len(body) and body[dot_index] in self.N:
                    non_terminal = body[dot_index]
                    # Add all productions for the non-terminal
                    for production in self.get_productions_for_non_terminal(non_terminal):
                        new_item = (non_terminal, tuple(production.split(" ")), 0)
                        # Add new items only if they aren't already in the closure
                        if new_item not in closure_list and new_item not in new_items:
                            new_items.append(new_item)
                            added = True
            # Extend the closure list with the new items
            closure_list.extend(new_items)

        return closure_list

    def goto(self, items, symbol):
        goto_list = []
        for item in items:
            head, body, dot_index = item
            # Check if the dot is before the specified symbol
            if dot_index < len(body) and body[dot_index] == symbol:
                new_item = (head, body, dot_index + 1)  # Move the dot one step to the right
                if new_item not in goto_list:
                    goto_list.append(new_item)
        return self.closure(goto_list)

    def canonical_collection(self):
        # Start with the initial item for the augmented grammar
        start_item = (f"{self.S}'", (self.S,), 0) # Body is a tuple
        initial_state = self.closure([start_item]) # Compute closure of the start item
        states = [initial_state] # List to store all states (ordered)
        transitions = {} # Dictionary to store transitions (state, symbol -> next state)

        added = True
        while added:
            added = False
            for state in states:
                for symbol in self.N + self.Sigma:
                    next_state = self.goto(state, symbol)
                    # Add the new state if it is not already in the states list
                    if next_state and next_state not in states:
                        states.append(next_state)
                        transitions[(tuple(state), symbol)] = next_state
                        added = True

        return states, transitions

    def print_canonical_collection(self):
        states, transitions = self.canonical_collection()

        # Print states
        print("\nCanonical States:")
        for i, state in enumerate(states):
            print(f"State {i}:")
            for item in state:
                head, body, dot_index = item
                production = " ".join(body[:dot_index]) + " • " + " ".join(body[dot_index:])
                print(f"{head} -> {production}")

        # Print transitions
        print("\nTransitions:")
        for (state, symbol), target_state in transitions.items():
            print(f"From state {state} on symbol {symbol} -> {target_state}")

    def build_parsing_table(self):
        states, _ = self.canonical_collection()

        state_to_index = {tuple(s): i for i, s in enumerate(states)}

        action = {}
        goto = {}
        conflicts = []

        # We have an augmented start production: S' -> S
        # Accept condition: When we see item (S' -> S •, at end)

        for i, state in enumerate(states):
            for item in state:
                head, body, dot_index = item

                if head == f"{self.S}'" and dot_index == len(body):
                    self._put_action(action, i, '$', ('accept',), conflicts)

                elif dot_index < len(body):
                    symbol = body[dot_index]
                    if symbol in self.Sigma:
                        # It's a terminal, so we do a shift
                        next_state = self.goto(state, symbol)
                        if next_state:
                            j = state_to_index.get(tuple(next_state))
                            self._put_action(action, i, symbol, ('shift', j), conflicts)
                    else:
                        # It's a non-terminal, this will go into the GOTO table
                        next_state = self.goto(state, symbol)
                        if next_state:
                            j = state_to_index.get(tuple(next_state))
                            if j is not None:
                                self._put_goto(goto, i, symbol, j, conflicts)

                else:
                    for t in self.Sigma + ['$']:
                        self._put_action(action, i, t, ('reduce', (head, body)), conflicts)

        if conflicts:
            for c in conflicts:
                print("Conflict detected: ", c)
            raise ValueError("Conflicts detected in LR(0) parsing table.")

        return action, goto

    def _handle_shift(self, stack, state, symbol, node_stack, output, tokens, index):
        stack.append(symbol)
        stack.append(state)
        node_id = output.add_node(symbol)
        node_stack.append(node_id)
        if symbol != '':
            index += 1
        return index

    def _handle_reduce(self, stack, head, body, node_stack, output, current_symbol, index):
        to_pop = 2 * len(body)
        children = []
        while to_pop > 0:
            stack.pop()
            stack.pop()
            node_id = node_stack.pop()
            children.append(node_id)
            to_pop -= 2
        children.reverse()

        state = stack[-1]
        if (state, head) not in self.goto_table:
            raise ValueError(f"Syntax error at token {current_symbol}, position {index}")

        next_state = self.goto_table[(state, head)]
        stack.append(head)
        stack.append(next_state)

        head_node_id = output.add_node(head)
        for c_id in children:
            output.set_father(c_id, head_node_id)
        output.set_siblings(children)
        output.nodes[head_node_id].children = children
        node_stack.append(head_node_id)
        output.add_production(head, body)

    def _handle_accept(self, node_stack, output):
        if len(node_stack) == 1:
            output.set_root(node_stack[0])
        
    def build_parsing_tree(self, tokens):
        stack = [0]
        output = Tree()
        node_stack = []
        index = 0

        while True:
            print(stack)
            state = stack[-1]
            current_symbol = tokens[index] if index < len(tokens) else '$'

            if (state, current_symbol) not in self.action_table:
                # check if there is an epsilon production
                if (state, '') not in self.action_table:
                    raise ValueError(f"Syntax error at token {current_symbol}, position {index}")
                current_symbol = ''

            action = self.action_table[(state, current_symbol)]
            
            if action[0] == 'shift':
                index = self._handle_shift(stack, action[1], current_symbol, node_stack, output, tokens, index)

            elif action[0] == 'reduce':
                self._handle_reduce(stack, action[1][0], action[1][1], node_stack, output, current_symbol, index)

            elif action[0] == 'accept':
                self._handle_accept(node_stack, output)
                return output
            
    def _put_action(self, action, state, symbol, value, conflicts):
        key = (state, symbol)
        if key in action and action[key] != value:
            # Conflict
            conflicts.append(f"Action conflict at state {state}, symbol {symbol}: {action[key]} vs {value}")
        else:
            action[key] = value

    def _put_goto(self, goto, state, non_terminal, value, conflicts):
        key = (state, non_terminal)
        if key in goto and goto[key] != value:
            # Conflict
            conflicts.append(f"Goto conflict at state {state}, non_terminal {non_terminal}: {goto[key]} vs {value}")
        else:
            goto[key] = value