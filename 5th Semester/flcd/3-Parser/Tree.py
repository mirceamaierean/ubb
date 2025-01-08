class TreeNode:
    def __init__(self, node_id, symbol):
        self.id = node_id
        self.symbol = symbol
        self.father = None
        self.sibling = None
        self.children = []

class Tree:
    def __init__(self):
        self.productions = []
        self.nodes = []
        self.root_id = None

    def add_production(self, head, body):
        self.productions.append((head, body))

    def add_node(self, symbol):
        node_id = len(self.nodes)
        node = TreeNode(node_id, symbol)
        self.nodes.append(node)
        return node_id

    def set_root(self, node_id):
        self.root_id = node_id

    def set_father(self, child_id, father_id):
        self.nodes[child_id].father = father_id

    def set_siblings(self, children_ids):
        for i in range(len(children_ids)-1):
            self.nodes[children_ids[i]].sibling = children_ids[i+1]

    def print_to_screen(self):
        print("Input accepted. Productions used:")
        for p in self.productions:
            head, body = p
            print(f"{head} -> {' '.join(body)}")

        print("\nParsing tree (father-sibling table):")
        print("ID | SYMBOL | FATHER | SIBLING")
        for node in self.nodes:
            father = node.father if node.father is not None else -1
            sibling = node.sibling if node.sibling is not None else -1
            print(f"{node.id} | {node.symbol} | {father} | {sibling}")

    def print_to_file(self, filename):
        with open(filename, 'w') as f:
            f.write("Input accepted. Productions used:\n")
            for p in self.productions:
                head, body = p
                f.write(f"{head} -> {' '.join(body)}\n")

            f.write("\nParsing tree (father-sibling table):\n")
            f.write("ID | SYMBOL | FATHER | SIBLING\n")
            for node in self.nodes:
                father = node.father if node.father is not None else -1
                sibling = node.sibling if node.sibling is not None else -1
                f.write(f"{node.id} | {node.symbol} | {father} | {sibling}\n")