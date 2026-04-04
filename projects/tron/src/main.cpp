#include <FastLED.h>

#define DATA_PIN 23

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)

#define P1_UP_PIN 16
#define P1_DOWN_PIN 17
#define P1_LEFT_PIN 18
#define P1_RIGHT_PIN 19

#define P2_UP_PIN 21
#define P2_DOWN_PIN 22
#define P2_LEFT_PIN 25
#define P2_RIGHT_PIN 26

static CRGB leds[NUM_LEDS];
static uint8_t occupancy[NUM_LEDS]; // 0 = empty, 1 = P1, 2 = P2

enum Dir : uint8_t { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

struct Player {
    uint8_t x;
    uint8_t y;
    Dir dir;
    CRGB color;
    bool alive;
};

static Player p1;
static Player p2;

static const uint16_t TICK_MS = 120;
static uint32_t lastTick = 0;

static uint16_t XY(uint8_t x, uint8_t y) {
    // Serpentine wiring by columns: each column is 8 pixels tall.
    // Column 0 goes top->bottom, column 1 goes bottom->top, etc.
    if (x % 2 == 0) {
        return (x * MATRIX_HEIGHT) + y;
    }
    return (x * MATRIX_HEIGHT) + (MATRIX_HEIGHT - 1 - y);
}

static bool isOpposite(Dir a, Dir b) {
    return (a == DIR_UP && b == DIR_DOWN) ||
           (a == DIR_DOWN && b == DIR_UP) ||
           (a == DIR_LEFT && b == DIR_RIGHT) ||
           (a == DIR_RIGHT && b == DIR_LEFT);
}

static void clearBoard() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
        occupancy[i] = 0;
    }
    FastLED.show();
}

static void setPlayerStart(Player &p, uint8_t x, uint8_t y, Dir d, const CRGB &c, uint8_t id) {
    p.x = x;
    p.y = y;
    p.dir = d;
    p.color = c;
    p.alive = true;
    uint16_t idx = XY(x, y);
    occupancy[idx] = id;
    leds[idx] = c;
}

static void resetGame() {
    clearBoard();
    setPlayerStart(p1, 6, 3, DIR_RIGHT, CRGB::Red, 1);
    p2.alive = false;
    FastLED.show();
}

static bool pressed(uint8_t pin) {
    return digitalRead(pin) == LOW;
}

static void readInputs() {
    Dir next;
    if (pressed(P1_UP_PIN)) next = DIR_UP;
    else if (pressed(P1_DOWN_PIN)) next = DIR_DOWN;
    else if (pressed(P1_LEFT_PIN)) next = DIR_LEFT;
    else if (pressed(P1_RIGHT_PIN)) next = DIR_RIGHT;
    else next = p1.dir;
    if (!isOpposite(p1.dir, next)) p1.dir = next;

    bool p2Pressed = true;
    if (pressed(P2_UP_PIN)) next = DIR_UP;
    else if (pressed(P2_DOWN_PIN)) next = DIR_DOWN;
    else if (pressed(P2_LEFT_PIN)) next = DIR_LEFT;
    else if (pressed(P2_RIGHT_PIN)) next = DIR_RIGHT;
    else {
        p2Pressed = false;
        next = p2.dir;
    }

    if (!p2.alive) {
        if (p2Pressed) {
            uint8_t sx = 25;
            uint8_t sy = 4;
            if (occupancy[XY(sx, sy)] == 0) {
                setPlayerStart(p2, sx, sy, next, CRGB::Blue, 2);
                FastLED.show();
            }
        }
        return;
    }

    if (!isOpposite(p2.dir, next)) p2.dir = next;
}

static bool stepPlayer(const Player &p, uint8_t &nx, uint8_t &ny) {
    int16_t tx = p.x;
    int16_t ty = p.y;
    switch (p.dir) {
        case DIR_UP:
            ty -= 1;
            if (ty < 0) ty = MATRIX_HEIGHT - 1;
            break;
        case DIR_DOWN:
            ty += 1;
            if (ty >= MATRIX_HEIGHT) ty = 0;
            break;
        case DIR_LEFT:
            tx -= 1;
            if (tx < 0) tx = MATRIX_WIDTH - 1;
            break;
        case DIR_RIGHT:
            tx += 1;
            if (tx >= MATRIX_WIDTH) tx = 0;
            break;
    }
    nx = static_cast<uint8_t>(tx);
    ny = static_cast<uint8_t>(ty);
    return true;
}

static void gameOverFlash(bool p1Crash, bool p2Crash) {
    CRGB color = CRGB::White;
    if (p1Crash && !p2Crash) color = CRGB::Blue;
    if (p2Crash && !p1Crash) color = CRGB::Red;

    for (int i = 0; i < 3; i++) {
        fill_solid(leds, NUM_LEDS, color);
        FastLED.show();
        delay(200);
        clearBoard();
        delay(200);
    }
    resetGame();
}

static void tick() {
    if (!p1.alive) {
        resetGame();
        return;
    }

    if (!p2.alive) {
        uint8_t n1x, n1y;
        stepPlayer(p1, n1x, n1y);

        bool crash1 = occupancy[XY(n1x, n1y)] != 0;
        if (crash1) {
            p1.alive = false;
            gameOverFlash(true, false);
            return;
        }

        uint16_t i1 = XY(n1x, n1y);
        occupancy[i1] = 1;
        leds[i1] = p1.color;
        p1.x = n1x; p1.y = n1y;
        FastLED.show();
        return;
    }

    uint8_t n1x, n1y, n2x, n2y;
    bool in1 = stepPlayer(p1, n1x, n1y);
    bool in2 = stepPlayer(p2, n2x, n2y);

    bool crash1 = !in1;
    bool crash2 = !in2;

    if (in1 && occupancy[XY(n1x, n1y)] != 0) crash1 = true;
    if (in2 && occupancy[XY(n2x, n2y)] != 0) crash2 = true;

    if (in1 && in2 && n1x == n2x && n1y == n2y) {
        crash1 = true;
        crash2 = true;
    }

    if (crash1 || crash2) {
        p1.alive = !crash1;
        p2.alive = !crash2;
        gameOverFlash(crash1, crash2);
        return;
    }

    uint16_t i1 = XY(n1x, n1y);
    uint16_t i2 = XY(n2x, n2y);

    occupancy[i1] = 1;
    occupancy[i2] = 2;

    leds[i1] = p1.color;
    leds[i2] = p2.color;

    p1.x = n1x; p1.y = n1y;
    p2.x = n2x; p2.y = n2y;

    FastLED.show();
}

void setup() {
    Serial.begin(115200);

    pinMode(P1_UP_PIN, INPUT_PULLUP);
    pinMode(P1_DOWN_PIN, INPUT_PULLUP);
    pinMode(P1_LEFT_PIN, INPUT_PULLUP);
    pinMode(P1_RIGHT_PIN, INPUT_PULLUP);

    pinMode(P2_UP_PIN, INPUT_PULLUP);
    pinMode(P2_DOWN_PIN, INPUT_PULLUP);
    pinMode(P2_LEFT_PIN, INPUT_PULLUP);
    pinMode(P2_RIGHT_PIN, INPUT_PULLUP);

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(5);
    resetGame();
}

void loop() {
    readInputs();
    uint32_t now = millis();
    if (now - lastTick >= TICK_MS) {
        lastTick = now;
        tick();
    }
}
