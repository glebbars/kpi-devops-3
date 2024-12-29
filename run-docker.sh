#!/bin/bash

# Variables
IMAGE_NAME="http-server-trigonometry"

docker build --no-cache -t $IMAGE_NAME .
docker run -d --name trigonometry-backend -p 8081:8081 $IMAGE_NAME
