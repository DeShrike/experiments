#ifndef INITEST_H
#define INITEST_H

#ifdef __cplusplus
extern "C" {
#endif

#define PRESS_SHORT 1
#define PRESS_LONG 2
#define PRESS_HOLD 3

#define STATE_IDLE 1
#define STATE_RUNNING 2
#define STATE_SHUTDOWN_REQUESTED 3
#define STATE_SHUTTINGDOWN 4

#define ACTION_START_RUNNING 1
#define ACTION_REVERSE 2
#define ACTION_CANCEL_SHUTDOWN 3
#define ACTION_START_SHUTDOWN 4
#define ACTION_GET 5

#ifdef __cplusplus
}
#endif

#endif /* INITEST_H */
