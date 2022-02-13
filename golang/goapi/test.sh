#!/bin/bash

echo GET /books
curl localhost:8080/books

echo POST /books
curl localhost:8080/books --include --header "Content-Type: applications/json" -d @body.json --request "POST"

echo GET /books/2
curl localhost:8080/books/2

echo GET /books/4
curl localhost:8080/books/5

echo PATCH /checkout
curl localhost:8080/checkout?id=1 --request "PATCH"

echo PATCH /checkout
curl localhost:8080/checkout?id=88 --request "PATCH"

echo PATCH /checkout
curl localhost:8080/checkout?id=1 --request "PATCH"

echo PATCH /checkout
curl localhost:8080/checkout?id=1 --request "PATCH"

echo PATCH /checkout
curl localhost:8080/checkout --request "PATCH"

echo PATCH /return
curl localhost:8080/return?id=1 --request "PATCH"

echo PATCH /return
curl localhost:8080/return?id=1 --request "PATCH"
