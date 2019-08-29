import csv

if __name__ == '__main__':
    fields_to_filter = [
        "EventLog",
        "RecordNumber",
        "TimeGenerated",
        "TimeWritten",
        "EventID",
        "EventType",
        "EventTypeName",
        "EventCategory",
        "EventCategoryName",
        "SourceName",
        "ComputerName",
        "SID",
        "Message"
    ]

    with open("log.csv") as logfile:
        reader = csv.DictReader(logfile)

        with open("filtered.csv", "w") as output:
            writer = csv.DictWriter(output, reader.fieldnames)

            writer.writeheader()

            for row in reader:
                x = row.values()

                if all(["\"" not in item for item in row.values()]):
                    filtered = {field_name: row[field_name] for field_name in fields_to_filter}

                    writer.writerow(filtered)
                else:
                    a = 7
