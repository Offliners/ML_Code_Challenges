from __future__ import annotations

import os
import math
import random
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

random.seed(config['seed'])


def single_neuron_model(features: list[list[float]], labels: list[bool], weights: list[float], bias: float) -> list[float] | float:
    probabilities = []
    for feature_vector in features:
        z = sum(weight * feature for weight, feature in zip(weights, feature_vector)) + bias
        prob = 1 / (1 + math.exp(-z))
        probabilities.append(prob)
    
    mse = sum((prob - label) ** 2 for prob, label in zip(probabilities, labels)) / len(labels)
    
    return probabilities, mse


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    num_data = random.randint(config['data_lower'], config['data_upper'])
    feature_size = random.randint(config['feature_size_lower'], config['feature_size_upper'])
    testcase_input.append([num_data, feature_size])

    features = []
    for _ in range(num_data):
        feature = [random.uniform(config['feature_lower'], config['feature_upper']) for _ in range(feature_size)]
        features.append(feature)
        testcase_input.append(feature)

    label_size = feature_size
    labels = [random.choice([config['false_label'], config['true_label']]) for _ in range(label_size)]
    testcase_input.append([label_size])
    testcase_input.append(labels)

    weight_size = feature_size
    weights = [random.uniform(config['weight_lower'], config['weight_upper']) for _ in range(weight_size)]
    testcase_input.append([weight_size])
    testcase_input.append(weights)

    bias = random.uniform(config['bias_lower'], config['bias_upper'])
    testcase_input.append([bias])

    prob, mse = single_neuron_model(features, labels, weights, bias)
    testcase_output.append(prob)
    testcase_output.append([mse])

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
                line_str = [f"{e:.8f}" for e in line]
                f_out.writelines(f'{" ".join(line_str)}\n')

        print(f'{bcolors.OKGREEN}Pattern no.{i} done!{bcolors.ENDC}')


if __name__ == '__main__':
    input_path = './input'
    output_path = './groundtruth_output'
    os.makedirs(input_path, exist_ok=True)
    os.makedirs(output_path, exist_ok=True)
    main(input_path, output_path)