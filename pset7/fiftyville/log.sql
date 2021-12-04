-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.


-- Get description of the crime scene report on the day of the crime

SELECT description
FROM crime_scene_reports
WHERE
    year = 2020
    AND month = 7
    AND day = 28
    AND street = 'Chamberlin Street';

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present
-- at the time — each of their interview transcripts mentions the courthouse.


-- Get witness statement in the courtroom on the day of the crime

SELECT transcript
FROM interviews
WHERE
    year = 2020
    AND month = 7
    AND day = 28
    AND transcript LIKE '%courthouse%';

-- Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the courthouse parking lot and drive away.

-- If you have security footage from the courthouse parking lot,
-- you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized.

-- Earlier this morning, before I arrived at the courthouse,
-- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.

-- In the call, I heard the thief say that they were planning to take
-- the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- Get Thief by intersecting suspect names in every witness statement

-- Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the courthouse parking lot and drive away.
SELECT name
FROM people
JOIN courthouse_security_logs
    ON people.license_plate = courthouse_security_logs.license_plate
WHERE
    year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25 -- within ten minutes
    AND activity = 'exit' -- thief drive away
INTERSECT
-- Earlier this morning, before I arrived at the courthouse,
-- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
SELECT name
FROM people
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
WHERE
    year = 2020
    AND month = 7
    AND day = 28
    AND atm_location = 'Fifer Street' -- walking on Fifer Street
    AND transaction_type = 'withdraw' -- thief withdrawing some money
INTERSECT
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
SELECT name
FROM people
JOIN phone_calls -- phone call
    ON people.phone_number = phone_calls.caller
WHERE
    year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60 -- less than a minute
INTERSECT
-- In the call, I heard the thief say that they were planning to take
-- the earliest flight out of Fiftyville tomorrow.
SELECT name
FROM people
JOIN passengers
    ON people.passport_number = passengers.passport_number
WHERE flight_id IN (
    SELECT id
    FROM flights
    WHERE
        year = 2020
        AND month = 7
        AND day = 29 -- tomorrow: 28 + 1
    ORDER BY -- the earliest flight out
        hour,
        minute
    LIMIT 1 -- the earliest flight out
    );
-- Thief is Ernest


-- Get thief destination

-- In the call, I heard the thief say that they were planning to take
-- the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT city
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE
        year = 2020
        AND month = 7
        AND day = 29
        ORDER BY -- the earliest flight out
            hour,
            minute
        LIMIT 1 -- the earliest flight out
    );

-- Thief destination is London


-- Get thief accomplice

-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
SELECT name
FROM people
JOIN phone_calls -- phone call
    ON people.phone_number = phone_calls.receiver
WHERE
    year = 2020
    AND month = 7
    AND day = 28
    AND duration < 60 -- less than a minute
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE name = "Ernest" -- thief
    );

-- Thief accomplice is Berthold
