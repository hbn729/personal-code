import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report
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

nb_classifier = GaussianNB()
nb_classifier.fit(X_train, y_train)
y_pred = nb_classifier.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
print(f'预测准确率: {accuracy:.2f}')

# 显示分类报告
cr = classification_report(y_test, y_pred)
print('分类报告:')
print(cr)