#!/usr/bin/env python3

import os
from sys import argv
from tabulate import tabulate
from statistics import mean

def evaluate(N):
    names = ["Recursive execution", "Recursive execution with optimizations", "Stack machine", "Stack machine with optimization", "C++ program"]
    times = { names[0] : [], names[1] : [], names[2] : [], names[3] : [], names[4] : [] }
    for _ in range(N):
        # Recursive execution
        os.system("./recursive_execution/calc < input > tmp")
        times[names[0]].append(int(open("tmp", "r").readlines()[1]))

        # Recursive execution with optimizations
        os.system("./recursive_execution_with_optimization/calc < input > tmp")
        times[names[1]].append(int(open("tmp", "r").readlines()[1]))

        # Execute with stack machine
        os.system("./stack_machine/calc < input > tmp")
        times[names[2]].append(int(open("tmp", "r").readlines()[1]))

        # Execute with stack machine with optimizations
        os.system("./stack_machine_with_optimization/calc < input > tmp")
        times[names[3]].append(int(open("tmp", "r").readlines()[1]))

        # Execute in C++ code
        os.system("./cpp_program/cpp-program > tmp")
        times[names[4]].append(int(open("tmp", "r").readlines()[1]))

    print(tabulate(times, showindex="always", headers="keys", numalign="center"))
    print(f"\nAverage of runtime over {N} runs:\n\n" +
        tabulate([
                [names[0], mean(times[names[0]])],
                [names[1], mean(times[names[1]])],
                [names[2], mean(times[names[2]])],
                [names[3], mean(times[names[3]])],
                [names[4], mean(times[names[4]])]
            ], headers= ["Method", "time in us"]
        )
    )
    print()
    os.remove("tmp")

if __name__ == "__main__":
    N = int(argv[1]) if len(argv) > 1 else 10
    evaluate(N)
