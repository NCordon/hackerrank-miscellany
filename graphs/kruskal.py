#!/usr/bin/python3
from operator import attrgetter

class Edge:
    def __init__(self, first, second, cost):
        self.first  = first
        self.second = second
        self.cost   = cost

class DisjointSet:
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank   = [0 for i in range(n)]

    def find(self, node):
        if node != self.parent[node]:
            self.parent[node] = self.find(self.parent[node])

        return self.parent[node];


    def merge(self, u, v):
        u_parent = self.find(u)
        v_parent = self.find(v)

        if self.rank[u_parent] < self.rank[v_parent]:
            self.parent[u_parent] = v_parent
        else:
            self.parent[v_parent] = u_parent

        if self.rank[u_parent] == self.rank[v_parent]:
            self.rank[v_parent] += 1


def mst(n, edges):
    edges = sorted(edges, key = attrgetter("cost"))
    result = 0
    forests = DisjointSet(n);

    for e in edges:
        first  = forests.find(e.first)
        second = forests.find(e.second)

        if first != second:
            result += e.cost
            forests.merge(first, second)

    return result


# Number of nodes
n = int(input())
# Number of edges
m = int(input())
edges = []

for i in range(m):
    u,v,w = map(int, input().split())
    current = Edge(u,v,w)
    edges.append(current)

result = mst(n, edges)
print(result)
