(ns ru.nsu.fit.djachenko.dev_tech.task5
  (:gen-class))

(import '(java.lang Math))

(defn func
  [x]
  (* 2 x))

(def step 0.17)

(defn rectangle
  [f x]
  (* (f x) step)
  )

(defn partial_sum
  [f, x, self]
  (if (<= x 0)
    0
    (+ (self f (- x step) self) (rectangle f x))
  ))


(defn integral_internal
  [f, part]
  (fn
    [x]
    (part f (* (Math/floor (/ x step)) step) part)
    ))

(defn integral
  [f]
  (integral_internal f (memoize partial_sum)))


(def integ (integral func))

(println (time ((integral func) 4)))

(println (time (integ 2)))
(println (time (integ 2)))
(println (time (integ 4)))