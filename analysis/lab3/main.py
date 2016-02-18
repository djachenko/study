from math import sqrt

from sklearn.datasets import load_iris
from sklearn.metrics import adjusted_rand_score

N = 3
DIMENSION = 4


def metric(sample1, sample2):
    total = 0

    for i in range(DIMENSION):
        total += (sample1[i] - sample2[i]) ** 2

    return sqrt(total)


def classify(samples):
    centers = samples[:N]

    while True:
        clusters = [[] for _ in range(N)]

        for sample in samples:
            distances = [metric(sample, center) for center in centers]
            cluster_index = distances.index(min(distances))

            clusters[cluster_index].append(sample)

        new_centers = [[sum(feature_column) / len(cluster) for feature_column in zip(*cluster)] for cluster in clusters]

        diffs = []

        for i in range(N):
            diffs.append(metric(centers[i], new_centers[i]))

        if all((diff < 0.001 for diff in diffs)):
            return clusters
        else:
            centers = new_centers


def main():
    iris = load_iris()

    data = [list(i[1]) + [i[0]] for i in list(enumerate(iris.data))]

    clusters = classify(data)

    predicted = [0 for _ in range(len(iris.data))]

    for i in range(len(clusters)):
        for element in clusters[i]:
            predicted[element[DIMENSION]] = i

    accuracy = adjusted_rand_score(iris.target, predicted)

    print(accuracy)


if __name__ == '__main__':
    main()
