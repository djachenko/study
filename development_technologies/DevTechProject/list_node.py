from versions_table import VersionsTable


class ListNode:
    def __init__(self, value, revision):
        super().__init__()

        self.__value = value
        self.__versions = VersionsTable()

        self.__versions.set(None, revision)

    def get_value(self):
        return self.__value

    def get_next(self, revision):
        return self.__versions.get(revision)

    def set_next(self, next_node, revision):
        self.__versions.set(next_node, revision)
