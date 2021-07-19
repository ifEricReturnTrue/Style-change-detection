import torch
import transformers
import numpy as np
import os


# For DistilBERT:
model_class, tokenizer_class, pretrained_weights = (
transformers.DistilBertModel, transformers.DistilBertTokenizer, 'distilbert-base-uncased')
# Load pretrained model/tokenizer
tokenizer = tokenizer_class.from_pretrained(pretrained_weights)
model = model_class.from_pretrained(pretrained_weights)
model.eval()


def generate_sentence_embedding(sentence):
    word_pieces = "[CLS]" + sentence + "[SEP]"
    sentence_tokens = tokenizer.tokenize(word_pieces)
    token_ids = tokenizer.convert_tokens_to_ids(sentence_tokens)  # token_ids is a list
    max_len = 50
    padded_tokens = np.array([token_ids + [0] * (max_len - len(token_ids))])  # add paddings to the token_ids
    attention_mask = np.where(padded_tokens != 0, 1, 0)  # ask BERT to ignore the paddings
    attention_mask_tensor = torch.tensor(attention_mask)
    input_tensor = torch.tensor(padded_tokens)
    with torch.no_grad():
        output = model(input_tensor, attention_mask=attention_mask_tensor)
    # print(output[0].shape)
    CLSFeature = output[0][:, 0, :].numpy()  # convert tensors to numpy array to fit the scikit-learn library
    # CLSFeature = torch.squeeze(CLSFeature, dim=0)
    #print(CLSFeature.shape)
    return CLSFeature


# generate_sentence_embedding("I love coding.")

def generate_document_embedding(dir_path):
    # Change the directory
    os.chdir(dir_path)
    document_training_matrix = np.zeros([1, 768])
    for file in os.listdir():
        # Check whether file is in text format or not
        if file.endswith(".txt"):
            file_path = f"{dir_path}/{file}"
            with open(file_path, 'r') as train_sample:
                Lines = train_sample.readlines()
                count = 0
                CLSFeature = np.zeros([1, 768])
                for line in Lines:
                    if line == "\n":
                        continue
                    count += 1
                    CLSFeature += generate_sentence_embedding(line)
                CLSFeature /= count  # average the sentence embeddings, CLSFeature is ndArray of size [1,768]
                #print(CLSFeature.shape)
                document_training_matrix = np.concatenate((document_training_matrix, CLSFeature), axis=0)
                #print(document_training_matrix.shape)
    document_training_matrix = np.delete(document_training_matrix,0,0)
    # print(document_training_matrix)
    return document_training_matrix


def test():
    with open("problem-6.txt", 'r') as train_sample:
        Lines = train_sample.readlines()
        count = 0
        CLSFeature = np.zeros([1, 768])
        for line in Lines:
            if line == "\n":
                continue
            count += 1
            CLSFeature += generate_sentence_embedding(line)
        CLSFeature /= count  # average the sentence embeddings, CLSFeature is ndArray of size [1,768]
    print(CLSFeature)


generate_document_embedding("/Users/charlie/Desktop/2021暑研/stylometric analysis/Style change detection/pan21/train_seperated1")
