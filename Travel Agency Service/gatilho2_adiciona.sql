CREATE TRIGGER countryRestrictionsChanged
After UPDATE OF validVisaNeeded, covidTestNeeded, vaccineCertificateNeeded ON CountryRestrictions
FOR Each ROW
Begin
DELETE FROM Trip
WHERE destination = New.country AND clientSsn IN (SELECT ssn FROM Client WHERE documentId IN 
(SELECT id FROM Document WHERE ((hasValidVisa = FALSE AND New.validVisaNeeded = TRUE) OR (hasNegativeCovidTest = FALSE AND New.covidTestNeeded = TRUE) OR (hasVaccineCertificate = FALSE AND New.vaccineCertificateNeeded = TRUE))));
END;
