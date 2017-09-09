(ns ru.nsu.fit.djachenko.dev-tech.task7.task7-test
  (:use ru.nsu.fit.djachenko.dev_tech.task7.task7.core
        ru.nsu.fit.djachenko.dev_tech.task7.task7.evaluator
        ru.nsu.fit.djachenko.dev_tech.task7.task7.dnf)
  (:require [clojure.test :as test]))


(test/deftest defpackage-test
  (test/testing "or"
    (let [or_func (expr_or (expr_var :a) (expr_var :b))]
      (test/is (evaluate or_func {:a true :b true}))
      (test/is (evaluate or_func {:a true :b false}))
      (test/is (evaluate or_func {:a false :b true}))
      (test/is (not (evaluate or_func {:a false :b false})))
      )
    )
  (test/testing "and"
    (let [and_func (expr_and (expr_var :a) (expr_var :b))]
      (test/is (evaluate and_func {:a true :b true}))
      (test/is (not (evaluate and_func {:a true :b false})))
      (test/is (not (evaluate and_func {:a false :b true})))
      (test/is (not (evaluate and_func {:a false :b false})))
      )
    )
  (test/testing "not"
    (let [not_func (expr_not (expr_var :a))]
      (test/is (evaluate not_func {:a false}))
      (test/is (not (evaluate not_func {:a true})))
      )
    )
  (test/testing "impl"
    (let [impl_func (expr_impl (expr_var :a) (expr_var :b))]
      (test/is (evaluate impl_func {:a true :b true}))
      (test/is (not (evaluate impl_func {:a true :b false})))
      (test/is (evaluate impl_func {:a false :b true}))
      (test/is (evaluate impl_func {:a false :b false}))
      )
    )
  (test/testing "dnf"
    (test/testing "implications"
      (test/is (dnf? (dnf (expr_impl (expr_var :a) (expr_var :b)))))
      )
    (test/testing "nested_or"
      (test/is (dnf? (dnf (expr_or (expr_var :x) (expr_or (expr_var :y) (expr_var :z))))))
      )
    (test/testing "nested_and"
      (test/is (dnf? (dnf (expr_and (expr_var :x) (expr_and (expr_var :y) (expr_var :z))))))
      )
    (test/testing "duplicates_in_ands"
      ; (a and a and b) or (not(b) and not(b) and a)
      (test/is (dnf? (dnf (expr_or
                            (expr_and (expr_var :a) (expr_var :a) (expr_var :b))
                            (expr_and (expr_not (expr_var :b)) (expr_not (expr_var :b)) (expr_var :a))))))
      )
    (test/testing "distribution"
    ; a and (b or c) = (a and b) or (a and c)
      (test/is (dnf? (dnf (expr_and (expr_var :a) (expr_or (expr_var :b) (expr_var :c)) (expr_var :d)))))
      )
    (test/testing "replace_nots"
      (test/is (dnf? (dnf (expr_not (expr_or (expr_not (expr_var :a)) (expr_var :b))))))
      )
    (test/testing "replace_implications"
      (test/is (dnf? (dnf (expr_impl (expr_var :a) (expr_var :b)))))
    )
  )
  )

(test/run-tests)