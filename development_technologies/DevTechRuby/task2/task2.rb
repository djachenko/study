# require 'etc'



class Array;
  def main_func(lmbd, merger)
    thread_count = 4

    merger.((distributed_groups thread_count).map { |slice|
      Thread.new(slice, &lmbd)
    }.each(&:join).map(&:value))
  end

  def distributed_groups(num_groups)
    return [] if num_groups == 0

    slice_base = self.size / num_groups
    over_size = self.size % num_groups

    (0...over_size).map {|i| self[i * (slice_base + 1) ... (i + 1) * (slice_base + 1)]} +
    (over_size...num_groups).map { |i| self[i * slice_base + over_size ... (i + 1) * slice_base + over_size]}
  end

  def parallel_any?
    main_func(->(arr) { arr.any? }, ->(results) { results.any? })
  end

  def parallel_all?
    main_func(->(arr) { arr.all? }, ->(results) { results.all? })
  end

  def parallel_map(&block)
    main_func(->(arr) { arr.map(&block) }, ->(results) { results.reduce { |acc, i| acc + i } })
  end

  def parallel_select(&block)
    main_func(->(arr) { arr.select(&block) }, ->(results) {results.reduce { |acc, i| acc + i } })
  end
end

test_arr = [1, 2, 3, 4, 5]

puts test_arr.parallel_select {|i| i % 2 != 0}


def method a, b
  synchronized {
    field = a + b
    return a
  }
end