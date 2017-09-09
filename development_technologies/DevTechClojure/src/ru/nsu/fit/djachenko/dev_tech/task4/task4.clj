(ns ru.nsu.fit.djachenko.dev_tech.task4.task4
 (:gen-class))

(defn permute
 [permutations sources n]
 (if (== n 0)
  permutations
  (recur (reduce (fn
                    [acc permutation]
                    (concat acc
                            (map (fn
                                      [source_element]
                                      (conj permutation
                                            source_element))
                                     (filter (fn
                                              [x]
                                              (or
                                               (empty? permutation)
                                               (not (== 0 (compare x (last permutation))))
                                               ))
                                             sources))))
                   []
                   permutations)
           sources
           (dec n))))


(def result (permute [[]] ['a, 'b, 'c, 'd], 4))

;(println result)
;(println (count result))























