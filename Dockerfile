FROM ubuntu:18.04

# Get depedencies
RUN apt-get update && apt-get upgrade -y
RUN apt-get install clang gcc software-properties-common -y
RUN add-apt-repository ppa:snaipewastaken/ppa -y
RUN apt-get update && apt-get install criterion -y
