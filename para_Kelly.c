#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declaracion de variables enteras
    int turnos, i, j, id_turno, operarios, id_op, producidas, malas, buenas, opcion;
    int tot_prod_t=0, tot_buen_t=0, tot_mal_t=0, tot_prod_dia=0, tot_buen_dia=0, tot_mal_dia=0, tot_ops_dia=0;
    
    // Declaracion de decimales para dinero y estadisticas
    float porc_malas=0.0, ganancia=0.0, multa=0.0, bono=0.0, pago_neto=0.0;
    float gan_t=0.0, mul_t=0.0, bon_t=0.0, net_t=0.0;
    float gan_d=0.0, mul_d=0.0, bon_d=0.0, net_d=0.0;
    float efi_t=0.0, efi_d=0.0, porc_malas_d=0.0, prom_op=0.0, prom_t=0.0;

    // Caracteres para texto
    char inicial_sup, salir;

    // Constantes definidas por el problema
    const float PRECIO = 75.50, PENALTY = 15.25, BONUS = 0.08;
    const int MAX_DEFECTOS = 10;

    printf("=========================================\n SISTEMA METALMECANICO \n=========================================\n\n");
    
    // Pide turnos y controla que no metan letras
    printf("Turnos a trabajar (2 a 5): ");
    while(scanf("%d", &turnos) != 1 || turnos < 2 || turnos > 5) {
        printf("Error, ingresa un numero valido (2-5): ");
        while(getchar() != '\n'); // Limpia si metio letras por accidente
    }

    // Recorre cada turno
    for(i = 1; i <= turnos; i++) {
        // Pone los contadores del turno en cero
        tot_prod_t=0; tot_buen_t=0; tot_mal_t=0; gan_t=0.0; mul_t=0.0; bon_t=0.0; net_t=0.0;

        printf("\n--- TURNO %d ---\nID del turno: ", i);
        // Validar codigo de turno
        while(scanf("%d", &id_turno) != 1 || id_turno <= 0) {
            printf("ID invalido. Ingresa numero: ");
            while(getchar() != '\n');
        }

        printf("Inicial supervisor: ");
        scanf(" %c", &inicial_sup); // El espacio limpia el enter anterior

        // Valida operarios entre 5 y 20
        printf("Cuantos operarios (5 a 20): "); 
        while(scanf("%d", &operarios) != 1 || operarios < 5 || operarios > 20) {
            printf("Rango erroneo. Intenta (5-20): "); 
            while(getchar() != '\n');
        }
        tot_ops_dia += operarios; // Suma al total del dia

        // Recorre los operarios
        for(j = 1; j <= operarios; j++) {
            printf("\n> Operario %d <\nID: ", j); 
            while(scanf("%d", &id_op) != 1 || id_op <= 0) {
                printf("ID malo. De nuevo: "); while(getchar() != '\n');
            }

            printf("Piezas creadas: "); 
            while(scanf("%d", &producidas) != 1 || producidas < 0) {
                printf("No pueden ser negativas: "); while(getchar() != '\n');
            }

            printf("Piezas malas: "); 
            // Valida que las malas no superen a las producidas
            while(scanf("%d", &malas) != 1 || malas < 0 || malas > producidas) {
                printf("Error logico. Reingresa: "); while(getchar() != '\n');
            }
            
            buenas = producidas - malas; // Saca las buenas por resta
            porc_malas = (producidas > 0) ? ((float)malas / producidas) * 100.0 : 0.0; // Evita dividir por cero
            
            // Calculo de plata
            ganancia = buenas * PRECIO; 
            multa = malas * PENALTY;  
            bono = (porc_malas < 2.0) ? ganancia * BONUS : 0.0; // Solo hay bono si es menor a 2%
            pago_neto = ganancia + bono - multa; 
            
            printf(">> Buenas: %d | Malas: %.2f%% | Neto: B/.%.2f\nCategoria: ", buenas, porc_malas, pago_neto);
            // Clasificacion segun produccion
            if(producidas > 120 && porc_malas < 3.0) printf("Excelente\n");
            else if(producidas >= 90 && producidas <= 120 && porc_malas < 6.0) printf("Bueno\n");
            else if(producidas >= 70 && producidas <= 89) printf("Regular\n");
            else printf("Deficiente\n");
            
            // Acumula para el turno y el dia
            tot_prod_t += producidas; tot_buen_t += buenas; tot_mal_t += malas;
            gan_t += ganancia; mul_t += multa; bon_t += bono; net_t += pago_neto;
            
            tot_prod_dia += producidas; tot_buen_dia += buenas; tot_mal_dia += malas;
            gan_d += ganancia; mul_d += multa; bon_d += bono; net_d += pago_neto;
        }
        
        // Menu de fin de turno
        do {
            printf("\n--- MENU DE TURNO ---\n1. Ver Resumen\n2. Ver Eficiencia\n3. Ver Alertas\n4. Continuar\nElije: ");
            while(scanf("%d", &opcion) != 1) { // Anti letras
                printf("Opcion invalida: "); while(getchar() != '\n');
            }
            
            switch(opcion) {
                case 1:
                    printf("\nResumen-> Ops: %d | Total: %d | Buenas: %d | Malas: %d | Plata: B/.%.2f\n", operarios, tot_prod_t, tot_buen_t, tot_mal_t, gan_t); break;
                case 2:
                    efi_t = (tot_prod_t > 0) ? ((float)tot_buen_t / tot_prod_t) * 100.0 : 0.0; // Eficiencia en porcentaje
                    printf("\nEficiencia: %.2f%%\nNivel: ", efi_t);
                    if(efi_t >= 98.0) printf("Excelente\n");
                    else if(efi_t >= 95.0 && efi_t < 98.0) printf("Muy Buena\n");
                    else if(efi_t >= 90.0 && efi_t < 95.0) printf("Aceptable\n");
                    else printf("Critica\n");
                    break;
                case 3:
                    efi_t = (tot_prod_t > 0) ? ((float)tot_buen_t / tot_prod_t) * 100.0 : 0.0;
                    printf("\nAlertas:\n"); // Revisa varios ifs simples
                    if(tot_mal_t > MAX_DEFECTOS) printf("- Muchas malas\n");
                    if(tot_prod_t < 500) printf("- Produccion baja\n");
                    if(efi_t < 90.0) printf("- Baja eficiencia\n");
                    if(mul_t > 250.0) printf("- Multas extremas\n");
                    break;
                case 4: printf("Siguiente...\n"); break;
                default: printf("Opcion no existe.\n");
            }
        } while(opcion != 4);
    } 
    
    // Estadisticas finales globales
    porc_malas_d = (tot_prod_dia > 0) ? ((float)tot_mal_dia / tot_prod_dia) * 100.0 : 0.0; 
    efi_d = (tot_prod_dia > 0) ? ((float)tot_buen_dia / tot_prod_dia) * 100.0 : 0.0; 
    prom_op = (tot_ops_dia > 0) ? (float)tot_prod_dia / tot_ops_dia : 0.0; 
    prom_t = (turnos > 0) ? (float)tot_prod_dia / turnos : 0.0; 
    
    printf("\n*** REPORTE FINAL DEL DIA ***\n");
    printf("1. Turnos: %d\n2. Operarios: %d\n3. Producidas: %d\n4. Buenas: %d\n5. Malas: %d\n6. %% Malas: %.2f%%\n", turnos, tot_ops_dia, tot_prod_dia, tot_buen_dia, tot_mal_dia, porc_malas_d);
    printf("7. Bonos: B/.%.2f\n8. Multas: B/.%.2f\n9. Bruto: B/.%.2f\n10. Neto: B/.%.2f\n11. Prom/Operario: %.2f\n12. Prom/Turno: %.2f\n", bon_d, mul_d, gan_d, net_d, prom_op, prom_t);
    
    printf("\nNota global: "); // Evaluacion de la empresa
    if(efi_d >= 98.0 && porc_malas_d < 2.0) printf("Excelente\n");
    else if(efi_d >= 95.0) printf("Muy Buena\n");
    else if(efi_d >= 90.0) printf("Buena\n");
    else if(efi_d >= 85.0) printf("Regular\n");
    else printf("Deficiente\n");
    
    // Forma visual con asteriscos
    printf("\nGrafico:\n");
    for(i = 1; i <= turnos; i++) {
        for(j = 1; j <= i; j++) printf("*"); // Imprime de 1 hasta turno
        printf("\n");
    }
    for(i = turnos - 1; i >= 1; i--) {
        for(j = 1; j <= i; j++) printf("*"); // Imprime restando
        printf("\n");
    }

    printf("\nEnter para salir");
    while(getchar() != '\n'); // Limpia lo que quede
    getchar(); // Pausa
    return 0;
}
