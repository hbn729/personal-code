import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['SimHei']
# 加载数据集
file_path = 'C:\\Users\\hbn\\Desktop\\Bank\\bank-additional.csv'
data = pd.read_csv(file_path, sep=';')

# 分离特征和标签
X = data.drop(columns=['y'])
y = data['y']

# 实例化LabelEncoder
label_encoder = LabelEncoder()

# 对标签进行编码
y = label_encoder.fit_transform(y)

# 识别分类特征和数值特征
categorical_features = X.columns[X.dtypes == 'object'].tolist()
numerical_features = X.columns[X.dtypes != 'object'].tolist()

# 对分类特征进行OneHot编码，数值特征保持不变
preprocessor = ColumnTransformer(
    transformers=[
        ('num', 'passthrough', numerical_features),
        ('cat', OneHotEncoder(), categorical_features)
    ])

# 应用预处理器到特征数据集
X_processed = preprocessor.fit_transform(X)

# 分割数据集为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X_processed, y, test_size=0.3, random_state=42)

# 标准化特征值
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# 初始化KNN分类器
knn = KNeighborsClassifier(n_neighbors=5)

# 训练模型
knn.fit(X_train, y_train)

# 预测测试集
y_pred = knn.predict(X_test)

# 计算准确率
accuracy = accuracy_score(y_test, y_pred)
print(f'预测准确率: {accuracy:.2f}')

# 使用PCA将数据降维到2维
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_processed)

# 绘制原始数据集
plt.figure(figsize=(10, 6))
plt.scatter(X_pca[:, 0], X_pca[:, 1], c=y, cmap='viridis', edgecolor='k', s=100)
plt.title('原始数据集')
plt.xlabel('主成分1')
plt.ylabel('主成分2')
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