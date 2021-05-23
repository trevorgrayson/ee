import logging
import os
import hashlib
from flask import Flask 

from afirmatron import File 
from afirmatron.version import should_update
from afirmatron import api as afirm

logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

app = Flask(__name__)
app.register_blueprint(afirm.routes, url_prefix='/things')

@app.route('/')
def welcome():
    return 'Engage the Afirmatron'

