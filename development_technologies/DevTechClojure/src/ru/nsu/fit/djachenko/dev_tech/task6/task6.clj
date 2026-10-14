(ns ru.nsu.fit.djachenko.dev_tech.task6.task6
  (:gen-class))

(import '(java.lang Math))


(defn func
  [x]
  (* 2 x))

(def step 0.01)

(defn rectangle
  [f x]
  (* (/ (+ (f x) (f (- x step))) 2) step)
  )

(defn partials
  ([f] (partials f step 0))
  ([f, x, acc]
   (lazy-seq (cons (+ acc (rectangle f x)) (partials f (+ x step) (+ acc (rectangle f x)))))))


(defn integral [f]
  (let [part_seq (partials f)]
    (fn [x]
      (nth part_seq (dec (Math/floor (/ x step)))))))

(def i (integral func))

(println (i 3))