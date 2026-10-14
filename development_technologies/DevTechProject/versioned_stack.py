import random

from list_node import ListNode
from revision import Revision
from versions_table import VersionsTable


class VersionedStack:
    def __init__(self, revision):
        super().__init__()

        self.__tops = VersionsTable()

        self.__head = ListNode(None, revision)

    def push(self, value, revision):
        new_node = ListNode(value, revision)

        top = self.__head.get_next(revision)
        new_node.set_next(top, revision)

        self.__head.set_next(new_node, revision)

    def pop(self, revision):
        top = self.__head.get_next(revision)

        if top:
            next_after_top = top.get_next(revision)

            self.__head.set_next(next_after_top, revision)

            return top.get_value()
        else:
            return None

    def empty(self, revision):
        top = self.__head.get_next(revision)

        return top is not None

    def clear(self, revision):
        self.__head.set_next(None, revision)

    def merge(self, revision_from, revision_to):
        self.clear(revision_to)

        node_iter = self.__head

        while node_iter.get_next(revision_from) is not None:
            next_node = node_iter.get_next(revision_from)

            node_iter.set_next(next_node, revision_to)

            node_iter = next_node


def test_api():
    data_size = 10
    data = list(range(data_size))

    tests = [
        ([(0, 0)], []),  # creation
        ([(3, 3)], list(reversed(range(3)))),  # normal write and read
        ([(3, 3), (3, 3)], list(reversed(range(3))) + list(reversed(range(3, 6)))),  # add and read to empty, repeat
        ([(3, 1), (1, 3)], [2, 3, 1, 0]),  # add, read not all, add some more and read all
        ([(1, 3), (3, 3)], [0, None, None, 3, 2, 1])  # add, read more than exists, add some more and read all
    ]

    all_tests_results = []

    for test, expected_results in tests:
        test_data = data[:]

        revision = Revision()

        vqueue = VersionedStack(revision)

        actual_results = []

        for push_count, read_count in test:
            push_data = test_data[:push_count]
            test_data = test_data[push_count:]

            for i in push_data:
                vqueue.push(i, revision)

            for _ in range(read_count):
                actual_results.append(vqueue.pop(revision))

        all_tests_results.append(
            all([actual == expected for actual, expected in zip(actual_results, expected_results)]))

    return all(all_tests_results)


def test_versions():
    data_count = 10
    data = list(range(10))
    random.shuffle(data)

    parent_revision = Revision()

    vstack = VersionedStack(parent_revision)

    for i in data:
        vstack.push(i, parent_revision)

    child_revision = parent_revision.fork()

    child_data = [vstack.pop(child_revision) for _ in range(data_count)]
    parent_data = [vstack.pop(parent_revision) for _ in range(data_count)]

    child_results = [a == b for a, b in zip(reversed(data), child_data)]
    parent_results = [a == b for a, b in zip(reversed(data), parent_data)]

    result_sameness = [a == b for a, b in zip(child_data, parent_data)]

    for i in parent_data:
        vstack.push(i, parent_revision)

    random.shuffle(child_data)

    for i in child_data:
        vstack.push(i, child_revision)

    vstack.merge(child_revision, parent_revision)

    parent_postfork_data = [vstack.pop(parent_revision) for _ in range(data_count)]

    parent_postfork_results = [a == b for a, b in zip(parent_postfork_data, reversed(child_data))]

    total_results = [
        all(child_results),
        all(parent_results),
        all(result_sameness),
        all(parent_postfork_results)
    ]

    return all(total_results)


def test_stack():
    test_results = [
        test_api(),
        test_versions()
    ]

    if all(test_results):
        print("Passed")
    else:
        print("Failed")


if __name__ == '__main__':
    test_stack()
