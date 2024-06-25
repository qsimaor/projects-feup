PRAGMA foreign_keys = ON;
 
INSERT INTO Activity (name, specialOccasion, equipmentNeeded, skillNeeded, duration, specialDeal, cost)
VALUES
 	("Skiing", NULL, TRUE, TRUE, 120, 10, 25),
 	("Hiking", NULL, FALSE, FALSE, 120, NULL, 0),
 	("Beach", NULL, FALSE, FALSE, 180, NULL, 0),
 	("Wedding Ceremony", "Wedding", FALSE, FALSE, 300, NULL, 3500);
 	
INSERT INTO Document (hasValidVisa, hasNegativeCovidTest, hasVaccineCertificate)
VALUES
 	(TRUE, TRUE, TRUE),
 	(TRUE, TRUE, FALSE),
 	(TRUE, FALSE, TRUE),
 	(TRUE, FALSE, FALSE),
 	(FALSE, TRUE, TRUE),
 	(FALSE, TRUE, FALSE),
 	(FALSE, FALSE, TRUE),
 	(FALSE, FALSE, FALSE);
 	
INSERT INTO CountryRestrictions (country, validVisaNeeded, covidTestNeeded, vaccineCertificateNeeded)
VALUES
 	("Portugal", TRUE, TRUE, TRUE),
 	("Italy", TRUE, TRUE, FALSE),
 	("China", TRUE, FALSE, FALSE),
 	("Japan", FALSE, FALSE, FALSE);
 	
INSERT INTO Client (name, dob, address, countryOrigin, documentId)
VALUES
 	("Pedro Silva", NULL, "Rua António Mota n22", "Portugal", (SELECT id FROM Document WHERE (hasValidVisa = TRUE AND hasNegativeCovidTest = TRUE AND hasVaccineCertificate = FALSE))),
 	("John Doe", "12-05-2021", NULL, "England", (SELECT id FROM Document WHERE (hasValidVisa = TRUE AND hasNegativeCovidTest = FALSE AND hasVaccineCertificate = FALSE))),
 	("Jotaro Kujo", NULL, NULL, "Japan",(SELECT id FROM Document WHERE (hasValidVisa = TRUE AND hasNegativeCovidTest = FALSE AND hasVaccineCertificate = TRUE))),
 	("António Costa", NULL, NULL, "Portugal",(SELECT id FROM Document WHERE (hasValidVisa = TRUE AND hasNegativeCovidTest = TRUE AND hasVaccineCertificate = TRUE)));
 	
INSERT INTO Payment (cardNumber, paymentMethod, ssn)
VALUES
 	(25452594, "mbway", (SELECT ssn FROM Client WHERE (name = "Pedro Silva"))),
 	(25346256, "mastercard", (SELECT ssn FROM Client WHERE (name = "John Doe"))),
 	(87534462, "mastercard", (SELECT ssn FROM Client WHERE (name = "Jotaro Kujo"))),
 	(64257721, "mastercard", (SELECT ssn FROM Client WHERE (name = "António Costa")));
 	
INSERT INTO Disability (name, type, care)
VALUES
	("Shellfish Allergy", "Allergy", "Restaurants");
	
INSERT INTO ClientDisability (clientSsn, disabilityName)
VALUES
	((SELECT ssn FROM Client WHERE (name = "Pedro Silva")), "Shellfish Allergy");
	
INSERT INTO Hotel (name, location, starRating, disabilityFriendly, petFriendly, vehicleHire, hasSpa, hasBreakfast, hasGym)
VALUES
	("Five Seasons", "Italy", 4, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE),
	("Estrela Azul", "Portugal", 2, FALSE, TRUE, FALSE, FALSE, TRUE, FALSE),
	("Páoxiāo de shīzi jiǔdiàn", "China", 5, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE),
	("Minami no hoseki", "Japan", 4, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE);
	
INSERT INTO HotelRoom (roomNumber, hotelName, isAvailable, tripId, numOfBeds, type, pricePerNight)
VALUES
	(5, "Five Seasons", true, NULL, 2, "twin", 75),
	(6, "Five Seasons", true, NULL, 2, "twin", 75),
	(7, "Five Seasons", true, NULL, 2, "double", 125),
	(8, "Five Seasons", true, NULL, 2, "double", 125),
	(2, "Estrela Azul", true, NULL, 1, "single", 25),
	(16, "Estrela Azul", true, NULL, 1, "single", 25),
	(56, "Estrela Azul", true, NULL, 1, "single", 25),
	(17, "Estrela Azul", true, NULL, 2, "double", 45),
	(18, "Estrela Azul", true, NULL, 2, "double", 45),
	(687, "Páoxiāo de shīzi jiǔdiàn", true, NULL, 2, "president suite", 600),
	(788, "Páoxiāo de shīzi jiǔdiàn", true, NULL, 1, "president suite", 450),
	(1, "Minami no hoseki", true, NULL, 2, "double", 150),
	(2, "Minami no hoseki", true, NULL, 2, "double", 150),
	(11, "Minami no hoseki", true, NULL, 2, "king", 250);
	
