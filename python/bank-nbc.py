import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report
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