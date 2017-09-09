(ns ru.nsu.fit.djachenko.dev_tech.task7.dnf
  (:use ru.nsu.fit.djachenko.dev_tech.task7.core)
  (:require [clojure.pprint :as pprint :refer [pprint print-table]]))

; atom = const or var
(defn atom? [expr]
  (or
    (constant? expr)
    (variable? expr)))

; literal = atom or not(atom)
(defn literal? [expr]
  (or
    (atom? expr)
    (and (expr_not? expr)
         (atom? (expr_arg_nth expr 1)))))

; every argument - literal
(defn consist_of_literal? [expr]
  (every? literal? (expr_args expr)))

; elementary conjuction = literal or AND expr consists of literal with distinct args
(defn elementary_conjuction? [expr]
  (or (literal? expr) (and
                        (expr_and? expr)
                        (consist_of_literal? expr)
                        (= (expr_args expr) (distinct (expr_args expr))))))

; dnf = disjunction of elementary conjuctions
(defn dnf? [expr]
  (or
    (elementary_conjuction? expr)
    (and
      (expr_or? expr)
      (every? elementary_conjuction? (expr_args expr)))))



(defn replace_implications [expr]
  (if (expr_impl? expr)
    (expr_or
      (expr_not (replace_implications (expr_arg_nth expr 1)))
      (replace_implications (expr_arg_nth expr 2)))
    (if (atom? expr)
      expr
      (expr_with_type (expr_type expr) (map replace_implications (expr_args expr))))))

; if 'expr_not?' -> dispatch by expr_type
; else -> replace_negative_exprs in args
(defmulti replace_nots
          (fn [expr]
    (if (not (expr_not? expr))
      :default
      (expr_type (expr_arg_nth expr 1)))))

(defmethod replace_nots :default [expr]
  (if (atom? expr)
    expr
    (expr_with_type (expr_type expr) (map replace_nots (expr_args expr)))))

; not(true) = false, not(false) = true
(defmethod replace_nots :const [expr]
  (expr_const (not (constant_value expr))))

; not(var) = not(var)
(defmethod replace_nots :var [expr]
  expr)

; not (not (a)) = a
(defmethod replace_nots :not [expr]
  (replace_nots (expr_arg_nth (expr_arg_nth expr 1) 1)))

; not (a or b) = not(a) and not(b)
(defmethod replace_nots :or [expr]
  (let [not_arg (expr_arg_nth expr 1)]
    (apply expr_and
      (map
        (fn [sub_expr]
          (replace_nots (expr_not sub_expr)))
        (expr_args not_arg)))))

; not (a and b) = not(a) or not(b)
(defmethod replace_nots :and [expr]
  (let [not_arg (expr_arg_nth expr 1)]
    (apply expr_or
      (map
        (fn [sub_expr]
          (replace_nots (expr_not sub_expr)))
        (expr_args not_arg)))))


(defn distribution [expr]
  (if (literal? expr)
    expr
    (if (expr_and? expr)
      (let [disjunctions (filter (fn [x]
                                   (expr_or? x))
                                 (expr_args expr))
            not_disjunctions (filter
                               (fn [x]
                                 (not (expr_or? x)))
                               (expr_args expr))]
        (apply expr_or
               (map (fn [and_args]
                      (apply expr_and and_args))
                    (reduce (fn [ands_arg_lists disjunction]
                              (reduce (fn [acc disjunction_arg]
                                        (concat acc (map (fn [and_arg_list]
                                                           (conj and_arg_list disjunction_arg))
                                                         ands_arg_lists)))
                                      []
                                      (expr_args disjunction))
                              )
                            [not_disjunctions]
                            disjunctions)
                    )))
      (apply expr_or (map distribution (expr_args expr))))))

; (a and a and b) or (not(b) and not(b) and a) = (a and b) or (not(b) and a)
; expressions like (:and A) will be transformed to A because of 'expr_or' and 'expr_and' behaviour
(defn remove_duplicates_in_ands [expr]
  (apply expr_or
    (map
      (fn [sub_expr]
        (if (expr_and? sub_expr)
          (apply expr_and (distinct (expr_args sub_expr)))
          (if (literal? expr)
            expr
            (remove_duplicates_in_ands sub_expr)))
        )
      (expr_args expr))))

; (expr_and (var x) (expr_and (var y) (var z)) = (expr_and (var x) (var y) (var z))
(defn expand_nested_and [expr]
  (if (not (expr_and? expr))
    expr
    (apply expr_and (reduce (fn [args cur]
                              (if (expr_and? cur)
                                (concat args (expr_args cur))
                                (concat args (list cur))))
                            []
                            (expr_args expr)))))

; (expr_or (var x) (expr_or (var y) (var z)) = (expr_or (var x) (var y) (var z))
(defn expand_nested_or [expr]
  (if (not (expr_or? expr))
    expr
    (apply expr_or (reduce (fn [args cur]
                              (if (expr_or? cur)
                                (concat args (expr_args cur))
                                (concat args (list cur))))
                            []
                           (expr_args expr)))))

(defn dnf [expr]
  (if (dnf? expr)
    expr
    (expand_nested_or
      (expand_nested_and
        (remove_duplicates_in_ands
          (distribution
            (replace_nots
              (replace_implications expr))))))))