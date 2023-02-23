from collections import defaultdict

class Grafo(object):
    """ Implementação básica de um grafo. """

    def __init__(self, arestas, direcionado=False):
        """Inicializa as estruturas base do grafo."""
        self.adj = defaultdict(set)
        self.direcionado = direcionado
        self.adiciona_arestas(arestas)


    def get_vertices(self):
        """ Retorna a lista de vértices do grafo. """
        return list(self.adj.keys())


    def get_arestas(self):
        """ Retorna a lista de arestas do grafo. """
        return [(k, v) for k in self.adj.keys() for v in self.adj[k]]


    def adiciona_arestas(self, arestas):
        """ Adiciona arestas ao grafo. """
        for u, v in arestas:
            self.adiciona_arco(u, v)


    def adiciona_arco(self, u, v):
        """ Adiciona uma ligação (arco) entre os nodos 'u' e 'v'. """
        self.adj[u].add(v)
        # Se o grafo é não-direcionado, precisamos adicionar arcos nos dois sentidos.
        if not self.direcionado:
            self.adj[v].add(u)


    def existe_aresta(self, u, v):
        """ Existe uma aresta entre os vértices 'u' e 'v'? """
        return u in self.adj and v in self.adj[u]


    def vizinhos(self, nodo):
        return self.adj[nodo]


    def __len__(self):
        return len(self.adj)


    def __str__(self):
        return '{}({})'.format(self.__class__.__name__, dict(self.adj))


    def __getitem__(self, v):
        return self.adj[v]

def intercept(set1, set2):
    result = set()
    for i in set1:
        if i in set2:
                result.add(i)
    return result

def bicolor(grafo: Grafo):
    for i in grafo.get_vertices():
        vizinhos = grafo.vizinhos(i)
        for v in vizinhos:
            vizinhos_vizinhos = grafo.vizinhos(v)
            if len(intercept(vizinhos, vizinhos_vizinhos)) != 0:
                return False
    return True

def main():
    while True:
        try:
            nv = input()
            na = int(input())
            arestas = set()
            for _ in range(0, na):
                aresta = map(int, input().split())
                arestas.add(tuple(aresta))
            grafo = Grafo(arestas)
            print("BICOLORABLE." if bicolor(grafo) else "NOT BICOLORABLE.")
       
        except:
            break
    # arestas = [(0, 1), (1, 2)]
    # grafo = Grafo(arestas)
    # print(bicolor(grafo))
    
main()
