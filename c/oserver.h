#ifndef CCAN_OSERVER_H
#define CCAN_OSERVER_H

void oserver_serve(int fd);
int oserver_setup(void);

#define OSERVER_PORT 2727
#endif /* CCAN_OSERVER_H */
