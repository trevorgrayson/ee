////
//// Created by trevor on 1/30/26.
////
//#include <ESP8266WebServer.h>
//
//ESP8266WebServer server(80);
//
//void handlePost() {
//    server.send(200, "text/plain", "OK");
//}
//
//void handleBody() {
//    HTTPUpload& upload = server.upload();
//
//    if (upload.status == UPLOAD_FILE_START) {
//        Serial.println("Body start");
//    }
//    else if (upload.status == UPLOAD_FILE_WRITE) {
//        Serial.write(upload.buf, upload.currentSize);  // stream chunk
//    }
//    else if (upload.status == UPLOAD_FILE_END) {
//        Serial.println("\nBody end");
//    }
//}
//
//void setup() {
//    Serial.begin(115200);
//
//    server.on("/print", HTTP_POST, handlePost, handleBody);
//    server.begin();
//}
//
//void loop() {
//    server.handleClient();
//}
