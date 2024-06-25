.mode columns
.headers on
.nullvalue NULL

SELECT c.ssn, c.name, d.hasValidVisa, d.hasNegativeCovidTest, d.hasVaccineCertificate
FROM Client as c LEFT JOIN Document as d
WHERE (c.documentId = d.id);

