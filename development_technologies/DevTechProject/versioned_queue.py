import random

from list_node import ListNode
from revision import Revision
from versions_table import VersionsTable


class VersionedQueue:
    def __init__(self, revision):
        super().__init__()

        self.__head = ListNode(None, revision)
        self.__tails = VersionsTable()

        self.__tails.set(self.__head, revision)

    def add(self, value, revision):
        new_node = ListNode(value, revision)

        current_tail = self.__tails.get(revision)

        current_tail.set_next(new_node, revision)

        self.__tails.set(new_node, revision)

    def __reset_tail(self, revision):
        self.__tails.set(self.__head, revision)

    def get(self, revision):
        first_node = self.__head.get_next(revision)

        if first_node:
            second_node = first_node.get_next(revision)

            self.__head.set_next(second_node, revision)

            if not second_node:
                self.__reset_tail(revision)

        if first_node:
            return first_node.get_value()
        else:
            return None

    def clear(self, revision):
        self.__head.set_next(None, revision)
        self.__reset_tail(revision)

    def merge(self, revision_from, revision_to):
        self.clear(revision_to)

        node_iter = self.__head

        while node_iter.get_next(revision_from) is not None:
            next_node = node_iter.get_next(revision_from)

            node_iter.set_next(next_node, revision_to)

            node_iter = next_node

        self.__tails.set(node_iter, revision_to)


def test_api():
    data_size = 10
    data = list(range(data_size))

    tests = [
        ([(0, 0)], []),  # creation
        ([(3, 3)], list(range(3))),  # normal write and read
        ([(3, 3), (3, 3)], list(range(6))),  # add and read to empty, repeat
        ([(3, 1), (1, 3)], list(range(4))),  # add, read not all, add some more and read all
        ([(1, 3), (3, 3)], [0, None, None, 1, 2, 3])  # add, read more than exists, add some more and read all
    ]

    all_tests_results = []

    for test, expected_results in tests:
        test_data = data[:]

        revision = Revision()

        vqueue = VersionedQueue(revision)

        actual_results = []

        for push_count, read_count in test:
            push_data = test_data[:push_count]
            test_data = test_data[push_count:]

            for i in push_data:
                vqueue.add(i, revision)

            for _ in range(read_count):
                actual_results.append(vqueue.get(revision))

        test_results = [actual == expected for actual, expected in zip(actual_results, expected_results)]

        all_tests_results.append(all(test_results))

    return all(all_tests_results)


def test_versions():
    data_count = 10
    data = list(range(10))
    random.shuffle(data)

    parent_revision = Revision()

    vqueue = VersionedQueue(parent_revision)

    for i in data:
        vqueue.add(i, parent_revision)

    child_revision = parent_revision.fork()

    child_data = [vqueue.get(child_revision) for _ in range(data_count)]
    parent_data = [vqueue.get(parent_revision) for _ in range(data_count)]

    child_results = [a == b for a, b in zip(data, child_data)]
    parent_results = [a == b for a, b in zip(data, parent_data)]

    result_sameness = [a == b for a, b in zip(child_data, parent_data)]

    for i in parent_data:
        vqueue.add(i, parent_revision)

    random.shuffle(child_data)

    for i in child_data:
        vqueue.add(i, child_revision)

    vqueue.merge(child_revision, parent_revision)

    parent_postfork_data = [vqueue.get(parent_revision) for _ in range(data_count)]

    parent_postfork_results = [a == b for a, b in zip(parent_postfork_data, child_data)]

    total_results = [
        all(child_results),
        all(parent_results),
        all(result_sameness),
        all(parent_postfork_results)
    ]

    return all(total_results)


def test_queue():
    test_results = [
        test_api(),
        test_versions()
    ]

    if all(test_results):
        print("Passed")
    else:
        print("Failed")


if __name__ == '__main__':
    test_queue()
