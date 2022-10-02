-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT *
  FROM crime_scene_reports
 WHERE month = 7
       AND day = 28; -- Search crime reports on
--July 28th CRIME AT 10:15am


SELECT *
  FROM interviews
 WHERE day = 28
       AND month = 7
       AND transcript LIKE '%bakery%'; -- 3 Interviews, left in a car, was on the phone for less then 60secs
--went to ATM in legget street earlier. First flight next day


SELECT *
  FROM phone_calls
 WHERE day = 28
       AND month = 7
       AND duration < 60;
--Calls with less than 60sec duration on July 28th


SELECT *
  FROM people
       JOIN phone_calls
       ON phone_calls.caller = people.phone_number
          AND day = 28
          AND month = 7
          AND duration < 60;
--List of People who made a phone call who lasted less than 60sec


SELECT *
  FROM bakery_security_logs
       JOIN people
       ON bakery_security_logs.license_plate = people.license_plate
 WHERE day = 28
       AND month = 7
       AND hour = 10
       AND minute BETWEEN 15
       AND 25;
--List of people who left the bakery in a 10min timeframe after the theft


SELECT *
  FROM people
       JOIN bank_accounts
       ON bank_accounts.person_id = people.id
       JOIN atm_transactions
       ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.day = 28
   AND atm_transactions.month = 7
   AND atm_transactions.transaction_type = 'withdraw'
   AND atm_transactions.atm_location LIKE '%Legget%Street%';
--List of people who withdrew money on ATM on July 28th at Legget Street.


SELECT people.name
  FROM bakery_security_logs
       JOIN people
       ON bakery_security_logs.license_plate = people.license_plate
       AND day = 28
       AND month = 7
       AND hour = 10
       AND minute BETWEEN 15 AND 25
 WHERE people.name =
       (SELECT name
          FROM people
               JOIN bank_accounts
               ON bank_accounts.person_id = people.id
               JOIN atm_transactions
               ON atm_transactions.account_number = bank_accounts.account_number
         WHERE atm_transactions.day = 28
           AND atm_transactions.month = 7
           AND atm_transactions.transaction_type = 'withdraw'
           AND atm_transactions.atm_location LIKE '%Legget%Street%');
--Cross reference between who withdrew money on Legget Street
--and who left the bakery between 10h15 and 10h25
--Shows Bruce as result


SELECT name
  FROM people
       JOIN phone_calls
       ON phone_calls.receiver = people.phone_number
          AND day = 28
          AND month = 7
          AND duration < 60
 WHERE phone_calls.caller =
       (SELECT phone_number
          FROM people
         WHERE name = 'Bruce');
--Who did Bruce called? Assuming he was the caller
--Called Robin


SELECT city, hour, minute
  FROM airports
       JOIN flights
       ON airports.id = flights.destination_airport_id
          AND day = 29
          AND month = 7
       WHERE (SELECT destination_airport_id
             FROM flights
                  JOIN airports
                  ON airports.id = flights.origin_airport_id
            WHERE airports.city = 'Fiftyville')
 ORDER BY hour, minute;
--Check Flights on the 29th, from Fiftyville first flight out is to New York at 8h:20;


SELECT name,
       flights.destination_airport_id,
       airports.city,
       flights.hour, flights.minute
  FROM people
       JOIN passengers
       ON people.passport_number = passengers.passport_number
       JOIN flights
       ON passengers.flight_id = flights.id
       JOIN airports
       ON airports.id = flights.destination_airport_id
          AND flights.day = 29
          AND flights.month = 7
          AND name = 'Bruce'
 WHERE flights.origin_airport_id =
       (SELECT id
          FROM airports
         WHERE city = 'Fiftyville')
ORDER BY hour, minute;
--Shows that Bruce got on the first flight out of Fiftyville with New York as destination


SELECT people.name AS thief,
       (SELECT name
          FROM people
          JOIN phone_calls
          ON phone_calls.receiver = people.phone_number
             AND day = 28
             AND month = 7
             AND duration < 60
         WHERE phone_calls.caller =
               (SELECT phone_number
                  FROM people
                 WHERE name =
                       (SELECT people.name
                          FROM bakery_security_logs
                               JOIN people
                               ON bakery_security_logs.license_plate = people.license_plate
                                  AND day = 28
                                  AND month = 7
                                  AND hour = 10
                                  AND minute BETWEEN 15 AND 25
                          WHERE people.name =
                                (SELECT name
                                   FROM people
                                        JOIN bank_accounts
                                        ON bank_accounts.person_id = people.id
                                        JOIN atm_transactions
                                        ON atm_transactions.account_number = bank_accounts.account_number
                                  WHERE atm_transactions.day = 28
                                    AND atm_transactions.month = 7
                                    AND atm_transactions.transaction_type = 'withdraw'
                                    AND atm_transactions.atm_location LIKE '%Legget%Street%')))) AS accomplice,
         (SELECT airports.city
            FROM people
            JOIN passengers
            ON people.passport_number = passengers.passport_number
            JOIN flights
            ON passengers.flight_id = flights.id
            JOIN airports
            ON airports.id = flights.destination_airport_id
               AND flights.day = 29
               AND flights.month = 7
               AND name =
                   (SELECT people.name
                          FROM bakery_security_logs
                               JOIN people
                               ON bakery_security_logs.license_plate = people.license_plate
                                  AND day = 28
                                  AND month = 7
                                  AND hour = 10
                                  AND minute BETWEEN 15 AND 25
                          WHERE people.name =
                                (SELECT name
                                   FROM people
                                        JOIN bank_accounts
                                        ON bank_accounts.person_id = people.id
                                        JOIN atm_transactions
                                        ON atm_transactions.account_number = bank_accounts.account_number
                                  WHERE atm_transactions.day = 28
                                    AND atm_transactions.month = 7
                                    AND atm_transactions.transaction_type = 'withdraw'
                                    AND atm_transactions.atm_location LIKE '%Legget%Street%'))
           WHERE flights.origin_airport_id =
                 (SELECT id
                    FROM airports
                   WHERE city = 'Fiftyville')
            ORDER BY hour, minute) AS destination
  FROM bakery_security_logs
       JOIN people
       ON bakery_security_logs.license_plate = people.license_plate
       AND day = 28
       AND month = 7
       AND hour = 10
       AND minute BETWEEN 15 AND 25
 WHERE people.name =
       (SELECT name
          FROM people
               JOIN bank_accounts
               ON bank_accounts.person_id = people.id
               JOIN atm_transactions
               ON atm_transactions.account_number = bank_accounts.account_number
         WHERE atm_transactions.day = 28
           AND atm_transactions.month = 7
           AND atm_transactions.transaction_type = 'withdraw'
           AND atm_transactions.atm_location LIKE '%Legget%Street%');
--Nested queries where it show a table with thief, accomplice and destination