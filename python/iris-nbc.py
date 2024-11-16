import pandas as pd

# 加载数据集
file_path = 'C:\\Users\\hbn\\Desktop\\Iris\\iris.csv'
data = pd.read_csv(file_path, header=None)

# 显示前几行数据以检查
print(data.head())
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, StandardScaler

# 分割数据集为特征和标签
X = data.iloc[:, :-1].values
y = data.iloc[:, -1].values

# 如果标签是字符串，需要将其编码为数值
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)

# 分割数据集为训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# 标准化特征值
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report

# 初始化朴素贝叶斯分类器
nb_classifier = GaussianNB()

# 训练模型
nb_classifier.fit(X_train, y_train)

# 预测测试集
y_pred = nb_classifier.predict(X_test)

# 计算准确率
accuracy = accuracy_score(y_test, y_pred)
print(f'预测准确率: {accuracy:.2f}')

# 显示分类报告
cr = classification_report(y_test, y_pred)
print('分类报告:')
print(cr)
