from __future__ import annotations

import os
import random
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

random.seed(config['seed'])

def matrix_dot_vector(a: list[list[int|float]], b: list[int|float]) -> list[int|float]:
    if len(a[0]) != len(b):
        return [-1]
    
    vals = []
    for i in a:
        hold = 0
        for j in range(len(i)):
            hold+=(i[j] * b[j])
        vals.append(hold)

    return vals


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    mat_A_row = random.randint(config['size_A_row_lower'], config['size_A_row_upper'])
    mat_A_col = random.randint(config['size_A_col_lower'], config['size_A_col_upper'])

    testcase_input.append([mat_A_row, mat_A_col])
    mat_A = []
    for _ in range(mat_A_row):
        row_data = [random.uniform(config['value_lower'], config['value_upper']) for _ in range(mat_A_col)]
        mat_A.append(row_data)
        testcase_input.append(row_data)

    vec_B_col = config['size_B_col_size']
    vec_B_row = mat_A_col
    if random.random() < config['prob_mismatch']:
        while vec_B_row == mat_A_col:
            vec_B_row = random.randint(config['size_B_row_lower'], config['size_B_row_upper'])    

    testcase_input.append([vec_B_row, vec_B_col])
    vec_B = [random.uniform(config['value_lower'], config['value_upper']) for _ in range(vec_B_row)]
    testcase_input.append(vec_B)

    testcase_output.append(matrix_dot_vector(mat_A, vec_B))

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