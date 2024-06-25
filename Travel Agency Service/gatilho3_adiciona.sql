CREATE TRIGGER activityCanBeDoneInSeason
BEFORE INSERT ON TripBookedActivities
FOR EACH ROW 
WHEN (SELECT season FROM Trip WHERE id = New.tripId) IN (SELECT restrictedSeason FROM SeasonRestriction WHERE SeasonRestriction.activityId = New.activityId)
BEGIN
SELECT raise(ignore);
END;
