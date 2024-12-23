from util import read
import networkx as nx

edges = list(map(lambda x: tuple(x.split("-")), read().splitlines()))
graph = nx.Graph(edges)
print(','.join(sorted(max(nx.find_cliques(graph), key=len))))
