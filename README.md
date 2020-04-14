# Example: task_watchdog

This test code shows how to initialize the task watchdog in main loop.
Based on official example :[task_watchdog](https://github.com/espressif/esp-idf/tree/master/examples/system/task_watchdog)


### Test:

Program should run with TWDT being triggered for 5 times , then start reset TWDT in a loop for 20 seconds, then TWDT will be triggered every 2 seconds again.

