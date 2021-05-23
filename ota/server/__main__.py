from os import environ
from . import app

app.run(host='0.0.0.0', 
        port=5000, 
        # static_folder='static',
        debug=environ.get('ENV', 'development'))
