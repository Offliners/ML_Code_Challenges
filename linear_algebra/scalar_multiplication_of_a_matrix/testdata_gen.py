from __future__ import annotations

import os
import random
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

random.seed(config['seed'])

def scalar_multiply(matrix: list[list[int|float]], scalar: int|float) -> list[list[int|float]]:
    return [[element * scalar for element in row] for row in matrix]


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    row_size = random.randint(config['size_row_lower'], config['size_row_upper'])
    col_size = random.randint(config['size_col_lower'], config['size_col_upper'])
    testcase_input.append([row_size, col_size])

    k = random.uniform(config['k_lower'], config['k_upper'])
    testcase_input.append([k])

    mat = []
    for _ in range(row_size):
        row_data = [random.uniform(config['value_lower'], config['value_upper']) for _ in range(col_size)]
        mat.append(row_data)
        testcase_input.append(row_data)
    
    k_mat = scalar_multiply(mat, k)
    for i in range(row_size):
        testcase_output.append(k_mat[i])

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