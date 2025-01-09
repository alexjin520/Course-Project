import subprocess, os, filecmp
from benchmark import test_serial, test_parallel
import matplotlib.pyplot as plt


def sample(i):
    os.system("printf '#define NUM_THREADS {}\n// auto generated by graph.py\n// do not touch\n' > thread_info.h".format(str(i)))
    subprocess.call(["python3", "generate_data.py", str(i)])
    if not filecmp.cmp("serial_output.txt", "parallel_output.txt"):
        print("Benchmark failed!")
        exit(-1)
    return test_serial(), test_parallel()

def sample_avg(i):
    four_tries = [sample(i) for j in range(4)]
    s_avg = sum([x for (x, y) in four_tries]) / 4
    p_avg = sum([y for (x, y) in four_tries]) / 4
    return s_avg, p_avg

sample_points = range(1,17)
time_s = []
time_p = []
for i in sample_points:
    print("Testing ", i, " thread(s)")
    result_s, result_p = sample_avg(i)
    time_s.append(result_s)
    time_p.append(result_p)

os.system("printf '// auto generated by graph.py\n// do not touch\n' > thread_info.h")

# print(time_s)
# print(time_p)
plt.plot(sample_points, time_s, label="serial")
plt.plot(sample_points, time_p, label="parallel")
plt.xlabel("Thread Number")
plt.ylabel("Time (in seconds)")
plt.title("Thread Number vs. Execution Time")
plt.legend()
plt.savefig("compare.png")




