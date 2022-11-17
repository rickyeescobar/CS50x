CREATE TABLE transactions (
    transaction_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
    id INTEGER NOT NULL,
    transaction_date TEXT NOT NULL ,
    transaction_type TEXT NOT NULL,
    size INTEGER NOT NULL,
    instrument TEXT NOT NULL,
    instrument_price NUMERIC NOT NULL,
    cash_change NUMERIC NOT NULL,
    FOREIGN KEY (id)
        REFERENCES users (id)
);


DATETIME('now','localtime')

INSERT INTO transactions ( id, transaction_date, transaction_type, size, instrument, instrument_price, cash_change )
VALUES( ? , datetime('now','localtime') , "BUY" , ? , ? , ? , ? );

SELECT instrument FROM transactions WHERE

SELECT instrument, sum(size) AS position FROM transactions GROUP BY instrument HAVING position != 0 and id = ? ;

