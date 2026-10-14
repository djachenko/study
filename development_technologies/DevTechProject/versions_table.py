class VersionsTable:
    def __init__(self):
        super().__init__()

        self.__versions = dict()

    def get(self, revision):
        vkeys = self.__versions.keys()
        rkeys = revision.versions()

        common_versions = set(self.__versions.keys()).intersection(revision.versions())

        if common_versions:
            latest_version = max(common_versions)

            return self.__versions[latest_version]
        else:
            return None

    def set(self, value, revision):
        self.__versions[revision.current_version()] = value

    def remove(self, segment):
        del self.__versions[segment.version]
