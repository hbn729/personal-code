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
file_path = 'C:\\Users\\hbn\\Desktop\\AiIntroExpReport\\Bank\\bank-additional.csv'
data = pd.read_csv(file_path, sep=';')


X = data.drop(columns=['y'])
y = data['y']
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)
categorical_features = X.columns[X.dtypes == 'object'].tolist()
numerical_features = X.columns[X.dtypes != 'object'].tolist()
preprocessor = ColumnTransformer(
    transformers=[
        ('num', 'passthrough', numerical_features),
        ('cat', OneHotEncoder(), categorical_features)
    ])


X_processed = preprocessor.fit_transform(X)
X_train, X_test, y_train, y_test = train_test_split(X_processed, y, test_size=0.3, random_state=42)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)


knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f'预测准确率: {accuracy:.2f}')
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