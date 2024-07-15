from __future__ import annotations

import os
import random
import numpy as np
from config import config

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

np.random.seed(config['seed'])
random.seed(config['seed'])


def linear_regression_normal_equation(X: list[list[float]], y: list[float]) -> list[float]:
    X = np.array(X)
    y = np.array(y).reshape(-1, 1)
    X_transpose = X.T
    theta = np.linalg.inv(X_transpose.dot(X)).dot(X_transpose).dot(y)
    theta = theta.flatten().tolist()
    return theta


def gen() -> list[list[str], list[str]]:
    testcase_input = []
    testcase_output = []

    num_equ = random.randint(config['equ_lower'], config['equ_upper'])
    num_coef = random.randint(config['coef_lower'], config['coef_upper'])

    testcase_input.append([num_equ, num_coef + config['target_col_size']])
    X = []
    y = []
    for _ in range(num_equ):
        data = [random.uniform(config['value_lower'], config['value_upper']) for _ in range(num_coef + config['target_col_size'])]
        X.append(data[:-1])
        y.append(data[-1])
        testcase_input.append(data)

    ans = linear_regression_normal_equation(X, y)
    testcase_output.append(ans)

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