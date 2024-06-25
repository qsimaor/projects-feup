.mode columns
.headers on
.nullvalue NULL

SELECT name, COUNT(CASE WHEN NOT isAvailable THEN 1 END) * 100 / COUNT(roomNumber) as RoomOcupationPercentage
FROM Hotel LEFT JOIN HotelRoom
ON (name = hotelName)
GROUP BY name
ORDER BY RoomOcupationPercentage DESC;
