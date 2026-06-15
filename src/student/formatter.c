#include "student_api.h"

#include "syscall_names.h"

#include <stdio.h>

void student_debug_raw_event(const struct syscall_event *ev,
                             char *buf,
                             size_t bufsz)
{
    if (ev == NULL || buf == NULL || bufsz == 0) {
        return;
    }
    if(ev->entering){
        snprintf(buf, bufsz, "pid=%d %s entrada args=(%#lx, %#lx, %#lx, %#lx, %#lx, %#lx)",
                 ev->pid,
                 syscall_name(ev->syscall_no),
                 ev->args[0],
                 ev->args[1],
                 ev->args[2],
                 ev->args[3],
                 ev->args[4],
                 ev->args[5]);

    } else {
        snprintf(buf, bufsz, "pid=%d %s %s",
                 ev->pid,
                 syscall_name(ev->syscall_no),
                 ev->entering ? "entrada" : "saida");
    }
}

void student_format_event(const struct syscall_event *ev,
                          char *buf,
                          size_t bufsz)
{
    snprintf(buf, bufsz, "%s(%#lx, %#lx, %#lx, %#lx, %#lx, %#lx) = %ld",
             syscall_name(ev->syscall_no),
             ev->args[0],
             ev->args[1],
             ev->args[2],
             ev->args[3],
             ev->args[4],
             ev->args[5],
             ev->ret);
}
