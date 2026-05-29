* **Institución:** Escuela Politécnica Nacional
* **Facultad:** Ingeniería en Sistemas
* **Materia:** Sistemas Operativos
* **Autor:** Alejandro Villacrés
* **Curso:** GR3SW

## Proyecto Integrador MiniKernel
Este proyecto simula los procesos concurrentes y la planificación que realiza el CPU. Está desarrollado en C y utiliza POSIX.

## Compilación
El proyecto está diseñado para ejecutarse en entornos Unix/Linux. 

Para compilar se debe abrir el terminal en la carpeta raíz del proyecto y ejecutar el siguiente comando:

```bash
gcc src/main.c src/queue.c src/cpu.c src/metrics.c -I./include -lpthread -o minikernel
./minikernel
```
