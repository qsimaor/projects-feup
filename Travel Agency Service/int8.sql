.mode columns
.headers on
.nullvalue NULL

SELECT Activity.name, sum(numberOfPeople) * cost as totalProfit
FROM (TripBookedActivities LEFT JOIN Trip ON (tripId = Trip.id)) LEFT JOIN Activity
ON (activityId = Activity.id)
GROUP BY Activity.name;
