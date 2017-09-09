(ns ru.nsu.fit.djachenko.dev_tech.task7.evaluator
  (:use ru.nsu.fit.djachenko.dev_tech.task7.core
        ru.nsu.fit.djachenko.dev_tech.task7.dnf))



; [values] - dictionary {var_name: var_value}
(defmulti evaluate
          (fn [expr values]
    (expr_type expr)))

(defn subevaluate [expr values]
  (map
    (fn [subexpr]
      (evaluate subexpr values))
    (expr_args expr)))

(defmethod evaluate :const [expr values]
  (constant_value expr))

(defmethod evaluate :var [expr values]
  (let [var_name (variable_name expr)]
    (if (contains? values var_name)
      (get values var_name)
      (throw (Exception. (format "variable %s isn't set" var_name))))))

(defmethod evaluate :not [expr values]
  (not (evaluate (expr_arg_nth expr 1) values)))

(defmethod evaluate :or [expr values]
  (let [x (subevaluate expr values)]
    (not (not-any? true? x))))

(defmethod evaluate :and [expr values]
  (every? true? (subevaluate expr values)))

; a impl b = not(a) or b
(defmethod evaluate :impl [expr values]
  (or
    (not (evaluate (expr_arg_nth expr 1) values))
    (evaluate (expr_arg_nth expr 2) values)))
