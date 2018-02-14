import atexit
import subprocess
from os import path
from socket import socket

from wot_stream_log import *

class Protocol(object): # I Want Enums

    def __init__(self):

        # ordinary responses
        self.__ok = 'ok'
        self.__bp = 'bp'
        self.__er = 'er'
        self.__uw = 'uw'

        # 'stat' responses
        self.__ntin = 'ntin'
        self.__stpd = 'stpd'
        self.__busy = 'busy'
        self.__srtd = 'srtd'

    # ordinary responses

    @property
    def ok(self):
        return self.__ok

    @property
    def badOperation(self):
        return self.__bp

    @property
    def error(self):
        return self.__er

    @property
    def unawailable(self):
        return self.__uw

    # 'stat' responses

    @property
    def notInitialized(self):
        return self.__ntin

    @property
    def started(self):
        return self.__srtd

    @property
    def busy(self):
        return self.__busy

    @property
    def stopped(self):
        return self.__stpd
    

class WoTStreamRemote(object):

    def __init__(self, address, port):
        self.__proto = Protocol()
        self.__address = address
        self.__port = port
        self.__sc = None
        self.__wsr = None
        self.connect()
        self.initialize()

    @property
    def proto(self):
        return self.__proto

    def connect(self):
        if self.__connect() == self.proto.unawailable:
            if self.__startWoTStream() == self.proto.unawailable:
                return self.proto.unawailable
            return self.__connect()
        return self.proto.ok
    
    def getState(self):
        return self.__safeRemoteExec('stat', 4)

    def initialize(self):
        return self.__safeRemoteExec('init')

    def updateToken(self, token):
        return self.__safeRemoteExec('updt: ' + token)

    def startStream(self):
        return self.__safeRemoteExec('srts')

    def stopStream(self):
        return self.__safeRemoteExec('stps')    

    def __safeRemoteExec(self, command, response_length=2):
        try:
            return self.__send(command, response_length)
        except:
            return self.__proto.unawailable

    def __send(self, command, response_length):
        self.__sc.send(command)
        return self.__sc.recv(response_length)

    def __connect(self):
        wsrLogInfo('try connect to wot_stream')
        try:
            self.__sc = socket()
            self.__sc.connect((self.__address, self.__port))
            wsrLogInfo('connection successful')
            return self.proto.ok
        except:
            wsrLogError("can't connect to wot_stream")
        return self.proto.unawailable

    def __startWoTStream(self):
        wsrLogInfo('try start wot_stream')
        if self.getState() == self.proto.unawailable:
            wsr_path = path.abspath(path.join(__file__,  r'../../../../../wot_stream/'))
            full_name = wsr_path + r'\wot_stream.exe'
            sinfo = subprocess.STARTUPINFO()
            sinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
            try:
                wsr = subprocess.Popen(full_name, cwd=wsr_path, startupinfo=sinfo)
                atexit.register(wsr.kill)
                wsrLogInfo('wot_stream started')
            except:
                wsrLogError("can't start wot_stream")
                return self.proto.unawailable
        else:
            wsrLogInfo('wot_stream already started')
        return self.proto.ok