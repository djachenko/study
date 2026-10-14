(defun <> (a b) (not (eq a b)))
(defun neq (a b) (not (eq a b)))

;1
(defun mylength (l) (cond ((null l) 0) (l (+ 1 (mylength (cdr l))))))

;2
(defun lastatom (l) (cond ((null (cdr l)) (car l)) ((cdr l) (lastatom (cdr l)))))

;3
(defun findatomreal (a l pos) (cond 
((null l) '())  
(l (cond 
	((= (car l) a) (cons pos (findatomreal (cdr l) a (+ pos 1)))) 
	((<> (car l) a) (findatomreal (cdr l) a (+ pos 1)))))))

(defun findatom (a l) (findatomreal a l 0))

;4
(defun compare (l) (cond ((null l) T) ((null (cdr l)) T) ((eq (car l) (car (cdr l))) (compare (cdr l))) ((not (eq (car l) (car (cdr l)))) NIL)))

;5a
(defun insertOnce (fin ins lis) (cond ((null lis) '()) ((not (null lis)) (cond ((= (car lis) fin) (cons ins lis)) ((<> (car lis) fin) (cons (car lis) (insertOnce fin ins (cdr lis))))))))

;5b
(defun insert (fin ins lis) (cond ((null lis) '()) ((not (null lis)) (cond ((= (car lis) fin) (cons ins (cons fin (insert fin ins (cdr lis))))) ((<> (car lis) fin) (cons (car lis) (insert fin ins (cdr lis))))))))

;6
(defun del (a l) (cond ((null l) '()) ((not (null l)) (cond ((= (car l) a) (del a (cdr l))) ((<> (car l) a) (cons (car l) (del a (cdr l))))))))
