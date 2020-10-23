# First Image

FROM golang:alpine AS builder

WORKDIR /go/src/app

COPY webserver.go .

RUN go build -o webserver .

# New Image

FROM alpine

WORKDIR /app

COPY --from=builder /go/src/app/ /app/

CMD ["./webserver"]
