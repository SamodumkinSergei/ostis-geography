FROM ubuntu:focal
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Minsk
# install dependencies
COPY ./scripts/install_deps_ubuntu.sh /tmp/install_deps_ubuntu.sh
RUN apt-get update && \
    apt-get install -y --no-install-recommends sudo tzdata git && \
    /tmp/install_deps_ubuntu.sh

WORKDIR /ostis-geography
COPY . .
RUN cd /ostis-geography/scripts && ./install_project.sh --no_build_kb --no_build_sc_web

WORKDIR /ostis-geography/scripts

ENTRYPOINT ["bash", "/ostis-geography/scripts/docker_entrypoint.sh", "serve"]
