#!/bin/bash
# This script will download the Solr Docker image, start the container, and post the data to Solr

# Note: Run this script from the 'Data' directory where the data files are located

# Stop and remove the Solr container if it already exists
docker stop solr
docker rm solr

# Start the Solr container with the required options
docker run -p 8983:8983 --name solr -v "${PWD}":/data -d solr:9.3

# Create the Solr collection
docker exec solr bin/solr create_core -c arquivo

# Try posting sample data to Solr
docker exec solr bin/post -c arquivo ../../data/sample.json

# If the sample data was posted successfully, delete it
docker exec solr bin/solr delete -c arquivo

# Upload schema.json to core books
curl -X POST -H 'Content-type:application/json' \
--data-binary "@schema.json" \
http://localhost:8983/solr/arquivo/schema

# reload core
curl "http://localhost:8983/solr/admin/cores?action=RELOAD&core=arquivo"

# Post the data to Solr using the 'docker exec' command
docker exec solr bin/post -c books ../../data/*.json