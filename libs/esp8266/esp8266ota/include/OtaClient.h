#pragma once

#include <Arduino.h>

class OtaClient {
public:
    OtaClient(const String& server,
              const String& firmwareName,
              const String& currentVersion);

    void begin();
    void checkForUpdate();

private:
    String _server;
    String _firmwareName;
    String _currentVersion;

    String buildCheckUrl();
    bool performUpdate(const String& binUrl);
};
