class Segment:
    versions_count = 0

    def __init__(self, parent):
        super().__init__()

        self.parent = parent
        self.version = Segment.versions_count
        Segment.versions_count += 1
