import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
import matplotlib.pyplot as plt
from pylab import mpl
# 设置显示中文字体
mpl.rcParams["font.sans-serif"] = ["SimHei"]
# 加载数据集
file_path = 'C:\\Users\\hbn\\Desktop\\AiIntro\\Iris\\iris.csv'
data = pd.read_csv(file_path, header=None)

X = data.iloc[:, :-1].values
y = data.iloc[:, -1].values
label_encoder = LabelEncoder()
y_encoded = label_encoder.fit_transform(y)


X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)


knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f'预测准确率: {accuracy:.2f}')

# 绘制原始数据集的前两个特征
plt.figure(figsize=(10, 6))
plt.scatter(X[:, 0], X[:, 1], c=y_encoded, cmap='viridis', edgecolor='k', s=100)
plt.title('原始数据集（前两个特征）')
plt.xlabel('特征1')
plt.ylabel('特征2')
plt.show()

# 测试不同K值的准确率
neighbors = list(range(1, 11))
accuracies = []

for k in neighbors:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train, y_train)
    y_pred = knn.predict(X_test)
    accuracies.append(accuracy_score(y_test, y_pred))

# 绘制K值与准确率的关系图
plt.figure(figsize=(10, 6))
plt.plot(neighbors, accuracies, marker='o')
plt.title('K值与预测准确率')
plt.xlabel('K值')
plt.ylabel('预测准确率')
plt.show()