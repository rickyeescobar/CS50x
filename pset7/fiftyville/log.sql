-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema

CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);

-- Searched through the police data base

SELECT * FROM crime_scene_reports WHERE street LIKE "%humphrey street%";

-- Found the record
--  id  | year | month | day |     street      |                   description
--| 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
                                                --Interviews were conducted today with three witnesses who were present at the
                                                --time – each of their interview transcripts mentions the bakery. |

SELECT licence_plate FROM bakery_security_logs WHERE day = "28" AND month = "7" AND (minute > "13" AND minute < "26";

| id  | year | month | day | hour | minute | activity | license_plate |
| 259 | 2021 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |

| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |

+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 745650 | Sophia  | (027) 555-1068 | 3642612721      | 13FNH73       |

SELECT * FROM phone_calls WHERE




SELECT * FROM interviews WHERE month = "7" AND day = "28";

| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car
                                     in the bakery parking lot and drive away. If you have security footage from
                                     the bakery parking lot, you might want to look for cars that left the parking
                                     lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this
                                         morning, before I arrived at Emma's bakery, I was walking by the ATM on
                                         Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to
                                        them for less than a minute. In the call, I heard the thief say that they
                                        were planning to take the earliest flight out of Fiftyville tomorrow. The
                                        thief then asked the person on the other end of the phone to purchase the
                                        flight ticket. |


-- look at bakery security logs and cross reference people license plates

SELECT *
FROM people
WHERE license_plate
IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND (minute > "13" AND minute < "26"));

SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26");


SELECT *
FROM people
WHERE license_plate
IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"));

+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 745650 | Sophia  | (027) 555-1068 | 3642612721      | 13FNH73       |
+--------+---------+----------------+-----------------+---------------+


 SELECT * FROM airports;

| id | abbreviation |                full_name                |     city      |
+----+--------------+-----------------------------------------+---------------+
| 1  | ORD          | O'Hare International Airport            | Chicago       |
| 2  | PEK          | Beijing Capital International Airport   | Beijing       |
| 3  | LAX          | Los Angeles International Airport       | Los Angeles   |
| 4  | LGA          | LaGuardia Airport                       | New York City |
| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
| 6  | BOS          | Logan International Airport             | Boston        |
| 7  | DXB          | Dubai International Airport             | Dubai         |
| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |
| 9  | HND          | Tokyo International Airport             | Tokyo         |
| 10 | CDG          | Charles de Gaulle Airport               | Paris         |
| 11 | SFO          | San Francisco International Airport     | San Francisco |
| 12 | DEL          | Indira Gandhi International Airport     | Delhi         |

SELECT * FROM flights WHERE day = "28" AND month = "7" AND year = "2021" and origin_airport_id IN (

+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 1  | 8                 | 7                      | 2021 | 7     | 28  | 17   | 50     |
| 6  | 8                 | 5                      | 2021 | 7     | 28  | 13   | 49     |
| 17 | 8                 | 4                      | 2021 | 7     | 28  | 20   | 16     |
| 34 | 8                 | 5                      | 2021 | 7     | 28  | 17   | 20     |
| 35 | 8                 | 4                      | 2021 | 7     | 28  | 16   | 16     |



SELECT *
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
((SELECT id FROM airports WHERE city LIKE "fiftyville"));

+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT * FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60";
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+

SELECT *
FROM people
WHERE license_plate
IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"))
AND phone_number in
(SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60");

+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |



SELECT * FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" ;
SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" ;

SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" );
+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 49610011       | 686048    | 2010          |
| 86363979       | 948985    | 2010          |
| 26013199       | 514354    | 2012          |
| 16153065       | 458378    | 2012          |
| 28296815       | 395717    | 2014          |
| 25506511       | 396669    | 2014          |
| 28500762       | 467400    | 2014          |
| 76054385       | 449774    | 2015          |
| 81061156       | 438727    | 2018          |
+----------------+-----------+---------------+

SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" );

 -- people with licence plate at the scene
 -- phone call less than one minute on day of crime
 -- used atm on legget street earlier that morning

SELECT *
FROM people
WHERE license_plate
IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60")
AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" ));

+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+



-- look at flights again

SELECT *
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
((SELECT id FROM airports WHERE city LIKE "fiftyville"));

SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
((SELECT id FROM airports WHERE city LIKE "fiftyville"));

SELECT * FROM passengers WHERE flight_id IN
(SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville"));

SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville"));


-- cross reference passport number of people on flights out of fiftyville, on 7 /29 to other query

SELECT *
FROM people
WHERE license_plate
IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60")
AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND transaction_type LIKE "Withdrawal" AND year = "2021" AND month = "7" AND day = "28" ))
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville")));


|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |

SELECT *
FROM people
WHERE license_plate
IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60")
AND id IN
(SELECT person_id FROM bank_accounts
 WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" ))
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville")));



SELECT * FROM airports WHERE id IN(
SELECT destination_airport_id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville")
AND id IN
(SELECT flight_id FROM passengers WHERE passport_number = "3592750733" OR passport_number = "5773159633"));


SELECT *
FROM people
WHERE license_plate
IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60")
AND id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location LIKE "Leggett%" AND transaction_type LIKE "withdrawal" AND year = "2021" AND month = "7" AND day = "28" ))
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" and origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville")));


SELECT *
FROM people
WHERE license_plate
IN
(SELECT license_plate
FROM bakery_security_logs
WHERE day = "28" AND month = "7" AND year = "2021" AND hour = "10" AND (minute > "13" AND minute < "26"))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE year = "2021" AND month = "7" AND day = "28" AND duration < "60")
AND id IN
(SELECT person_id FROM bank_accounts
 WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE transaction_type = "withdraw" AND atm_location LIKE "Leggett%" AND year = "2021" AND month = "7" AND day = "28" ))
AND passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2021" AND hour = "8" AND origin_airport_id IN
(SELECT id FROM airports WHERE city LIKE "fiftyville")));

-- THIEF is BRUCE
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+

-- now to find accomplice

SELECT * from phone_calls WHERE caller = "(367) 555-5533" AND year = "2021" AND month = "7" AND day = "28" and duration < "60";


SELECT * from people WHERE phone_number IN (SELECT receiver from phone_calls WHERE caller = "(367) 555-5533" AND year = "2021" AND month = "7" AND day = "28" and duration < "60");
|   id   | name  |  phone_number  | passport_number | license_plate |
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |

-- robin

--either new york or boston
