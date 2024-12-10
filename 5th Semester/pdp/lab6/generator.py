import random
import argparse
import sys

def generate_hamiltonian_cycle(n):
    """
    Generates a Hamiltonian cycle for a directed graph with n nodes.
    The cycle is 1 -> 2 -> 3 -> ... -> n -> 1.

    Returns:
        List of tuples representing directed edges in the cycle.
    """
    cycle = []
    for i in range(0, n - 1):
        cycle.append((i, i + 1))
    cycle.append((n - 1, 0))  
    return cycle

def generate_additional_edges(n, existing_edges, extra_edges):
    """
    Generates additional random edges for a directed graph, ensuring no duplicates or self-loops.

    Args:
        n (int): Number of nodes in the graph.
        existing_edges (set): Set of existing edges to avoid duplicates.
        extra_edges (int): Number of additional edges to generate.

    Returns:
        List of tuples representing additional directed edges.
    """
    additional = []
    possible_edges = set((u, v) for u in range(0, n) for v in range(0, n) if u != v) - existing_edges

    if extra_edges > len(possible_edges):
        print(f"Error: Cannot add {extra_edges} extra edges. Maximum possible is {len(possible_edges)}.")
        sys.exit(1)

    additional = random.sample(possible_edges, extra_edges)
    return additional

def write_graph(n, edges, output_file):
    """
    Writes the graph to a file in the specified format.

    Args:
        n (int): Number of nodes.
        edges (list): List of tuples representing directed edges.
        output_file (str): File path to write the graph.
    """
    m = len(edges)
    with open(output_file, 'w') as f:
        f.write(f"{n} {m}\n")
        for u, v in edges:
            f.write(f"{u} {v}\n")
    print(f"Graph written to {output_file} with {n} nodes and {m} edges.")

def main():
    parser = argparse.ArgumentParser(description="Generate a directed graph with a Hamiltonian cycle.")
    parser.add_argument('-n', '--nodes', type=int, required=True, help='Number of nodes in the graph.')
    parser.add_argument('-e', '--extra_edges', type=int, default=0, help='Number of additional random edges to add.')
    parser.add_argument('-o', '--output', type=str, default='graph.in', help='Output file name.')

    args = parser.parse_args()

    n = args.nodes
    extra_edges = args.extra_edges
    output_file = args.output

    if n < 1:
        print("Error: Number of nodes must be at least 1.")
        sys.exit(1)

    # Generate Hamiltonian cycle
    cycle = generate_hamiltonian_cycle(n)
    existing_edges = set(cycle)

    # Generate additional edges
    if extra_edges > 0:
        additional = generate_additional_edges(n, existing_edges, extra_edges)
    else:
        additional = []

    # Combine all edges
    all_edges = cycle + additional

    # Write to file
    write_graph(n, all_edges, output_file)

if __name__ == "__main__":
    main()
