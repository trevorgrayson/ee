import os
from os import environ
import logging
import hashlib
import json
from flask import (
    Blueprint, request, Response, send_from_directory,
    make_response
)

from afirmatron import File 
from .binary import BIN_DIR

routes = Blueprint('afirmatron', __name__)
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

THINGS = {}


def device_name(request):
    return request.headers.get('X-Esp8266-Sta-Mac')


def md5sum(request):
    return  request.headers.get('X-Esp8266-Sketch-Md5')


@routes.route('/')
def index():
    return json.dumps(THINGS)


def should_update(dname, md5):
    return THINGS[dname] != md5
    

@routes.route('/update')
def update():
    dname = device_name(request)
    md5 = md5sum(request)

    THINGS[dname] = THINGS.get(dname)
    logger.info(request.headers)
    if should_update(dname, md5):
        try:
            binary = File.from_filename(dname)
            THINGS[dname] = binary.md5
            return make_response(send_from_directory(BIN_DIR, binary.filename),
                                 200, response_headers(binary))
        except FileNotFoundError:
            return 'Not Found.', 404

    return 'current', 304
    

@routes.route('/update/<string:dname>', methods=["POST"])
def upload(dname):
    octet = request.get_data()
    binary = File.save(dname, octet)
    THINGS[dname] = binary.md5
    return 'ok', 201


def response_headers(binary):
    filebody = open(BIN_DIR + "/" + binary.filename, 'rb').read()
    headers = {
        # 'HTTP 200 OK'
        'Content-Type': 'application/octet-stream',
        'Content-Disposition': 'attachment; filename={}'.format(binary.filename),
        'Content-Length': binary.length,
        'x-MD5': hashlib.md5(binary.octet).hexdigest()
    }
    logger.info(headers)
    return headers
