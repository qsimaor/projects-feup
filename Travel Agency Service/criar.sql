DROP TABLE IF EXISTS Client;
DROP TABLE IF EXISTS Trip;
DROP TABLE IF EXISTS Document;
DROP TABLE IF EXISTS CountryRestrictions;
DROP TABLE IF EXISTS Payment;
DROP TABLE IF EXISTS Disability;
DROP TABLE IF EXISTS Flight;
DROP TABLE IF EXISTS Hotel;
DROP TABLE IF EXISTS HotelRoom;
DROP TABLE IF EXISTS Activity;
DROP TABLE IF EXISTS ClientFlightSeat;
DROP TABLE IF EXISTS SeasonRestriction;
DROP TABLE IF EXISTS ClientDisability;
DROP TABLE IF EXISTS TripBookedActivities;
DROP TABLE IF EXISTS HotelActivities;
DROP TABLE IF EXISTS ClientInterestedAndCapable;

CREATE TABLE Activity (
	id INTEGER PRIMARY KEY,
	name VARCHAR(32) NOT NULL,
	specialOccasion VARCHAR(32),
	equipmentNeeded BOOLEAN NOT NULL,
	skillNeeded BOOLEAN NOT NULL,
	duration INTEGER NOT NULL,
	specialDeal INTEGER DEFAULT NULL,
	cost INTEGER NOT NULL CHECK (cost >= 0)
);

CREATE TABLE Document (
	id INTEGER PRIMARY KEY,
	hasValidVisa BOOLEAN NOT NULL,
	hasNegativeCovidTest BOOLEAN NOT NULL,
	hasVaccineCertificate BOOLEAN NOT NULL
);

CREATE TABLE CountryRestrictions (
	country VARCHAR(32) PRIMARY KEY,
	validVisaNeeded BOOLEAN NOT NULL,
	covidTestNeeded BOOLEAN NOT NULL,
	vaccineCertificateNeeded BOOLEAN NOT NULL
);

CREATE TABLE Trip (
	id INTEGER PRIMARY KEY,
	destination REFERENCES CountryRestrictions(country) ON DELETE SET NULL ON UPDATE CASCADE,
	clientSsn REFERENCES Client(ssn) ON DELETE CASCADE ON UPDATE CASCADE,
	budget INTEGER NOT NULL CONSTRAINT minimumBudget CHECK(budget>=0),
	numberOfPeople INTEGER NOT NULL CONSTRAINT minimumPeople CHECK(numberOfPeople>= 1),
	season	VARCHAR(6),
	duration INTEGER NOT NULL CONSTRAINT minimumTripDuration CHECK(duration>= 1),
	totalCost INTEGER DEFAULT 0 CONSTRAINT minimumTotalCost CHECK(totalCost>= 0)
);

CREATE TABLE Client (
	ssn INTEGER PRIMARY KEY,
	name VARCHAR(64) NOT NULL UNIQUE,
	dob DATE,
	address VARCHAR(255),
	countryOrigin VARCHAR(30) NOT NULL,
	documentId REFERENCES Document(id) ON DELETE SET NULL ON UPDATE CASCADE
);

CREATE TABLE Payment (
	cardNumber INTEGER PRIMARY KEY,
	paymentMethod VARCHAR(16) NOT NULL,
	ssn REFERENCES Client(ssn) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL
);

CREATE TABLE Disability (
	name VARCHAR(64) PRIMARY KEY,
	type VARCHAR(16) NOT NULL,
	care VARCHAR(16) NOT NULL
);

CREATE TABLE Flight (
	flightNumber INTEGER PRIMARY KEY,
	leavingAirport VARCHAR(128) NOT NULL,
	arrivingAirport VARCHAR(128) NOT NULL,
	timeOfFlight TIME NOT NULL,
	durationFlight INTEGER NOT NULL CONSTRAINT minimumFlightDuration CHECK (durationFlight>= 1),
	pricePerSeat INTEGER NOT NULL CONSTRAINT minimumSeatPrice CHECK (pricePerSeat>= 1),
	areServicesAvailable BOOLEAN NOT NULL,
	numOfSeatsAvailable INTEGER NOT NULL CONSTRAINT minimumNumOfSeatsAvailable CHECK (numOfSeatsAvailable >= 0)
);

CREATE TABLE Hotel (
	name VARCHAR(128) PRIMARY KEY,
	location VARCHAR(32) NOT NULL,
	starRating INTEGER NOT NULL CONSTRAINT starRatingRange CHECK (starRating>=1 AND starRating <= 5),
	disabilityFriendly BOOLEAN NOT NULL,
	petFriendly BOOLEAN NOT NULL,
	vehicleHire BOOLEAN NOT NULL,
	hasSpa BOOLEAN NOT NULL,
	hasBreakfast BOOLEAN NOT NULL,
	hasGym BOOLEAN NOT NULL
);

CREATE TABLE HotelRoom (
	roomNumber INTEGER NOT NULL,
	hotelName REFERENCES Hotel(name) ON DELETE CASCADE ON UPDATE CASCADE,
	isAvailable BOOLEAN NOT NULL DEFAULT TRUE,
	tripId REFERENCES Trip(id) ON DELETE SET NULL ON UPDATE CASCADE,
	numOfBeds INTEGER NOT NULL,
	type INTEGER NOT NULL,
	pricePerNight INTEGER NOT NULL,
	PRIMARY KEY (roomNumber, hotelName)
);

CREATE TABLE ClientFlightSeat (
	tripId REFERENCES Trip(id) ON DELETE CASCADE ON UPDATE CASCADE,
	flightNumber REFERENCES Flight(flightNumber) ON DELETE CASCADE ON UPDATE CASCADE,
	seatNumber INTEGER NOT NULL,
	PRIMARY KEY (flightNumber, seatNumber)
);

CREATE TABLE SeasonRestriction (
	activityId REFERENCES Activity(id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	restrictedSeason VARCHAR(6) NOT NULL
);

CREATE TABLE ClientDisability (
	clientSsn REFERENCES Client(ssn) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	disabilityName REFERENCES Disability(name) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	PRIMARY KEY (clientSsn, disabilityName)
);

CREATE TABLE TripBookedActivities (
	activityId REFERENCES Activity(id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	tripId REFERENCES Trip(id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	PRIMARY KEY (activityId, tripId)
);

CREATE TABLE HotelActivities (
	activityId REFERENCES Activity(id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	hotelName REFERENCES Hotel(name) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	distance INTEGER NOT NULL,
	PRIMARY KEY (activityId, hotelName)
);

CREATE TABLE ClientInterestedAndCapable (
	clientSsn REFERENCES Client(ssn) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	activityId REFERENCES Activity(id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	hasEquipment BOOLEAN NOT NULL,
	isSkilled BOOLEAN NOT NULL,
	PRIMARY KEY (clientSsn, activityId)
);
