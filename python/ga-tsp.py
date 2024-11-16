import numpy as np
import random
import matplotlib.pyplot as plt

# 参数
POP_SIZE = 100        # 种群大小
GEN_COUNT = 1000      # 迭代次数
MUTATION_RATE = 0.01  # 变异率
CROSSOVER_RATE = 0.8  # 交叉率
N = 10                # 节点数量
CITY_RANGE = 100      # 节点坐标范围

# 随机生成n个二维节点
cities = np.random.randint(0, CITY_RANGE, (N, 2))

# 计算距离矩阵
def distance_matrix(cities):
    dist_matrix = np.zeros((N, N))
    for i in range(N):
        for j in range(N):
            dist_matrix[i, j] = np.linalg.norm(cities[i] - cities[j])
    return dist_matrix

dist_matrix = distance_matrix(cities)

# 个体表示
def create_individual():
    individual = list(range(N))
    random.shuffle(individual)
    return individual

# 适应度函数
def fitness(individual, dist_matrix):
    total_distance = 0
    for i in range(N - 1):
        total_distance += dist_matrix[individual[i], individual[i + 1]]
    total_distance += dist_matrix[individual[-1], individual[0]]  # 回到起点
    return total_distance

# 轮盘赌
def selection(population, fitnesses):
    max_fit = sum(1 / (fit + 1e-10) for fit in fitnesses)  # 避免除以0
    pick = random.uniform(0, max_fit)
    current = 0
    for individual, fit in zip(population, fitnesses):
        current += 1 / (fit + 1e-10)
        if current > pick:
            return individual

# 交叉（部分映射交叉）
def crossover(parent1, parent2):
    size = len(parent1)
    cxpoint1, cxpoint2 = sorted(random.sample(range(size), 2))
    
    child1, child2 = [-1]*size, [-1]*size
    child1[cxpoint1:cxpoint2] = parent1[cxpoint1:cxpoint2]
    child2[cxpoint1:cxpoint2] = parent2[cxpoint1:cxpoint2]
    
    fill_child(child1, parent2)
    fill_child(child2, parent1)

    return child1, child2

def fill_child(child, parent):
    p2_index = 0
    for i in range(len(child)):
        if child[i] == -1:
            while parent[p2_index] in child:
                p2_index += 1
            child[i] = parent[p2_index]

# 变异操作（交换两个随机位置）
def mutate(individual):
    pos1, pos2 = random.sample(range(len(individual)), 2)
    individual[pos1], individual[pos2] = individual[pos2], individual[pos1]

# 初始化种群
population = [create_individual() for _ in range(POP_SIZE)]

# 主循环
best_distance = float('inf')
best_individual = None

for gen in range(GEN_COUNT):
    fitnesses = [fitness(ind, dist_matrix) for ind in population]
    
    new_population = []
    
    for _ in range(POP_SIZE // 2):
        parent1 = selection(population, fitnesses)
        parent2 = selection(population, fitnesses)
        
        if random.random() < CROSSOVER_RATE:
            child1, child2 = crossover(parent1, parent2)
        else:
            child1, child2 = parent1[:], parent2[:]
        
        if random.random() < MUTATION_RATE:
            mutate(child1)
        if random.random() < MUTATION_RATE:
            mutate(child2)
        
        new_population.extend([child1, child2])
    
    population = new_population
    
    # 输出当前最优解
    current_best = min(population, key=lambda ind: fitness(ind, dist_matrix))
    current_distance = fitness(current_best, dist_matrix)
    if current_distance < best_distance:
        best_distance = current_distance
        best_individual = current_best
    print(f"第 {gen}代: 最短路径 = {best_distance}")

# 输出最终结果
print(f"Best Route: {best_individual}")
print(f"Best Distance: {best_distance}")

# 可视化结果
def plot_route(cities, route):
    plt.figure(figsize=(10, 6))
    plt.plot(cities[route + [route[0]], 0], cities[route + [route[0]], 1], 'o-')
    
    for i, city in enumerate(cities):
        plt.text(city[0], city[1], str(i), fontsize=12, ha='right')
        
    plt.title('TSP')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(True)
    plt.xlim(-5, CITY_RANGE + 5)
    plt.ylim(-5, CITY_RANGE + 5)
    plt.show()

plot_route(cities, best_individual)
