.mode columns
.headers on
.nullvalue NULL

SELECT r1.*
FROM HotelRoom r1 LEFT JOIN HotelRoom r2
ON r1.pricePerNight > r2.pricePerNight AND r1.hotelName = r2.hotelName
WHERE r2.roomNumber IS NULL;
