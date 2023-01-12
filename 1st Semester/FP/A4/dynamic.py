from pprint import pprint


def compute_solution(x, y, dp):
    sol = ""
    n = len(x) - 1
    m = len(y) - 1

    while n:
        if x[n] == y[m]:
            sol = x[n] + sol
            n -= 1
            m -= 1
        elif dp[n - 1][m] < dp[n][m - 1]:
            m -= 1
        else:
            n -= 1

    return sol


def compute_matrix(x, y):

    dp = [[0 for _ in range(len(x) + 1)] for _ in range(len(y) + 1)]

    for i in range(1, len(x)):
        for j in range(1, len(y)):
            if x[i] == y[j]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
            pprint(dp)
            print("\n")

    return dp


def solve():
    x = " " + input()
    y = " " + input()

    dp = compute_matrix(x, y)

    print("The length of the longest common subsequence of the arrays is ",
          dp[len(x) - 1][len(y) - 1])
    print("One of the longest common subsequences of the arrays is ",
          compute_solution(x, y, dp))


solve()
