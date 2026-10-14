(defun <> (a b) (not (eq a b)))
(defun neq (a b) (not (eq a b)))

;1
(defun mylength (l) (cond ((null l) 0) (l (+ 1 (mylength (cdr l))))))

(defun check (l) (if (null (cdr l))
T
(if (<= (cdar l) (cdadr l))
	(check (cdr l))
	NIL)))

(defun less (l a) (if (null l)
'()
(if (< (cdar l) a) 
	(cons (car l) (less (cdr l) a))
	(less (cdr l) a))))

(defun more (l a) (if (null l)
'()
(if (> (cdar l) a) 
	(cons (car l) (more (cdr l) a))
	(more (cdr l) a))))

(defun same (l a) (if (null l)
'()
(if (eq (cdar l) a) 
	(cons (car l) (same (cdr l) a))
	(same (cdr l) a))))

(defun qsort (l) (if (null l)
'()
(append (qsort (less l (cdar l))) (append (same l (cdar l)) (qsort (more l (cdar l))))))) 

(defun mymerge (l1 l2) (qsort (append (mainfirst l1 l2) (mainsecond l1 l2))))

(defun mainfirst (l1 l2) (if (null l1)
'()
(if (null (assoc (caar l1) l2))
	(cons (car l1) (mainfirst (cdr l1) l2))
	(cons (cons (caar l1) (+ (cdar l1) (cdr (assoc (caar l1) l2)))) (mainfirst (cdr l1) l2)))))

(defun mainsecond (l1 l2) (if (null l2)
'()
(if (null (assoc (caar l2) l1))
	(cons (car l2) (mainsecond l1 (cdr l2)))
	(mainsecond l1 (cdr l2)))))
