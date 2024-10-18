import numpy as np
import time

def get_element(n, small, big):
    """计算矩阵中的一个元素"""
    return (1 + small) * (n - big)

def get_cyclic(n):
    """生成一个 n x n 的循环矩阵"""
    A = np.zeros((n, n), dtype=float)  # 初始化 n x n 的零矩阵
    factor = 1.0 / (n + 1)  # 缩放因子

    for i in range(n):
        A[i, i] = factor * get_element(n, i, i)  # 对角线元素
        for j in range(i + 1, n):
            element = get_element(n, i, j)  # 非对角元素
            A[i, j] = factor * element
            A[j, i] = factor * element  # 矩阵对称性
    return A

def benchmark(n):
    """基准测试，生成矩阵并计算其逆"""
    print(f"Benchmarking with size: {n}x{n}")

    A = get_cyclic(n)  # 生成矩阵

    # 测量求逆时间
    start_time = time.time()
    A_inv = np.linalg.inv(A)
    end_time = time.time()

    elapsed_time = (end_time - start_time) * 1000  # 转换为毫秒
    print(f"Inverse Time with NumPy: {elapsed_time:.2f} ms")
    print("Benchmarking finished!\n")

def main():
    # 打印 n = 4 的逆矩阵
    A1 = get_cyclic(4)
    A1_inv = np.linalg.inv(A1)
    print("The inverse matrix for n = 4:\n")
    print(A1_inv)

    # 打印 n = 8 的逆矩阵
    A2 = get_cyclic(8)
    A2_inv = np.linalg.inv(A2)
    print("\nThe inverse matrix for n = 8:\n")
    print(A2_inv)

    # 基准测试不同大小的矩阵
    benchmark(100)
    benchmark(200)
    benchmark(400)
    benchmark(800)

if __name__ == "__main__":
    main()
