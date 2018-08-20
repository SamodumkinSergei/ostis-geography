FROM ubuntu:focal as base
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Moscow
# install dependencies
COPY ./scripts/install_deps_ubuntu.sh /tmp/install_deps_ubuntu.sh
RUN apt-get update && \
    apt-get install -y --no-install-recommends sudo tzdata git && \
    /tmp/install_deps_ubuntu.sh

WORKDIR /ostis-geography
COPY . .
RUN cd /ostis-geography/scripts && ./install_project.sh --no_build_kb --no_build_sc_web


# COPY /ostis-geography/problem-solver/cxx/sc-machine/scripts /ostis-geography/problem-solver/cxx/sc-machine/scripts
# COPY /ostis-geography/problem-solver/cxx/sc-machine/requirements.txt /ostis-geography/problem-solver/cxx/sc-machine/requirements.txt
# RUN /ostis-geography/problem-solver/cxx/sc-machine/scripts/install_deps_ubuntu.sh && apt-get install -y --no-install-recommends tini

# COPY /ostis-geography/bin /ostis-geography/bin
# COPY /ostis-geography/scripts /ostis-geography/scripts
# COPY /ostis-geography/ostis-geography.ini /ostis-geography/ostis-geography.ini

# COPY /ostis-geography/scripts/docker_entrypoint.sh /ostis-geography/scripts/docker_entrypoint.sh
WORKDIR /ostis-geography/scripts

ENTRYPOINT ["bash", "/ostis-geography/scripts/docker_entrypoint.sh", "serve"]
