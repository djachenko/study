(ns ru.nsu.fit.djachenko.dev_tech.task4.task4-test
   (:use ru.nsu.fit.djachenko.dev_tech.task4.task4)
   (:require [clojure.test :as test]))

(defn check
  [permutation]
  (if (<= (count permutation) 1)
    true
    (if (== 0 (compare (first permutation) (first (rest permutation))))
      false
      (recur (rest permutation)))))

(test/deftest defpackage-test
  (test/testing "count"
    (test/is (== (count (permute [[]] ['a 'b 'c 'd] 4)) 108)))
  (test/testing "permutations uniq"
    (test/is (distinct? (permute [[]] ['a 'b 'c 'd] 4))))
  (test/testing "internal condition"
    (test/is (every? check (permute [[]] ['a 'b 'c 'd] 4))))
  )


(test/run-tests)
