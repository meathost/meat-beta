FROM debian:buster-slim

RUN apt-get update

RUN apt-get install build-essential libfcgi-dev libmysqlclient-dev

RUN ./mypsswd.sh

RUN make

