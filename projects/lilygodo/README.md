# lilygodo

`lilygodo` is the first MVP for the LILYGO T5 4.7 inch e-paper board. It fetches the `doing` list from `http://txtin.gs/status` and renders it as a single readable dashboard.

## Architecture

- `src/main.cpp`: board bring-up, Wi-Fi connection, refresh loop, and display composition.
- `libs/TxtingStatus`: reusable HTTP + JSON client for the `txtin.gs/status` endpoint.
- `reference/lilygoepd47`: retained as the board baseline for the display library and known-good PlatformIO settings.

## Configuration

Build-time credentials are supplied through `platformio.ini`:

- `WIFI_SSID`
- `WIFI_PASSWORD`
- `STATUS_URL`

The defaults are empty for Wi-Fi credentials and `http://txtin.gs/status` for the endpoint. Override them with `build_flags` or an untracked `platformio.local.ini` include before flashing hardware.

Example `platformio.local.ini`:

```ini
[env:eink47]
build_flags =
    ${env:eink47.build_flags}
    '-DWIFI_SSID="your-ssid"'
    '-DWIFI_PASSWORD="your-password"'
```

You can also override the values directly in a local build invocation or use the tracked `eink47-local` environment in `platformio.ini`.

## MVP Boundaries

- Keep endpoint fetching and JSON parsing reusable in `libs/TxtingStatus`.
- Keep e-paper layout decisions project-local to `lilygodo`.
- Prefer a simple full-screen refresh loop before introducing partial refresh or sleep scheduling.
