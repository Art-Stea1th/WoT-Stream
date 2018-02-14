def wsrLogInfo(message):
    wsrLog('INFO', message)

def wsfLogWarning(message):
    wsrLog('WARNING', message)

def wsrLogError(message):
    wsrLog('ERROR', message)

def wsrLogUnexpected(message):
    wsrLog('UNEXPECTED', message)

def wsrLog(level, message):
    if level and message:
        print getWSRLogSuffix() + level + ': ' + str(message)

def getWSRLogSuffix():
    return 'WSR-'