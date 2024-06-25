.mode columns
.headers on
.nullvalue NULL

SELECT t.id, hr.pricePerNight * t.duration + a.cost + f.pricePerSeat * t.numberOfPeople as totalCost
FROM Trip as t
LEFT JOIN HotelRoom as hr
ON t.id = hr.tripId
LEFT JOIN TripBookedActivities as tba
ON t.id = tba.tripId
LEFT JOIN Activity as a
ON a.id = tba.activityId
LEFT JOIN ClientFlightSeat as cfs
ON t.id = cfs.tripId
LEFT JOIN Flight as f
ON cfs.flightNumber = f.flightNumber
GROUP BY t.id;
