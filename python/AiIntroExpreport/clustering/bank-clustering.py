import pandas as pd
import numpy as np
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import AgglomerativeClustering
import matplotlib.pyplot as plt
import seaborn as sns
from pylab import mpl
from sklearn.decomposition import PCA
# 设置显示中文字体
mpl.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams['axes.unicode_minus'] = False

file_path = 'C:\\Users\\hbn\\Desktop\\AiIntroExpReport\\Bank\\bank-additional.csv'
data = pd.read_csv(file_path, sep=';')

# 选择数值聚类
numerical_features = ['age', 'duration', 'campaign', 'pdays', 'previous', 'emp.var.rate', 'cons.price.idx', 'cons.conf.idx', 'euribor3m', 'nr.employed']
X = data[numerical_features]
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

#kmeans
kmeans = KMeans(n_clusters=3, random_state=0)
kmeans_labels = kmeans.fit_predict(X_scaled)
data['kmeans'] = kmeans_labels

# 层次
agglomerative = AgglomerativeClustering(n_clusters=3, linkage='ward') 
agglomerative_labels = agglomerative.fit_predict(X_scaled)
data['层次'] = agglomerative_labels


# 可视化
plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)
sns.scatterplot(x='age', y='duration', hue='kmeans', data=data, palette='viridis')
plt.title('kmeans')
plt.subplot(1, 2, 2)
sns.scatterplot(x='age', y='duration', hue='层次', data=data, palette='plasma')
plt.title('层次')
plt.tight_layout()
plt.show()

#PCA
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)
data['pca1'] = X_pca[:,0]
data['pca2'] = X_pca[:,1]

plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)
sns.scatterplot(x='pca1', y='pca2', hue='kmeans', data=data, palette='viridis')
plt.title('kmeans-PCA')
plt.subplot(1, 2, 2)
sns.scatterplot(x='pca1', y='pca2', hue='层次', data=data, palette='plasma')
plt.title('层次-PCA')
plt.tight_layout()
plt.show()

# 评估
from sklearn.metrics import silhouette_score, davies_bouldin_score
print("kmeans轮廓系数:", silhouette_score(X_scaled, kmeans_labels))
print("层次聚类轮廓系数:", silhouette_score(X_scaled, agglomerative_labels))
print("kmeansDB:", davies_bouldin_score(X_scaled, kmeans_labels))
print("层次DB:", davies_bouldin_score(X_scaled, agglomerative_labels))

