from __future__ import annotations

import os
import random
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

random.seed(config['seed'])

def inverse_2x2(matrix: list[list[float]]) -> list[list[float]]:
    a, b, c, d = matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]
    determinant = a * d - b * c
    if determinant == 0:
        return None
    inverse = [[d/determinant, -b/determinant], [-c/determinant, a/determinant]]
    return inverse


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    row_size = config['size_row']
    col_size = config['size_col']
    testcase_input.append([row_size, col_size])

    mat = []
    for _ in range(row_size):
        if random.random() < config['prob_zero_det']:
            row_data = [0] * col_size
        else:
            row_data = [random.uniform(config['value_lower'], config['value_upper']) for _ in range(col_size)]
        mat.append(row_data)
        testcase_input.append(row_data)

    mat_inv = inverse_2x2(mat)
    if not mat_inv:
        testcase_output.append([-1])
    else:
        for i in range(row_size):
            testcase_output.append(mat_inv[i])

    return testcase_input, testcase_output
        

def main(input_path: str, output_path: str) -> None:
    num_testcase = config['num_testcase']
    for i in range(num_testcase):
        input, output = gen()

        input_path_index = os.path.join(input_path, f'{i}.in')
        with open(input_path_index, 'w') as f_in:
            input_str_0 = [str(e) for e in input[0]]
            f_in.writelines(f'{" ".join(input_str_0)}\n')
            for line in input[1:]:
                line_str = [f"{e:.8f}".format(e) for e in line]
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