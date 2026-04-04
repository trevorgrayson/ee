#include <FastLED.h>

#define DATA_PIN 23

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)
#define SNAKE_LEN 5
#define ROUND_SHOW_MS 700

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

struct Trail {
    uint16_t buf[NUM_LEDS];
    uint16_t head;
    uint16_t len;
};

static Player p1;
static Player p2;
static Trail t1;
static Trail t2;
static uint16_t roundNum = 0;

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

static void drawDigit3x5(uint8_t x, uint8_t y, uint8_t digit, const CRGB &c) {
    static const uint16_t font[10] = {
        0b111101101101111, // 0
        0b010110010010111, // 1
        0b111001111100111, // 2
        0b111001111001111, // 3
        0b101101111001001, // 4
        0b111100111001111, // 5
        0b111100111101111, // 6
        0b111001001001001, // 7
        0b111101111101111, // 8
        0b111101111001111  // 9
    };
    if (digit > 9) return;
    uint16_t bits = font[digit];
    for (uint8_t row = 0; row < 5; row++) {
        for (uint8_t col = 0; col < 3; col++) {
            uint8_t bit = 14 - (row * 3 + col);
            if ((bits >> bit) & 0x1) {
                uint8_t px = x + col;
                uint8_t py = y + row;
                if (px < MATRIX_WIDTH && py < MATRIX_HEIGHT) {
                    leds[XY(px, py)] = c;
                }
            }
        }
    }
}

static void showRoundNumber(uint16_t round) {
    char buf[6];
    snprintf(buf, sizeof(buf), "%u", round);
    uint8_t len = strlen(buf);
    uint8_t totalWidth = (len * 3) + (len > 0 ? (len - 1) : 0);
    uint8_t startX = (MATRIX_WIDTH - totalWidth) / 2;
    uint8_t startY = (MATRIX_HEIGHT - 5) / 2;

    for (uint8_t i = 0; i < len; i++) {
        uint8_t digit = static_cast<uint8_t>(buf[i] - '0');
        drawDigit3x5(startX + i * 4, startY, digit, CRGB::White);
    }
    FastLED.show();
    delay(ROUND_SHOW_MS);
}

static void trailReset(Trail &t) {
    t.head = 0;
    t.len = 0;
}

static void trailAddAndTrim(Trail &t, uint16_t idx, uint8_t id) {
    t.buf[t.head] = idx;
    t.head = (t.head + 1) % NUM_LEDS;
    if (t.len < NUM_LEDS) t.len++;
    if (SNAKE_LEN > 0 && t.len > SNAKE_LEN) {
        uint16_t tailIndex = (t.head + NUM_LEDS - t.len) % NUM_LEDS;
        uint16_t tailIdx = t.buf[tailIndex];
        t.len--;
        if (occupancy[tailIdx] == id) {
            occupancy[tailIdx] = 0;
            leds[tailIdx] = CRGB::Black;
        }
    }
}

static void setPlayerStart(Player &p, Trail &t, uint8_t x, uint8_t y, Dir d, const CRGB &c, uint8_t id) {
    p.x = x;
    p.y = y;
    p.dir = d;
    p.color = c;
    p.alive = true;
    uint16_t idx = XY(x, y);
    occupancy[idx] = id;
    leds[idx] = c;
    trailReset(t);
    trailAddAndTrim(t, idx, id);
}

static void resetGame() {
    clearBoard();
    roundNum++;
    showRoundNumber(roundNum);
    clearBoard();
    setPlayerStart(p1, t1, 6, 3, DIR_RIGHT, CRGB::Red, 1);
    trailReset(t2);
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
                setPlayerStart(p2, t2, sx, sy, next, CRGB::Blue, 2);
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
        trailAddAndTrim(t1, i1, 1);
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
    trailAddAndTrim(t1, i1, 1);
    trailAddAndTrim(t2, i2, 2);

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
