FROM ubuntu:focal as base
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Minsk
# install dependencies
COPY ./scripts /tmp/scripts
COPY ./problem-solver/cxx/sc-machine/scripts /tmp/problem-solver/cxx/sc-machine/scripts
COPY ./problem-solver/cxx/sc-machine/requirements.txt /tmp/problem-solver/cxx/sc-machine/requirements.txt
RUN apt-get update && \
    apt-get install -y --no-install-recommends sudo ccache tini tzdata && \
    /tmp/scripts/install_problem_solver_deps.sh

FROM base as builder
ENV CCACHE_DIR=/ccache

RUN apt-get install -y --no-install-recommends git && \
    /tmp/scripts/install_problem_solver_deps.sh --dev

COPY . /ostis-geography
WORKDIR /ostis-geography/scripts
RUN --mount=type=cache,target=/ccache/ ./build_problem_solver.sh -r

FROM base as final
COPY --from=builder /ostis-geography/problem-solver/cxx/sc-machine/scripts /ostis-geography/problem-solver/cxx/sc-machine/scripts
COPY --from=builder /ostis-geography/problem-solver/cxx/sc-machine/requirements.txt /ostis-geography/problem-solver/cxx/sc-machine/requirements.txt

COPY --from=builder /ostis-geography/bin /ostis-geography/bin
COPY --from=builder /ostis-geography/scripts /ostis-geography/scripts
COPY --from=builder /ostis-geography/ostis-geography.ini /ostis-geography/ostis-geography.ini

COPY --from=builder /ostis-geography/interface /ostis-geography/interface
COPY --from=builder /ostis-geography/ostis-osm /ostis-geography/ostis-osm

WORKDIR /nika/scripts
ENTRYPOINT ["/usr/bin/tini", "--", "/ostis-geography/problem-solver/cxx/sc-machine/scripts/docker_entrypoint.sh"]
