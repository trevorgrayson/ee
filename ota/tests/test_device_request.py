from pytest import fixture
from flask import Flask
from afirmatron.api import routes

app = Flask(__name__)
app.register_blueprint(routes)


HEADERS = {
    "User-Agent": "ESP8266-http-Update",
    "X-Esp8266-Chip-Id": "10771118",
    "X-Esp8266-Sta-Mac": "bob",
    "X-Esp8266-Ap-Mac": "5C:CF:7F:A4:5A:AE",
    "X-Esp8266-Free-Space": "647168",
    "X-Esp8266-Sketch-Size": "315296",
    "X-Esp8266-Sketch-Md5": "b672da7ee227ee83b364e410e6eea40d",
    "X-Esp8266-Chip-Size": "4194304",
    "X-Esp8266-Sdk-Version": "2.2.2-dev(38a443e)",
    "X-Esp8266-Mode": "sketch"
}


class TestDeviceRequests:
    @fixture
    def client(self):
        return app.test_client()

    def test_update_5C(self, client):
        response = client.get('/update', headers=HEADERS)
        assert 200 == response.status_code

    def test_update_original(self, client):
        HEADERS.update({"X-Esp8266-Sta-Mac": "a0:20:a6:27:0b:b2"})
        response = client.get('/update', headers=HEADERS)
        assert 200 == response.status_code
