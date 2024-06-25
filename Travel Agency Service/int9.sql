.mode columns
.headers on
.nullvalue NULL

SELECT name, count(roomNumber) as roomCount
FROM Hotel LEFT JOIN HotelRoom
ON (name = hotelName)
GROUP BY name;
