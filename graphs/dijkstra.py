#!/usr/bin/python3
from queue import PriorityQueue

def solveDijkstra(adjacencies, weight):
    n = len(adjacencies)
    dist = [float('inf') for i in range(n)]
    dist[0] = 0
    to_visit = PriorityQueue()

    for u in adjacencies[0]:
        to_visit.put((weight[0][u], u))

    while not to_visit.empty():
        d,v = to_visit.get()

        if d < dist[v]:
            dist[v] = d
            for u in adjacencies[v]:
                to_visit.put((d + weight[v][u], u))

    return dist


num_nodes = int(input())
num_edges = int(input())
weight    = [[float('inf') for i in range(num_nodes)] for j in range(num_nodes)]
adjacencies = [[] for i in range(num_nodes)]

for i in range(num_edges):
    u,v,w = map(int, input().split())
    weight[u][v] = weight[v][u] = w
    adjacencies[u].append(v)
    adjacencies[v].append(u)

print(solveDijkstra(adjacencies, weight))
