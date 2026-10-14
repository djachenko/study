(ns ru.nsu.fit.djachenko.dev_tech.task7.core)

(defn expr_with_type [type exprs]
  (cons type exprs))

;; constant: (:const VAL). VAL = [true|false]
(defn expr_const [val]
  {:pre [(or (true? val) (false? val))]}
  (list :const val))

;; variable: (:var NAME). NAME is keyword
(defn expr_var [name]
  {:pre [(keyword? name)]}
  (list :var name))

;; expr_or: (:epr_or E1 E2 ... En) = E1 or E2 or ... or En
(defn expr_or [& exprs]
  (let [size (count exprs)]
    (if (> size 0)
      (if (= size 1)
        (first exprs)
        (cons :or exprs)))))

;; expr_and: (:epr_and E1 E2 ... En) = E1 and E2 and ... and En
(defn expr_and [& exprs]
  (let [size (count exprs)]
    (if (> size 0)
      (if (= size 1)
        (first exprs)
        (cons :and exprs)))))

;; expr_impl: (:epr_impl EL ER) = EL -> ER
(defn expr_impl [el er]
  (list :impl el er))

;; expr_not: (:epr_not EXPR) = not EXPR
(defn expr_not [expr]
  (list :not expr))



(defn constant_value [expr]
  (second expr))

(defn variable_name [expr]
  (second expr))

;; Possible values: :const, :var, :expr_or, :expr_and, :expr_impl, :expr_not
(defn expr_type [expr]
  (first expr))

;; All expr arguments. Example: (expr_args (:epr_and E1 E2 ... En)): (E1 E2 ... En)
(defn expr_args [expr]
  (if (or (= (expr_type expr) :var)
          (= (expr_type expr) :const))
    (list expr)
    (rest expr)))

;; nth arg of expr.
(defn expr_arg_nth [expr n]
  (nth expr n))



(defn variable? [expr]
  (= (first expr) :var))

(defn constant? [expr]
  (= (first expr) :const))

(defn same_variables? [vl vr]
  (and
    (variable? vl)
    (variable? vr)
    (= (variable_name vl)
       (variable_name vr))))

(defn expr_or? [expr]
  (= (first expr) :or))

(defn expr_and? [expr]
  (= (first expr) :and))

(defn expr_impl? [expr]
  (= (first expr) :impl))

(defn expr_not? [expr]
  (= (first expr) :not))

