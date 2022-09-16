import argparse

from sc_kpm import ScServer

from modules.lakes_module.LakesModule import LakesModule

SC_SERVER_HOST = "host"
SC_SERVER_PORT = "port"

SC_SERVER_HOST_DEFAULT = "localhost"
SC_SERVER_PORT_DEFAULT = "8090"


def main(args: dict):
    server = ScServer()
    server.connect(f"ws://{args[SC_SERVER_HOST]}:{args[SC_SERVER_PORT]}")

    server.add_modules(LakesModule())


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--host', type=str, dest=SC_SERVER_HOST, default=SC_SERVER_HOST_DEFAULT, help="Sc-server host")
    parser.add_argument(
        '--port', type=int, dest=SC_SERVER_PORT, default=SC_SERVER_PORT_DEFAULT, help="Sc-server port")
    args = parser.parse_args()

    main(vars(args))
