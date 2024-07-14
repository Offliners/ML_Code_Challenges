from __future__ import annotations

import os
import random
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

random.seed(config['seed'])

def calculate_covariance_matrix(vectors: list[list[float]]) -> list[list[float]]:
    n_features = len(vectors)
    n_observations = len(vectors[0])
    covariance_matrix = [[0 for _ in range(n_features)] for _ in range(n_features)]

    means = [sum(feature) / n_observations for feature in vectors]

    for i in range(n_features):
        for j in range(i, n_features):
            covariance = sum((vectors[i][k] - means[i]) * (vectors[j][k] - means[j]) for k in range(n_observations)) / (n_observations - 1)
            covariance_matrix[i][j] = covariance_matrix[j][i] = covariance

    return covariance_matrix


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    vec_row = random.randint(config['size_row_lower'], config['size_row_upper'])
    vec_col = config['size_col_size']

    testcase_input.append([vec_row, vec_col])
    num_vec = random.randint(config['vec_lower'], config['vec_upper'])
    testcase_input.append([num_vec])

    vecs = [[random.uniform(config['value_lower'], config['value_upper']) for _ in range(vec_row)] for _ in range(num_vec)]

    for i in range(num_vec):
        testcase_input.append(vecs[i])
    
    ans = calculate_covariance_matrix(vecs)
    for i in range(num_vec):
        testcase_output.append(ans[i])

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