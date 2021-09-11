from os import environ
from . import app

if __name__ == "__main__":
    app.run(host='0.0.0.0', 
            port=5000, 
            # static_folder='static',
            debug=environ.get('ENV', 'development'))
