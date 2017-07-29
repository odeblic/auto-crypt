from socket import *

from enum import Enum

class Status(Enum):
    SERVER_INIT
    CLIENT_INIT
    INIT
    ONLINE
    OFFLINE
    NEGO
    SYNC
    SAFE

class MessageType(Enum):
    DATA
    CLEAR
    HEARTBEAT
    KEY
    ALGO
    SEQ_NUM


class Message(object):
    def __init__(self):
        self.__protocol = None
        self.__version = None
        self.__message_type = None
        self.__sequence_number = None
        self.__content = None


class AutoCrypt(object):
    def __init__(self, port, host = None):
        self.__port = port
        self.__host = host
        self.__socket = socket(AF_INET, SOCK_DGRAM)
        if host is None:
            self.__socket.bind(('', port))

    def send(self, msg):
        addr = ("127.0.0.1", self.__port)
        self.__socket.sendto(msg, addr)

    def receive(self):
        return 0

    def get_status(self):
        return 0

    def kill(self):
        self.__socket.close()