INSERT INTO SeasonRestriction (activityId, restrictedSeason)
VALUES
	((SELECT id FROM Activity WHERE (name = "Skiing")), "summer"),
	((SELECT id FROM Activity WHERE (name = "Skiing")), "spring"),
	((SELECT id FROM Activity WHERE (name = "Hiking")), "winter"),
	((SELECT id FROM Activity WHERE (name = "Beach")), "winter"),
	((SELECT id FROM Activity WHERE (name = "Beach")), "fall");
	
INSERT INTO HotelActivities (activityId, hotelName, distance)
VALUES
	((SELECT id FROM Activity WHERE (name = "Beach")), "Five Seasons", 1),
	((SELECT id FROM Activity WHERE (name = "Skiing")), "Estrela Azul", 25),
	((SELECT id FROM Activity WHERE (name = "Hiking")), "Estrela Azul", 20),
	((SELECT id FROM Activity WHERE (name = "Skiing")), "Páoxiāo de shīzi jiǔdiàn", 5),
	((SELECT id FROM Activity WHERE (name = "Skiing")), "Minami no hoseki", 15),
	((SELECT id FROM Activity WHERE (name = "Hiking")), "Minami no hoseki", 10);
	
INSERT INTO Flight (leavingAirport, arrivingAirport, timeOfFlight, durationFlight, pricePerSeat, areServicesAvailable, numOfSeatsAvailable)
VALUES
	("Portugal", "China", "18-11-2021 16:30", 600, 250, TRUE, 90),
	("England", "Portugal", "06-07-2021 10:30", 120, 45, TRUE, 50),
	("England", "Italy", "23-06-2021 11:00", 150, 120, TRUE, 120),
	("Portugal", "Japan", "28-06-2021 13:00", 190, 160, FALSE, 130),
	("Japan", "Portugal", "30-06-2021 9:00", 540, 350, TRUE, 200);
	
INSERT INTO Trip (destination, clientSsn, budget, numberOfPeople, season, duration, totalCost)
VALUES
	("China", (SELECT ssn FROM Client WHERE (name = "Pedro Silva")), 15000, 2, "winter", 7, 0),
	("Portugal", (SELECT ssn FROM Client WHERE (name = "John Doe")),  5000, 1, "summer", 15, 0),
	("Japan", (SELECT ssn FROM Client WHERE (name = "António Costa")),  10000, 3, "summer", 10, 0),
	("Portugal", (SELECT ssn FROM Client WHERE (name = "Jotaro Kujo")),  8000, 2, "winter", 8, 0);
	
INSERT INTO ClientFlightSeat (tripId, flightNumber, seatNumber)
VALUES
	(1, 1, 15),
	(1, 1, 16),
	(2, 2, 75),
	(3, 4, 10),
	(3, 4, 11),
	(3, 4, 12),
	(4, 5, 80),
	(4, 5, 81),
	(4, 5, 82);
	
INSERT INTO ClientInterestedAndCapable (clientSsn, activityId, hasEquipment, isSkilled)
VALUES
	((SELECT ssn FROM Client WHERE (name = "Pedro Silva")), (SELECT id FROM Activity WHERE (name = "Skiing")), TRUE, TRUE),
	((SELECT ssn FROM Client WHERE (name = "John Doe")), (SELECT id FROM Activity WHERE (name = "Hiking")), FALSE, FALSE),
	((SELECT ssn FROM Client WHERE (name = "Jotaro Kujo")), (SELECT id FROM Activity WHERE (name = "Hiking")), FALSE, FALSE),
	((SELECT ssn FROM Client WHERE (name = "António Costa")), (SELECT id FROM Activity WHERE (name = "Skiing")), TRUE, TRUE);
	
INSERT INTO TripBookedActivities (activityId, tripId)
VALUES
	((SELECT id FROM Activity WHERE (name = "Skiing")), 1),
	((SELECT id FROM Activity WHERE (name = "Hiking")), 2),
	((SELECT id FROM Activity WHERE (name = "Skiing")), 3),
	((SELECT id FROM Activity WHERE (name = "Beach")), 4);
	
UPDATE HotelRoom
SET tripId = 1, isAvailable = FALSE
WHERE roomNumber = 687 AND hotelName = "Páoxiāo de shīzi jiǔdiàn";

UPDATE HotelRoom
SET tripId = 2, isAvailable = FALSE
WHERE roomNumber = 56 AND hotelName = "Estrela Azul";

UPDATE HotelRoom
SET tripId = 3, isAvailable = FALSE
WHERE roomNumber = 2 AND hotelName = "Minami no hoseki";

UPDATE HotelRoom
SET tripId = 3, isAvailable = FALSE
WHERE roomNumber = 11 AND hotelName = "Minami no hoseki";

UPDATE HotelRoom
SET tripId = 4, isAvailable = FALSE
WHERE roomNumber = 18 AND hotelName = "Estrela Azul";
