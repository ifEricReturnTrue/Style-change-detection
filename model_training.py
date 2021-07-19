import os
import json
import numpy as np
from sklearn.metrics import accuracy_score
from embedding_generation import generate_sentence_embedding, generate_document_embedding
from sklearn import svm
import pickle
import joblib


def trim_training_labels(dir_path):
    # Change the directory
    os.chdir(dir_path)
    dt = np.dtype(np.int32)
    true_labels_arr = np.array([], dtype=dt)
    for file in os.listdir():
        # Check whether file is in json format or not
        if file.endswith(".json"):
            file_path = f"{dir_path}/{file}"
            with open(file_path, 'r') as train_label:
                # returns JSON object as a dictionary
                label_dic = json.load(train_label)
                multi_author_label = label_dic["multi-author"]
                true_labels_arr = np.append(true_labels_arr,multi_author_label)
    return true_labels_arr


# def save_model(classifier):
#     """
#     Save a already trained model
#     """
#     with open(sklearn_svm_model, 'wb') as file:
#         pickle.dump(classifier, file)


x_train = generate_document_embedding("/Users/charlie/Desktop/2021暑研/stylometric analysis/Style change detection/pan21/train_seperated_txt")
y_train = trim_training_labels("/Users/charlie/Desktop/2021暑研/stylometric analysis/Style change detection/pan21/train_seperated_json")
x_validate = generate_document_embedding("/Users/charlie/Desktop/2021暑研/stylometric analysis/Style change detection/pan21/validate_seperated_txt")
y_validate = trim_training_labels("/Users/charlie/Desktop/2021暑研/stylometric analysis/Style change detection/pan21/validate_seperated_json")
# print(x_train.shape)
# print(y_train.shape)
clf = svm.SVC()
clf.fit(x_train, y_train)
#save_model(clf)
trainingAccuracy = 100 * (accuracy_score(clf.predict(x_validate), y_validate))
print(trainingAccuracy)


