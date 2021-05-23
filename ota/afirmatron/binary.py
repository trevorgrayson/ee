from os import environ
from hashlib import md5

BIN_DIR = environ.get('BIN_DIR', 'binaries')


def bin_path(device_name):
    return "{}/{}.bin".format(BIN_DIR, device_name)


class File:
    def __init__(self, **kwargs):
        self.filename = kwargs.get('filename')
        self.md5 = kwargs.get('md5')
        self.octet = kwargs.get('octet')
        self.length = kwargs.get('length')
    
    @classmethod
    def from_filename(cls, device_name=None, **kwargs):
        filebody = open(bin_path(device_name), 'rb').read()
        return File(
            filename=device_name + '.bin',
            md5=md5(filebody).hexdigest(),
            length=len(filebody),
            octet=filebody
        )

    @classmethod
    def save(cls, device_name, octet):
        with open(bin_path(device_name), 'wb') as fp:
            fp.write(octet)

        return cls.from_filename(device_name)
