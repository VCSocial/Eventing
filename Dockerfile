FROM ubuntu:18.04

# Get depedencies
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y clang gcc software-properties-common \
  && apt-get -y install make libsystemd-dev

# Add cirterion repository, and install
RUN add-apt-repository ppa:snaipewastaken/ppa -y
RUN apt-get update && apt-get install -y criterion
