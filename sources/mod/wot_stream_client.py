from socket import socket
from warnings import warn

class ServerOk(object):             # ..0
    def __str__(self):
        return 'Server: Ok'
    def __int__(self):
        return 0

class ServerReadyToReceive(object): # ..1
    def __str__(self):
        return 'Server: Ready To Receive'
    def __int__(self):
        return 1

class ServerError(object):          # 255
    def __str__(self):
        return 'Server: Error'
    def __int__(self):
        return 255

class WoTStreamRemote(object):

    def __init__(self, address, port):
        self.__connected = False
        self.__address = address
        self.__port = port
        self.__sc = socket()
        self.__init_connect(address, port)    

    def __init_connect(self, address, port):
        try:
            self.__sc.connect((address, port))
            self.__connected = True
        except:
            self.__connected = False

    @property
    def Connected(self):
        return self.__connected

    def Initialize(self):
        self.__send_command(1)

    def StartStream(self, token):
        self.__send_command(2, token)

    def StopStream(self):
        self.__send_command(3)

    def Shutdown(self):
        self.__send_command(4)
        self.__sc.close()
        self.__sc.shutdown()

    def __send(self, command, data = None):
        if data:
            if self.__send_command(command) == ServerReadyToReceive():
                if self.__send_data(data) == ServerOk():
                    return
                else:
                    warn('server ready to receive, but data not accepted')
            else:
                warn('the command contains data but the server didn\'t ready to accept')
        else:
            self.__send_command(command)
        

    def __send_command(self, command):

        if command == None:
            raise ValueError('command must be a byte')

        cmd = str(int(command))[0]
        self.__sc.send(cmd)

        response = self.__decode_response(self.__sc.recv(1))
        if response != ServerOk() and response != ServerReadyToReceive():
            warn('the command execution didn\'t confirmed by the server')

        return response
        

    def __send_data(args, data):

        if data == None:
            raise ValueError('data string can\'t be \'None\' or empty')

        self.__sc.send(data)
        response = self.__decode_response(self.__sc.recv(1))
        if response != ServerOk():
            warn('the data receiving didn\'t confirmed by the server')

        return response

    def __decode_response(self, value):
        try:
            response = int(value)
            if response == 0:
                return ServerOk()
            elif response == 1:
                return ServerReadyToReceive()
            elif response == 255:
                return ServerError()
            raise
        except:
            return None

def test():

    wsr = WoTStreamRemote('127.0.0.1', 48684)    

    if wsr.Connected:

        wsr.Initialize()
        raw_input()

        wsr.StartStream('0123-4567-89AB-CDEF')
        raw_input()

        wsr.StopStream()
        raw_input()
    else:
        print 'WoTStream server unawailable'

    wsr.Shutdown()
    raw_input()

    

if __name__ == "__main__":
    test()