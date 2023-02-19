-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Initial info: All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2021 AND street = "Humphrey Street";
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.



Getting witness statements

SELECT id, name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- Witness statements:
--1) ID = 161, name = Ruth, Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--2) ID = 162, name = Eugene, I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--3) ID = 163, name = Raymond, As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT id, activity, license_plate, hour, minute FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25;

--Possible Thief Licence Plates:
--| id  | activity | license_plate | hour | minute |
--| 260 | exit     | 5P2BI95       | 10   | 16     |
--| 261 | exit     | 94KL13X       | 10   | 18     |
--| 262 | exit     | 6P58WS2       | 10   | 18     |
--| 263 | exit     | 4328GD8       | 10   | 19     |
--| 264 | exit     | G412CB7       | 10   | 20     |
--| 265 | exit     | L93JTIZ       | 10   | 21     |
--| 266 | exit     | 322W7JE       | 10   | 23     |
--| 267 | exit     | 0NTHK55       | 10   | 23     |

SELECT id, account_number, transaction_type, amount FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";
--ATM activity on Leggett Street:

--+-----+----------------+------------------+--------+
--| id  | account_number | transaction_type | amount |
--+-----+----------------+------------------+--------+
--| 246 | 28500762       | withdraw         | 48     |
--| 264 | 28296815       | withdraw         | 20     |
--| 266 | 76054385       | withdraw         | 60     |
--| 267 | 49610011       | withdraw         | 50     |
--| 269 | 16153065       | withdraw         | 80     |
--| 288 | 25506511       | withdraw         | 20     |
--| 313 | 81061156       | withdraw         | 30     |
--| 336 | 26013199       | withdraw         | 35     |
--+-----+----------------+------------------+--------+

SELECT id, caller, receiver, duration FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28;
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28;
--+-----+----------------+----------------+----------+
--| id  |     caller     |    receiver    | duration |
--+-----+----------------+----------------+----------+
--| 221 | (130) 555-0289 | (996) 555-8899 | 51       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 36       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 45       |
--| 234 | (609) 555-5876 | (389) 555-5198 | 60       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 50       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 43       |
--| 255 | (770) 555-1861 | (725) 555-3243 | 49       |
--| 261 | (031) 555-6622 | (910) 555-3251 | 38       |
--| 279 | (826) 555-1652 | (066) 555-9701 | 55       |
--| 281 | (338) 555-6650 | (704) 555-2131 | 54       |
--+-----+----------------+----------------+----------+

SELECT id, abbreviation, full_name, city FROM airports WHERE city = "Fiftyville";
--+----+--------------+-----------------------------+------------+
--| id | abbreviation |          full_name          |    city    |
--+----+--------------+-----------------------------+------------+
--| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
--+----+--------------+-----------------------------+------------+

SELECT id, origin_airport_id, destination_airport_id, hour, minute FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29;
SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29;

List of flights day after the robbery from Fiftyville Regional Airport
--+----+-------------------+------------------------+------+--------+
--| id | origin_airport_id | destination_airport_id | hour | minute |
--+----+-------------------+------------------------+------+--------+
--| 18 | 8                 | 6                      | 16   | 0      |
--| 23 | 8                 | 11                     | 12   | 15     |
--| 36 | 8                 | 4                      | 8    | 20     |
--| 43 | 8                 | 1                      | 9    | 30     |
--| 53 | 8                 | 9                      | 15   | 20     |
--+----+-------------------+------------------------+------+--------+


SELECT id, name, phone_number, passport_number, license_plate FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28);
SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28);

--+--------+---------+----------------+-----------------+---------------+
--|   id   |  name   |  phone_number  | passport_number | license_plate |
--+--------+---------+----------------+-----------------+---------------+
--| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
--| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
--| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       | ---
--| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | ---
--| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | ---
--| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | ---
--+--------+---------+----------------+-----------------+---------------+

SELECT flight_id, passport_number, seat FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29) AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28))
SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29) AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28))
--Passengers who were at the bakery and made phone calls within the time frame who also took a flight out of Fiftyville the day after.

--+-----------+-----------------+------+
--| flight_id | passport_number | seat |
--+-----------+-----------------+------+
--| 18        | 3592750733      | 4C   |
--| 36        | 1695452385      | 3B   |
--| 36        | 5773159633      | 4A   |
--| 36        | 8294398571      | 6C   |
--+-----------+-----------------+------+

SELECT id, name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29) AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28)));

--+--------+--------+
--|   id   |  name  |
--+--------+--------+
--| 398010 | Sofia  |
--| 514354 | Diana  |
--| 560886 | Kelsey |
--| 686048 | Bruce  |
--+--------+--------+

SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street") AND person_id IN (SELECT id FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29) AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28))));

--ID of people who withdrew from the bank at the proper time and called in the bakery at the proper time and got on a flight from Fiftyville the next day.
--+-----------+
--| person_id |
--+-----------+
--| 686048    |
--| 514354    |
--+-----------+

SELECT id, name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street") AND person_id IN (SELECT id FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29) AND passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60)))));
--+--------+-------+
--|   id   | name  |
--+--------+-------+
--| 514354 | Diana |
--| 686048 | Bruce |
--+--------+-------+

SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28)
AND people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29))
AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25)
AND people.id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"));


--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | Flight ID = 36, dest = 4
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       | Flight ID = 18, 24, 54
--+--------+-------+----------------+-----------------+---------------+

--Finding flight ids for Bruce and Diana.
SELECT * FROM passengers WHERE passport_number = 5773159633;
SELECT * FROM passengers WHERE passport_number = 3592750733;

--Finding airport id's for where Bruce and Diana each flew to. Diana flew back to FiftyVille so it cant be her.
SELECT * FROM flights WHERE id IN (18, 24, 54, 36) AND origin_airport_id = 8;

--Finding the name of the airport Bruce flew to.
SELECT * FROM airports WHERE id = 4;

--Finding the phone number of who bruce called on that day
SELECT * FROM phone_calls WHERE caller = "(367) 555-5533" AND year = 2021 AND month = 7 AND day = 28;

--Finding the name of the person Bruce called on that day
SELECT * FROM people WHERE phone_number = "(375) 555-8161";