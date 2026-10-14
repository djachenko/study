(ns ru.nsu.fit.djachenko.dev_tech.task5.task5-test
  (:use ru.nsu.fit.djachenko.dev_tech.task5.task5)
  (:require [clojure.test :as test]))


(def epsilon 1)

(defn abs [n] (max n (-' n)))

(defn float= [x y]
  (println (<= (abs (- x y)) epsilon))
  (<= (abs (- x y)) epsilon))


(test/deftest defpackage-test
  (test/testing "count"
    (test/is (float= ((integral func) 2) 4))
    (test/is (float= ((integral func) 3) 9))
    (test/is (float= ((integral func) 4) 16))
    )
  )

(test/run-tests)