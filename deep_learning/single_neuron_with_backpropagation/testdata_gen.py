from __future__ import annotations

import os
import numpy as np
import random
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

np.random.seed(config['seed'])
random.seed(config['seed'])

def sigmoid(x: float) -> float:
    return 1 / (1 + np.exp(-x))

def train_neuron(features: list[list[float]], 
                 labels: list[float], 
                 initial_weights: list[float], 
                 initial_bias: float, 
                 learning_rate: float, 
                 epochs: int) -> list[float] | float | list[float]:
    
    weights = np.array(initial_weights)
    bias = initial_bias
    features = np.array(features)
    labels = np.array(labels)
    mse_values = []

    for _ in range(epochs):
        z = np.dot(features, weights) + bias
        predictions = sigmoid(z)
        mse = np.mean((predictions - labels) ** 2)
        mse_values.append(mse)

        # Gradient calculation for weights and bias
        errors = predictions - labels
        weight_gradients = np.dot(features.T, errors * predictions * (1 - predictions))
        bias_gradient = np.sum(errors * predictions * (1 - predictions))
        
        # Update weights and bias
        weights -= learning_rate * weight_gradients / len(labels)
        bias -= learning_rate * bias_gradient / len(labels)

        # Round weights and bias for output
        updated_weights = weights
        updated_bias = bias

    return updated_weights.tolist(), updated_bias, mse_values


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    epochs = random.randint(config['epoch_lower'], config['epoch_upper'])
    num_data = random.randint(config['data_lower'], config['data_upper'])
    feature_size = random.randint(config['feature_size_lower'], config['feature_size_upper'])
    testcase_input.append([epochs, num_data, feature_size])

    features = []
    for _ in range(num_data):
        feature = [random.uniform(config['feature_lower'], config['feature_upper']) for _ in range(feature_size)]
        features.append(feature)
        testcase_input.append(feature)

    label_size = num_data
    labels = [random.choice([config['false_label'], config['true_label']]) for _ in range(label_size)]
    testcase_input.append([label_size])
    testcase_input.append(labels)

    weight_size = feature_size
    initial_weights = [random.uniform(config['weight_lower'], config['weight_upper']) for _ in range(weight_size)]
    testcase_input.append([weight_size])
    testcase_input.append(initial_weights)

    initial_bias = random.uniform(config['bias_lower'], config['bias_upper'])
    testcase_input.append([initial_bias])

    lr = random.uniform(config['lr_lower'], config['lr_upper'])
    testcase_input.append([lr])

    final_weights, final_bias, mse = train_neuron(features, labels, initial_weights, initial_bias, lr, epochs)
    testcase_output.append(final_weights)
    testcase_output.append([final_bias])
    testcase_output.append(mse)

    return testcase_input, testcase_output
        

def main(input_path: str, output_path: str) -> None:
    num_testcase = config['num_testcase']
    for i in range(num_testcase):
        input, output = gen()

        input_path_index = os.path.join(input_path, f'{i}.in')
        with open(input_path_index, 'w') as f_in:
            for line in input:
                line_str = [str(e) for e in line]
                f_in.writelines(f'{" ".join(line_str)}\n')
        
        output_path_index = os.path.join(output_path, f'{i}.out')
        with open(output_path_index, 'w') as f_out:
            for line in output:
                line_str = [str(e) for e in line]
                f_out.writelines(f'{" ".join(line_str)}\n')

        print(f'{bcolors.OKGREEN}Pattern no.{i} done!{bcolors.ENDC}')


if __name__ == '__main__':
    input_path = './input'
    output_path = './groundtruth_output'
    os.makedirs(input_path, exist_ok=True)
    os.makedirs(output_path, exist_ok=True)
    main(input_path, output_path)