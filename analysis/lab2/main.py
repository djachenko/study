from __future__ import division
from collections import defaultdict
from math import log

__author__ = 'justin'

EPSILON = 10 ** (-7)


def train(samples):
    classes = defaultdict(lambda: 0)
    frequences = defaultdict(lambda: 0)

    for features, label in samples:
        classes[label] += 1

        for feature in features:
            frequences[label, feature] += 1

    for label, feature in frequences:
        frequences[label, feature] /= classes[label]

    for c in classes:
        classes[c] /= len(samples)

    return classes, frequences


def classify(classifier, features):
    classes, prob = classifier

    return min(classes.keys(),
               key=lambda cl: -log(classes[cl]) + sum(
                       -log(prob.get((cl, feature), EPSILON)) for feature in features))


def get_features(sample):
    return (
        'll: %s' % sample[-1],
        'fl: %s' % sample[0],
        'sl: %s' % sample[1],
    )


def main():
    samples = list(line.strip().lower().split(" ") for line in open('names.txt', encoding="utf8"))
    features = [(get_features(feat), label) for feat, label in samples]
    classifier = train(features)

    print('gender: ', classify(classifier, get_features(u'Аполлон')))


if __name__ == '__main__':
    main()
