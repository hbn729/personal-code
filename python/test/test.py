import numpy as np  
import matplotlib.pyplot as plt  
import random  
from pylab import mpl
# 设置显示中文字体
mpl.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams['axes.unicode_minus'] = False
# 参数设置  
num_clusters = 3         # 聚类数量  
max_iterations = 100     # 最大迭代次数  
num_samples = 150        # 样本数量  
fuzzy_parameter = 2.0    # 模糊聚类参数  

# 生成模拟数据集  
def generate_data(num_samples, num_features, num_clusters):  
    """生成模拟数据，以便进行聚类实验。"""  
    data = []  
    np.random.seed(0)  # 设置随机种子以便重现结果  
    for i in range(num_clusters):  
        # 在每个聚类中生成随机数据点  
        center = np.random.rand(num_features) * 10  # 生成聚类中心  
        points = np.random.normal(loc=center, scale=0.5, size=(num_samples // num_clusters, num_features))  
        data.extend(points)  
    return np.array(data)  

data = generate_data(num_samples, 2, num_clusters)  # 生成二维数据  

def initialize_membership_matrix():  
    """初始化模糊隶属度矩阵，使用随机值。"""  
    membership_matrix = []  
    for _ in range(num_samples):  
        random_values = [random.random() for _ in range(num_clusters)]  
        normalized_values = [x / sum(random_values) for x in random_values]  # 归一化  
        membership_matrix.append(normalized_values)  
    return membership_matrix  

def calculate_cluster_centers(membership_matrix):  
    """根据当前的隶属度矩阵计算新的聚类中心。"""  
    cluster_centers = []  
    for j in range(num_clusters):  
        # 计算聚类j的新中心  
        weighted_values = np.power([membership_matrix[i][j] for i in range(num_samples)], fuzzy_parameter)  
        denominator = sum(weighted_values)  
        numerator = np.zeros(2)  # 二维数据  
        
        for i in range(num_samples):  
            data_point = data[i]  
            numerator += weighted_values[i] * data_point  
        
        cluster_centers.append(numerator / denominator)  # 计算新中心  
    return np.array(cluster_centers)  

def update_membership_values(membership_matrix, cluster_centers):  
    """根据与聚类中心的距离更新隶属度值。"""  
    for i in range(num_samples):  
        distances = [np.linalg.norm(data[i] - center) for center in cluster_centers]  
        for j in range(num_clusters):  
            membership_matrix[i][j] = 1 / sum((distances[j] / distances[c]) ** (2 / (fuzzy_parameter - 1)) for c in range(num_clusters))  
    return membership_matrix  

def get_cluster_labels(membership_matrix):  
    """根据最大隶属度值返回每个数据点的聚类标签。"""  
    return [np.argmax(membership) for membership in membership_matrix]  

def fuzzy_c_means_clustering():  
    """执行模糊C均值聚类的主要函数。"""  
    membership_matrix = initialize_membership_matrix()  
    for _ in range(max_iterations):  
        cluster_centers = calculate_cluster_centers(membership_matrix)  
        membership_matrix = update_membership_values(membership_matrix, cluster_centers)  
    cluster_labels = get_cluster_labels(membership_matrix)  
    return cluster_labels, cluster_centers  

def xie_beni(membership_matrix, centers):  
    """计算聚类结果的Xie-Beni有效性指数。"""  
    sum_cluster_distance = sum(membership_matrix[j][i] ** 2 * np.sum((data[j] - centers[i]) ** 2) for i in range(num_clusters) for j in range(num_samples))  
    
    # 计算最小类间距离  
    min_cluster_distance = np.inf  
    for i in range(num_clusters - 1):  
        for j in range(i + 1, num_clusters):  
            distance = np.sum((centers[i] - centers[j]) ** 2)  
            min_cluster_distance = min(min_cluster_distance, distance)  

    return sum_cluster_distance / (num_samples * min_cluster_distance)  

# 执行模糊C均值聚类  
labels, centers = fuzzy_c_means_clustering()  
validity_index = xie_beni(initialize_membership_matrix(), centers)  

# 打印结果  
print("聚类标签:", labels)  
print("聚类中心:", centers)  
print("Xie-Beni有效性指数:", validity_index)  

# 可视化聚类结果  
plt.figure(figsize=(16.5, 12.5))  
colors = ['r', 'b', 'g']  
markers = ['o', '+', '*']  
for idx in range(num_clusters):  
    plt.scatter(data[np.array(labels) == idx, 0], data[np.array(labels) == idx, 1],   
                marker=markers[idx], color=colors[idx], label=f'聚类 {idx}', s=10)  
plt.scatter(centers[:, 0], centers[:, 1], marker='x', color='m', s=100, label='聚类中心')  
plt.xlabel('特征 1')  
plt.ylabel('特征 2')  
plt.title('模糊C均值聚类结果')  
plt.legend()  
plt.show()
