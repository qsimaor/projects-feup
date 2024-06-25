CREATE TRIGGER hotelRoomChosen
After UPDATE Of tripId on HotelRoom
FOR Each ROW
Begin
UPDATE Trip
SET totalCost = totalCost + New.pricePerNight * duration
WHERE id = New.tripId;
UPDATE Trip
SET totalCost = totalCost - New.pricePerNight * duration
WHERE id = Old.tripId;
END;
