# Mapa do código do toytrace

## Onde o programa começa

O programa começa em `src/main.c`. A função `main` recebe os argumentos da linha de comando e chama a camada de CLI para interpretar o comando solicitado.

## Onde o comando trace é interpretado

A interpretação dos argumentos acontece em `src/cli.c`. O comando principal esperado é `trace`, usado no formato:

    ./toytrace trace -- programa [argumentos...]

A CLI separa os argumentos do próprio `toytrace` dos argumentos do programa alvo.

## Onde o processo alvo é criado

O processo alvo deve ser criado no runtime de tracing, em `src/trace_runtime.c`, principalmente na função `launch_tracee`.

Essa função ainda possui o TODO da Semana 2. A ideia é que ela faça o `fork` e, no filho, execute a sequência:

1. `PTRACE_TRACEME`;
2. `raise(SIGSTOP)`;
3. `execvp`.

## Onde o runtime espera e controla o tracee

O controle principal do tracee também fica em `src/trace_runtime.c`.

As funções importantes são:

- `wait_for_initial_stop`;
- `configure_trace_options`;
- `resume_until_next_syscall`;
- `wait_for_syscall_stop`;
- `fill_event_from_regs`.

Essas funções representam o fluxo básico com `ptrace`, `waitpid`, `PTRACE_SYSCALL` e `PTRACE_GETREGS`.

## Onde o runtime chama o callback

O runtime monta eventos do tipo `struct syscall_event` e entrega esses eventos para a camada de aluno por meio de callback.

A função de pareamento fica em `src/student/pairer.c`.

## Arquivos que o grupo deve modificar

Os principais arquivos com TODO são:

- `src/trace_runtime.c`;
- `src/student/pairer.c`;
- `src/student/formatter.c`.

## Primeiro TODO observado

Ao executar:

    ./toytrace trace -- ./tests/targets/hello_write

o primeiro erro observado foi:

    erro: TODO Semana 2: implementar launch_tracee()

## Principal dúvida técnica atual

A principal dúvida inicial é como implementar corretamente a coreografia entre processo pai e filho usando `fork`, `PTRACE_TRACEME`, `SIGSTOP`, `execvp`, `waitpid` e `PTRACE_SYSCALL`, sem causar race condition ou deixar o processo filho travado.
