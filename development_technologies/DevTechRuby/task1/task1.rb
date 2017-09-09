chars = %w(a b c d)

def permute(permutations, sources, n)
  return permutations if n == 0

  permute(permutations.reduce([]) {|acc, permutation|
    acc + sources.select{|sym| permutation.empty? || sym != permutation[-1]}.map {|j|
      permutation + [j]
    }
  }, sources, n-1)
end


p permute([[]], chars, 4).size