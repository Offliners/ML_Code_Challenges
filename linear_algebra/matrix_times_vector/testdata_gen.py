import os
import random
from config import config
from typing import List, Tuple

class bcolors:
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

random.seed(config['seed'])


def gen() -> Tuple[List[str], List[str]]:
    testcase_input = []
    testcase_output = []

    data_size = random.randint(config['size_lower'], config['size_upper'])
    testcase_input.append(data_size)

    flag = random.random() < config['prob_flag']
    if flag:
        testcase_input.append(1)
    else:
        testcase_input.append(0)
    
    data = []
    for _ in range(data_size):
        d = random.randint(config['value_lower'], config['value_upper'])
        testcase_input.append(d)
        data.append(d)

    if flag:
        data_sort = sorted(data, reverse=True)
    else:
        data_sort = sorted(data)

    for d in data_sort:
        testcase_output.append(d)

    return testcase_input, testcase_output
        

def main(input_path: str, output_path: str) -> None:
    num_testcase = config['num_testcase']
    for i in range(num_testcase):
        input, output = gen()

        input_path_index = os.path.join(input_path, f'{i}.in')
        with open(input_path_index, 'w') as f_in:
            for line in input:
                f_in.writelines(f'{line}\n')
        
        output_path_index = os.path.join(output_path, f'{i}.out')
        with open(output_path_index, 'w') as f_out:
            for line in output:
                f_out.writelines(f'{line}\n')

        print(f'{bcolors.OKGREEN}Pattern no.{i} done!{bcolors.ENDC}')


if __name__ == '__main__':
    input_path = './input'
    output_path = './golden_output'
    os.makedirs(input_path, exist_ok=True)
    os.makedirs(output_path, exist_ok=True)
    main(input_path, output_path)