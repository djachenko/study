(defun <> (a b) (not (eq a b)))
(defun neq (a b) (not (eq a b)))

;0!
(defun tline (tree) (cond 
((null tree) '())
((not (null tree)) (cond
	((atom (car tree)) (cons (car tree) (tline (cdr tree))))
	((not (atom (car tree))) (append (tline (car tree)) (tline (cdr tree))))))))
	
;1
(defun tlength (tree) (cond ((null tree) 0) (tree (cond ((atom tree) 1) ((not (atom tree)) (+ (tlength (car tree)) (tlength (cdr tree))))))))

;2
(defun tlastatom (tree) (cond ((null tree) NIL) (tree (cond ((atom tree) tree)  ((not (atom tree)) (cond ((null (cdr tree)) (tlastatom (car tree))) ((cdr tree) (tlastatom (cdr tree)))))))))

;3
(defun tfindatomreal (a tree pos) (cond 
((null tree) '()) 
(tree (cond 
	((atom (car tree)) (cond 
		((= (car tree) a) (cons pos (tfindatomreal a (cdr tree) (+ pos 1)))) 
		((<> (car tree) a) (tfindatomreal a (cdr tree) (+ pos 1))))) 
	((not (atom (car tree))) (cons (tfindatomreal a (car tree) 0) (tfindatomreal a (cdr tree) (+ pos 1))))))))

(defun tfindatom1 (a tree) (tfindatomreal a tree 0))
(defun tfindatom2 (a tree) (findatom a (tline tree)))

;4!
(defun tcompare (tree1 tree2) (if (atom tree1) 
(if (atom tree2) 
	(eq tree1 tree2) 
	NIL) 
(if (atom tree2) 
	NIL 
	(if (tcompare (car tree1) (car tree2))
		(tcompare (cdr tree1) (cdr tree2))
		NIL))))


(defun tcompare2 (tree) (if (null tree) 
T
(if (atom tree) 
	T
	(if (null (cdr tree))
		(tcompare2 (car tree))	
		(if (tcompare (car tree) (car (cdr tree)))
			(tcompare2 (cdr tree))
			NIL)))))

;5!
(defun insert (ins fin tree) (if (null tree) 
'()
(if (tcompare (car tree) fin) 
	(cons ins (cons fin (insert ins fin (cdr tree)))) 
	(cons (car tree) (insert ins fin (cdr tree))))))

;6!
(defun del (a tree) (if (null tree)
'() 
(if (tcompare a (car tree)) 
	(del a (cdr tree)) 
	(if (not (atom (car tree)))
		(cons (del a (car tree)) (del a (cdr tree)))
		(cons (car tree) (del a (cdr tree)))))))

;7!
(defun delrepeat (tree) (if (null tree)
'()
(cons (car tree) (delrepeat (del (car tree) (cdr tree))))))

;8
(defun lreverse (l) (if (null l)
'()
(append (lreverse (cdr l)) (list (car l)))))


(defun treverse (tree) (if (null tree)
'()
(if (atom tree)
	tree
	(append (treverse (cdr tree)) (list (treverse (car tree)))))))
