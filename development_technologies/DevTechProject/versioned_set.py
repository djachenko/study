import random

from revision import Revision
from tree_node import TreeNode
from itertools import chain, combinations

from versions_table import VersionsTable


class VersionedSet:
    @staticmethod
    def __default_comparator(a, b):
        if a == b:
            return 0
        elif a < b:
            return -1
        elif a > b:
            return 1

    def __init__(self, comparator=None):
        super().__init__()

        if not comparator:
            comparator = VersionedSet.__default_comparator

        self.roots = VersionsTable()
        self.comparator = comparator

    def contains(self, value, revision):
        return self.find_node(value, revision) is not None

    def get_root(self, revision):
        return self.roots.get(revision)

    def set_root(self, new_root, revision):
        self.roots.set(new_root, revision)

    def add(self, value, revision):
        if self.contains(value, revision):
            return

        new_node = TreeNode(value, revision)

        if self.get_root(revision) is None:
            self.set_root(new_node, revision)

            return

        current_node = self.get_root(revision)

        while current_node is not None:
            node_value = current_node.get_value()
            comparison_result = self.comparator(value, node_value)

            if comparison_result > 0:
                right = current_node.get_right(revision)

                if right is None:
                    current_node.set_right(new_node, revision)

                    return
                else:
                    current_node = right
            else:
                left = current_node.get_left(revision)

                if left is None:
                    current_node.set_left(new_node, revision)

                    return
                else:
                    current_node = left

    def find_node(self, value, revision):
        node = self.get_root(revision)

        while node is not None:
            node_value = node.get_value()
            comparison_result = self.comparator(value, node_value)

            if comparison_result == 0:
                return node
            elif comparison_result > 0:
                node = node.get_right(revision)
            else:
                node = node.get_left(revision)

        return None

    def find_parent(self, child_node, revision, start=None):
        if start is None:
            start = self.get_root(revision)

        if child_node is None:
            return None

        current_node = start
        value = child_node.get_value()

        while current_node is not None:
            node_value = current_node.get_value()
            comparison_result = self.comparator(value, node_value)

            if comparison_result == 0:
                raise Exception()
            elif comparison_result > 0:
                right = current_node.get_right(revision)

                if right is child_node:
                    return current_node
                elif right:
                    current_node = right
            else:
                left = current_node.get_left(revision)

                if left is child_node:
                    return current_node
                else:
                    current_node = left

        return None

    @staticmethod
    def get_min(root, r):
        while root is not None:
            if root.get_left(r) is None:
                return root.get_value()
            else:
                root = root.get_left(r)

        return None

    def __rec_delete(self, value, revision, node):
        if node is None:
            return None

        n_value = node.get_value()

        c_res = self.comparator(value, n_value)

        if c_res < 0:
            node.set_left(self.__rec_delete(value, revision, node.get_left(revision)), revision)
        elif c_res > 0:
            node.set_right(self.__rec_delete(value, revision, node.get_right(revision)), revision)
        else:
            left = node.get_left(revision)
            right = node.get_right(revision)

            if left is not None and right is not None:
                next_val = self.get_min(right, revision)

                new_node = TreeNode(next_val, revision)

                new_node.set_left(left, revision)
                new_node.set_right(self.__rec_delete(next_val, revision, right), revision)

                return new_node
            elif left is None:
                return right
            else:
                return left

        return node

    def rec_delete(self, value, revision):
        self.set_root(self.__rec_delete(value, revision, self.get_root(revision)), revision)

    def __merge_inner(self, node, revision_from, revision_to):
        if node is None:
            return

        left = node.get_left(revision_from)
        right = node.get_right(revision_from)

        self.__merge_inner(left, revision_from, revision_to)
        self.__merge_inner(right, revision_from, revision_to)

        node.set_left(left, revision_to)
        node.set_right(right, revision_to)

    def merge(self, revision_from, revision_to):
        self.__merge_inner(self.get_root(revision_from), revision_from, revision_to)

        self.roots.set(self.roots.get(revision_from), revision_to)

    def __size(self, node, revision):
        if node is None:
            return 0

        return 1 + self.__size(node.get_left(revision), revision) + self.__size(node.get_right(revision), revision)

    def size(self, revision):
        return self.__size(self.get_root(revision), revision)


def powerset(iterable):
    xs = list(iterable)
    # note we return an iterator rather than a list
    return chain.from_iterable(combinations(xs, n) for n in range(len(xs) + 1))


def test_api():
    data = list(range(10))
    random.shuffle(data)

    subsets = powerset(data)

    revision = Revision()

    total_results = []

    for subset in subsets:
        vset = VersionedSet()

        for i in data:
            vset.add(i, revision)

        for i in subset:
            vset.rec_delete(i, revision)

        contains_result = [vset.contains(i, revision) == (i not in subset) for i in data]

        total_results.append(all(contains_result))

    return all(total_results)


def test_versions():
    data = list(range(10))
    random.shuffle(data)

    subsets = powerset(data)

    revision = Revision()

    total_results = []

    for subset in subsets:
        vset = VersionedSet()

        for i in data:
            vset.add(i, revision)

        child = revision.fork()

        for i in subset:
            vset.rec_delete(i, child)

        parent_results = [vset.contains(i, revision) for i in data]
        child_result = [vset.contains(i, child) == (i not in subset) for i in data]

        total_results.append(all(parent_results))
        total_results.append(all(child_result))

        vset.merge(child, revision)

        parent_postmerge_results = [vset.contains(i, revision) == (i not in subset) for i in data]

        total_results.append(all(parent_postmerge_results))

    return all(total_results)


def test_set():
    test_results = [
        test_api(),
        test_versions()
    ]

    if all(test_results):
        print("Passed")
    else:
        print("Failed")


if __name__ == '__main__':
    test_set()
