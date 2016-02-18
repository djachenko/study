from sklearn.cross_validation import train_test_split
from sklearn.datasets import load_iris
from sklearn.metrics import mean_squared_error

__author__ = 'justin'

ALPHA = 0.03
EPSILON = 0.001


def h(theta):
    return lambda x: sum(x[i] * theta[i] for i in range(len(x)))


def derive(hf, deg, y, x):
    res = 0

    count = 0

    for i in range(len(x)):
        res += (hf(x[i]) - y[i]) * x[i][deg]
        count += 1

    res /= len(x)

    return res


def train(x_train, y_train):
    n = len(x_train[0])
    theta = [0 for _ in range(n)]

    hypotesis = h(theta)

    while True:
        hypotesis = h(theta)
        theta_next = [theta[i] - ALPHA * derive(hypotesis, i, y_train, x_train) for i in range(n)]

        diffs = [abs(theta[i] - theta_next[i]) for i in range(n)]

        convergence = all([diff < EPSILON for diff in diffs])

        if convergence:
            break
        else:
            theta = theta_next

    return hypotesis


def main():
    iris = load_iris()

    x_train, x_test, y_train, y_test = train_test_split(iris.data, iris.target, random_state=4)

    hypotesis = train(x_train, y_train)

    predicted = [hypotesis(x) for x in x_test]
    score = mean_squared_error(y_test, predicted)

    print(score)


if __name__ == '__main__':
    main()
