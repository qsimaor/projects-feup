.mode columns
.headers on
.nullvalue NULL

SELECT count(CASE WHEN validVisaNeeded THEN 1 END) as numOfCountriesThatRequireVisa, count(CASE WHEN covidTestNeeded THEN 1 END) as numOfCountriesThatRequireCovidTest, count(CASE WHEN vaccineCertificateNeeded THEN 1 END) as numOfCountriesThatRequireVaccineCertificate
FROM CountryRestrictions;
