import os
import time
import sys
from matplotlib import pyplot as plt

projeto_name = "projeto_2.cpp"


def main():
    time_data = []
    input_data = []
    nxn_data = []
    os.system("rm -r tests")
    os.system("mkdir tests")
    os.system("g++ -std=c++11 -O3 -Wall " + projeto_name + " -lm -o main")
    os.system("g++ -std=c++11 -O3 -Wall ladrilho_valido.cpp -lm -o gerador")
    for i in range(1, 9):
        os.system(
            "./gerador " + str(i) + " " + str(i) + " > tests/test" + str(i) + ".txt"
        )
        test = "tests/test" + str(i) + ".txt"
        shell_command = "./main < " + test
        start_time = time.time()
        stout = os.popen(shell_command).read()
        end_time = time.time()
        time_data.append(end_time - start_time)
        print(stout)
        input_data.append(stout)
        nxn_data.append(i)
    os.system("rm -r tests")
    plt.plot(nxn_data, input_data, "--bo", label="line with marker")
    plt.ylabel("call of functions")
    plt.xlabel("Size of square")
    plt.title("function complexity")
    plt.show()


if __name__ == "__main__":
    main()
