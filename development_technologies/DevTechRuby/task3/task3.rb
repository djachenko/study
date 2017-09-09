# (?<EventLog>\w*),\
# (?<RecordNumber>\w*),\
# (?<TimeGenerated>\w*),\
# (?<TimeWritten>\w*),\
# (?<EventID>\w*),\
# (?<EventType>\w*),\
# (?<EventTypeName>\w*),\
# (?<EventCategory>\w*),\
# (?<EventCategoryName>\w*),\
# (?<SourceName>\w*),\
# (?<ComputerName>\w*),\
# (?<SID>\w*),\
# (?<Message>\w*),\


# (?<year>\d{4})-(?<month>\d{2})-(?<day>\d{2}) (?<hour>\d{2}):(?<minutes>\d{2}):(?<seconds>\d{2})

regex = /^
(?<EventLog>[\w\\.:]+),
(?<RecordNumber>\d+),
(?<TimeGenerated>\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}),
(?<TimeWritten>\d{4}-\d{2}-\d{2}\s\d{2}:\d{2}:\d{2}),
(?<EventID>\d+),
(?<EventType>\d+),
(?<EventTypeName>\w[\w\s]*),
(?<EventCategory>\d*),
(?<EventCategoryName>\w[\w\s]*),
(?<SourceName>\w[\w\s\-]*),
(?<SID>\w*),
(?<ComputerName>\w[\w-]*),
(?<Message>[^,]*),
(?<rest>.*)
$/x

computers = Hash.new
event_types = Hash.new

def add_stats_entry(dict, key)
  dict[key] = 0 unless dict.has_key? key

  dict[key] += 1
end

File.open('filtered.csv', 'r') { |f|
  f.each_line { |line|
    res = regex.match line

    add_stats_entry computers, res['ComputerName']
    add_stats_entry event_types, res['EventTypeName']
  }
}

puts computers
puts
puts event_types