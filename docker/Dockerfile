FROM debian:stretch
LABEL maintainer="PAC Developers <devs@paccoin.org>"
LABEL description="Dockerised PaccoinCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
