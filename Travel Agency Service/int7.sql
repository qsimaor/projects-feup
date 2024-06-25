.mode columns
.headers on
.nullvalue NULL

SELECT name, max(budget) as budget
FROM Trip LEFT JOIN Client
ON ssn = clientSsn;
