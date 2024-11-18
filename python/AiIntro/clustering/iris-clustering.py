import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans, AgglomerativeClustering
from sklearn.preprocessing import StandardScaler
from pylab import mpl
# 设置显示中文字体
mpl.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams['axes.unicode_minus'] = False

file_path = 'C:\\Users\\hbn\\Desktop\\AiIntro\\Iris\\iris.csv'
data = pd.read_csv(file_path, header=None)
X = data.iloc[:, :-1].values 
y = data.iloc[:, -1].values 
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# KMeans 聚类
kmeans = KMeans(n_clusters=3, random_state=0)  # 3个聚类中心
kmeans_labels = kmeans.fit_predict(X_scaled)

# 层次聚类
agglomerative = AgglomerativeClustering(n_clusters=3)
agglomerative_labels = agglomerative.fit_predict(X_scaled)

# 特征有4个，选前两个可视化
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1], c=kmeans_labels, cmap='viridis')
plt.title('kmeans')
plt.xlabel('特征1')
plt.ylabel('特征2')


plt.subplot(1, 2, 2)
plt.scatter(X_scaled[:, 0], X_scaled[:, 1], c=agglomerative_labels, cmap='viridis')
plt.title('层次聚类')
plt.xlabel('特征1')
plt.ylabel('特征2')

plt.tight_layout()
plt.show()
from sklearn.metrics import silhouette_score, davies_bouldin_score
print("kmeans轮廓系数:", silhouette_score(X_scaled, kmeans_labels))
print("层次聚类轮廓系数:", silhouette_score(X_scaled, agglomerative_labels))
print("kmeansDB:", davies_bouldin_score(X_scaled, kmeans_labels))
print("层次DB:", davies_bouldin_score(X_scaled, agglomerative_labels))

