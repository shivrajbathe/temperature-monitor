#ifndef APP_H
#define APP_H

/*
 * Application orchestration. app_init() performs the boot sequence
 * (load config, select sensor, init outputs, start the sampling timer).
 * app_run_once() is one iteration of the non time-critical main loop.
 */
void app_init(void);
void app_run_once(void);

#endif /* APP_H */
