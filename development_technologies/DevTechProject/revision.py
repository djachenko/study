from segment import Segment


class Revision:
    def __init__(self, root=None, current=None):
        super().__init__()

        if current is None:
            current = Segment(None)

        self.current = current
        self.root = root

    def versions(self):
        results = []

        p = self.current

        while p is not None:
            results.append(p.version)

            p = p.parent

        return results

    def fork(self):
        new_revision = Revision(self.current, Segment(self.current))
        self.current = Segment(self.current)

        return new_revision

    def current_version(self):
        return self.current.version
