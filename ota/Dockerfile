FROM python:3.8-slim-buster

WORKDIR /app

ENV BIN_DIR=/app/binaries
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

COPY . .

CMD [ "gunicorn", "-w", "1", "--bind", "0.0.0.0:8000", "app:app"]
