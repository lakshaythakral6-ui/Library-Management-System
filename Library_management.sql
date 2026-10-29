
-- LIBRARY MANAGEMENT SYSTEM

-- 1. CREATE BOOKS TABLE
CREATE TABLE books (
    book_id INT PRIMARY KEY,
    title VARCHAR(150) NOT NULL,
    author VARCHAR(100) NOT NULL,
    available BOOLEAN DEFAULT TRUE
);

-- 2. CREATE STUDENTS TABLE
CREATE TABLE students (
    student_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    course VARCHAR(50) NOT NULL,
    contact VARCHAR(15) NOT NULL
);

-- 3. CREATE TRANSACTIONS TABLE
CREATE TABLE transactions (
    transaction_id INT AUTO_INCREMENT PRIMARY KEY,
    book_id INT NOT NULL,
    student_id INT NOT NULL,
    issue_date DATE NOT NULL,
    due_date DATE NOT NULL,
    return_date DATE DEFAULT NULL,
    FOREIGN KEY (book_id) REFERENCES books(book_id),
    FOREIGN KEY (student_id) REFERENCES students(student_id)
);

-- 4. INSERT BOOKS
INSERT INTO books VALUES
(101, 'C++ Programming', 'E. Balagurusamy', TRUE),
(102, 'Let Us C', 'Yashavant Kanetkar', TRUE),
(103, 'Database System Concepts', 'Abraham Silberschatz', TRUE),
(104, 'Computer Networks', 'Andrew Tanenbaum', TRUE),
(105, 'Data Structures', 'Reema Thareja', TRUE);

-- 5. INSERT STUDENTS
INSERT INTO students VALUES
(1001, 'Lakshay Thakral', 'BCA', '9876543210'),
(1002, 'Aarav Sharma', 'BCA', '9876501234'),
(1003, 'Priya Verma', 'BCA', '9876512345');

-- 6. DISPLAY BOOKS
SELECT * FROM books;

-- 7. DISPLAY STUDENTS
SELECT * FROM students;

-- 8. SEARCH BOOK
SELECT * FROM books WHERE book_id = 101;

-- 9. AVAILABLE BOOKS
SELECT * FROM books WHERE available = TRUE;

-- 10. ISSUE BOOK
START TRANSACTION;

UPDATE books
SET available = FALSE
WHERE book_id = 101 AND available = TRUE;

INSERT INTO transactions
(book_id, student_id, issue_date, due_date)
SELECT 101, 1001, CURDATE(),
DATE_ADD(CURDATE(), INTERVAL 14 DAY)
WHERE ROW_COUNT() = 1;

COMMIT;

-- 11. DISPLAY TRANSACTIONS
SELECT * FROM transactions;

-- 12. RETURN BOOK
START TRANSACTION;

UPDATE transactions
SET return_date = CURDATE()
WHERE transaction_id = 1
AND return_date IS NULL;

UPDATE books
SET available = TRUE
WHERE book_id = 101
AND NOT EXISTS (
    SELECT 1 FROM transactions
    WHERE book_id = 101 AND return_date IS NULL
);

COMMIT;

-- 13. DISPLAY FINAL BOOK RECORDS
SELECT * FROM books;

-- 14. DISPLAY TOTAL BOOKS
SELECT COUNT(*) AS total_books FROM books;

-- 15. DISPLAY TOTAL STUDENTS
SELECT COUNT(*) AS total_students FROM students;

