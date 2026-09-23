# -*- coding: utf-8 -*-
"""
Created on Wed Jan  8 23:26:11 2025

@author: user
"""

import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

# Créer un graphe orienté
G = nx.DiGraph()

# Ajouter les nœuds avec attributs
nodes = [(i, {"color": "blue", "size": 5000}) for i in range(27)]

"""
# Liste des nœuds à exclure
excluded_nodes = {5, 7, 8, 10, 11, 12, 14, 15, 18, 19, 21, 22, 23, 25, 2}

# Créer un graphe sans ces nœuds
nodes = [(i, {"color": "blue", "size": 5000}) for i in range(27) if i not in excluded_nodes]
"""



# Ajuster les attributs spécifiques des nœuds
nodes[0] = (0, {"color": "blue", "size": 5000})  # Nœud central
nodes[8] = (8, {"color": "blue", "size": 5000})   # Nœud 8 en rose
nodes[9] = (9, {"color": "blue", "size": 5000})  # Nœud 9 en vert

# Ajouter les nœuds correctement au graphe
G.add_nodes_from(nodes)



# Ajouter les arcs avec étiquettes
edges = [
    (0, 0, 'bl'),
    (0, 1, 'l'),
    (1, 1, 'l + c'),
    (1, 2, 'autre'),
    (0, 3, ';'),
    (0, 4, 'c'),
    (4, 5, 'autre'),
    (0, 6, ':'),
    (6, 7, '='),
    (6, 8, 'autre'),
    (0, 9, '<'),
    (9, 10, '='), (9, 11, '>'), (9, 12, 'autre'),
    (0, 13, '>'), (13, 15, 'autre'), (13, 14, '='), # Liens impliquant 13, 14, 15
    (0, 16, '='),
    (0, 17, '|'), (17, 19, 'autre'), (17, 18, '|'),  # Liens impliquant 17, 18, 19
    (0, 20, '('), (20, 25, 'autre'),               # Liens impliquant 20, 25
    (20, 21, '*'), (21, 22, '*'), (22, 23, ')'), # Suite pour 21, 22, 23
    (21,21, 'autre'),
    (0, 26, ','), (0, 24, ')'),                # Liens impliquant 26, 24
]

"""
edges = [
    (0, 0, 'bl'),
    (0, 1, 'l'),
    (0, 3, ';'),
    (0, 4, 'c'),
    (0, 6, ':'),
    (0, 9, '<'),
    (0, 13, '>'),
    (0, 16, '='),
    (0, 17, '|'),
    (0, 20, '('),
    (0, 26, ','),
    (0, 24, ')')]

"""

G.add_edges_from([(u, v, {"label": lbl}) for u, v, lbl in edges])

# Extraire les étiquettes pour l'affichage
edge_labels = {(u, v): d.get('label', '') for u, v, d in G.edges(data=True)}

print (G)

# Positionner les nœuds de façon circulaire autour du nœud 0
angle_step = 2 * np.pi / (len(nodes) - 1)  # Nombre d'angles
radius = 2  # Rayon du cercle
pos = {0: (0, 0)}  # Position centrale pour le nœud 0



# Parcourir les nœuds dans l'ordre inverse
for i, node in enumerate(range(len(nodes)-1, 0, -1)):  # Inverse de l'itération
    if i != 25:
        angle = i * angle_step
        pos[node] = (radius * np.cos(angle), radius * np.sin(angle))
    else:
        # Optionnel: assigner une position spécifique pour le nœud 25 si nécessaire
        pos[node] = (radius * np.cos(25 * angle_step), radius * np.sin(25 * angle_step))


# Dessiner le graphe avec styles
plt.figure(figsize=(15, 12))
node_colors = [data["color"] for _, data in G.nodes(data=True)]
node_sizes = [data["size"] for _, data in G.nodes(data=True)]

nx.draw(
    G, pos, with_labels=True, node_color=node_colors, node_size=node_sizes, 
    edge_color='black', arrowsize=70, font_weight='bold'
)
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=30, label_pos=0.5)

nx.spring_layout(G, weight='length')

# Afficher le graphe
plt.show()
