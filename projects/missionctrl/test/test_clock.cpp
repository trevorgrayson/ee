//
// Created by trevor on 2/19/2024.
// set PATH=%PATH%;D:\msys64\mingw64\bin;D:\msys64\ucrt64\bin;D:\msys64\usr\bin

#include "unity.h"
// #include "file_to_test.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_function_should_doBlahAndBlah(void) {
    // test stuff
}

void test_function_should_doAlsoDoBlah(void) {
    // more test stuff
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
    return runUnityTests();
}

/**
  * For Arduino framework
  */
void setup() {
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}
void loop() {}

/**
  * For ESP-IDF framework
  */
void app_main() {
    runUnityTests();
}