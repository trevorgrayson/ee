upload:
	@test -n "$$WIFI_SSID" || (echo "WIFI_SSID is not set"; exit 1)
	@test -n "$$WIFI_PASS" || (echo "WIFI_PASS is not set"; exit 1)
	pio run -t upload
html: src/webapp.h
	#pio run -t uploadfs

src/webapp.h:
	xxd -i spa.html > src/webapp.h
