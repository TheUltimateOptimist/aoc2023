import networkx as nx
from util import read

graph = nx.Graph()

for line in read().split("\n"):
    left, right = line.split(":")
    for node in right.strip().split():
        graph.add_edge(left, node)
        graph.add_edge(node, left)

graph.remove_edges_from(nx.minimum_edge_cut(graph))
a, b = nx.connected_components(graph)
print(f"result = {len(a) * len(b)}")
