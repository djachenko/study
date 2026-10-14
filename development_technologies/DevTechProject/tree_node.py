from versions_table import VersionsTable


class TreeNode:
    def __init__(self, value, revision):
        super().__init__()

        self.__value = value

        self.__left = VersionsTable()
        self.__right = VersionsTable()

        self.__left.set(None, revision)
        self.__right.set(None, revision)

    def get_value(self):
        return self.__value

    def set_left(self, node, revision):
        self.__left.set(node, revision)

    def get_left(self, revision):
        return self.__left.get(revision)

    def set_right(self, node, revision):
        self.__right.set(node, revision)

    def get_right(self, revision):
        return self.__right.get(revision)
